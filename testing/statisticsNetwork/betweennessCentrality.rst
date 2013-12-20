
``betweennessCentrality(filename)``
	Writes the betweenness centrality of each individual node to a text file.
	The file contains the centralities written in order of the node number.

Parameters
----------
``filename``: String
         Name of the file to which the betweenness centralities will be written


Notes
-----
If :math:`n` is the number of nodes in the network and :math:`\mathcal{D}_{jk}` is the set of all shortest path between node :math:`j` and node :math:`k`, the betweenness centrality of node :math:`i` is:

.. math::
   \frac{1}{n (n-1)} \sum_{j,k} \frac{ \left\lvert \left\{ D \in \mathcal{D}_{jk} \middle | i \in D \right\} \right\rvert}{ \left\lvert \mathcal{D}_{jk} \right\rvert }

The normalisation is such that the betweenness centrality is always in the interval :math:`\left[ 0, 1 \right]`.
The distance between two nodes is defined as described in :ref:`meanPathLength`.
