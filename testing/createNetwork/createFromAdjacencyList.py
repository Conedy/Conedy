import conedy as co

net = co.network()


#net.completeNetwork (10, co.node(), co.weightedEdge());
net.completeNetwork(10)

net.saveAdjacencyList("output/createFromAdjacencyList.py.mat")
net.clear()
net.createFromAdjacencyList("output/createFromAdjacencyList.py.mat", co.node(), co.weightedEdge() )

net.saveAdjacencyList("output/createFromAdjacencyList.py.mat2")

