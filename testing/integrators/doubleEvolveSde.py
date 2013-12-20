import conedy as co

N = co.network()


N.addNode(co.ornUhl())
N.observeTime("output/doubleEvolveSde.py.series")
N.observeAll("output/doubleEvolveSde.py.series", co.component(0) )
N.evolve(0.0,1.0)
N.evolve(1.0, 2.0)



