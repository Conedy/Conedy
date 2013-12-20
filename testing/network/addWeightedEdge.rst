
network.addWeightedEdge(source, target, weight)
   Adds an edge with weight "weight" to the network, connecting node "source" with node "target"

Parameters
----------
source: int
   Number of the node which is the source of the added connection.
target: int
   Number of the node which is the target of the added connection.
weight : float
  The weight of the added edge. 



Note
----
For nodes which represent a differential equation, the added connection represent a coupling in the expected direction (source influences target). The command is äquivalent to addEdge (source, target, weightedEdge(weight)).




