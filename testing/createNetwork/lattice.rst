

network.lattice(sizex, sizey, a, node=dynNode, edge=weightedEdge)
   Adds a 2 dimensional lattice to the network.

Parameters
----------

        sizex : int
                Size of the lattice in x-direction.

        sizey : int
                Size of the lattice in y-direction.

        a : float
                Every node is connected to all neighbors whoose euclidian distance is smaller than a.

        node : nodeBlueprint
                Every added node is a copy of this blueprint.

        edge : edgeBlueprint
                Every added edge is a copy of this blueprint.
        
        
Returns
-------
the number of the first added node. The following nodes have consecutive numbers.
