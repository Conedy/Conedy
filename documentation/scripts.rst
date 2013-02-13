.. _scriptInterpreter :

The built-in script interpreter
///////////////////////////////

Conedy does not only ship with a Python module, but also with its own script interpreter.

Why use the script interpreter?
-------------------------------

The Python module and the script interpreter both provide everything, Conedy has to offer.
Beyond this, however, the script interpreter’s functionality is rather limited, whereas Python offers a vast amount of libraries.
On the other hand, the interpreter can easily be linked statically, which can be very useful, if you want to distribute computations onto a cluster.
Furthermore supports the `Condor`_ job management system (see below).

So, if you are only using Conedy on a single computer, you will usually want to use its Python module.
If you want your calculations to run on other computers but a full install of Conedy on all of them is impossible or significantly troublesome, you should take a look at the script interpreter—even more, if your job management software is Condor.



Differences to the Python module
--------------------------------

We illustrate the differences between both ways of using Conedy with an example Python script and its corresponding script for use with the script interpreter::

	#! /usr/bin/env python

	import conedy as co

	N = co.network()

	for p in [i*0.1 for i in range(11)]:
		for k in range(4,11):
			N.torusNearestNeighbors(100, 100, k, co.lorenz(), co.staticWeightedEdge(0.1))
			N.rewireUndirected(p)
			N.randomizeStates(co.lorenz(), co.gaussian(0.0, 2.0), co.gaussian(0.0, 2.0), co.gaussian(0.0, 2.0))

			co.set("samplingTime", 1.0)
			co.set("odeStepType", "gsl_rk8pd")

			N.observeTime("sw_%G_%G" % (p,k))
			N.observeSum("sw_%G_%G" % (p,k), co.component(0))

			N.evolve(0.0,10000.0)

			N.removeObserver()
			N.clear()

(This example script generates `small-world`_ networks based on a 100×100 torus of ``lorenz`` oscillators with rewiring probabilities p and mean degrees k.
P is varied between 0.1 and 1.0, k between 4 and 10.
The dynamics on each of these networks is integrated for 10000 time units and the sum over all nodes of the first component is written to a file, whose name contains the current values of p and k.)

.. _small-world: http://en.wikipedia.org/wiki/Small-world_network


The following script performs the same operations, if run with ``conedy``::

	network N;

	for (double p = 0.0; p <= 1.0; p += 0.1)
	{
		for (int k = 4; k <= 10; k++)
		{
			N.torusNearestNeighbors(100, 100, k, lorenz(), staticWeightedEdge(0.1));
			N.rewireUndirected(p);
			N.randomizeStates(lorenz, gaussian(0.0, 2.0), gaussian(0.0, 2.0), gaussian(0.0, 2.0));

			samplingTime = 1.0;
			odeStepType = "gsl_rk8pd";

			N.observeTime("sw_" + p + "_" + k);
			N.observeSum("sw_" + p + "_" + k, component(0));

			N.evolve(0.0,10000.0);

			N.removeObserver();
			N.clear();
		};
	};






The following differences can be spotted:

- Commands are separated by semicola instead of newlines.
- The name-space declaration `co.` has vanished.
- Loops are done in C-style, except for a semicolon at the end of each loop.
- Calls of ``co.set`` have been replaced by direct assignments.
- Strings are handled differently.

Note that most commands in the :ref:`reference` have an example for use with the script interpreter.
If you are familiar with Bison/Flex grammar files, you may also look into the files ``Parser.yy`` and ``Scanner.ll`` of Conedy’s source code.
Although the built-in interpreter supports some C-constructs, it may still be limited in some cases.


Vectorising Loops
-----------------

In the above example, it is not neccessary to compute the bodies of the inner loop in a specific order. Instead each one may be issued independently; the loop is vectorisable. With a Conedy script this can easily be done in the following way:

- Replace the ``for`` of the loop you want to vectorise by ``vectorFor``.
- Pass the numbers of the iteration, you want to compute, as an additional argument to the conedy script interpreter.

In the above example both loops are vectorisable. If you replace both occurences of ``for`` by ``vectorFor``, you can issue the second iteration of the inner loop in the first iteration of the outer loop with::

	conedy script.co 0 1

assuming, that the script is stored in ``script.co``. Note the zero-based enumeration.

At the moment, Conedy only supports to vectorise two nested loops.
Note, however, that you can still use a regular loop in the innermost vectorised loop.

Having vectorised your loops, distributed computing is quite straightforward, since only the ``conedy`` executable is needed to run such a script.

``conedyCondor``
----------------

`Condor`_ is a job management system developed at the Computer Science Department of the University of Wisconsin.

``conedyCondor`` is a tool, that automatically generates a DAG file from a script with vectorized loops (see above). All you need to do to distribute computations is calling this file with ``condor_submit_dag``.

In addition to ``vectorFor``, ``conedyCondor`` also interpretes the command ``chainFor``, which causes the bodies of the respective loop to be processed one after another—but possibly on different machines. “Communication” between these different iterations has to happen via files, however.

``conedyCondor`` is not installed by default; you need to add ``condor`` to the ``todo`` list in your ``config.h`` and than recompile ``conedy``.

.. _Condor: http://www.cs.wisc.edu/condor/
