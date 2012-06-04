import conedy as co

N = co.network()


N.completeNetwork (10, co.node(), co.weighedEdge());

N.saveAdjacencyList("output/createFromAdjacencyList.py.mat")
N.clear()
N.createFromAdjacencyList("output/createFromAdjacencyList.py.mat")

N.saveAdjacencyList("output/createFromAdjacencyList.py.mat2")

