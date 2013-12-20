

DGL of pcoMirolloMonte
------------------------------------------

::


	if (phase > 0)

	{

	delta = (b() + a() * phase);

	if (delta + phase > 1 )

	delta = 1 - phase;

	else if (delta + phase < 0)

	{

	delta = -phase;

	}

	}

	else delta = 0;

Parameter of pcoMirolloMonte
-----------------------------------------



- pcoMirolloMonte_a 		 =  0.0100000000000000; 
- pcoMirolloMonte_b 		 =  0.0200000000000000; 
- pcoMirolloMonte_SIZE 		 =  100000.0000000000000000; 
- pcoMirolloMonte_m 		 =  15.0000000000000000; 

