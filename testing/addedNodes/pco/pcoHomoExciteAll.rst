

DGL of pcoHomoExciteAll
------------------------------------------

::


	delta =  a() * exp ( - b() * phase);

	if (delta  + phase > 1.0)

	delta = 1 - phase;

	if ( delta  + phase <= 0)

	delta = - phase;

Parameter of pcoHomoExciteAll
-----------------------------------------



- pcoHomoExciteAll_a 		 =  0.0100000000000000; 
- pcoHomoExciteAll_b 		 =  10.0000000000000000; 
- pcoHomoExciteAll_netSize 		 =  10000.0000000000000000; 

