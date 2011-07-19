network.observe(nodeNumber, fileName, edgeType = edge)
  Adds the state of the node nodeNumber to the list of observed features. Whenever net.snapshot or net.evolve is called, observed features of the network will be written to the respective files. The file format is a space delimited matrix in which columns are observed features in the order in which they are added to the network. 

Parameters
----------
nodeNumber : int
  The number of the node that is to be observed
fileName : string
  The name of the file to which data is written

edgeType : edgeBlueprint
   Nodes are observed via an edge, which is a copy of this blueprint.
