

DGL of pdeMirolloPopulation_500
------------------------------------------

::


	double overlap ( double targetl, double targetr, double i, double j);

	unsigned int N = 500;

	double int2 = 0;

	double targetl = 0;

	double targetr = 0;

	unsigned int binl, binr;

	unsigned int i;

	for (i = 0; i < 500 * 500 ; i++) int2 = int2 + x[i];

	//		double xlast = 1 - int2;

	double rate [N];

	double ptcMirollo_500 (double phi, double avalue, double bvalue, double tau, double theta);

	double inverseR (double phi);

	double etaMinus1 [N];

	unsigned int eta, phi;

	unsigned int leftBoundaryBin = (unsigned int) ((t_ref() -timeDelay())*N);

	unsigned int rightBoundaryBin = (unsigned int) ((1 - timeDelay())*N);

	// determine the rate

	//		rate [0] = m() * x[N-1 + N*0] ;

	for (eta = 0; eta < N; eta++)

	{

	if (eta >= leftBoundaryBin && eta < rightBoundaryBin)

	rate[eta] = N* N* m() * x[N-1 + N*eta ] / int2;

	else

	rate[eta] = 0.0;

	}

	// boundary condition x[eta, 0] = x[eta,1]

	etaMinus1[0] = 0.0;

	for (eta = 1; eta < N; eta++)

	{

	etaMinus1[eta] = 0.0;

	dxdt[eta + N * 0] = - (x[eta + N*0] - x[eta + N* (N-1)]) * N  -(x[eta +N*0] - x[eta - 1 + N*0]) * N   - (rate[eta] + rate[0]) * x[eta + N *0] ;

	}

	// boundary condition x[0, phi] = x[1, phi]

	for (phi = 0; phi < N; phi++)

	etaMinus1[phi] = x[N-1 + N*phi];

	dxdt[0 + N * 0] = - (x[0 + N*0] - x[0 + N* (N-1)]) * N  -(x[0 +N*0] - etaMinus1[0]) * N   - (rate[0] + rate[0]) * x[0+ N *0];

	for (phi = 1; phi < N; phi++)

	dxdt[0 + N * phi] = - (x[0 + N*phi] - etaMinus1[phi]) * N   - (x[0 + N*phi] - x [0 + N* (phi-1)]) * N    - (rate[phi] + rate[0]) * x[0 + N *phi];

	// convection + weggerauschte

	for (eta = 1; eta < N; eta++)

	for (phi = 1; phi < N; phi ++)

	{

	dxdt[eta + N*phi] = - (x[eta + N*phi] - x[eta - 1 + N*phi] ) * N - ( x[eta + N*phi] - x[eta + N*(phi-1)] ) * N    - (rate[eta]+ rate[phi])  * x[eta + N*phi]    ;

	}

	// excitedField

	for (phi = 0; phi < N; phi ++)

	{

	for (eta = 0; eta < N; eta ++)

	{

	// source oscillator gets excited

	targetl = ptcMirollo_500 (((double)eta)/N, a(), b(), timeDelay(), t_ref());

	targetr = ptcMirollo_500 (((double)(eta+1))/N,a(), b(), timeDelay(), t_ref() );

	binl = (unsigned int) (N*targetl+ 0.000001);

	binr = (unsigned int) (N*targetr- 0.000001);

	if (binl < leftBoundaryBin)  binl = leftBoundaryBin;

	if (binr > rightBoundaryBin- 1) binr = rightBoundaryBin - 1;

	for (unsigned int j = binl ; j < binr + 2; j = j + 1)

	{

	dxdt[ j + N*phi]+= rate[eta] * x[eta+ N*phi] * overlap ( targetl, targetr, ((double )j) / N, ((double)j+1)/N) /( targetr - targetl);

	}

	dxdt[ rightBoundaryBin + N* phi] += rate[eta] * x[eta+N*phi] * overlap (targetl, targetr,  ((double)rightBoundaryBin + 1) / N  , 1000.0)/ ( targetr - targetl);

	dxdt[ leftBoundaryBin + N* phi] +=  rate[eta] * x[eta+N*phi] * overlap (targetl, targetr, -1000.0, ((double)leftBoundaryBin) / N )/ ( targetr - targetl);

	//dxdt[ leftBoundaryBin + N* phi] +=  rate[eta] * x[eta+N*phi] * overlap (targetl, targetr, -1000.0, ((double)leftBoundaryBin) / N )/ ( targetr - targetl);

	//for (unsigned int j = leftBoundaryBin  ; j < rightBoundaryBin + 1; j = j + 1)

	//{

	//	dxdt[ j + N*phi]+= rate[eta] * x[eta+ N*phi] * overlap ( targetl, targetr, ((double )j) / N, ((double)j+1)/N) /( targetr - targetl);

	//}

	//dxdt[ rightBoundaryBin + N* phi] += rate[eta] * x[eta+N*phi] * overlap (targetl, targetr,  ((double)rightBoundaryBin + 1) / N  , 1000.0)/ ( targetr - targetl);

	// target oscillator gets excited

	targetl = ptcMirollo_500 (  ((double) phi)/N, a(), b(), timeDelay(), t_ref());

	targetr = ptcMirollo_500 (  ((double)(phi+1))/N, a(),b(),timeDelay(), t_ref());

	binl = (unsigned int) (N*targetl+ 0.000001);

	binr = (unsigned int) (N*targetr- 0.000001);

	if (binl < leftBoundaryBin)  binl = leftBoundaryBin;

	if (binr > rightBoundaryBin - 1) binr = rightBoundaryBin - 1;

	for (unsigned int j = binl; j < binr + 2; j = j + 1)

	{

	dxdt[ eta + N*j] +=  rate[phi] *x[eta+ N*phi] * overlap ( targetl, targetr, ((double )j) / N, ((double)j+1)/N) /( targetr - targetl);

	}

	dxdt[eta +   rightBoundaryBin *N] += rate[phi] *x[eta+N*phi] * overlap (targetl, targetr, ((double)rightBoundaryBin + 1) / N, 1000.0)/ ( targetr - targetl);

	dxdt[eta +   leftBoundaryBin * N] += rate[phi] *x[eta+N*phi] * overlap (targetl, targetr, -1000.0, ((double)leftBoundaryBin)  / N )/ ( targetr - targetl);

	}

	}

	}

	double ptcMirollo_500 (double phase, double avalue , double bvalue, double tau , double theta)

	{

	return phase + bvalue +  avalue * ( phase - theta + tau ) / ( 1 - theta ) ;

Parameter of pdeMirolloPopulation_500
-----------------------------------------



- pdeMirolloPopulation_500_m 		 =  10.0000000000000000; 
- pdeMirolloPopulation_500_a 		 =  0.0200000000000000; 
- pdeMirolloPopulation_500_b 		 =  0.0200000000000000; 
- pdeMirolloPopulation_500_timeDelay 		 =  0.0100000000000000; 
- pdeMirolloPopulation_500_t_ref 		 =  0.0500000000000000; 

