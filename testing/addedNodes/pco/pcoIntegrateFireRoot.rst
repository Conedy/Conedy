

DGL of pcoIntegrateFireRoot
------------------------------------------

::


	delta = 1.0 / logalpha() * log ( exp((logalpha()) * phase  )   - (1 - alpha()) * coupling) - phase ;

	if (delta + phase > 1 )

	delta = 1 - phase;

Parameter of pcoIntegrateFireRoot
-----------------------------------------



- pcoIntegrateFireRoot_alpha 		 =  0.9000000000000000; 
- pcoIntegrateFireRoot_logalpha 		 =  0.9000000000000000; 

