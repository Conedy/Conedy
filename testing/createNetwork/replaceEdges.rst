``directedNetwork.replaceEdges(probability, edge, node)``
``undirectedNetwork.replaceEdges(probability, node)``
   Replaces connections in the network by connections between randomly chosen source and target nodes.

Parameters
----------

``probability``: double (:math:`\in\left[ 0, 1 \right]`)
   Replacement probability.

``edge``: edge template
   Replace edges with newly created edges of this type.

``node``: node template
	Only consider edges for replacement if both, source and target node are of this type.
	If not specified, all edges are considered.
