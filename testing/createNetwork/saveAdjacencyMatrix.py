import conedy as co

net = co.network()


net.randomNetwork (10, 0.2, co.node(), co.weightedEdge());

net.saveAdjacencyMatrix("output/saveAdjacencyMatrix.py.mat")
net.clear()
net.createFromAdjacencyMatrix("output/saveAdjacencyMatrix.py.mat")

net.saveAdjacencyMatrix("output/saveAdjacencyMatrix.py.mat2")

