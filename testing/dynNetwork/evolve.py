
import conedy as co

N = co.network()


N.addNode(co.roessler())
N.evolve(0.0,100.0)
