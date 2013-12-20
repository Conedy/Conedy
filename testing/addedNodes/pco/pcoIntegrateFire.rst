

DGL of pcoIntegrateFire
------------------------------------------

::


	if ( ( phase > t_ref() - timeDelay() ) && ( phase < 1 - timeDelay() ) )

	{

	delta = 1.0 / log(alpha()) * log ( pow(alpha(), (phase - t_ref() + timeDelay() ) / (1 - t_ref() ) )   - (1 - alpha()) * coupling) - (phase -t_ref() + timeDelay()) / (1 - t_ref());

	if (delta + phase > 1 - timeDelay() )

	delta = 1 - timeDelay() - phase;

	if (delta + phase < 0 - timeDelay())

	delta = -(phase + timeDelay());

	}

	else

	delta = 0;

Parameter of pcoIntegrateFire
-----------------------------------------



- pcoIntegrateFire_t_ref 		 =  0.0500000000000000; 
- pcoIntegrateFire_alpha 		 =  0.9000000000000000; 
- pcoIntegrateFire_timeDelay 		 =  0.0100000000000000; 

