Network creation and manipulation
========

Conedy depends on his own network class in order to apply the different available integration schemes. The network is represented in memory by an adjacency list. To create an empty network as a starting point, Conedy accepts the following syntax::

   >>> import conedy as co
   >>> N = co.network()



For the creation and manipulation of the networks, elementary functions are supplied, which can be combined in an arbitrary sequence. This allows to create the desired network in py




.. In addition, it is possible to import networks from networkx and to create them from files containing graphML, whitespace-seperated txt-files matrices or adjacency lists. 


Beside these elementary functions, Conedy supplies more complex functions, which add many nodes and edges at the same time. The following example will add a directed random network of 100 logistic maps, where two nodes are connected with a propability of 0.1 by a weighted edge::

   >>> edgeblueprint = co.weightedEdge()
   >>> firstNodenumber = N.randomNetwork(100, 0.1, nodeblueprint, edgeblueprint)

Functions, which create more than one node will return the number of the first created node. Other created nodes have consecutive numbers. Similar to this example with random networks, functions which create one and two dimensional lattices and tori are available, and it is possible to create networks from files which contain either adjacency lists or matrices. 

