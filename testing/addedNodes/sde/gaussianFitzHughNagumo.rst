

DGL of gaussianFitzHughNagumo
------------------------------------------

::


	dxdt[0] = x[0]* ( a()-x[0] ) * ( x[0]-1.0 )-x[1]+I() + couplingSum();

	dxdt[1] = b() *x[0]-c() *x[1];

	s[0] = sigmaNoise();

Parameter of gaussianFitzHughNagumo
-----------------------------------------



- gaussianFitzHughNagumo_a 		 =  0.1000000000000000; 
- gaussianFitzHughNagumo_b 		 =  0.0100000000000000; 
- gaussianFitzHughNagumo_c 		 =  0.0200000000000000; 
- gaussianFitzHughNagumo_I 		 =  0.0000000000000000; 
- gaussianFitzHughNagumo_sigmaNoise 		 =  0.0000000000000000; 

