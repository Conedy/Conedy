import conedy as co

N = co.network()

nodeNumber = N.addNode(co.roessler())

N.observe (nodeNumber, "output/removeObserver.py.series")
N.removeObserver()

N.evolve(0.0,100.0)  # This command should not write values to the file.


