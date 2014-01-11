import conedy as co

N = co.network()

co.set("roessler_omega", 20.0)
co.set("roessler_a", 0.165)
co.set("roessler_b", 0.2)
co.set("roessler_c", 10.0)
co.set("lorenz_S", 10.0)
co.set("lorenz_r", 28.0)
co.set("lorenz_b", 8.0/3.0)

co.set("samplingTime", 0.01)

i = N.addNode(co.roessler())
j = N.addNode(co.lorenz())

N.addEdge(i, j, co.weightedEdge(2.5))


N.setState(i, 0.0, 0.0, 0.0)
N.setState(j, 1.0, 1.0, 1.0)

N.observeTime("output/roesslerLorenzCoupled.py.series")
N.observe(i,"output/roesslerLorenzCoupled.py.series",co.component(0))
N.observe(i,"output/roesslerLorenzCoupled.py.series",co.component(1))
N.observe(i,"output/roesslerLorenzCoupled.py.series",co.component(2))
N.observe(j,"output/roesslerLorenzCoupled.py.series",co.component(0))
N.observe(j,"output/roesslerLorenzCoupled.py.series",co.component(1))
N.observe(j,"output/roesslerLorenzCoupled.py.series",co.component(2))


N.evolve(0.0,1500.0)
