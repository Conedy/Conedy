Selecting node parameters and initial conditions
========


Node templates
--------------

For network creation, Conedy supplies elementary functions which allow you to add single nodes or edges as well as higher-level functions which add random networks or lattices, or manipulate an already existing network.


.. testsetup:: *

   import conedy as co





All these functions in Conedy accept a parameter which allows you to specify the type of the added node(s). We call this parameter a node template. To add a single node of type ``logisticMap``, the following code can be used:

.. testcode:: test2

   N = co.network()
   nodeNumber = N.addNode(co.logisticMap())

Nodes in Conedy are identified by an 32 bit integer, which is returned by ``addNode`` in case you want to access the node later (e.g. to connect an edge to it).




Node parameters
---------------

Most node dynamics depend on certain parameters. For example, the node dynamics :ref:`logisticMap` is defined by :math:`x_{n+1} = r x_n ( 1 - x_n)` with :math:`r` as a parameter, which can be assessed by ``logisticMap_r`` in Conedy.

When a node is added as in the above example, default values for node parameters are used, for example the default value of ``logisticMap_r`` is 3.58 (as documented in :ref:`logisticMap`). In case you want to add different parameters, a full set of parameters can be specified as arguments, e.g.


.. testcode:: test1

   N = co.network()
   N.addNode(co.logisticMap(2.6))

To change a parameter after node creation, the ``setParam``-function can be used. Just specify node number, parameter name and the new desired new value

.. testcode:: test2

   N.setParam(nodeNumber, "logisticMap_r", 3.53)


Another way to control parameters is to change the default values. For example

.. testsetup:: 
   import conedy as co


.. testcode:: 

	N = co.network()
	for i in range(500):
		N.addNode(co.lorenz())
	co.set("lorenz_S", 11)
	co.set("lorenz_r", 25)

will create a network of 500 nodes, all with :ref:`lorenz` dynamics and all with ``lorenz_s`` = 11 and ``lorenz_r`` = 25 as well as the third parameter ``lorenz_b`` equalling its predefined standard value. Since all nodes of the above network use the same memory for the parameters, it makes no difference, whether default values are changed before or after network creation. However, if the parameters of a node have been changed (e.g. by ``setParam``), they are stored in a different memory position and will not be affected by a change of the default parameters

.. testsetup:: 
   import conedy as co

.. testcode:: 

	N = co.network()
	nodeNumber = N.addNode(co.logisticMap())
	N.setParam(nodeNumber, "logisticMap_r", 1.0)
	co.set("logisticMap_r", 3.5)
	print N.getParam(nodeNumber, "logisticMap_r")    # returns 1.0

.. testoutput::
  :HIDE:

   1.0


.. testcode:: 

	N = co.network()
	nodeNumber = N.addNode(co.logisticMap())
	co.set("logisticMap_r", 3.5)
	print N.getParam(nodeNumber, "logisticMap_r")    # returns 3.5

.. testoutput::
   :HIDE:

   3.5

.. _randomizing :

Randomizing node parameters
---------------------------

Random number generators in Conedy
``````````````````````````````````
Conedy uses the random number generators of the GNU Scientific Library (GSL). Therefore the prefered algorithm can be specified by setting environment variables (see `the GSL’s documentation`_). When importing Conedy, a random seed is created using the system time and written to the console. If you want to have reproducible simulation values—or in case you want to start many simulations at the same time without the risk of identical seeds—, you can set a random seed manually (e.g. to 42) by calling::

   co.setRandomSeed(42)

.. _the GSL’s documentation: http://www.gnu.org/software/gsl/manual/html_node/Random-Number-Generation.html

For the randomization of parameters (or initial conditions) objects are provided, which specify the desired random distribution. The following example will create an object for uniformly distributed random numbers between 0.2 and 0.4::

   randomNumber = uniform(0.2,0.4)

In addition, the following distributions are available:

-  ``gaussian(m, s)``

  Gaussian distributed random numbers with mean m and standard deviation s.

-  ``bimodal(l, u, p)``

  Will draw the number l with probability p and the number u with probability 1–p.

-  ``constant(c)``

  All drawn numbers have value c. (This can be useful, if you want some states not to be randomized.)


.. _parameterRandomization :

Parameter randomization
``````````````````````````

Parameters are randomized with the :ref:`randomizeParameter` command. For example, the following line will randomize the parameter ``lorenz_b`` of all ``lorenz`` nodes in ``N`` with Gaussian random numbers::

	N.randomizeParameter("lorenz_b", co.gaussian(2.5,0.5))


Initial conditions of nodes
----------------------------

Before the dynamical is integrated,  initial conditions can be set. There are two ways to change node states in Conedy (apart from evolving the network).

First, each node may be modified directly with the ``setState`` command. In the following example a ``lorenz`` node is added to the network, its number is memorized as ``nodeNumber`` and its state is set to (1.0, 1.0, 1.0)::

	N = co.network()
	nodeNumber = N.addNode(co.lorenz())
	setState (nodeNumber, 1.0, 1.0, 1.0)


Alternatively with the :ref:`randomizeStates` command the states all nodes of a certain node type can be randomized. Suppose we random initial conditions for the first component of 500 ``lorenz`` nodes and the other two components fixed to 1.0::

	N = co.network()

	for i in range(500):
		N.addNode(co.lorenz())

	N.randomizeStates(co.lorenz(), co.gaussian(1.0, 0.5), co.constant(1.0), co.constant(1.0))


Note that here node templates are used in a different way than before, namely to specify the nodes in the network which are manipulated (in this case all nodes of type ``lorenz``). To target only nodes with certain parameters, these can be specified. The following command will set uniformly distributed states to all ``logisticMap``-nodes in the network N, which have a parameter ``logisticMap_r`` of 3.59::

	N.randomizeStates(co.lorenz(3.59), uniform (0.0,1.0))








