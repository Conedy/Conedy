import conedy as co

net = co.network()


net.completeNetwork (10, co.node(), co.weighedEdge());

net.saveAdjacencyList("output/createFromAdjacencyList.py.mat")
net.clear()
net.createFromAdjacencyList("output/createFromAdjacencyList.py.mat")

net.saveAdjacencyList("output/createFromAdjacencyList.py.mat2")

