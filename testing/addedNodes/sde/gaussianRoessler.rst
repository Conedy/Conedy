

DGL of gaussianRoessler
------------------------------------------

::


	dxdt[0]=	-omega() * x[1] - x[2]+ couplingSum() - weightSum()*x[0];

	dxdt[1]= x[0] + a() * x[1];

	dxdt[2]= b() + x[2] *( x[0] - c() );

	s[0]= sigmaNoise();

Parameter of gaussianRoessler
-----------------------------------------



- gaussianRoessler_omega 		 =  0.8900000000000000; 
- gaussianRoessler_a 		 =  0.1650000000000000; 
- gaussianRoessler_b 		 =  0.2000000000000000; 
- gaussianRoessler_c 		 =  10.0000000000000000; 
- gaussianRoessler_sigmaNoise 		 =  0.0000000000000000; 

