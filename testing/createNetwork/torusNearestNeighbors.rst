``network.torusNearestNeighbors(sizex, sizey, neighbours, node= dynNode, edge = weightedEdge)``
	Adds a 2-dimensional, cyclic lattice (torus) to the network, in which each node is connected to a fixed number of nearest neighbours.

Parameters
----------
``sizex``: integer
   Size of the torus in x-direction

``sizey``: integer
   Size of the torus in y-direction

``neighbours`` : integer
	The number of neighbours each node is connected to.
	If the choice cannot be made unique, neighbours are chosen randomly.

``node``: node template
	Every added node is a copy of this template.

``edge``: edge template
	Every added edge is a copy of this template.

