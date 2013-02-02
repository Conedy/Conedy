import conedy as co
import numpy as np

N = co.network()

co.set("outputBinary", True)
co.set("samplingTime" , 0.015)

N.observeTime("output/writeBinary.py.time")

N.evolve(0.0,10.0)
N.removeObserver()

print np.fromfile("output/writeBinary.co.time", dtype=np.float64)
