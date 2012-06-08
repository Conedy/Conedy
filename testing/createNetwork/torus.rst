
``network.torus(sizex, sizey, a, node=dynNode, edge=weightedEdge)``
  Adds a 2-dimensional, cyclic lattice to the network.

Parameters
----------
``sizex``: integer
        Size of the lattice in x-direction.
``sizey``: integer
        Size of the network in y-direction.
``a`` : double
        Every node is connected to all neighbours in a distance smaller than ``a``.
``node`` : node template
        Every added node is a copy of this template.
``edge`` : edge template
        Every added edge is a copy of this template.


