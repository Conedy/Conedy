import conedy as co

N = co.network()


N.completeNetwork (10, co.node(), co.weightedEdge());

N.saveAdjacencyMatrix("output/createFromAdjacencyMatrix.py.mat")
N.clear()
N.createFromAdjacencyMatrix("output/createFromAdjacencyMatrix.py.mat")

N.saveAdjacencyMatrix("output/createFromAdjacencyMatrix.py.mat2")




