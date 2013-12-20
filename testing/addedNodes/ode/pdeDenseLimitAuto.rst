

DGL of pdeDenseLimitAuto
------------------------------------------

::


	double phase;

	double phaseminus;

	double xlast = 1;

	for (unsigned int i = 0; i < 100 - 1; i++) xlast -= x[i];

	double rate =xlast * 100 / ( 1 - ( a() + b()) * xlast * 100);

	double xminus1 = xlast * ( 1 + (a() * 0.0   + b()) * rate) / (  1 + b() * rate);

	phase =  ((double)0) / 100;

	phaseminus =  ((double) (100-1)) / 100;

	dxdt[0]=- ( ( 1 + ( a() * phase + b() ) * rate ) * x [ 0]  -( 1 + ( a() * phaseminus + b() ) * rate ) * xminus1) *100;

	for (unsigned int i = 1; i < 100 ; i++)

	{

	phase = ((double)i) / 100;

	phaseminus = ((double)i-1)/100;

	dxdt[i]= -( ( 1 + ( a() * phase + b() ) * rate ) * x [ i]  -( 1 + ( a() * phaseminus + b() ) * rate ) * x [ i - 1]) *100;

	}

Parameter of pdeDenseLimitAuto
-----------------------------------------



- pdeDenseLimitAuto_a 		 =  0.0100000000000000; 
- pdeDenseLimitAuto_b 		 =  0.0200000000000000; 

