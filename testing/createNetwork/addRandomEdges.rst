
network.addRandomEdges (m, edge=weightedEdge) 
	Add edges with randomly chosen source and target nodes until the network reaches a certain mean degree. Self-connetions and parallel edges are excluded.

Parameters
----------

m :  float
	Nodes are added until the mean degree of the network reaches m.


edge : edgeTemplate
	Every added edge is a copy of this template.

