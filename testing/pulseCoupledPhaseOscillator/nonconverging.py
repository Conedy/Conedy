import conedy as co


co.set("samplingTime", 0.025)



co.set("pcoIntegrateFire_noiseFrequency", 0.0)
co.set("pcoIntegrateFire_timeDelay", 0.01)
co.set("pcoIntegrateFire_t_ref", 0.05)
co.set("pcoIntegrateFire_alpha", 0.9)


net = co.network()




rewiring = 0.5
coupling = 0.012

#n.useLatticePositioning(100,100);

net.torusNearestNeighbors(40,40,36.0, co.pcoIntegrateFire(), co.weightedEdge())

net.rewire(rewiring)

net.randomizeStates(co.pcoIntegrateFire(), co.uniform(0.0,1.0));
net.randomizeWeights(co.uniform(coupling,coupling));

net.saveAdjacencyList("output/nonconverging.py.graph");

net.observeTime("output/nonconverging.py.phaseCoherence");
net.observePhaseCoherence("output/nonconverging.py.phaseCoherence");
net.evolve(0.0,100.0);

