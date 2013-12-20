import conedy as co


N = co.network()


N.completeNetwork (10, co.node(), co.weightedEdge());

N.saveGraphML("output/saveGraphML.py.graph")


#N.clear()
#N.createFromAdjacencyList("output/createFromAdjacencyList.py.mat")

#N.saveAdjacencyList("output/createFromAdjacencyList.py.mat2")

