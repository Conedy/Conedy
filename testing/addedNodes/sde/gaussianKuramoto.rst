

DGL of gaussianKuramoto
------------------------------------------

::


	dxdt[0] = omega();

	s[0] = sigmaNoise();

	forEachEdge(

	dxdt[0] = dxdt[0] + weight * sin ( 2 * M_PI * (state - x[0]));

	)

Parameter of gaussianKuramoto
-----------------------------------------



- gaussianKuramoto_omega 		 =  1.0000000000000000; 
- gaussianKuramoto_sigmaNoise 		 =  0.0000000000000000; 

