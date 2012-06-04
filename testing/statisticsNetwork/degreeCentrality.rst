
``degreeCentrality(filename)``
	Writes the degree of each individual node to a text file.
	The file contains the degrees written in order of the node number.
	The redundant name was only chosen to distinguish this function from :ref:`degree`.

Parameters
----------
``filename``: string
         Name of the file to which the degrees will be written


Notes
-----
If :math:`n` is the number of nodes in the network and :math:`A` is its adjacency matrix (i.e. :math:`A_{ij} = 1`, if there is an edge connectiong node :math:`i` to node :math:`j`, and :math:`A_{ij} = 0` otherwise), the degree is  of node :math:`i` is defined as:

.. math::
	\sum_{j=1}^{n} A_{ij}

See also: :ref:`degree`
