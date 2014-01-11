import conedy as co

N = co.network()

co.set("roessler_omega", 0.89)
co.set("roessler_a", 0.165)
co.set("roessler_b", 0.2)
co.set("roessler_c", 10.0)

co.set("samplingTime", 0.01)


N.addNode(co.roessler())

#co.set("roessler_omega", 1.0)

N.setParam (0, "roessler_omega", 1.0);

N.addNode(co.roessler())


#N.addWeightedEdge(0,1,0.5)
#N.addWeightedEdge(1,0,0.5)
N.addEdge(0,1,co.weightedEdge(0.5))
N.addEdge(1,0,co.weightedEdge(0.5))



N.setState(0, 0.0,0.0,0.0)
N.setState(1, 1.0,1.0,0.0)

N.printNodeStatistics();


N.observeTime("output/roesslerRoesslerCoupled.py.series")

N.observe(0,"output/roesslerRoesslerCoupled.py.series", co.component(0))
N.observe(0,"output/roesslerRoesslerCoupled.py.series", co.component(1))
N.observe(0,"output/roesslerRoesslerCoupled.py.series", co.component(2))

N.observe(1,"output/roesslerRoesslerCoupled.py.series", co.component(0))
N.observe(1,"output/roesslerRoesslerCoupled.py.series", co.component(1))
N.observe(1,"output/roesslerRoesslerCoupled.py.series", co.component(2))


N.evolve(0.0,1500.0)
