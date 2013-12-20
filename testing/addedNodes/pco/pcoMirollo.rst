

DGL of pcoMirollo
------------------------------------------

::


	if (phase > 0)

	{

	delta = (b() + a() * phase);

	if (delta + phase > 1 )

	delta = 1 - phase;

	else if ( delta + phase < 0)

	delta = - phase;

	}

	else delta = 0;

Parameter of pcoMirollo
-----------------------------------------



- pcoMirollo_a 		 =  0.0100000000000000; 
- pcoMirollo_b 		 =  0.0200000000000000; 

