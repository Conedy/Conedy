

DGL of gaussianLorenz
------------------------------------------

::


	dxdt[0] = S() *( x[1] - x[0] );

	dxdt[1] = x[0] *( r() - x[2] ) - x[1];

	dxdt[2] = x[0] * x[1] - b() * x[2] +couplingSum() - weightSum()*x[2];

	s[0] = sigmaNoise();

Parameter of gaussianLorenz
-----------------------------------------



- gaussianLorenz_S 		 =  10.0000000000000000; 
- gaussianLorenz_r 		 =  28.0000000000000000; 
- gaussianLorenz_b 		 =  2.6666666000000001; 
- gaussianLorenz_sigmaNoise 		 =  0.0000000000000000; 

