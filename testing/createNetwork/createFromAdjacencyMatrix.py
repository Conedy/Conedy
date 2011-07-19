import conedy as co

net = co.network()


net.completeNetwork (10, co.node(), co.weightedEdge());

net.saveAdjacencyMatrix("output/createFromAdjacencyMatrix.py.mat")
net.clear()
net.createFromAdjacencyMatrix("output/createFromAdjacencyMatrix.py.mat")

net.saveAdjacencyMatrix("output/createFromAdjacencyMatrix.py.mat2")




