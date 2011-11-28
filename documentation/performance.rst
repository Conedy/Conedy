Performance
===========






memory usage of node parameters
-------------------------------


virtual vs static edges
-----------------------





In many situations it is not neccesarry that a node of a certain kind has edges of different kind. As this is in Conedy implemented by virtual functions, the needed v-table will consume memory.  In addition whenever a node during numerical integration requires the state of a connected node, virtual function calls have to be made, which -- depending on the circumstances -- may be unneccessaryily slow. Conedy offers the possibility to create so called static nodes for which both the kind of outgoing edges of a node and the node type of the target nodes is specified at compile time.  For these nodes, no virtual function calls have to be made during integration. For cases with many unweighted edgse, the memory consumption of static nodes on 64 bit machines  is reduced by a factor of 4! (compared to virtual nodes) This is because in virtual nodes in addition to the target node number (4 byte) and the v-table (8 byte) most compiler will leave another 4 bytes unused due to alignment. 

To use static edges add::

   staticEdges=1

to the description file for your node. Additionally the edge type which should be associated with your node has to be defined by e.g.::

   staticEdgeType= weightedEdge

Optionally you can choose a nodetype for target nodes, which eliminates another virtual function call:: 

   staticTargetNodeType= roessler






The following table shows memory usage of edgse in Conedy for 64 bit.

edgetype            static          virtual functions
=====               ========        =================
edge                    4                 16
staticWeightedEdge      4                 16
weightedEdge            16                24







