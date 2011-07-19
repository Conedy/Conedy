

closenessCentrality(filename)
      Writes the closeness centrality of each individual node in a textfile.
      The file contains the centralities written in order of the nodenumber.

Parameters
----------
filename : string
         name of the file to which the closeness centralities will be written



Notes
-----
If n is the number of nodes in the network and :math:`l_{ij}` is the shortest
pathlength between the nodes i and j, the Closeness Centrality of node i is
defined in the following way.

.. math::
   closenessCentrality(i)=\frac{n-1}{\sum_{j\neq i}l_{ij}}

The normalisation is done in such a way that the Closeness Centrality is in
the range [0:1] for binary networks.
The distance between two nodes is calculated by taking the inverse of the
weight of the connecting edge.

For the Closeness Centrality to give useful results the is network needed to be
connected in a sense that all nodes need to be reachable from any other node.

