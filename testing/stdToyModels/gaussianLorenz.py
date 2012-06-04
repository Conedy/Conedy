import conedy as co

N = co.network()


co.setRandomSeed(0)
co.set("gaussianLorenz_S", 10.0)
co.set("gaussianLorenz_r", 28.0)
co.set("gaussianLorenz_b", 8.0/3.0)
co.set("gaussianLorenz_sigmaNoise", 10.0)
co.set("samplingTime", 0.01)


N.addNode(co.gaussianLorenz())
N.setState(0, 1.0, 1.0, 1.0)

N.observeTime("output/gaussianLorenz.py.series")
N.observeAll("output/gaussianLorenz.py.series", co.component(0))
N.observeAll("output/gaussianLorenz.py.series", co.component(1))
N.observeAll("output/gaussianLorenz.py.series", co.component(2))


N.evolve(0.0,1500.0)
