

network.cycle(size, b, node=dynNode, edge=weightedEdge)
        Adds a closed chain to the network in which every node is connected to b neighbors on each side.

Parameters
----------
size : int
        Number of nodes in the chain

b : int
        Number of nearest neighbours to each side every node in the chain is connected to.

node : nodeBlueprint
        Every added node is a copy of this blueprint.

edge : edgeBlueprint
        Every added edge is a copy of this blueprint.

        
Returns
-------
the number of the first added node. The following nodes have consecutive numbers.
