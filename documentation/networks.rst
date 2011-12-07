.. _edgesAndNetworks :

Edges and networks
==================

.. _edges :

Edges
-----

Edges in Conedy indicate that two nodes are in some way dynamically coupled. The excact form of this coupling depends on the node. For example the same edge may represent diffusive coupling for ordinary differential equations or a coupling as one would expect for a coupled map lattice in case of iterated maps.

Edges provide the target node with two variables:

-  ``state``: The state which is offered by the coupled node, possibly transformed by the edge. For most edges this is the zeroth dynamical variable of the coupled node.

-  ``weight``: A floating point number for the coupling strength. Again, the provided number depends on the edge type.

See subsection :ref:`equations<dynamicsEquations>` in section :ref:`Defining new node types<addingNewNodes>` on how ``weight`` and ``state`` are processed by the target node.


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

Conedy provides several edge types:

	- ``edge``: An edge with weight 1.0.
	- ``weightedEdge``: An edge whose weight is given as an argument.
	- ``staticWeightedEdge``: Like ``weightedEdge``, but all edges of this type always share the same weight. The usage of ``staticWeightedEdge`` may significantly reduce the memory consumption of large networks, which is usually made up mainly by edges.
	- ``stepEdge``: Takes one argument ``threshold``. The returned ``state`` is 1 if the zeroth dynamical variable of the coupled node is smaller than ``threshold`` and 0 otherwise.
	- ``randomTarget``: Every time the target of such an edge is queried, it will return a random node. The range from which this node can be chosen can be given as an argument to ``randomTarget``. This edge type is intended for use with pulse-coupled oscillators, but may also be used with ``map`` nodes, where it randomizes the source instead of the target though. You will never want to use this edge type with differential equation dynamics (trust us).
	- ``component``: Like edge, but with an argument you can specify ``target`` to return any dynamical variable, not just the zeroth one.
   - ``staticComponent``: like component, but the returned dynamical variable is shared among all edges of this kind.


There also exist variants of ``stepEdge``, ``randomTarget``, ``component`` and ``staticComponent`` with weights and static weights. All arguments have to be supplied in the order implied by the name. E.g. the edge staticComponent_randomTarget, will first use an number for the dynamical variable as in ``staticComponent`` and then two numbers for the range of chosen nodes as in ``randomTarget``.

See the :ref:`reference for edges<edgesReference>` for a list of available edge types and their syntax.



Network creation and manipulation
---------------------------------

In principle, any network implementable in Conedy can be created step by step in Python using only the elementary functions :ref:`addNode` and :ref:`addEdge`. For example the following commands create a “line” of 100 ``lorenz`` nodes connected by binary edges:

.. testcode::

	N = co.network()
	nodeNumbers = [N.addNode(co.lorenz()) for i in range(100)]
	for i in range(99):
		N.addEdge(nodeNumbers[i], nodeNumbers[i+1], co.edge())

Beside these elementary functions, Conedy supplies more complex functions, which add more than one node and edge at the same time. For example, instead of the above commands, the :ref:`line` command might have been used:

.. testcode::

	N = co.network()
	N.line(100, 1, co.lorenz(), co.edge())

Functions, which create more than one node will return the number of the first created node. Other created nodes have consecutive numbers. Note, that most of these functions add a structure to the network without clearing it beforehand. However, if you want to clear a network, you can do so with the :ref:`clear` command.

Apart from such network creation functions, there are some network manipulation functions like ``rewire`` and ``rewireUndirected``, which might help you to create the desired network. An example for this is given in the :ref:`tutorial<tutorialNetworkCreation>`.

You can also create a network directly from adjacency data in a file with the commands :ref:`createFromAdjacencyList` and :ref:`createFromAdjacencyMatrix`.

See :ref:`createManipulate` for a full list of commands in Conedy, which create or manipulate networks.


.. _measures :

Network Measures
----------------

Once you have created a network, you can apply network analysis tools to it. For example if a network’s creation involved randomness, you might want to check, whether it is connected with the :ref:`isConnected` command.

Conedy also includes some node-specific measures like centralities

.. testcode:: 

	if N.isConnected():
		N.betweennessCentrality("betweenness")
		N.closenessCentrality("closeness")

Here the betweenness and closeness centrality of each node are saved in the text files ``betweenness`` or ``closeness`` respectively, if ``N`` is a connected network.

See :ref:`networkMeasures` for a complete list of supplied network measures.
