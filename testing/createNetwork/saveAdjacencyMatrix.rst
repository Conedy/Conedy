
``network.saveAdjacencyMatrix(fileName)``
	Writes the adjacency matrix of the network to a file.


Parameters
----------

``fileName``: string
	Name of the file to which the adjacency matrix is written


File format
-----------
The text file will contain the entries of the adjacency matrix separated by whitespace and newlines::

   0     0.1   0    0.1
   0.1   0     0.1  0
   0     0.1   0    0.1

:ref:`createFromAdjacencyMatrix` reads files in this format.
