import conedy as co


N = co.network()

co.set("samplingTime" , 0.01)
co.set("roessler_omega" , 0.89)
co.set("roessler_a" , 0.165)
co.set("roessler_b" , 0.2)
co.set("roessler_c" , 10.0)



N.addNode(co.roessler())
N.setState(0, 0.0, 0.0, 0.0)
N.observeTime("output/roessler.py.series")
N.observeAll("output/roessler.py.series", co.component(0))
N.observeAll("output/roessler.py.series", co.component(1))
N.observeAll("output/roessler.py.series", co.component(2))


N.evolve(0.0,1500.0)
