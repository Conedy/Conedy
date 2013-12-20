import conedy as co

N = co.network()


N.randomNetwork (10, 0.2, co.node(), co.weightedEdge());

N.saveAdjacencyMatrix("output/saveAdjacencyMatrix.py.mat")
N.clear()
N.createFromAdjacencyMatrix("output/saveAdjacencyMatrix.py.mat")

N.saveAdjacencyMatrix("output/saveAdjacencyMatrix.py.mat2")

