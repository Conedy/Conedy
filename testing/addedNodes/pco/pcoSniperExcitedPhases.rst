

DGL of pcoSniperExcitedPhases
------------------------------------------

::


	delta = a() * coupling * ( 1 - cos (2 * M_PI * phase));

	if ( delta > 1 - phase)

	delta = 1 - phase;

	if ( delta  + phase <= 0)

	delta = - phase;

	if (print() > 0.5)

	cout << setprecision(20) << getNumber() << " " << dynNode::time << " " << phase << " " << phase + delta <<  endl;

Parameter of pcoSniperExcitedPhases
-----------------------------------------



- pcoSniperExcitedPhases_a 		 =  0.0010000000000000; 
- pcoSniperExcitedPhases_b 		 =  0.0000000000000000; 
- pcoSniperExcitedPhases_print 		 =  0.0000000000000000; 

