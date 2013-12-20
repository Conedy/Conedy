import conedy as co

N = co.network()


#N.completeNetwork (10, co.node(), co.weightedEdge());
N.completeNetwork(10)

N.saveAdjacencyList("output/createFromAdjacencyList.py.mat")
N.clear()
N.createFromAdjacencyList("output/createFromAdjacencyList.py.mat", co.node(), co.weightedEdge() )

N.saveAdjacencyList("output/createFromAdjacencyList.py.mat2")

