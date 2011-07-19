



#include "phaseResponseOscillators.h"

namespace conedy
{

/*	void pcoIFNeuron::clean ( unsigned int timesteps )
	{
		privateLogarithm = log ( alpha() );
	}*/
/*	void pcoIFNeuronDelay::clean ( unsigned int timesteps )
	{
		privateLogarithm = log ( alpha() );
	}

	void pcoRealIFNeuronDelay::clean ( unsigned int timesteps )
	{
		privateLogarithm = log ( alpha() );
	}



*/





	void pcoTrapez::excite ( baseType coupling )
	{	
		baseType phase = 1.0 + this->time - eventHandler::getKey ( _fire_ );
		if (phase < a() ) {
			return;			
		}
		else if ( phase < b()) {
				phase += (phase-a())/(b()-a()) * h1();
		}
		else if (phase < c()) {
				phase += 1.0 / (c() - b()) * ((phase - b()) * h2() + (c() - phase) *h1()); 
		}
		else if (phase < d()) {
			phase += (d() -phase)/(d()-c()) * h2(); 
		}
		else
			return;


			if ( coupling > 0 )
			{
				if ( phase > 1  )
					phase = 1;
				eventHandler::decreaseKey ( _fire_,1.0  + this->time - phase );
			}
			else
			{
				if ( phase < 0 )
					phase = 0;
				eventHandler::increaseKey ( _fire_,1.0  + this->time - phase );
			}
		

	}







/*


	void pcoNonleaky::excite ( baseType c )
	{
		baseType phase = 1.0 + this->time - eventHandler::getKey ( _fire_ );
		if ( ( phase > t_ref() - timeDelay() ) && ( phase < 1 - timeDelay() ) )
		{


			phase = phase + c;

			if ( c > 0 )
			{
				if ( phase > 1 - timeDelay() )
					phase = 1 - timeDelay();
				eventHandler::decreaseKey ( _fire_,1.0  + this->time - phase );
			}
			else
			{
				if ( phase < 0 )
					phase = 0;
				eventHandler::increaseKey ( _fire_,1.0  + this->time - phase );
			}


		}

	}

*/

/*	void pcoRealIFNeuronDelay::excite ( baseType c )           // gibt zurück, ob das Neuron sofort feuert.
	{
		baseType phase = 1.0 + this->time - eventHandler::getKey ( _fire_ );
		if ( phase > t_ref())  
		{
			phase = 1.0 / logAlpha() * log ( pow(alpha(), phase) - (1 - alpha())/(1 - t_ref()) * c);
			if ( c > 0 )
			{
				if ( phase > 1 )
					phase = 1;
				eventHandler::decreaseKey ( _fire_,1.0  + this->time - phase );
			}
			else
			{
				if ( phase < 0 )
					phase = 0;
				eventHandler::increaseKey ( _fire_,1.0  + this->time - phase );
			}
		}
	}



	void pcoIFNeuronDelay::excite ( baseType c )           // gibt zurück, ob das Neuron sofort feuert.
	{
		baseType phase = 1.0 + this->time - eventHandler::getKey ( _fire_ );
		if ( phase > t_ref())  
		{
			phase = phase	 +  c * ( t_ref() - 1 ) * ( 1 - alpha() ) / exp ( logAlpha() * ( phase - t_ref()) / ( 1 - t_ref() ) ) / logAlpha();
			if ( c > 0 )
			{
				if ( phase > 1 )
					phase = 1;
				eventHandler::decreaseKey ( _fire_,1.0  + this->time - phase );
			}
			else
			{
				if ( phase < 0 )
					phase = 0;
				eventHandler::increaseKey ( _fire_,1.0  + this->time - phase );
			}
		}
	}
*/
/*	void pcoMirollo::excite ( baseType c )           // gibt zurück, ob das Neuron sofort feuert.
	{

		baseType phase = 1.0 + this->time - eventHandler::getKey ( _fire_ );

		if ( ( phase > t_ref() - timeDelay() ) && ( phase < 1 - timeDelay() ) )
		{
			phase = phase	 +  a() +  b() * ( phase - t_ref() + timeDelay() ) / ( 1 - t_ref() ) ;


			if ( c > 0 )
			{
				if ( phase > 1 - timeDelay() )
					phase = 1 - timeDelay();
				eventHandler::decreaseKey ( _fire_,1.0  + this->time - phase );
			}
			else
			{
				if ( phase < 0 )
					phase = 0;
				eventHandler::increaseKey ( _fire_,1.0  + this->time - phase );
			}
		}
	}
*/
	/*
	void pcoIFNeuron::excite ( baseType c )           // gibt zurück, ob das Neuron sofort feuert.
	{

		baseType phase = 1.0 + this->time - eventHandler::getKey ( _fire_ );

		if ( ( phase > t_ref() - timeDelay() ) && ( phase < 1 - timeDelay() ) )
		{
			phase = phase	 +  c * ( t_ref() - 1 ) * ( 1 - alpha() ) / exp ( logAlpha() * ( phase - t_ref() + timeDelay() ) / ( 1 - t_ref() ) ) / logAlpha();
			if ( c > 0 )
			{
				if ( phase > 1 - timeDelay() )
					phase = 1 - timeDelay();
				eventHandler::decreaseKey ( _fire_,1.0  + this->time - phase );
			}
			else
			{
				if ( phase < 0 )
					phase = 0;
				eventHandler::increaseKey ( _fire_,1.0  + this->time - phase );
			}
		}
	}
*/
}
