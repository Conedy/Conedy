#!/usr/bin/env/ python
import conedy as co 

N=co.network()

nodeTemplate=co.pcoMirollo()
 
N.cycle(1000, 10, nodeTemplate, co.staticWeightedEdge(1.0))

N.observePhaseCoherence("rp20")

N.removeRandomEdges(0.01, co.staticWeightedEdge(1.0))
N.removeRandomEdges(0.01, co.staticWeightedEdge(1.0))
