network.line(size, a, node=dynNode, edge=weightedEdge)
        Adds an open chain to the network a.

Parameters
----------
size : int
        Number of nodes in the chain

a : int
        Number of nearest neighbours to each side, nodes not at boandaries in the chain are connected to.

node : nodeBlueprint
        Every added node is a copy of this blueprint.

        edge : edgeBlueprint
        Every added edge is a copy of this blueprint.

Returns
-------
the number of the first added node. The following nodes have consecutive numbers.
                  
