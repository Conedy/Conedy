

#include "pulseCoupledPhaseOscillator.h"
#include "gslNoise.h"

namespace conedy
{

    void pcoBase::setStateVec ( vector <double  >  &r ) 
	{
		baseType value = r[0];

		eventHandler::registerCallBack ( _fire_,  dynNode::time + ( 1 - value ) );
//		updateKey(_fire_, dynNode::time + ( 1 - value ));

	}


    void pcoBase::printStatistics(ostream &os, double nodeVerbosity, double edgeVerbosity ) {
        node::printStatistics(os, nodeVerbosity, edgeVerbosity);
        if (nodeVerbosity > 1.5)
        {
           params<baseType>::printStatistics();
           if (dimension() > 0)
           {      
            cout << "state:" ;
                 cout << getState();
           }
    
        }
         os << endl;
    }

	void pcoBase::clean ()
	{

		eventHandler::registerCallBack ( _fire_,   nextFiring() + timeOffset );				

	}

	baseType pcoBase::getState() { return 1 - nextFiring() + time ; }

	baseType pcoBase::callBack ( unsigned int eventSignature )
	{

		if ( eventSignature == _fire_ )
		{

#ifdef DEBUG			
			cout << "Firing:" << getNumber() << endl;
#endif
			this->fire();
//			return this->time + 1.0;// + gslNoise::getGaussian ( 0, numeric_limits<baseType>::epsilon() * 1000.0 );

			return nextEvent() + 1;
				
		}

		else // if (eventSignature == _exciteRandomly_)
		{
			this->excite ( noiseIntensity() );
			return this->time + gslNoise::getExponential ( noiseFrequency() );
		}

	}


	pcoBase::~pcoBase()
	{
		for (unsigned int i =0; i < numberOfEvents(); i++)
			eventHandler::unregisterCallBack(i);
	}


	pcoBase::pcoBase ( const pcoBase &b ) : dynNode ( b ), eventHandler ( b )
	{
		eventHandler::registerCallBack ( _fire_,  1.0 );
		if ( noiseFrequency() != 0.0 )
			eventHandler::registerCallBack ( _exciteRandomly_,dynNode::time + gslNoise::getExponential ( noiseFrequency() ) );
		else
			eventHandler::registerCallBack ( _exciteRandomly_,dynNode::time + numeric_limits<baseType>::max() );
	}

	

//	pcoDelay::pcoDelay ( const pcoDelay &b ) : eventHandler ( b ),  dynNode ( b )
//	{
//		eventHandler::registerOneCallBack ( _distributeRandomely_,  numeric_limits<baseType>::max() );	;
//	}


	//	pcoDelay  () : pcoBase () {};






	baseType escapeNoiseNeuron::callBack ( unsigned int eventSignature )
	{

		if ( eventSignature == _fire_ )
		{
			this->fire();
			return this->time + t_ref() + gslNoise::getExponential ( exp ( -   escapeNoise_a() * pot + escapeNoise_b() ) );
		}

		else // if (eventSignature == _exciteRandomly_)
		{
			this->excite ( pcoBase::noiseIntensity() );
			return this->time + gslNoise::getExponential ( pcoBase::noiseFrequency() );

		}

	}





	void escapeNoiseNeuron::excite ( baseType c )
	{
		//				baseType phase = 1.0 + pcoBase::exactTime - this->x[0];
		if ( ( pcoBase::nextFiring() - this->time >= timeDelay() ) && ( this->time - lastFiring >t_ref() -timeDelay() ) ) // nicht mehr refraktär und noch nicht feuernd
		{
			pot = pot + c;


			baseType newKey = this->time + timeDelay() +gslNoise::getExponential ( exp ( - escapeNoise_a() * pot+ escapeNoise_b() ) );
			//					pcoBase::decreaseKey();
			eventHandler::updateKey ( _fire_, newKey );


		}
	}










	baseType pcoDelay::callBack ( unsigned int eventSignature )
	{
		if ( eventSignature == _fire_ )
		{
			sendExcitations();
			return this->time + 1.0; // + gslNoise::getGaussian ( 0, numeric_limits<baseType>::epsilon() * 1000.0 );
		}
		else if ( eventSignature == _exciteRandomly_ )
		{
			this->excite ( noiseIntensity() );
			return this->time + gslNoise::getExponential ( noiseFrequency() );
		}
		else // if (eventSignature == _distributeExcitations_ )
		{
			fire();
			return 0;
		}


	}

	void pcoDelay::sendExcitations ()
	{
		registerOneTimeCallBack ( _distributeExcitations_, dynNode::time + timeDelay() );
//		eventHandler::increaseKey ( _fire_, time + numeric_limits<baseType>::epsilon() * 1000.0 );
	}

	/*
		void pcoDelay::excite ( baseType c )
		{

			baseType phase = 1.0 + this->time - eventHandler::getKey(_fire_);
			if (phase > t_ref())
			{
				baseType newKey = this->x[0]    -  c;


				phase = phase   +  c * (t_ref() - 1) * (1 - alpha() ) / exp( logAlpha() *  (phase - t_ref() + timeDelay()) / (1 - t_ref())) / logAlpha();


				if (phase > 1)
				{
					phase = 1;
					fire();
				}
				else
					eventHandler::decreaseKey(_fire_,newKey);



			}
		}

	*/

/*
	void pcoNonleaky::clean ()
	{

		if ( !eventHandler::alreadyRegistered() )
			eventHandler::registerCallBack ( _fire_,  dynNode::time + 1.0 );

		if ( noiseFrequency() != 0.0 )
		{
			if ( ( nextRandomExcitation() == numeric_limits<baseType>::max() ) || ( !eventHandler::alreadyRegistered() ) )

				eventHandler::registerCallBack ( _exciteRandomly_,dynNode::time + gslNoise::getExponential ( noiseFrequency() ) );
		}
		else
			eventHandler::registerCallBack ( _exciteRandomly_,dynNode::time + numeric_limits<baseType>::max() );

	}
*/


	baseType pcoBase::timeOffset = 0;

}
