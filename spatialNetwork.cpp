

#include "spatialNetwork.h"



namespace conedy
{
//nodeDescriptor spatialNetwork::addNode()
//{

//	return network::addNode();

//}



void spatialNetwork::connectCloseNodes(node *source, node * target, baseType dist, edgeBlueprint *l)
{
	int sourceNodeType = source->getNodeInfo().theNodeType;

	int targetNodeType = target->getNodeInfo().theNodeType;

	nodeList sources, targets;
	nodeIterator si, ti;
	verticesMatching(sources, sourceNodeType);
	verticesMatching(targets, targetNodeType);

	double distance = dist * dist;

	for (si = sources.begin(); si != sources.end(); si++)
		for (ti = targets.begin(); ti != targets.end(); ti++)
			if ((euclidianDistance(*si, *ti) < distance) && (*si != *ti))
				addEdge(*si, *ti, l);
}

void spatialNetwork::connectCloseNodesTorus(node *source, node * target, baseType dist, edgeBlueprint *l)
{
	int sourceNodeType = source->getNodeInfo().theNodeType;

	int targetNodeType = target->getNodeInfo().theNodeType;

	nodeList sources, targets;
	nodeIterator si, ti;
	verticesMatching(sources, sourceNodeType);
	verticesMatching(targets, targetNodeType);

	double distance = dist * dist;

	for (si = sources.begin(); si != sources.end(); si++)
		for (ti = targets.begin(); ti != targets.end(); ti++)
			if ((euclidianDistanceTorus(*si, *ti) < distance) && (*si != *ti))
				addEdge(*si, *ti, l);
}






nodeDescriptor spatialNetwork::addNode( nodeBlueprint *n)
{
	if ((n->getNodeInfo().theNodeKind == _dynNode_) && nodePositioner != NULL)
	{
		nodePos.push_back(nodePositioner->getNodePosition());
		return network::addNode(n);
	}
	else
		return network::addNode(n);


}


};
