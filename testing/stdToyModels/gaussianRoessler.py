import conedy as co


N = co.network()

co.set("gaussianRoessler_omega" , 0.89)
co.set("gaussianRoessler_a" , 0.165)
co.set("gaussianRoessler_b" , 0.2)
co.set("gaussianRoessler_c" , 10.0)
co.set("gaussianRoessler_sigmaNoise", 1.0)
co.set("samplingTime" , 0.01)



N.addNode(co.gaussianRoessler())
N.setState(0, 0.0, 0.0, 0.0)
N.observeTime("output/gaussianRoessler.py.series")
N.observeAll("output/gaussianRoessler.py.series", co.component(0))
N.observeAll("output/gaussianRoessler.py.series", co.component(1))
N.observeAll("output/gaussianRoessler.py.series", co.component(2))
N.evolve(0.0,1500.0)


