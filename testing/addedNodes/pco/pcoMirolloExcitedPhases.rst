

DGL of pcoMirolloExcitedPhases
------------------------------------------

::


	if ( ( phase > t_ref() - timeDelay() ) && ( phase < 1 - timeDelay() ) )

	{

	delta =  b() +  a() * ( phase - t_ref() + timeDelay() ) / ( 1 - t_ref() ) ;

	if (delta + phase > 1 - timeDelay() )

	delta = 1 - timeDelay() - phase;

	}

	else

	delta = 0;

	if (print() > 0.5)

	cout << setprecision(20) << getNumber() << " " << dynNode::time << " " << phase << " " << phase + delta <<  endl;

Parameter of pcoMirolloExcitedPhases
-----------------------------------------



- pcoMirolloExcitedPhases_a 		 =  0.0010000000000000; 
- pcoMirolloExcitedPhases_b 		 =  0.0000000000000000; 
- pcoMirolloExcitedPhases_print 		 =  0.0000000000000000; 
- pcoMirolloExcitedPhases_t_ref 		 =  0.0500000000000000; 
- pcoMirolloExcitedPhases_timeDelay 		 =  0.0100000000000000; 

