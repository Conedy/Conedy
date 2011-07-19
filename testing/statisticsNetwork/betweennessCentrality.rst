

betweennessCentrality(filename)
      Writes the betweenness centrality of each individual node in a textfile.
      The file contains the centralities written in order of the nodenumber.

Parameters
----------
filename : string
         name of the file to which the betweenness centralities will be written


Notes
-----
If n is the number of nodes in the network, :math:`\zeta_{jk}` is the
number of shortest paths between the nodes j and k
and :math:`\zeta_{jk}(i)` is the number of shortest paths between the nodes
j and k that pass through node i, the Betweenness Centrality of node i is
defined in the following way.

.. math::
   betweennessCentrality(i)=\frac{1}{n(n-1)}\sum_{j,k}\frac{\zeta_{jk}(i)}{\zeta_{jk}}

The normalisation is done in such a way that the Betweenness Centrality is in
the range [0:1].
The distance between two nodes is calculated by taking the inverse of the
weight of the connecting edge.
