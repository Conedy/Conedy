import conedy as co



co.setRandomSeed(0)

net = co.network()


net.cycle(1000,50, co.node(), co.weightedEdge())   # Creates a closed chain of 100 nodes where each is connected to its 10 nearest neighbors to each side.


print "should be close to 0.75:" + str ( net.meanClustering() ) 
print "should be close to " + str (1000.0/ 2 / 100) +":" + str ( net.meanPathLength() )  
print "should be 100:" + str ( net.meanDegree() ) 
