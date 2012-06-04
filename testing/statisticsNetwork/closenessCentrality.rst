
``closenessCentrality(filename)``
	Writes the closeness centrality of each individual node in a text file.
	The file contains the centralities written in order of the node number.

Parameters
----------
``filename``: String
         Name of the file to which the closeness centralities will be written


Notes
-----
If :math:`n` is the number of nodes in the network and :math:`l_{ij}` is the length of the shortest path between nodes :math:`i` and :math:`j`, the closeness centrality of node :math:`i` is defined as:

.. math::
	\frac{n-1}{ \sum_{j\neq i} l_{ij}}

The normalisation is such that the closeness centrality is always in the interval :math:`\left[ 0, 1 \right]`.
The distance between two nodes is defined as described in :ref:`meanPathLength`.