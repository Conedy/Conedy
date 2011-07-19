import conedy as co

net = co.network()


net.completeNetwork (10, co.node(), co.weightedEdge());

net.saveAdjacencyList("output/saveAdjacencyList.py.mat")
net.clear()
net.createFromAdjacencyList("output/saveAdjacencyList.py.mat")

net.saveAdjacencyList("output/saveAdjacencyList.py.mat2")

