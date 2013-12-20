

DGL of pdeMirolloRoot_10000
------------------------------------------

::


	double overlap ( double targetl, double targetr, double i, double j);

	unsigned int N = 10000;

	double leftOut = 0;

	double rightOut = 0;

	double int2 = 0;

	double targetl = 0;

	double targetr = 0;

	double phase = 0;

	double delta = 0;

	unsigned int i;

	unsigned int leftBoundaryBin = (unsigned int) ((t_ref() ) * N);

	// determine rate

	for (i = 0; i < 10000 ; i++) int2 = int2 + x[i];

	for (i = leftBoundaryBin; i < N ; i++)

	{

	phase = ((double)i) / N ;

	delta =  b() +  a() * ( phase - t_ref() ) / ( 1 - t_ref() ) ;

	targetl = phase + delta;

	phase = ((double)(i+1)) / N ;

	delta =  b() +  a() * ( phase - t_ref()  ) / ( 1 - t_ref() ) ;

	targetr = phase + delta;

	rightOut = rightOut + x[i] * overlap (targetl, targetr, 1.0, 1000.0)/( targetr - targetl);

	leftOut = leftOut + x[i] * overlap (targetl, targetr, -1000.0, ((double)leftBoundaryBin)/N   )/( targetr - targetl);

	}

	double rate =  m() * N * x [ ((unsigned int) timeDelay() * N  ) ]  / int2;

	// boundary condition

	// convection and wegrauschen

	dxdt[0] = - ( x[0] - x[N-1]) * N ;

	for (i = 1 ; i < leftBoundaryBin; i++)

	dxdt[i]= - (x[i] - x[i-1] ) * N;

	for (i = leftBoundaryBin; i < N ; i++)

	dxdt[i]= - (x[i] - x[i-1] ) * N - rate * x[i];

	dxdt[0] += rate *  rightOut;

	dxdt[leftBoundaryBin] += rate * leftOut;

	for (i = leftBoundaryBin ; i < N ; i++)

	{

	phase = ((double)i) / N ;

	delta =  b() +  a() * ( phase - t_ref() ) / ( 1 - t_ref() ) ;

	targetl = phase + delta;

	phase = ((double)(i+1)) / N ;

	delta =  b() +  a() * ( phase - t_ref()  ) / ( 1 - t_ref() ) ;

	targetr = phase + delta;

	unsigned int binl = (unsigned int) (N*targetl+ 0.00001);

	unsigned int binr = (unsigned int) (N*targetr- 0.00001);

	if (binl < leftBoundaryBin) binl = leftBoundaryBin;

	if (binr > N-1) binr = N-1;

	for (unsigned int j = binl; j < binr + 2; j = j + 1)

	{

	dxdt[j] = dxdt[j] + rate * x[i] * overlap ( targetl, targetr, ((double )j) / N, ((double)j+1)/N) /( targetr - targetl);

	}

	}

Parameter of pdeMirolloRoot_10000
-----------------------------------------



- pdeMirolloRoot_10000_m 		 =  0.2000000000000000; 
- pdeMirolloRoot_10000_a 		 =  0.0100000000000000; 
- pdeMirolloRoot_10000_b 		 =  0.0500000000000000; 
- pdeMirolloRoot_10000_t_ref 		 =  0.0500000000000000; 
- pdeMirolloRoot_10000_timeDelay 		 =  0.0100000000000000; 

