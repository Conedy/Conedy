

DGL of pcoMirolloPrintExcitedPhases
------------------------------------------

::


	if (print() > 0.5)

	cout << phase << endl;

	x[1] = x[1] + 1;

	if ( ( phase > t_ref() - timeDelay() ) && ( phase < 1 - timeDelay() ) )

	{

	delta =  b() +  a() * ( phase - t_ref() + timeDelay() ) / ( 1 - t_ref() ) ;

	if (delta + phase > 1 - timeDelay() )

	delta = 1 - timeDelay() - phase;

	}

	else

	delta = 0;

Parameter of pcoMirolloPrintExcitedPhases
-----------------------------------------



- pcoMirolloPrintExcitedPhases_a 		 =  0.0100000000000000; 
- pcoMirolloPrintExcitedPhases_b 		 =  0.0200000000000000; 
- pcoMirolloPrintExcitedPhases_t_ref 		 =  0.0500000000000000; 
- pcoMirolloPrintExcitedPhases_timeDelay 		 =  0.0100000000000000; 
- pcoMirolloPrintExcitedPhases_print 		 =  0.0000000000000000; 

