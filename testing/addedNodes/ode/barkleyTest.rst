

DGL of barkleyTest
------------------------------------------

::


	dxdt[0] = 1 / k() *  x[0] * (1 - x[0]) * ( x[0] - ( x[1] + b() ) / a() )   + couplingSum() - weightSum() * x[0];

	dxdt[1] = x[0] - x[1];

Parameter of barkleyTest
-----------------------------------------



- barkleyTest_a 		 =  0.7500000000000000; 
- barkleyTest_b 		 =  0.0100000000000000; 
- barkleyTest_k 		 =  0.0500000000000000; 

