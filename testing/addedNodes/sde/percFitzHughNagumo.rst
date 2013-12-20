

DGL of percFitzHughNagumo
------------------------------------------

::


	dxdt[0] = 1 / k() *  x[0] * (1 - x[0]) * ( x[0] - ( x[1] + b() ) / a() )   + couplingSum() - weightSum() * x[0];

	dxdt[1] = x[0] - x[1];

	s[0] = sigma();

Parameter of percFitzHughNagumo
-----------------------------------------



- percFitzHughNagumo_a 		 =  0.7500000000000000; 
- percFitzHughNagumo_b 		 =  0.0100000000000000; 
- percFitzHughNagumo_k 		 =  0.0500000000000000; 
- percFitzHughNagumo_sigma 		 =  0.1500000000000000; 

