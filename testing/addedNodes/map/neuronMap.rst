

DGL of neuronMap
------------------------------------------

::


	xprime[0] = (1-weightSum())*(x[0]*x[0]*exp(x[1]-x[0]) + k()) + couplingSum();

	xprime[1] = a() * x[1] - b() * x[0] + c();

Parameter of neuronMap
-----------------------------------------



- neuronMap_a 		 =  0.8900000000000000; 
- neuronMap_b 		 =  0.1800000000000000; 
- neuronMap_c 		 =  0.2800000000000000; 
- neuronMap_k 		 =  0.0300000000000000; 

