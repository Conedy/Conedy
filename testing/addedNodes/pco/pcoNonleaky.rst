

DGL of pcoNonleaky
------------------------------------------

::


	if ( ( phase > t_ref() - timeDelay() ) && ( phase < 1 - timeDelay() ) )

	{

	delta = coupling;

	if (delta + phase > 1 - timeDelay() )

	delta = 1 - timeDelay() - phase;

	}

	else

	delta = 0;

Parameter of pcoNonleaky
-----------------------------------------



- pcoNonleaky_t_ref 		 =  0.2000000000000000; 
- pcoNonleaky_timeDelay 		 =  0.1000000000000000; 

