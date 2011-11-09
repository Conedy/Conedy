.. _tutorial:

====================
Tutorial
====================
This tutorial aims at giving you a short impression of Conedy’s features and making you familiar with its working principle.

We examplarily generate a small-world network of coupled Rössler oscillators, choose parameters and initial conditions and write the results of the network’s numerical integration to a file. The Rössler oscillator is one of the standard toy models included in Conedy.


.. Knowledge of its mechanisms is not required for the understanding of any of the examples.

.. In the following examples the Roessler oscillator will appear as a node type.


Before we begin, we have to import Conedy to python.::

	#! /usr/bin/env python
	# -*- coding: utf-8 -*-

	import conedy as co

(If not stated otherwise, Conedy is assumed to have been imported like this throughout this manual.)


Selecting node dynamics
--------

First we specify the dynamics we want to consider::

	nodeTemplate = co.gaussianRoessler(0.165, 0.2, 10.0, 0.1)

``nodeTemplate`` now points to a noisy Rössler oscillator which Conedy will integrate with a strong Stratonovitch scheme of order 2.0. Its parameters are set by the arguments of ``gaussianRoessler``. (Details of the node dynamics and the parameters are described in :ref:`gaussianRoessler`.)

Conedy ships with a couple of pre-defined node dynamics (see :ref:`nodes`). In addition, it allows you to incorporate arbitrary dynamics by writing a small specification file, which mainly contains a differential equation (see :ref:`addingNewNodes`).


Creating a network
------------------
We want to create a `small-world`_ network which is based on a closed chain of nodes of 100 nodes, where each node is connected to its 4 nearest neighbors on each side. Subsequently, 10 percent of connections should be replaced by connections with random source and target nodes ::

	N = co.network()
	N.cycle(100, 4, nodeTemplate, co.weightedEdge(0.1))
	N.rewireUndirected(0.1)

Note, that if the network ``N`` had not been without nodes, the ``cycle`` method would have added a set of circularly connected nodes to the network without affecting the existing nodes.

See :ref:`createManipulate` for a list of commands in Conedy, which create or manipulate networks.

.. _small-world: http://en.wikipedia.org/wiki/Small-world_network


Analyzing a network
------------------
In order to control the network’s topology, we can calculate network-specific measures. Conedy supplies some standard measures like the mean shortest path length or the mean clustering coefficient::

	print "clustering coefficient:" + str (N.meanClustering())
	print "mean path length:" + str (N.meanPathLength())


Conedy also includes some node-specific measures like centralities::

   if N.isConnected():
      N.betweennessCentrality("betweenness")
      N.closenessCentrality("closeness")

Here the betweenness and closeness centrality of each node are saved in the text files ``betweenness`` or ``closeness`` respectively, if ``N`` is a connected network.

See :ref:`networkMeasures` for a list of network measures.


Randomizing node parameters
----------------

Until now all oscillators in our network are identical. The following commands change this by picking the initial state randomly from [–0.1, 0.1]³. Aditionally the parameter ``gaussianRoessler_omega``, which we have not touched yet, is picked the uniform distribution on the intervall [0.8, 1.2] for each oscillator::

	N.randomizeStates( nodeTemplate, co.uniform (-0.1,0.1), co.uniform (-0.1,0.1), co.uniform (-0.1, 0.1) )
	N.randomizeParameter( "gaussianRoessler_omega", co.uniform(0.8,1.2) )


Evolving and observing a network
-----------------

Next we tell Conedy that we want to evolve the time from t = 0 to t = 100 in order to let transients die out. The dynamical states will thus be integrated by a numerical integration (and we intentionally do not observe them)::

   N.evolve(0.0, 100.0)

After this we want the integration time and the z-component (component 2 in zero-based enumeration) of all 100 oscillators be written to a file every Δt = 0.01::

   N.observeTime("output_Roessler")
   N.observeAll("output_Roessler", co.component(2))
   co.set("samplingTime", 0.01)

During a second calling of ``evolve`` Conedy will compute the time series of the 100 Rössler oscillators using an integration time step of 0.01. For each time step, the time and the z-component of all oscillators will be written to ``output_Roessler``::

   N.evolve(100.0, 200.0)

Note, that in our example the absolute time values only affect the time which is saved to the file. Since the oscillator dynamics do not depend on absolute time, their time evolution would not have been affected, if we had used ``N.evolve(0.0, 100.0)`` instead.

See :ref:`observeDynamics` for a list of commands in Conedy, which involve numerical integration of the created networks.
