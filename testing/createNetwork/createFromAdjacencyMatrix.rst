
network.createFromAdjacencyMatrix(fileName, node = dynNode, edge= weightedEdge)
   Creates a network of identical nodes and edges according to an adjacency matrix which is read from a file.


Parameters
----------
fileName : string
   File name of the text file which contains the adjacency matrix.

node : nodeBlueprint
        Every added node is a copy of this blueprint.

edge : edgeBlueprint
        Every added edge is a copy of this blueprint.


Returns
-------
the number of the first added node. The following nodes have consecutive numbers.


File format
-----------
The text file should contain the adjacency matrix separated by newline and whitespace::

   0     0.1   0    0.1
   0.1   0     0.1  0    
   0     0.1   0    0.1
   0.1   0     0.1  0.0

