.. _set :

``set (parameter, newValue)``
   Sets the default value of a node parameter or a global variable to a different value. Nodes with default parameter are affected even if the ``set`` command is issued after node creation.


Example (node parameter)
++++++++++++++++++++++++
::

  import conedy as co

  co.set("lorenz_r", 29.0)


Global variables
++++++++++++++++

If no type is given for some variable, it is of Conedy’s floating point ``baseType``, which can be set at compile time and defaults to ``double``.

``samplingTime``
--------------------------------
Controls the interval in which registered observables are sampled (see :ref:`evolving`).


.. _edgeVerbosity :

``edgeVerbosity`` (integer)
--------------------------------
Controls the amount of information that is printed about edges by :ref:`printNodeStatistics`

.. _nodeVerbosity :

``nodeVerbosity`` (integer)
--------------------------------
Controls the amount of information that is printed about nodes by :ref:`printNodeStatistics`

``progressVerbosity``
--------------------------------
Every time :math:`\text{[Conedy’s time]} / \texttt{samplingTime}` is a multiple of `progressVerbosity`, Conedy prints its time to ``stdout``. If `progressVerbosity` is set to 0.0, Conedy does not report its progress.

``inputCompress`` (boolean)
--------------------------------
If ``True``, ``streamInNodes`` (which read and offer data from files) will expect Gzip-compressed files.

``outputAppend`` (boolean)
--------------------------------
If ``True`` output routines will append data to existing files instead of overwriting them.

``outputCompress`` (boolean)
--------------------------------
If ``True``, all generated files are compressed using Gzip.

``outputPrecision`` (integer)
--------------------------------
Sets the number of digits which are written by output routines.

``outputBinary`` (boolean)
--------------------------------
If ``True``, data is written as 64-bit doubles in binary form without seperation for different time steps. ``streamOutNode_compress``, ``streamOutNode_precision`` and ``streamOutNode_append`` will not apply.


``odeStepType`` (string)
------------------------
Sets the integrator used for evolving ``ode``-type nodes (see :ref:`odenodes`).

``odeRelError``
---------------
Sets the relative error not to be exceeded when evolving ``ode``-type nodes (see :ref:`odeprec`).

``odeAbsError``
---------------
Sets the absolute error not to be exceeded when evolving ``ode``-type nodes (see :ref:`odeprec`).

``odeStepSize``
---------------
Sets the step size used when evolving ``ode``-type nodes (see :ref:`odeprec`).

``odeIsAdaptive`` (boolean)
---------------------------
If ``True``, ``ode``-type nodes are integrated with adaptive step size. If ``False``, a fixed step size is used (see :ref:`odeprec`).


``sdeStepType`` (string)
------------------------
Sets the integrator used for evolving ``sde``-type nodes (see :ref:`sdenodes`).


.. vectorForInstruction_linux32
.. vectorForInstruction_linux64
.. vectorForInstruction_windows51
.. vectorForInstruction_windows60
.. vectorForInstruction_windows61



.. set standard parameter





