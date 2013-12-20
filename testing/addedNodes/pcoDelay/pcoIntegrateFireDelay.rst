

DGL of pcoIntegrateFireDelay
------------------------------------------

::


	if ( phase > t_ref())

	{

	delta = 1.0 / log(alpha()) * log ( pow(alpha(), (phase - t_ref()) /(1-t_ref()) )  - (1 - alpha()) * coupling) -  (  phase - t_ref())/(1 - t_ref());

	}

	else

	delta = 0;

Parameter of pcoIntegrateFireDelay
-----------------------------------------



- pcoIntegrateFireDelay_t_ref 		 =  0.0500000000000000; 
- pcoIntegrateFireDelay_alpha 		 =  0.9000000000000000; 

