

DGL of pcoThreePoint
------------------------------------------

::


	if ( phase > a())

	{

	delta = (phase - a()) * h2() / ( 1 - a());

	}

	else if (phase > 0)

	{

	delta = h1() - h1() / a() * phase;

	}

	else

	{

	delta = 0;

	}

	if (delta > 1 - phase)

	delta = 1 - phase;

Parameter of pcoThreePoint
-----------------------------------------



- pcoThreePoint_a 		 =  0.5000000000000000; 
- pcoThreePoint_h1 		 =  0.0100000000000000; 
- pcoThreePoint_h2 		 =  0.0100000000000000; 

