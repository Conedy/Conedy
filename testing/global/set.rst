.. _set :



set (parameter, newValue)
   Sets the standard value of a node parameter to a different value. Nodes with standard parameter are affected even if the set command occurs after node creation.


Example
-------
::

  import conedy as co
  
  co.set("lorenz_r", 29.0)



In addition Conedy has some global variable, which can also be set with this command:



dynNetwork_ioNodeDt
--------------------------------
Controls the interval in which registered observables are sampled.

network_edgeVerbosity
--------------------------------
Controls the amount of information that is printed about edges after a call of :ref:`printNodeStatistics`


network_nodeVerbosity
--------------------------------
Controls the amount of information that is printed about nodes after a call of :ref:`printNodeStatistics`


streamInNode_compress
--------------------------------
If set to 1.0, streamInNodes (which read and offer data from files) will expect gzip compressed files.



streamOutNode_append
--------------------------------
If set to 1.0, data is appended if a file with the same name already exists.

streamOutNode_compress
--------------------------------
If set to 1.0, all generated files are compressed using gzip.

streamOutNode_precision
--------------------------------
Sets the number of digits which are written 

streamOutNode_binary
--------------------------------
If set to 1.0, data is written as 64-bit doubles in binary form without seperation for different time steps. Also, the value of streamOutNode_compress, streamOutNode_precision and streamOutNode_append will not apply.




.. vectorForInstruction_linux32
.. vectorForInstruction_linux64
.. vectorForInstruction_windows51 
.. vectorForInstruction_windows60 
.. vectorForInstruction_windows61 



.. set standard parameter





