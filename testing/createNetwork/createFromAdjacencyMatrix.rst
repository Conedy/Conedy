
``network.createFromAdjacencyMatrix(fileName, node = dynNode, edge= weightedEdge)``
	Creates a network of identical nodes and edges according to an adjacency matrix which is read from a file.


Parameters
----------
``fileName``: string
	File name of the text file which contains the adjacency matrix.

``node``: node template
	Every added node is a copy of this template.

``edge``: edge template
	Every added edge is a copy of this template.


Returns
-------
the number of the first added node. The following nodes have consecutive numbers.


File format
-----------
The text file should contain the entries of the adjacency matrix separated by whitespace and newlines::

   0     0.1   0    0.1
   0.1   0     0.1  0
   0     0.1   0    0.1
   0.1   0     0.1  0.0

:ref:`saveAdjacencyMatrix` saves files in this very format.
