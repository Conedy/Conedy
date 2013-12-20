

DGL of pdeDenseLimitRootAuto
------------------------------------------

::


	double phase;

	double phaseminus;

	double xlast = 1;

	for (unsigned int i = 0; i < 10000 - 1; i++) xlast -= x[i];

	double rate =xlast * 10000;

	double xminus1 = xlast;

	phase =  ((double)0) / 10000;

	phaseminus =  ((double) (10000-1)) / 10000;

	int beginningZerobins = (theta() - tau()) * 10000;

	int endingZerobins = ( 1 -  tau()) * 10000;

	dxdt[0]=-  (x [ 0]  -  xminus1) *10000;

	for (unsigned int i = 1; i < 10000 ; i++)

	{

	if (i < beginningZerobins || i > endingZerobins)

	{

	phase = ((double)i) / 10000;

	phaseminus = ((double)i-1)/10000;

	dxdt[i]= -( x [ i] - x [ i - 1] ) *10000;

	}

	else if (i > beginningZerobins && i < endingZerobins)

	{

	phase = ((double)i) / 10000;

	phaseminus = ((double)i-1)/10000;

	dxdt[i]= -( ( 1 + ( a() * phase + b() ) * rate ) * x [ i]  -( 1 + ( a() * phaseminus + b() ) * rate ) * x [ i - 1]) *10000;

	}

	else if ( i == beginningZerobins)

	{

	phase = ((double)i) / 10000;

	phaseminus = ((double)i-1)/10000;

	dxdt[i]= -( ( 1 + ( a() * phase + b() ) * rate ) * x [ i]  - x [ i - 1]) *10000;

	}

	else if (i == endingZerobins)

	{

	phase = ((double)i) / 10000;

	phaseminus = ((double)i-1)/10000;

	dxdt[i]= -(x [ i] -  ( 1 + ( a() * phaseminus + b() ) * rate ) * x [ i-1]) *10000;

	}

	}

Parameter of pdeDenseLimitRootAuto
-----------------------------------------



- pdeDenseLimitRootAuto_a 		 =  0.0100000000000000; 
- pdeDenseLimitRootAuto_b 		 =  0.0200000000000000; 
- pdeDenseLimitRootAuto_tau 		 =  0.0400000000000000; 
- pdeDenseLimitRootAuto_theta 		 =  0.0800000000000000; 

