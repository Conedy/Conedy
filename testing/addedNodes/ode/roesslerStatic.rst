

DGL of roesslerStatic
------------------------------------------

::


	dxdt[0]=	-omega() * x[1] - x[2]+ couplingSum() - weightSum()*x[0];

	dxdt[1]= x[0] + a() * x[1];

	dxdt[2]= b() + x[2] *( x[0] - c() );

Parameter of roesslerStatic
-----------------------------------------



- roesslerStatic_omega 		 =  0.8900000000000000; 
- roesslerStatic_a 		 =  0.1650000000000000; 
- roesslerStatic_b 		 =  0.2000000000000000; 
- roesslerStatic_c 		 =  10.0000000000000000; 

