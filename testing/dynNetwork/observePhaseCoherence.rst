network.observe(fileName, edgeType = edge) 
  Adds the complex sum of the phases of all nodes to the list of observed features. Whenever net.snapshot or net.evolve is called, observed features of the network will be written to the respective files. The file format is a space delimited matrix in which columns are observed features in the order in which they are added to the network. 

Parameters
----------
fileName : string
  The name of the file to which data is written

edgeType : edgeTemplate
   Nodes are observed via an edge, which is a copy of this template.



.. math::
   r =  \frac {1}{|N|}  \sum\limits_{i \in N} e^{-2 \pi \phi_n}
