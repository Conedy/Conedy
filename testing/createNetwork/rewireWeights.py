
import conedy as co


N = co.network();


N.cycle (100,10, co.node(), co.weightedEdge());
print "should be 20:"+ str(N.meanDegree())
N.saveAdjacencyList("output/rewireWeights.co.before");


N.rewireWeights(0.5, co.uniform (2.0,2.0));

N.saveAdjacencyList("output/rewireWeights.co.after");
print "should be close to 1.5:"+ str(N.meanWeight())

