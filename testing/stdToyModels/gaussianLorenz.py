import conedy as co

net = co.network()


co.setRandomSeed(0)
co.set("gaussianLorenz_S", 10.0)
co.set("gaussianLorenz_r", 28.0)
co.set("gaussianLorenz_b", 8.0/3.0)
co.set("gaussianLorenz_sigmaNoise", 10.0)
co.set("samplingTime", 0.01)


net.addNode(co.gaussianLorenz())
net.setState(0, 1.0, 1.0, 1.0)

net.observeTime("output/gaussianLorenz.py.series")
net.observeAll("output/gaussianLorenz.py.series", co.component(0))
net.observeAll("output/gaussianLorenz.py.series", co.component(1))
net.observeAll("output/gaussianLorenz.py.series", co.component(2))


net.evolve(0.0,1500.0)
