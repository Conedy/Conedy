import conedy as co

N=co.network()

N.addNode(co.node())
N.addNode(co.node())

N.addEdge(0, 1, co.weightedEdge(0.1))
N.isLinked(0, 1)

N.removeEdge(0, 1, co.weightedEdge(0.1))   
N.isLinked(0, 1)

