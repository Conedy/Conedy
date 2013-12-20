

DGL of pcoSniperPrintExcitedPhases
------------------------------------------

::


	if (print() > 0.5)

	cout << phase << endl;

	x[1] = x[1] + 1;

	delta = a() * coupling * ( 1 - cos (2 * M_PI * phase));

	if ( delta > 1 - phase)

	delta = 1 - phase;

	if ( delta  + phase <= 0)

	delta = - phase;

Parameter of pcoSniperPrintExcitedPhases
-----------------------------------------



- pcoSniperPrintExcitedPhases_a 		 =  0.0100000000000000; 
- pcoSniperPrintExcitedPhases_print 		 =  0.0000000000000000; 

