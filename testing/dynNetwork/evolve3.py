import conedy as co

net = co.network()


newNodeNumber = net.addNode( co.roessler() )


net.observeTime("output/evolve3.py.series")
net.observe(newNodeNumber, "output/evolve3.py.series")


net.evolve(0.0,3.0)
net.evolve(5.0,13.0)

net.evolve (-0.1, 0.0)
