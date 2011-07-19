

meanClustering()
      Returns the mean clustering coefficient of the network as a float.


Notes
-----
The mean clustering coefficient of a network is defined in the following way.
     
.. math::
      meanClustering = \frac{3\times \textnormal{\# of triangles in the network}}{\textnormal{\# of connected triplets of nodes in the network}}

The 3 in the numerator normalises the coefficent to the range of [0:1]
since a triplet can appear in three different positionings.

