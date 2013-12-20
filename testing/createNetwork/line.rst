``network.line(size, a, node template=dynNode, edge template=weightedEdge)``
	Adds an open chain to the network.

Parameters
----------
``size`` : integer
	Number of nodes in the chain

``a`` : integer
	Each node is connected to its ``a`` nearest neighbours (unless at the boundary).

``node template`` : node template
	Every added node is a copy of this template.

``edge template`` : edge template
	Every added edge is a copy of this template.

Returns
-------
The number of the first added node.
The following nodes have consecutive numbers.
