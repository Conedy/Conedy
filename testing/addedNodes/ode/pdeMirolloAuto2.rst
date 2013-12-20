

DGL of pdeMirolloAuto2
------------------------------------------

::


	double overlap ( double targetl, double targetr, double i, double j);

	unsigned int N = 100;

	double int1 = 0;

	double int2 = 0;

	double targetl = 0;

	double targetr = 0;

	unsigned int i;

	for (i = 0; i < 100 ; i++) int2 = int2 + x[i];

	double xlast = x[N-1];

	for (i = 0; i < N ; i++)

	{

	targetl = (1+a())*i/N+b();

	targetr = (1+a())*(i+1)/N+b();

	int1 = int1 + x[i] * overlap (targetl, targetr, 1.0, 1000.0)/( targetr - targetl);

	}

	double rate = m() * N * xlast / ( 1 - m() * int1);

	dxdt[0]= -(3*x[0] -4* x[N-1] + x[N-2]) * N + rate * ( int1) - rate *  x[0];

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

	for (unsigned int j = binl; j < binr; j = j + 1)

	{

	dxdt[j] = dxdt[j] + rate * x[i] * overlap ( targetl, targetr, ((double )j) / N, ((double)j+1)/N) /( targetr - targetl);

	}

	}

	}

	double overlap (double tl, double tr, double i, double j)

	{

	if (tr <= i)

	return 0.0;

	else if (tl >= j)

	return 0.0;

	else if (tr <= j && tl >= i)

	return tr - tl;

	else if (i >= tl && j <= tr)

	return j - i;

	else if (tr <= j)

	return tr - i;

	else

	return j - tl;

Parameter of pdeMirolloAuto2
-----------------------------------------



- pdeMirolloAuto2_m 		 =  0.2000000000000000; 
- pdeMirolloAuto2_a 		 =  0.0100000000000000; 
- pdeMirolloAuto2_b 		 =  0.0500000000000000; 

