

network.complete(size, node=dynNode, edge=weightedEdge)
        Adds a number of nodes such that every two nodes are connected.

Parameters
----------
size : int
        Number of nodes to be added.
node : nodeTemplate
        Every added node is a copy of this template.
edge : edgeTemplate
        Every added edge is a copy of this template.

                
Returns
-------
the number of the first added node. The following nodes have consecutive numbers.
