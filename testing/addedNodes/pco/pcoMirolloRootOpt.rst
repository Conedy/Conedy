

DGL of pcoMirolloRootOpt
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

Parameter of pcoMirolloRootOpt
-----------------------------------------



- pcoMirolloRootOpt_a 		 =  0.0100000000000000; 
- pcoMirolloRootOpt_b 		 =  0.0200000000000000; 
- pcoMirolloRootOpt_t_ref 		 =  0.0500000000000000; 
- pcoMirolloRootOpt_timeDelay 		 =  0.0100000000000000; 

