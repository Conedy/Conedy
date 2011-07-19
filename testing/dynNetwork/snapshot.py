import conedy as co

net = co.network()


newNodeNumber = net.addNode( co.roessler() )


net.observe(newNodeNumber, "output/snapshot.py.series", co.component(0))
net.observe(newNodeNumber, "output/snapshot.py.series", co.component(1))
net.observe(newNodeNumber, "output/snapshot.py.series", co.component(2))

net.snapshot()


