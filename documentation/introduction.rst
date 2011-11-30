.. _introduction:

============
Introduction
============
Overview
--------


Conedy is a scientific tool for the numerical integration of dynamical systems, whose mutual couplings are described by a network. Its name is an abbreviation of “Complex Networks Dynamics”.

Conedy supports different dynamical systems with various integration schemes, including ordinary differential equations, iterated maps, stochastic differential equations, and pulse coupled elements which are handled via events. In addition, it provides a simple way to implement your own dynamics. Each dynamical system is associated with a node in a network and edges between such nodes represent couplings. Conedy provides functions to build a network from various node and edge types.


Initial conditions and parameters can be chosen individually or drawn from random distributions. Conedy can numerically integrate  the coupled system while sampling user-defined observables in periodic intervals. Conedy was designed with focus on execution time and memory efficiency and allows the user to decide about performance issues at compile time.


Conedy can be interfaced via Python bindings (recommended) or with a built-in script interpreter, using a C-like syntax. The latter may be useful if you want to distribute computations onto a cluster as the interpreter can easily be linked statically (in contrast to Python) and also has support for the `Condor`_ job management system. Because the main syntax difference is that commands are separated by semicola instead of new lines, we only refer to the Python interface in most of this manual. However, there also is a :ref:`small chapter<scriptInterpreter>` devoted to the script interpreter and its features.

.. _Condor: http://www.cs.wisc.edu/condor/

In the following, a short example is given which shows how to use the Python bindings to obtain time series from coupled dynamical systems.

.. _introductionExample :

Short Example
-------------
We create a simple network with two nodes, one with Rössler and one with Lorenz dynamics. We add a directed edge, coupling the `Rössler`_ into the `Lorenz`_, and observe the oscillators for some time:


.. testcode:: INTRO

   #! /usr/bin/env python
   import conedy as co

   # Create an empty network, …
   N = co.network()

   # add the nodes, …
   nodeNumberRoessler = N.addNode(co.roessler())
   nodeNumberLorenz = N.addNode(co.lorenz())

   # and connect them with a directed edge with weight 1.0 (Roessler to Lorenz).
   N.addEdge(nodeNumberLorenz, nodeNumberRoessler, co.weightedEdge(1.))

   # Set the oscillators’ intial states.
   N.setState(nodeNumberRoessler, 0., 0., 0.)
   N.setState(nodeNumberLorenz, 1., 1., 1.)

   # Let 100.0 units of time pass, in order for transients to die out.
   N.evolve(0., 100.)

   # Set the time and each oscillator’s third component to be written to the file roesslerLorenzOut.
   N.observeTime("roesslerLorenzOut")
   N.observe(nodeNumberRoessler, "roesslerLorenzOut", co.component(2))
   N.observe(nodeNumberLorenz, "roesslerLorenzOut", co.component(2))

   # Let 400.0 units of time pass.
   N.evolve(100.,500.)


Voilà: Now we have timeseries of the two coupled oscillators written to a text file.

Of course there are more ways to configure the desired network and dynamics.
For a more detailed overview of Conedy’s features take a look at the :ref:`tutorial<tutorial>`.

.. _Rössler: http://en.wikipedia.org/wiki/Rössler_attractor
.. _Lorenz: http://en.wikipedia.org/wiki/Lorenz_attractor


Free Software
-------------
Conedy is free software licensed under the GPL:


    Conedy is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.



