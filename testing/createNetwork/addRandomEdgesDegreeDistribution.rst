
``directedNetwork.addRandomEdgesDegreeDistribution (random, edgeTemplate=weightedEdge)``
``undirectedNetwork.addRandomEdgesDegreeDistribution (random, edgeTemplate=weightedEdge)``
	Add edges of type ``edgeTemplate`` with randomly chosen source and target nodes such that each node gets a number of new connections which is drawn from the distribution ``random``. Self connections and parallel (duplicate) edges are avoided.

Parameters
----------

``random``:  float
	Nodes are added until the mean degree of the network reaches ``m``.

``edge``: edge template
	Every added edge is a copy of this template.

