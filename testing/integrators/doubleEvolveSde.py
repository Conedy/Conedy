import conedy as co

net = co.network()


net.addNode(co.ornUhl())
net.observeTime("output/doubleEvolveSde.py.series")
net.observeAll("output/doubleEvolveSde.py.series", co.component(0) )
net.evolve(0.0,1.0)
net.evolve(1.0, 2.0)



