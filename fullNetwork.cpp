


#include "fullNetwork.h"


namespace conedy {




 node *	getStaticNode (node *n, edgeVirtual *l )
{
/*	networkElementType nt = n->getNodeInfo().theNodeType;
	networkElementType et = l->getEdgeInfo().theEdgeType;

	node * ret;
		ret = n;

	if (nt == _pcoIFNeuron_) {
		if (et == _weightedEdge_)
			ret = new nodeTemplateEdges <weightedEdge <edge>, pcoIFNeuron, pcoIFNeuron>();
		if (et == _staticWeightedEdge_)
			ret = new nodeTemplateEdges <staticWeightedEdge <edge>, pcoIFNeuron, pcoIFNeuron>();
	}
	else if (nt == _pcoIFNeuronDelay_) {
		if (et == _staticWeightedEdge_)
			return new nodeTemplateEdges <staticWeightedEdge <edge>, pcoIFNeuronDelay, pcoIFNeuronDelay>();
	}
	else if (nt == _pcoMirollo_) {
		if (et == _staticWeightedEdge_)
			ret = new nodeTemplateEdges <staticWeightedEdge <edge>, pcoMirollo, pcoMirollo>();
	}
	else if (nt == _pcoNonleaky_) {
		if (et == _staticWeightedEdge_)
			ret = new nodeTemplateEdges <staticWeightedEdge <edge>, pcoNonleaky, pcoNonleaky>();
	}

//	ret->row = n.row;

	return  ret;
*/
	return NULL;
}


}

