``network.saveAdjacencyList(fileName)``
	Save the adjacency list of the network to a file.


Parameters
----------

``fileName``: string
	File name to which the adjacency list is written.

File Format
-----------

The text file will start with the number of nodes in the network.
Afterwards for every connection, there is a line which contains the following three entries:

* number of the source node,
* number of the target node,
* coupling strength.

Entries are seperated by spaces.

Example::

   2
   1 0 0.3
   0 1 0.9

:ref:`createFromAdjacencyList` reads files in this format.
