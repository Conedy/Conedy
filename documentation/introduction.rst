.. _introduction:

============
Introduction
============
Overview
--------


Conedy is a scientific tool for the numerical integration of dynamical systems, whose mutual couplings are described by a network. Its name is an abbrevation of “Complex Networks with Dynamics”.

Conedy supports different dynamical systems with various integration schemes, including ordinary differential equations, dynamical maps, stochastic differential equations and pulse coupled elements which are handled via events. In addition it provides a simple way to implement your own dynamics. Each dynamical system is represented by a node in a network and edges between such nodes represent couplings. Conedy provides tools to build a network from the various node and edge types and prepare this network for study, e. g. by choosing initial conditions or parameters from random distributions. Most importantly Conedy can integrate or evolve such a network and observe it simultaneously. Conedy was designed with focus on run-time and memory efficiency and allows the user to decide about performance issues, such as the selection of edge types XXXat compile time.

Conedy can be interfaced via python bindings (recommended) or with an built-in script interpreter, using a C-like syntax. This manual focusses on the python interface. The built-in script interpreter may be useful if you want to distribute computations onto a cluster, as it can easily be linked statically (in contrast to python). In addition it has support for creating `condor`_  dagman job files, converting the iterations of vectorizable loops into different jobs. Condor is a job management system developed at the Computer Science department of the University of Wisconsin. Most of the following description applies to both interfaces; every function of the python-binding corresponds to a function (of the same name) of the built-in interpreter. The main differences in syntax are:

-  add a ";" at the end of every command.
-  Blueprints are specified in < > instead of given as arguments similar as with templates in C++.

See the testing directory of the source code for example files. If you are familiar with bison/flex grammar files you may also look into Parser.yy and Scanner++ of the source code. Although the built-in interpreter supports C-contstructs like loops and if statements, it may still be limited in some cases.




.. _condor: http://www.cs.wisc.edu/condor/



In the following, a short example is given which shows how to use to python bindings to obtain data from coupled dynamical systems.

Short Example
-------------
We create a simple network with two nodes, one with Rössler and one with Lorenz dynamics. We add a directed edge, coupling the `Rössler`_ into the `Lorenz`_, and monitor the oscillators for some time::

	#! /usr/bin/env python
	# -*- coding: utf-8 -*-
	import conedy as co

	# Create the network, …
	N = co.network()

	# add the nodes to it, …
	numberRoessler = N.addNode(co.roessler())
	numberLorenz = N.addNode(co.lorenz())

	# and connect them with a directed edge with weight 1.0 (Rössler to Lorenz).
	N.addEdge(numberLorenz, numberRoessler, co.weightedEdge(1.))

	# Set the oscillators’ intial states.
	N.setState(numberRoessler, 0., 0., 0.)
	N.setState(numberLorenz, 1., 1., 1.)

	# Let 100.0 units of time pass, in order for transients to die out.
	N.evolve(0., 100.)

	# Set the time and each oscillator’s third component to be written to roesslerLorenzOut.
	N.observeTime("roesslerLorenzOut")
	N.observe(numberRoessler, "roesslerLorenzOut", co.component(2))
	N.observe(numberLorenz, "roesslerLorenzOut", co.component(2))

	# Let 400.0 units of time pass.
	N.evolve(100.,500.)

Voilà: Now we have timeseries (400.0 units) of the two coupled oscillators written down in a text file ``roesslerLorenzOut``.

Of course there are more ways to configure the desired network or time evolution.
For a more detailed overview of Conedy’s features take a look at the :ref:`tutorial<tutorial>`.

.. _Rössler: http://en.wikipedia.org/wiki/Rössler_attractor
.. _Lorenz: http://en.wikipedia.org/wiki/Lorenz_attractor


Free Software
-------------
Conedy is free software licensed under the GPL


    Conedy is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.



