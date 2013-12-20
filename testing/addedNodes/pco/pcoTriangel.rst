

DGL of pcoTriangel
------------------------------------------

::


	if (phase < a())

	delta = 0;

	else if (phase < b())

	delta = (phase-a())/(b()-a()) * h();

	else if (phase < c())

	delta = (c() -phase)/(c()-b()) * h();

	else delta = 0;

Parameter of pcoTriangel
-----------------------------------------



- pcoTriangel_a 		 =  0.5000000000000000; 
- pcoTriangel_b 		 =  0.8000000000000000; 
- pcoTriangel_c 		 =  0.9000000000000000; 
- pcoTriangel_h 		 =  0.0100000000000000; 

