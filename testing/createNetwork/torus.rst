

network.torus(sizex, sizey, a, node=dynNode, edge=weightedEdge)
  Adds a 2 dimensional lattice to the network.
  
Parameters
----------
sizex : int
        Size of the lattice in x-direction.
sizey : int
        Size of the network in y-direction.
a : int
        Every node is connected to all neighbors, if the distance is smaller than a.
node : nodeTemplate
        Every added node is a copy of this template.
edge : edgeTemplate
        Every added edge is a copy of this template.

        
