``network.lattice(sizex, sizey, a, node=dynNode, edge=weightedEdge)``
	Adds a 2-dimensional (open) lattice to the network.

Parameters
----------
``sizex``: integer
	Size of the lattice in x-direction.

``sizey``: integer
	Size of the lattice in y-direction.

``a`` : float
	Every node is connected to all neighbors whose euclidian distance is smaller than ``a``.

``node``: node template
	Every added node is a copy of this template.

``edge`` edge template
	Every added edge is a copy of this template.


Returns
-------
the number of the first added node.
The following nodes have consecutive numbers.
