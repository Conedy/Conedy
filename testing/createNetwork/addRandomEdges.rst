
network.addRandomEdges (m, edge=weightedEdge) 
	Adds edges with randomly chosen source and target nodes until the network reaches a certain mean degree.

Parameters
----------

m :  float
	Nodes are added until the mean degree of the network reaches m.


edge : edgeBlueprint
	Every added edge is a copy of this blueprint.

