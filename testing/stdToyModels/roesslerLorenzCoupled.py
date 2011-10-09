import conedy as co

net = co.network()

co.set("roessler_omega", 29.0)
co.set("roessler_a", 0.165)
co.set("roessler_b", 0.2)
co.set("roessler_c", 10.0)
co.set("lorenz_S", 10.0)
co.set("lorenz_r", 28.0)
co.set("lorenz_b", 8.0/3.0)

co.set("dynNetwork_ioNodeDt", 0.01)


net.addNode(co.roessler())
net.addNode(co.lorenz())

net.addEdge(1,0,co.weightedEdge(2.5))


net.setState(0, 0.0,0.0,0.0  )
net.setState(1, 1.0,1.0,1.0  )


net.observeTime("output/roesslerLorenzCoupled.py.series")
net.observe(0,"output/roesslerLorenzCoupled.py.series",co.component(0))
net.observe(0,"output/roesslerLorenzCoupled.py.series",co.component(1))
net.observe(0,"output/roesslerLorenzCoupled.py.series",co.component(2))
net.observe(1,"output/roesslerLorenzCoupled.py.series",co.component(0))
net.observe(1,"output/roesslerLorenzCoupled.py.series",co.component(1))
net.observe(1,"output/roesslerLorenzCoupled.py.series",co.component(2))


net.evolve(0.0,1500.0)

