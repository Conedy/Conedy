
``degree(nodeNumber)``
	Returns the degree of a node.

``nodeNumber``: integer
	The number of the node whose degree shall be returned.


Notes
-----
If :math:`n` is the number of nodes in the network and :math:`A` is its adjacency matrix (i.e. :math:`A_{ij} = 1`, if there is an edge connectiong node :math:`i` to node :math:`j`, and :math:`A_{ij} = 0` otherwise), the degree is  of node :math:`i` is defined as:

.. math::
	\sum_{j=1}^{n} A_{ij}

See also: :ref:`degreeCentrality`

