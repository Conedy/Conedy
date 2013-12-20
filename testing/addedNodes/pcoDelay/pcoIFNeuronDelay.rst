

DGL of pcoIFNeuronDelay
------------------------------------------

::


	if ( phase > t_ref())

	{

	delta =  coupling * ( t_ref() - 1 ) * ( 1 - alpha() ) / exp ( log(alpha()) * ( phase - t_ref()   ) / ( 1 - t_ref() ) ) / log(alpha());

	}

Parameter of pcoIFNeuronDelay
-----------------------------------------



- pcoIFNeuronDelay_t_ref 		 =  0.0500000000000000; 
- pcoIFNeuronDelay_alpha 		 =  0.9000000000000000; 

