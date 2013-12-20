``directedNetwork.randomNetwork(size, probability, node=dynNode, edge=weightedEdge)``
``undirectedNetwork.randomNetwork(size, probability, node=dynNode, edge=weightedEdge)``
	Adds a random network.

Parameters
----------
``size``: int
	Number of nodes to be added.
``probability``: double (:math:`\in\left[ 0, 1 \right]`)
	Probability for a connection between two nodes.
``node``: node template
	Every added node is a copy of this template.
``edge``: edge template
	Every added edge is a copy of this template.
