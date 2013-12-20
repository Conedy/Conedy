import conedy as co

N = co.network()


newNodeNumber = N.addNode( co.roessler() )


N.observeTime("output/evolve3.py.series")
N.observe(newNodeNumber, "output/evolve3.py.series")


N.evolve(0.0,3.0)
N.evolve(5.0,13.0)

N.evolve (-0.1, 0.0)
