

DGL of gaussianBarkleyTest
------------------------------------------

::


	dxdt [0] = 1/ k() * x [0]*(1 - x [0])*( x [0] -( x [1]+ b() )/ a() );

	dxdt [1] = x [0] - x [1];

	s [0] = sigma() ;

	s [1] = 0.0;

	dsdx [0] = 0.0;

	dsdx [1] = 0.0;

Parameter of gaussianBarkleyTest
-----------------------------------------



- gaussianBarkleyTest_a 		 =  0.7500000000000000; 
- gaussianBarkleyTest_b 		 =  0.0100000000000000; 
- gaussianBarkleyTest_k 		 =  0.0500000000000000; 
- gaussianBarkleyTest_sigma 		 =  0.1800000000000000; 

