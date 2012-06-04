``network.cycle(size, b, node=dynNode, edge=weightedEdge)``
	Adds a closed chain to the network in which every node is connected to ``b`` neighbours on each side.

Parameters
----------
``size``: integer
	Number of nodes in the chain

``b``: integer
	Each node is connected to its ``b`` nearest neighbours on each side.

``node``: node template
	Every added node is a copy of this template.

``edge``: edge template
	Every added edge is a copy of this template.


Returns
-------
The number of the first added node.
The following nodes have consecutive numbers.
