

DGL of hindmarshRose
------------------------------------------

::


	dxdt[0] = 3.0*x[0]*x[0]-x[0]*x[0]*x[0] + x[1] - x[2] + I() + couplingSum();

	dxdt[1] = 1.0-5*x[0]*x[0]-x[1];

	dxdt[2] = r() * ( 4* ( x[0]+1.6 )-x[2] );

Parameter of hindmarshRose
-----------------------------------------



- hindmarshRose_r 		 =  0.0010000000000000; 
- hindmarshRose_I 		 =  0.0000000000000000; 

