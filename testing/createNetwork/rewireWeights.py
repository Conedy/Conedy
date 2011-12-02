
import conedy as co


net = co.network();


net.cycle (100,10, node(), weightedEdge());
print "should be 20:"+ net.meanDegree()+ newline;
net.saveAdjacencyList("output/rewireWeights.co.before");


net.rewire(0.5, co.uniform (2.0,2.0));

net.saveAdjacencyList("output/rewireWeights.co.after");
print "should be close to 1.5:"+ net.meanWeight()+ "\n";
