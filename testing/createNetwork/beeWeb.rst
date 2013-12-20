
``beeWeb(sizex, sizey, node=dynNode, edge=weightedEdge)``
   Generates a bee web of size ``sizex`` * ``sizey`` in which each oscillator is connected to its nearest 6 neighbors.

Parameters
----------
``sizex``: The dimension of the bee web in x-direction.
	Number of nodes to be added.
``sizey``: The dimension of the bee web in y-direction, which has an angle of 60°  to the x-direction.

``node``: node template
	Every added node is a copy of this template.
``edge``: edge template
	Every added edge is a copy of this template.



Returns
-------
The number of the first added node.
The following nodes have consecutive numbers.

