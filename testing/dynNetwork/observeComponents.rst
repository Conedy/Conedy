``network.observeComponents(node,  fileName)``
  Adds all dynamical variable of ``node`` node to the list of observed features. Whenever net.snapshot or net.evolve is called, observed features of the network will be written to the respective files. The file format is a space delimited matrix in which columns are observed features in the order in which they are added to the network. 

Parameters
----------
node : int
   The number of the node whoose dynamical variables are observed.

fileName : string
  The name of the file to which data is written







