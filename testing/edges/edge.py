

network net;




int firstNode;
int secondNode;




firstNode = net.addNode<roessler>();
secondNode = net.addNode<roessler>();

net.addEdge (firstNode,secondNode, 1.0, component (2) );


net.printNodeStatistics();

