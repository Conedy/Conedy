

DGL of pcoMirolloDelayStatic
------------------------------------------

::


	if  ( phase > t_ref() )

	delta =  b() +  a() * ( phase - t_ref() ) / ( 1 - t_ref() ) ;

	else

	delta = 0;

Parameter of pcoMirolloDelayStatic
-----------------------------------------



- pcoMirolloDelayStatic_a 		 =  0.0100000000000000; 
- pcoMirolloDelayStatic_b 		 =  0.0200000000000000; 
- pcoMirolloDelayStatic_t_ref 		 =  0.0500000000000000; 

