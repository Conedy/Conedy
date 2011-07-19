
network.saveAdjacencyList(fileName)
   Save the adjacency list of the network to a file.


Parameters
----------

fileName : string
   File name to which the adjacency list is written.

File Format
-----------

The first line contains the number of nodes in the network. Subsequent lines contain the number of source node, number of target node and connection strength, separated by whitespace::

   2
   1 0 0.3
   0 1 0.9

