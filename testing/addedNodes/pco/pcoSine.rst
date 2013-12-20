

DGL of pcoSine
------------------------------------------

::


	delta =  -a() * sin (2 * phase * M_PI + b() * M_PI)  + a() *sin (b() * M_PI) ;

	if ( delta > 1 - phase)

	delta = 1 - phase;

	if ( delta  + phase <= 0)

	delta = - phase;

Parameter of pcoSine
-----------------------------------------



- pcoSine_a 		 =  0.0011000000000000; 
- pcoSine_b 		 =  0.0000000000000000; 

