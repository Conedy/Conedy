

DGL of pcoMirolloExciteAll
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

Parameter of pcoMirolloExciteAll
-----------------------------------------



- pcoMirolloExciteAll_a 		 =  0.0010000000000000; 
- pcoMirolloExciteAll_b 		 =  0.0000000000000000; 
- pcoMirolloExciteAll_netSize 		 =  10000.0000000000000000; 

