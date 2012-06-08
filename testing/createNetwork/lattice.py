
import conedy as co

N = co.network()

N.lattice (40,40,1.5, co.node(), co.weightedEdge()) #creates a lattice of nodes, where each is connected to its 8 (4 direct, 4 diagonal) nearest neighbors

print "should be slightly smaller than 8:" + str(N.meanDegree())
print "should be close to "+ str(12.0/28) +":" + str(N.meanClustering())








