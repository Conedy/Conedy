
``meanPathLength()``
     Returns the (weighted) mean shortest path length of the network. The “length” of an edge is considered to be the inverse of its weight. Unweighted edges therefore are considered to have a length of 1. This routine only works, if the whole network is connected. Self connections are not taken into account.

Notes
-----

If :math:`n` is the number of nodes in the network, :math:`S_{ij}` is the inverse of the weight of the edge connecting :math:`i` and :math:`j` (and :math:`\infty`, if this edge does not exist), :math:`\mathcal{P}_{ij}^l \mathrel{\mathop:}= \left\{P \in \left\{1,\ldots,n\right\}^l \middle | P_1=i, P_l=j\right\}` is the set of all paths of binary length :math:`l` from :math:`i` to :math:`j`, the mean shortest path length is defined as:

.. math::
	\binom{n}{2}^{-1}
	\sum\limits_{i=1}^n
	\sum\limits_{j=1}^{i-1}
	\min_l
	\min_{P\in\mathcal{P}_{ij}^l}
	\sum\limits_{k=1}^{l-1}
	S_{P_k P_{k+1}}


