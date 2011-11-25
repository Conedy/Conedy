Edges
========

XXXXXXXXXXXXX


Edges in Conedy indicate that two nodes are in some way dynamically coupled. The excact form of this coupling depends on the node. E. g. for a dyanimcal map the same edge may signify a coupling as one what would expect from a coupled map lattice, while it may indicate diffusive coupling for ordinary differential equations. In addition, edges in Conedy may carry a connection strength or do some calculations with the state of nodes before they are given to the coupled nodes.

As for nodes, edgeblueprints have to be created before addition of edges to the network. The following lines will add a second node and connect both by a weighted Edge::

   >>> secondNodeNumber = N.addNode(nodeblueprint)
   >>> edgeblueprint = co.weightedEdge(0.1)
   >>> N.addEdge(firstNodeNumber,secondNodeNumber,edgeblueprint)


For edges, which for large networks usually are responsible for most of the memory consumption, conedy offers different ways for handling coupling strengths:
XXXXX


 - edge                    all coupling strengths are set to 1
 - weightedEdges           edge with an arbitrary couping strength
 - staticWeightedEdge      all edges of this kind share the same coupling strength

On top



more complicate edges TODO



Edges provide their node with two variables:

-  state
   The state which is offered by the coupled node. Possibly transformed  by the edge. For the simplest edges (like weightedEdge) this is the zeroth component of the coupled node.

-  coupling
  A floating point number for the coupling strength. Again the provided number depends on the edge type








XX
