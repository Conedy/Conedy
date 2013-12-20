
``meanWeight()``
      Returns the mean weight of the network, taking only existing edges into account.

Notes
-----
If :math:`n` is the number of nodes and :math:`m` is the number of edges in the network and :math:`W_{ij}` is the weight of the edge connecting :math:`i` and :math:`j` (and 0, if this edge does not exist), the mean weight of the network is defined as:

.. math::
	\frac{1}{m} \sum_{i=1}^n \sum_{j=1}^n W_{ij}
