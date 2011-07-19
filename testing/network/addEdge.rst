
network.addEdge(source, target, edgeBlueprint)
   adds a edge to the network connecting node "source" with node "target"

Parameters
----------
source: int
   Number of the node which is the source of the added connection
target: int
   Number of the node which is the target of the added connection




Note
----
For nodes which represent a differential equation, the added connection represent a coupling in the opposite direction due to performance reasons. For pulse coupled oscillators, the added connection represent a coupling in the same direction.




