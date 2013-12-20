

DGL of hodgkinHuxley
------------------------------------------

::


	double alphan = (10.0 - x[0]) / ( 100.0 * ( exp (( 10.0 - x[0] ) / 10.0 ) - 1 ) );

	double alpham = (25.0 - x[0] ) / ( 10.0 * ( exp (( 25 - x[0] )/10.0)-1 ));

	double alphah = 0.07 * exp ( -x[0] / 20.0 );

	double betam = 4.0 * exp (-x[0]/18.0);

	double betah =1.0 / ( exp (( 30.0 - x[0]) / 10.0) + 1);

	double betan = 0.125 * exp ( - x[0] / 80.0);

	dxdt[0] = ( gna() /cm() ) *x[1]*x[1]*x[1]*x[2]* ( ena()-x[0] ) + ( gk() /cm() ) *x[3]*x[3]*x[3]*x[3]* ( ek()-x[0] ) + ( gpas() /cm() ) * ( vpas()-x[0] ) + ( couplingSum() /cm() ) + ( I() /cm() );

	dxdt[1] = alpham  * ( 1-x[1] )-betam *x[1];

	dxdt[2] = alphah  * ( 1-x[2] )-betah *x[2];

	dxdt[3] = alphan  * ( 1-x[3] )-betan *x[3];

Parameter of hodgkinHuxley
-----------------------------------------



- hodgkinHuxley_cm 		 =  1.0000000000000000; 
- hodgkinHuxley_gna 		 =  120.0000000000000000; 
- hodgkinHuxley_gk 		 =  36.0000000000000000; 
- hodgkinHuxley_gpas 		 =  0.3000000000000000; 
- hodgkinHuxley_ena 		 =  110.0000000000000000; 
- hodgkinHuxley_ek 		 =  -12.0000000000000000; 
- hodgkinHuxley_vpas 		 =  10.5999999999999996; 
- hodgkinHuxley_I 		 =  100.0000000000000000; 

