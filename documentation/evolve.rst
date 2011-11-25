Evolving and Observing
========


After having created the network, you will want to tell Conedy which features of the network should be observed during integration. Usually, you will call the ``evolve`` function, which evolves the dynamical state of all nodes in the network. In perdiodic intervals, a snapshot of all observed features is performed. The duration between snapshots can be controlled by setting the global variable ``samplingTime``::

   co.set("samplingTime", 0.01)
   co.evolve (0.0, 100.0)

This example will evolve the time of all nodes in the  network from 0.0 to 100.0 and write the states of all observed nodes to files every 0.01. The used algorithm for time evolution depends on the node type. 


Additionally, you can issue a snapshot of all observed features manually::
   
   co.snapshot()

This can for example be used to observe your dynamical system at arbitrary intervals. For this sake, one would set samplingTime to a large value and call the ``evolve`` function between successive snapshots::

   co.set("samplingTime", 100000.0);
   for i in range (0,100):
      co.evolve (i*i, (i+1)*(i+1))
      co.snapshot()

Conedy keeps lists of observable features for every file you wish to write to. Whenever data is written to files (due to a call of ``snapshot`` or ``evolve``), a new line is created  in all these files containing a whitespace-separated line with all elements of this list. Observable features are expressed by XXX edges to nodes. You can use standard unweighted edges, which get the same data from the node as a coupled node would. Or more complicated nodes, which calculate same observable of the node first. 


For example if you want Conedy to create a file named ``node0``, which contains the first three dynamical variables of node 0, you would use component-edges::

   net.observe(0,"node0", co.component(0))
   net.observe(0,"node0", co.component(1))
   net.observe(0,"node0", co.component(2))

These columns of the created files are ordered in the way, the corresponding observe commands had been called. The created files remain open until a call of :ref:`removeObserver` or :ref:`clear` had been issued  to the network. Therefore, you can evolve, change some parameter and evolve further in time. The following global variables allow to specify further how the data is written:

 - streamOutNode_compress     if this is set to 1.0, the  files will automatically be compressed with bzip2.
 - streamOutNode_append       if set to 1, data is appended to files instead of creating new files.
 - streamOutNode_precision    sets the number of counting digits for written floats.

