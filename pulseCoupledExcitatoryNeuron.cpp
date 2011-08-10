

#include "pulseCoupledExcitatoryNeuron.h"



namespace conedy 
{

			void pulseCoupledExcitatoryNeuron::setInitialCondition ( vector<double> &r )
			{
				baseType value = r[0];
				if ( value < 0 )   // refrakt�r
				{
					refractory = true;
					registerCallBack(_fire_, numeric_limits<baseType>::max());
					lastFiring = dynNode::time;
				}
				else if (value >= 1.0)   // feurend
				{
					refractory = false;
					registerCallBack(_fire_, dynNode::time + timeDelay());
									}
				else if (value == 0.0) // membranpotential null 
				{
					refractory = false;
					lastFiring = - numeric_limits<baseType>::max();
					registerCallBack(_fire_, numeric_limits<baseType>::max());

				}
				else   // membranpotential zwischen 0 und 1
				{
					refractory = false;
					lastFiring = dynNode::time + 1 / leakage() * log ( value );
					registerCallBack(_fire_, numeric_limits<baseType>::max());
				}

			}



 void pulseCoupledExcitatoryNeuron::clean ()
			{
				if (!eventHandler::alreadyRegistered())
				{
					eventHandler::registerCallBack (_fire_, numeric_limits<baseType>::max());
					refractory = false;
					lastFiring = -numeric_limits<baseType>::max();
				}


				if ( noiseFrequency() != 0.0 )
				{
					if ((nextRandomExcitation() == numeric_limits<baseType>::max() )|| (!eventHandler::alreadyRegistered()) )

						eventHandler::registerCallBack(_exciteRandomly_,dynNode::time + gslNoise::getExponential( noiseFrequency() ));
				}
				else
					eventHandler::registerCallBack(_exciteRandomly_,dynNode::time + numeric_limits<baseType>::max());
			}

			void pulseCoupledExcitatoryNeuron::excite ( baseType c )           // gibt zurück, ob das Neuron sofort feuert.
			{
//				numberOfExcitations++;
				if ( nextFiring() != numeric_limits<baseType>::max() )
					return;
				if (!refractory)
				{

					baseType phase = dynNode::time - lastFiring;
					baseType pot = exp ( -  leakage() * phase );
					if ( pot + c > 1 )
						eventHandler::decreaseKey(_fire_, dynNode::time + timeDelay());

					else
						lastFiring = dynNode::time + 1.0/ leakage() * log (pot  + c );
				}
				if ( refractory && dynNode::time - lastFiring > t_ref())
				{
					refractory = false;
					lastFiring = dynNode::time +  1.0 / leakage() * log ( c );
				}
			}
			 baseType pulseCoupledExcitatoryNeuron::callBack(unsigned int eventSignature)
			{
				
				if ( eventSignature == _fire_)
				{
					fireN();
					return numeric_limits<baseType>::max();
					
				}

				else // if (eventSignature == _exciteRandomly_)
				{
					excite ( noiseIntensity() );
					return this->time + gslNoise::getExponential(noiseFrequency());
				}
		
			}


			baseType pulseCoupledExcitatoryNeuron::getState() 
			{ 	
				if (nextFiring() == numeric_limits<baseType>::max())
				{
					if (refractory)
					{
					       if (dynNode::time - lastFiring < t_ref())
						       return params<baseType>::getParams(0);
					       else
						       return 0;
					}
					else
						return ( exp ( leakage() * ( -dynNode::time + lastFiring )) );	


				}
				else	
					return 1.0;
//				baseType res = numberOfExcitations;
//				numberOfExcitations = 0;
//				return res;
			}

			void pulseCoupledExcitatoryNeuron::fireN ()
			{
				fire();
				lastFiring = dynNode::time;
				refractory = true;
			}

	unsigned int pulseCoupledExcitatoryNeuron::numberOfExcitations;

}
