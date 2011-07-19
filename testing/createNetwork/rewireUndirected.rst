network.rewireUndirected(prop, node)
   Replaces bidirectional connections in the network by connections between randomly chosen source and target nodes. Only use for networks which are undirected.

Parameters
----------

prop : double
   Replacement propability.

node : nodeBlueprint
   Only consider edges for replacement if both source and target node is of this type. If no nodeBlueprint is specified, all edges are considered.




