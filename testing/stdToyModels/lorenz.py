import conedy as co


N = co.network()

co.set("lorenz_S", 10.0)
co.set("lorenz_r", 28.0)
co.set("lorenz_b", 8.0/3.0)
co.set("samplingTime" , 0.01)


N.addNode(co.lorenz())
N.setState(0, 1.0, 1.0, 1.0)
N.observeTime("output/lorenz.py.series")
N.observeAll("output/lorenz.py.series", co.component(0))
N.observeAll("output/lorenz.py.series", co.component(1))
N.observeAll("output/lorenz.py.series", co.component(2))


N.evolve(0.0,1500.0)
