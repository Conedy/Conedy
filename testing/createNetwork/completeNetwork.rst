

``network.complete(size, node=dynNode, edge=weightedEdge)``
	Adds a number of nodes such that there is an edge between every two nodes. In other words: every possible edge exists.

Parameters
----------
``size``: integer
	Number of nodes to be added.
``node``: node template
	Every added node is a copy of this template.
``edge``: edge template
	Every added edge is a copy of this template.


Returns
-------
the number of the first added node. The following nodes have consecutive numbers.
