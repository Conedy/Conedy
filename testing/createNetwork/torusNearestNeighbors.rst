network.torusNearestNeighbors(sizex, sizey, neighbors, node= dynNode, edge = weightedEdge)
   Adds a torus to the network, in which each node is connected to a fixed number of nearest neighbors


Parameters
----------
sizex : int
   Size of the torus in x-direction

sizey : int
   Size of the torus in y-direction

neighbors : float
   The number of neighbors each node is connected to. If the choice cannot be made unique, neighbors are chosen randomly.

node : nodeBlueprint
        Every added node is a copy of this blueprint.
edge : edgeBlueprint
        Every added edge is a copy of this blueprint.

