import conedy as co


net = co.network()

co.set("lorenz_s", 10.0)
co.set("lorenz_r", 28.0)
co.set("lorenz_b", 8.0/3.0)
co.set("dynNetwork_ioNodeDt" , 0.01)


net.addNode(co.lorenz())
net.setState(0, 1.0, 1.0, 1.0)
net.observeTime("output/lorenz.py.series")
net.observeAll("output/lorenz.py.series", co.component(0))
net.observeAll("output/lorenz.py.series", co.component(1))
net.observeAll("output/lorenz.py.series", co.component(2))


net.evolve(0.0,1500.0)
