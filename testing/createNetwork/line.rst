``network.line(size, a, nodeTemplate=dynNode, edgeTemplate=weightedEdge)``
	Adds an open chain to the network.

Parameters
----------
``size`` : int
	Number of nodes in the chain

``a`` : int
	Number of nearest neighbours to each side, a node is connected to (unless at the boundary).

``nodeTemplate`` : nodeTemplate
	Every added node is a copy of this template.

``edgeTemplate`` : edgeTemplate
	Every added edge is a copy of this template.

Returns
-------
The number of the first added node. The following nodes have consecutive numbers.

