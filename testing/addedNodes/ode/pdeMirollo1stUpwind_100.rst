

DGL of pdeMirollo1stUpwind_100
------------------------------------------

::


	double overlap ( double targetl, double targetr, double i, double j);

	unsigned int N = 100;

	double leftOut = 0;

	double rightOut = 0;

	double int2 = 0;

	double targetl = 0;

	double targetr = 0;

	unsigned int i;

	for (i = 0; i < 100 - 1 ; i++) int2 = int2 + x[i];

	for (i = 0; i < N ; i++)

	{

	targetl = (1+a())*i/N+b();

	targetr = (1+a())*(i+1)/N+b();

	rightOut = rightOut + x[i] * overlap (targetl, targetr, 1.0, 1000.0)/( targetr - targetl);

	leftOut = leftOut + x[i] * overlap (targetl, targetr, -1000.0, 0.0)/( targetr - targetl);

	}

	double rate = m() * N * x[N-1]/ int2 / ( 1 - m() * rightOut/int2   );

	dxdt[0]= -(x[0] - x[N-1]) * N + rate * ( rightOut) + rate * leftOut - rate *  x[0];

	for (i = 1 ; i < N ; i++)

	{

	dxdt[i]= - (x[i] - x[i-1] ) * N - rate * x[i];

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

Parameter of pdeMirollo1stUpwind_100
-----------------------------------------



- pdeMirollo1stUpwind_100_m 		 =  0.2000000000000000; 
- pdeMirollo1stUpwind_100_a 		 =  0.0100000000000000; 
- pdeMirollo1stUpwind_100_b 		 =  0.0500000000000000; 

