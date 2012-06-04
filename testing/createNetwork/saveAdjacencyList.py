import conedy as co

N = co.network()


N.completeNetwork (10, co.node(), co.weightedEdge());

N.saveAdjacencyList("output/saveAdjacencyList.py.mat")
N.clear()
N.createFromAdjacencyList("output/saveAdjacencyList.py.mat")

N.saveAdjacencyList("output/saveAdjacencyList.py.mat2")

