
``meanClustering()``
      Returns the mean clustering coefficient of the network as a float.


Notes
-----

If :math:`n` is the number of nodes in the network and :math:`A` is its adjacency matrix (i.e. :math:`A_{ij} = 1`, if there is an edge connectiong node :math:`i` to node :math:`j`, and :math:`A_{ij} = 0` otherwise), the mean clustering coefficient is defined as:

.. math::
	\binom{n}{3}^{-1}
	\sum\limits_{i=1}^n
	\sum\limits_{j=1}^{i-1}
	\sum\limits_{k=1}^{j-1}
	{A_{ij} A_{jk} A_{ki}}

This is the mean over all nodes of the node-wise clustering coefficent, which is defined as the rate at which two neighbours *of a given node* are neighbours. This usually differs from the global clustering coefficient, which is the rate at which two nodes that have a common neighbour are neighbours.
