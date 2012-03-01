
import conedy as co


net = co.network();


net.cycle (100,10, co.node(), co.weightedEdge());
print "should be 20:"+ str(net.meanDegree())
net.saveAdjacencyList("output/rewireWeights.co.before");


net.rewireWeights(0.5, co.uniform (2.0,2.0));

net.saveAdjacencyList("output/rewireWeights.co.after");
print "should be close to 1.5:"+ str(net.meanWeight())

