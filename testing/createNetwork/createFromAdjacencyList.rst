
network.createFromAdjacencyList(fileName, node = dynNode, edge= weightedEdge)
   Creates a network of identical nodes and edges according to an adjacency list which is read from a file.


Parameters
----------
fileName : string
   File name of the text file which contains the adjacency list.

node : nodeBlueprint
        Every added node is a copy of this blueprint.

edge : edgeBlueprint
        Every added edge is a copy of this blueprint.


Returns
-------
the number of the first added node. The following nodes have consecutive numbers.


File format
-----------
The text file should start with the number of nodes in the network. Afterwards for every connection a line is expected which contains the following three entries: 

-- number of the source node,
-- number of the target node,
-- coupling strength.

Entries should be seperated by whitespace or tab::

   2
   1 0 0.3
   0 1 0.9


