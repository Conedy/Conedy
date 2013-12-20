import conedy as co

N = co.network()


newNodeNumber = N.addNode( co.roessler() )


N.observe(newNodeNumber, "output/snapshot.py.series", co.component(0))
N.observe(newNodeNumber, "output/snapshot.py.series", co.component(1))
N.observe(newNodeNumber, "output/snapshot.py.series", co.component(2))

N.snapshot()


