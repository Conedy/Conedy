import conedy as co
N = co.network()
co.set ("roessler_a", 0.22)
co.set ("roessler_b", 0.1)
co.set ("roessler_c", 8.5)
r1 = N.addNode(co.roessler())
r2 = N.addNode(co.roessler())
r3 = N.addNode(co.roessler())
N.setParam(r1, "roessler_omega", 1.02)
N.setParam(r2, "roessler_omega", 1.0)
N.setParam(r3, "roessler_omega", 0.98)
N.randomizeStates (co.roessler(), co.uniform (-10.0, 10.0),co.uniform (-5.0, 5.0), co.uniform (-0.5, 1.5))
N.addEdge(r1, r2, co.weightedEdge(0.075))
N.addEdge(r2, r1, co.weightedEdge(0.075))
N.addEdge(r1, r3, co.weightedEdge(0.075))
N.addEdge(r3, r1, co.weightedEdge(0.075))
N.evolve(0.0, 100.0)
N.observeTime("roessler.dat")
N.observe(r1, "roessler.dat", co.component(1))
N.observe(r2, "roessler.dat", co.component(1))
N.observe(r3, "roessler.dat", co.component(1))
co.set("samplingTime", 0.01)
N.evolve(100.0, 200.0)

