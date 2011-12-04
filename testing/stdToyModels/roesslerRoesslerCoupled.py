import conedy as co

net = co.network()

co.set("roessler_omega", 0.89)
co.set("roessler_a", 0.165)
co.set("roessler_b", 0.2)
co.set("roessler_c", 10.0)

co.set("samplingTime", 0.01)


net.addNode(co.roessler())

#co.set("roessler_omega", 1.0)

net.setParam (0, "roessler_omega", 1.0);

net.addNode(co.roessler())


#net.addWeightedEdge(0,1,0.5)
#net.addWeightedEdge(1,0,0.5)
net.addEdge(0,1,co.weightedEdge(0.5))
net.addEdge(1,0,co.weightedEdge(0.5))



net.setState(0, 0.0,0.0,0.0)
net.setState(1, 1.0,1.0,0.0)

net.printNodeStatistics();


net.observeTime("output/roesslerRoesslerCoupled.py.series")

net.observe(0,"output/roesslerRoesslerCoupled.py.series", co.component(0))
net.observe(0,"output/roesslerRoesslerCoupled.py.series", co.component(1))
net.observe(0,"output/roesslerRoesslerCoupled.py.series", co.component(2))

net.observe(1,"output/roesslerRoesslerCoupled.py.series", co.component(0))
net.observe(1,"output/roesslerRoesslerCoupled.py.series", co.component(1))
net.observe(1,"output/roesslerRoesslerCoupled.py.series", co.component(2))


net.evolve(0.0,1500.0)
