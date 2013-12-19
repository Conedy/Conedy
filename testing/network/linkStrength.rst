``network.linkStrength(source, target)``
   Returns the weight of an edge between node ``source`` and node ``target``

 
Parameters
----------
``source``: int
   Number of the source node for the edge in question.
``target``: int
   Number of the target node for the edge in question.


Returns
-------
the weight of the edge between ``source`` and ``target``.


Note
----
The network generators in Conedy do not create multiple edges between the same nodes. A network may however contain such edges if it is read in from a file. In this case linkStrength returns the weight of the first edge it encounters.


