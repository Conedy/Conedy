
``meanDegree()``
      Returns the mean degree of the network as a float.


Notes
-----
If :math:`n` is the number of nodes in the network and :math:`A` is its adjacency matrix (i.e. :math:`A_{ij} = 1`, if there is an edge connectiong node :math:`i` to node :math:`j`, and :math:`A_{ij} = 0` otherwise), the mean degree is defined as:

.. math::
	\frac{1}{n} \sum_{i=1}^n \sum_{j=1}^n A_{ij}
