import conedy as co

N = co.network()

i = N.cycle(20, 1, co.node(), co.weightedEdge())

N.addEdge(i + 1, i + 7, co.weightedEdge(1.0))
N.addEdge(i + 7, i + 1, co.weightedEdge(2.0))
N.addEdge(i + 1, i +11, co.weightedEdge(3.0))
N.addEdge(i +11, i + 1, co.weightedEdge(4.0))


N.degreeCentrality("output/degreeCentrality.py.out")
