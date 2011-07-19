

meanPathLength()
     Returns the mean path length of the network as a float.


Notes
-----

If n is the number of nodes in the network and :math:`l_{ij}` is the shortest
pathlength between the nodes i and j, the mean path length of the network
is defined in the following way.

.. math::
   meanPathLength = \frac{1}{n(n-1)} \sum_i \sum_{j\neq i} l_{ij}

