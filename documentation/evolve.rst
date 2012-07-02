Evolving and Observing
======================

Setting observables
-------------------

Conedy keeps lists of observable features for every file you wish to write to. Whenever data is written to files (due to a call of ``snapshot`` or ``evolve``), a new line is created in all these files containing a whitespace-separated line with all elements of this list.

Observable features are specified by edges to nodes.

The same state variable (see :ref:`edges`) that is supplied by an edge to a coupled node can be written to files. For example if you want Conedy to create a file named ``node0``, which contains the first three dynamical variables of node 0, you would use component edges::

   net.observe(0, "node0", co.component(0))
   net.observe(0, "node0", co.component(1))
   net.observe(0, "node0", co.component(2))

The columns of the created files are ordered in the way, the corresponding observe commands had been called. The created files remain open until a call of :ref:`removeObserver` or :ref:`clear` had been issued to the network. Therefore, you can evolve, change some parameter and evolve further in time. The following global variables allow to specify further how the data is written:

 - ``streamOutNode_compress``: If this is set to ``True``, the  files will automatically be compressed with bzip2.
 - ``streamOutNode_append``: If this is set to ``True``, data is appended to an existing file instead of creating a new one.
 - ``streamOutNode_precision``: Sets the number of counting digits for written floats.

See :ref:`observeDynamics` for further observables.

.. _evolving :

Evolving
--------
After creating the network and setting the observables, you will usually call the ``evolve`` function, which evolves the dynamical state of all nodes in the network. In perdiodic intervals, a snapshot of all observed features is performed. The duration between snapshots can be controlled by setting the global variable ``samplingTime``, which defaults to 0.01::

   co.set("samplingTime", 0.01)
   co.evolve (0.0, 100.0)

This example will evolve the time of all nodes in the network from 0.0 to 100.0 and write the states of all observed nodes to files every 0.01. The used algorithm for time evolution depends on the node type (and parameters such as ``odeStepType``, see :ref:`addingNewNodes`).


Additionally, you can issue a snapshot of all observed features manually::

   co.snapshot()


This can be used to observe the network dynamics at arbitrary intervals, for example::

   co.set("samplingTime", 20000.0);
   for i in range (100):
      co.evolve (i*i, (i+1)*(i+1))
      co.snapshot()

Here, ``samplingTime`` is set to exceed the total evolution time in order to avoid automatic snapshots.
