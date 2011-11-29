Edges and networks
==================

.. _edges :

Edges
-----

Edges in Conedy indicate that two nodes are in some way dynamically coupled. The excact form of this coupling depends on the node. For example the same edge may represent diffusive coupling for ordinary differential equations and for iterated maps coupling as one would expect from a coupled map lattice.

Edges provide the target node with two variables:

-  ``state``: The state which is offered by the coupled node, possibly transformed by the edge. For most edges this is the zeroth dynamical variable of the coupled node.

-  ``weight``: A floating point number for the coupling strength. Again, the provided number depends on the edge type.

See :ref:`dynamicsEqations<the section about dynamics equations>` on how ``weight`` and ``state`` are processed by the target node.

Edge templates
``````````````

In analogy to :ref:`nodeTemplates`, most functions for network creation and manipulation accept edge templates as a parameter. For example the following code will add two Lorenz oscillators to a network and connect them with an edge with weight 0.1:

.. testsetup:: *

   import conedy as co

.. testcode::

	N = co.network()
	firstNodeNumber = N.addNode(co.lorenz())
	secondNodeNumber = N.addNode(co.lorenz())
	N.addEdge(firstNodeNumber,secondNodeNumber,co.weightedEdge(0.1))

Here ``weightedEdge`` provides the edge template, which is directly passed to ``addEdge``.


Edge types
``````````

Conedy provides the several edge types:

	- ``edge``: An edge with weight 1.0.
	- ``weightedEdge``: An edge whose weight is given as an argument.
	- ``staticWeightedEdge``: Like ``weightedEdge``, but all edges of this type always share the same weight. The usage of ``staticWeightedEdge`` may significantly reduce the memory consumption of large networks, which is usually made up mainly by edges.
	- ``stepEdge``: Takes one argument ``threshold``. The returned ``state`` is 1 if the zeroth dynamical variable of the coupled node is smaller than ``threshold`` and 0 otherwise.

XXXX

Network creation and manipulation
---------------------------------

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


Network Measures
----------------
