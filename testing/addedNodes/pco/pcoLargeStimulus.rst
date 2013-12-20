

DGL of pcoLargeStimulus
------------------------------------------

::


	delta =  phase <  0.5 ? a() * (1 - exp(phase)) : a() *( -1 + exp(-phase + 1.0));

	if ( delta > 1 - phase)

	delta = 1 - phase;

	if ( delta  + phase <= 0)

	delta = - phase;

Parameter of pcoLargeStimulus
-----------------------------------------



- pcoLargeStimulus_a 		 =  0.0010000000000000; 
- pcoLargeStimulus_b 		 =  0.0000000000000000; 

