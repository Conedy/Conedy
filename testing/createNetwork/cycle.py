import conedy as co



co.setRandomSeed(0)

N = co.network()


N.cycle(1000,50, co.node(), co.weightedEdge())   # Creates a closed chain of 1000 nodes where each is connected to its 50 nearest neighbors to each side.


print "should be close to 0.75:" + str ( N.meanClustering() ) 
print "should be close to " + str (1000.0/ 2 / 100) +":" + str ( N.meanPathLength() )  
print "should be 100:" + str ( N.meanDegree() ) 
