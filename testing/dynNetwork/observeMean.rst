network.observeMean(fileName, edgeType = edge)
      Adds the mean of node state to the list of observed features. Whenever net.snapshot or net.evolve is called, observed features of the network will be written to the respective files. The file format is a space delimited matrix in which columns are observed features in the order in which they are added to the network. 

      
fileName : string
  The name of the file to which data is written

edgeType : edgeTemplate
   Nodes are observed via an edge, which is a copy of this template.
