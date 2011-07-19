import conedy as co

net = co.network()

nodeNumber = net.addNode(co.roessler())

net.observe (nodeNumber, "output/removeObserver.py.series")
net.removeObserver()

net.evolve(0.0,100.0)  # This command should not write values to the file.


