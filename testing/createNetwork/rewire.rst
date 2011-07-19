network.rewire(prop, node)
   Replaces connections in the network by connections between randomly chosen source and target nodes.

Parameters
----------

prop : double
   Replacement propability.

node : nodeBlueprint
   Only consider edges for replacement if both source and target node is of this type. If no nodeBlueprint is specified, all edges are considered.




