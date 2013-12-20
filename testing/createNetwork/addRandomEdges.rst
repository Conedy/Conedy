
``network.addRandomEdges (m, edge=weightedEdge)``
	Add edges with randomly chosen source and target nodes until the network reaches a certain mean degree. Self connections and parallel (duplicate) edges are avoided.

Parameters
----------

``m``:  float
	Nodes are added until the mean degree of the network reaches ``m``.

``edge``: edge template
	Every added edge is a copy of this template.

