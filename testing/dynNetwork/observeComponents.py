import conedy as co

N = co.network()

nodeNumber = N.addNode(co.roessler())

N.observeComponents(nodeNumber, "output/observeComponents.py.initalCond")
N.snapshot()
