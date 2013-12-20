

DGL of pdeDenseLimitSmall
------------------------------------------

::


	double phase;

	double phaseminus;

	double xlast = 1 -x[0] - x[1] - x[2] - x[3] - x[4] - x[5] - x[6] - x[7] - x[8] - x[9] - x[10] - x[11] - x[12] - x[14];

	double rate =xlast * 15 / ( 1 - ( a() + b()) * xlast * 15);

	double xminus1 = xlast * ( 1 + (a() * 0.0   + b()) * rate) / (  1 + b() * rate);

	phase =  ((double)0) / 15;

	phaseminus =  ((double)14) / 15;

	dxdt[0]=- ( ( 1 + ( a() * phase + b() ) * rate ) * x [ 0]  -( 1 + ( a() * phaseminus + b() ) * rate ) * xminus1) *15;

	phase =  ((double)1) / 15;

	phaseminus =  ((double)0) / 15;

	dxdt[1]= -( ( 1 + ( a() * phase + b() ) * rate ) * x [ 1]  -( 1 + ( a() * phaseminus + b() ) * rate ) * x [ 0]) *15;

	phase =  ((double)2) / 15;

	phaseminus =  ((double)1) / 15;

	dxdt[2]= -( ( 1 + ( a() * phase + b() ) * rate ) * x [ 2]  -( 1 + ( a() * phaseminus + b() ) * rate ) * x [ 1]) *15;

	phase =  ((double)3) / 15;

	phaseminus =  ((double)2) / 15;

	dxdt[3]= -( ( 1 + ( a() * phase + b() ) * rate ) * x [ 3]  -( 1 + ( a() * phaseminus + b() ) * rate ) * x [ 2]) *15;

	phase =  ((double)4) / 15;

	phaseminus =  ((double)3) / 15;

	dxdt[4]= -( ( 1 + ( a() * phase + b() ) * rate ) * x [ 4]  -( 1 + ( a() * phaseminus + b() ) * rate ) * x [ 3]) *15;

	phase =  ((double)5) / 15;

	phaseminus =  ((double)4) / 15;

	dxdt[5]= -( ( 1 + ( a() * phase + b() ) * rate ) * x [ 5]  -( 1 + ( a() * phaseminus + b() ) * rate ) * x [ 4]) *15;

	phase =  ((double)6) / 15;

	phaseminus =  ((double)5) / 15;

	dxdt[6]= -( ( 1 + ( a() * phase + b() ) * rate ) * x [ 6]  -( 1 + ( a() * phaseminus + b() ) * rate ) * x [ 5]) *15;

	phase =  ((double)7) / 15;

	phaseminus =  ((double)6) / 15;

	dxdt[7]= -( ( 1 + ( a() * phase + b() ) * rate ) * x [ 7]  -( 1 + ( a() * phaseminus + b() ) * rate ) * x [ 6]) *15;

	phase =  ((double)8) / 15;

	phaseminus =  ((double)7) / 15;

	dxdt[8]= -( ( 1 + ( a() * phase + b() ) * rate ) * x [ 8]  -( 1 + ( a() * phaseminus + b() ) * rate ) * x [ 7]) *15;

	phase =  ((double)9) / 15;

	phaseminus =  ((double)8) / 15;

	dxdt[9]= -( ( 1 + ( a() * phase + b() ) * rate ) * x [ 9]  -( 1 + ( a() * phaseminus + b() ) * rate ) * x [ 8]) *15;

	phase =  ((double)10) / 15;

	phaseminus =  ((double)9) / 15;

	dxdt[10]= -( ( 1 + ( a() * phase + b() ) * rate ) * x [ 10]  -( 1 + ( a() * phaseminus + b() ) * rate ) * x [ 9]) *15;

	phase =  ((double)11) / 15;

	phaseminus =  ((double)10) / 15;

	dxdt[11]= -( ( 1 + ( a() * phase + b() ) * rate ) * x [ 11]  -( 1 + ( a() * phaseminus + b() ) * rate ) * x [ 10]) *15;

	phase =  ((double)12) / 15;

	phaseminus =  ((double)11) / 15;

	dxdt[12]= -( ( 1 + ( a() * phase + b() ) * rate ) * x [ 12]  -( 1 + ( a() * phaseminus + b() ) * rate ) * x [ 11]) *15;

	phase =  ((double)13) / 15;

	phaseminus =  ((double)12) / 15;

	dxdt[13]= -( ( 1 + ( a() * phase + b() ) * rate ) * x [ 13]  -( 1 + ( a() * phaseminus + b() ) * rate ) * x [ 12]) *15;

	phase =  ((double)14) / 15;

	phaseminus =  ((double)13) / 15;

	dxdt[14]= -( ( 1 + ( a() * phase + b() ) * rate ) * x [ 14]  -( 1 + ( a() * phaseminus + b() ) * rate ) * x [ 13]) *15;

Parameter of pdeDenseLimitSmall
-----------------------------------------



- pdeDenseLimitSmall_a 		 =  0.0100000000000000; 
- pdeDenseLimitSmall_b 		 =  0.0200000000000000; 

