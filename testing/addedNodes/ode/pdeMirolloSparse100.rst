

DGL of pdeMirolloSparse100
------------------------------------------

::


	double overlap ( double targeaatl, double targetr, double i, double j);

	unsigned int N = 100;

	double rightOut = 0;

	double leftOut = 0;

	double int2 = 0;

	double targetl = 0;

	double targetr = 0;

	unsigned int i;

	for (i = 0; i < 99 ; i++) int2 = int2 + x[i];

	double xlast = 1 - int2;

	for (i = 0; i < N ; i++)

	{

	targetl = (1+a())*i/N+b();

	targetr = (1+a())*(i+1)/N+b();

	rightOut = rightOut + x[i] * overlap (targetl, targetr, 1.0, 500.0)/( targetr - targetl);

	leftOut = leftOut + x[i] * overlap (targetl, targetr, -1000.0, 0.0)/( targetr - targetl);

	}

	double rate = m() * N * xlast / ( 1 - m() * rightOut);

	dxdt[0]= -(3*x[0] -4* xlast + x[N-1]) * N + rate * ( rightOut) + rate * leftOut - rate *  x[0];

	dxdt[1]= -(3*x[1] -4* x[0] + xlast) * N  - rate *  x[1];

	for (i = 2 ; i < N ; i++)

	{

	dxdt[i]= - (3*x[i] -4* x[i-1] + x[i-2]) * N - rate * x[i];

	}

	for (i = 0 ; i < N ; i++)

	{

	targetl = (1+a())*i/N+b();

	targetr = (1+a())*(i+1)/N+b();

	unsigned int binl = (unsigned int) (N*targetl+ 0.00001);

	unsigned int binr = (unsigned int) (N*targetr- 0.00001);

	if (binl < 0) binl = 0;

	if (binr > N-1) binr = N-1;

	for (unsigned int j = binl; j < binr + 1; j = j + 1)

	{

	dxdt[j] = dxdt[j] + rate * x[i] * overlap ( targetl, targetr, ((double )j) / N, ((double)j+1)/N) /( targetr - targetl);

	}

	}

Parameter of pdeMirolloSparse100
-----------------------------------------



- pdeMirolloSparse100_m 		 =  0.2000000000000000; 
- pdeMirolloSparse100_a 		 =  0.0100000000000000; 
- pdeMirolloSparse100_b 		 =  0.0500000000000000; 

