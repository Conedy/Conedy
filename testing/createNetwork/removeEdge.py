import conedy as co

nodeTemplate=co.pcoIntegrateFireDelay()

N=co.network()

N.cycle(100, 4, nodeTemplate, co.weightedEdge(0.1))
N.rewireUndirected(0.1)

N.observePhaseCoherence("meanPhase0")
N.evolve(0.0, 100.0)
N.removeObserver()


N.observePhaseCoherence("meanPhase1")
N.degreeCentrality("degrees0")
N.evolve(100.0, 200.0)
N.removeObserver()

N.removeEdge(88,5, co.weightedEdge(0.1))   

N.observePhaseCoherence("NewMeanPhase")
N.evolve(100.0, 200.0)
