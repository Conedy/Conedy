

DGL of pcoIFNeuron
------------------------------------------

::


	delta =  coupling * ( t_ref() - 1 ) * ( 1 - alpha() ) / exp ( logalpha() * ( phase - t_ref() + timeDelay() ) / ( 1 - t_ref() ) ) / logalpha();

	if ( delta +  phase > 1 - timeDelay() )

	delta = 1 - timeDelay() - phase;

Parameter of pcoIFNeuron
-----------------------------------------



- pcoIFNeuron_timeDelay 		 =  0.0100000000000000; 
- pcoIFNeuron_t_ref 		 =  0.0500000000000000; 
- pcoIFNeuron_alpha 		 =  0.9000000000000000; 
- pcoIFNeuron_logalpha 		 =  -0.1053605156578263; 

