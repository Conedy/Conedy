
import conedy as co
import numpy as np

N = co.network()

co.set("outputBinary", True)
co.set("samplingTime" , 0.015)

N.observePhaseCoherence("output/writeBinaryPhaseCoherence.py.inf");

N.evolve(0.0,10.0)
N.removeObserver()

print np.fromfile("output/writeBinaryPhaseCoherence.py.inf", dtype=np.float64)




