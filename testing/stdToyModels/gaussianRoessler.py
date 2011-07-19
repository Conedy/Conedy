import conedy as co


net = co.network()

co.set("gaussianRoessler_omega" , 0.89)
co.set("gaussianRoessler_a" , 0.165)
co.set("gaussianRoessler_b" , 0.2)
co.set("gaussianRoessler_c" , 10.0)
co.set("gaussianRoessler_sigmaNoise", 1.0)
co.set("dynNetwork_ioNodeDt" , 0.01)



net.addNode(co.gaussianRoessler())
net.setState(0, 0.0, 0.0, 0.0)
net.observeTime("output/gaussianRoessler.py.series")
net.observeAll("output/gaussianRoessler.py.series", co.component(0))
net.observeAll("output/gaussianRoessler.py.series", co.component(1))
net.observeAll("output/gaussianRoessler.py.series", co.component(2))
net.evolve(0.0,1500.0)


