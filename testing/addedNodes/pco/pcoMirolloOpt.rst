

DGL of pcoMirolloOpt
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

Parameter of pcoMirolloOpt
-----------------------------------------



- pcoMirolloOpt_a 		 =  0.0100000000000000; 
- pcoMirolloOpt_b 		 =  0.0200000000000000; 

