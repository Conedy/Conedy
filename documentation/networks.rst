Edges and networks
==================

.. _edges :

Edges
-----


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


Network creation and manipulation
========

Conedy depends on his own network class in order to apply the different available integration schemes. The network is represented in memory by an adjacency list. To create an empty network as a starting point, Conedy accepts the following syntax::

   N = co.network()



For the creation and manipulation of the networks, elementary functions (adding single edges or nodes) are supplied, which can be combined in an arbitrary sequence. This allows to create the desired network step by step in python. To add two nodes of type :ref:`roessler` to the network, the :ref:`addNode` command can be used::


   N.addNode(co.roessler())
   N.addNode(co.roessler())






.. In addition, it is possible to import networks from networkx and to create them from files containing graphML, whitespace-seperated txt-files matrices or adjacency lists.


Beside these elementary functions, Conedy supplies more complex functions, which add more than one node and edge at the same time. The following example will add to ``N`` a directed random network of 100 logistic maps, where two nodes are connected with a probability of 0.1 by a weighted edge::

   nodeTemplate = co.logisticMap()
   edgeTemplate = co.weightedEdge()
   firstNodenumber = N.randomNetwork(100, 0.1, nodeTemplate, edgeTemplate)

Functions, which create more than one node will return the number of the first created node. Other created nodes have consecutive numbers. Similar to this example with random networks, functions which create one and two dimensional lattices and tori are available, and it is possible to create networks from files which contain either adjacency lists or matrices.



