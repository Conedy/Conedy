#include "network.h"
#include "containerNode.h"

#include "eventHandler.h"
#include "nodeImplement.h"

#include <fstream>

namespace conedy
{



	void network::addEdges(nodeDescriptor source, nodeDescriptor target, edgeBlueprint *l)
	{
		addEdge(source,target,l);
	}




	void network::addEdge(nodeDescriptor source, nodeDescriptor target, edgeBlueprint *l)
	{
		if (directed)
			link (source,target, l);
		else
		{	
			link (source,target, l);
			link (target,source, l);
		}


	}


	void network::addWeightedEdge(nodeDescriptor source, nodeDescriptor target, baseType weight)
	{
		if (directed)
			link (source,target, weight);
		else
		{	
			link (source,target, weight);
			link (target,source, weight);
		}


	}



	void network::replaceNode(nodeDescriptor nodeNumber, nodeBlueprint *n)
	{
		throw "replaceNodes is a stub";
	}



	void network::removeEdges (edgeBlueprint * e)
	{
		edgeList el;
		networkElementType edgeType = ((edgeVirtual*) e) -> getEdgeInfo().theEdgeType;

		edgesMatching(el, edgeType);
		edgeIterator ei;
		for (ei = el.begin(); ei != el.end(); ei++)
			remove(*ei);
		clean(); // unsinnXXX todo

	}



	void network::clean ( )
	{
		evolveList.clear();
		upkeepList.clear();

		dynNode *nod;
		nodeList vl;
		nodeIterator it;
		verticesMatching(vl,_dynNode_);
		for (it = vl.begin(); it != vl.end(); it ++)
		{

			nod = ( dynamic_cast<dynNode*>( node::theNodes[*it]));
			nod->clean ( );
			if ( nod->timeEvolution() )
				evolveList.push_back ( nod );
			if ( nod->requiresUpkeep())
				upkeepList.push_back (nod);

		}

	}

	bool network::isDirected()
	{

		nodeIterator vi, vj;
		network::nodeList vl;
		verticesMatching(vl, _dynNode_ );

		bool res = false;

		for(vi=vl.begin(); vi!=vl.end(); vi++)
		{
			for(vj=vl.begin(); vj!=vi; vj++)
			{
				if( network::linkStrength(*vi,*vj) != network::linkStrength(*vj,*vi) )
				{
					res = true;
					break;
				}
			}
		}

		return res;
	}





	void network::verticesMatching(nodeList &res, node *n)
	{
		// TODO bug ?
		//		throw "stub verticesSimilar";
		if (n == network::stdNode)
			verticesMatching (res, _dynNode_);
		else
		{
			networkElementType nodeType= n->getNodeInfo().theNodeType;
			nodeIterator vi;
			for(vi = theNodes.begin(); vi != theNodes.end();vi++)                      // if n has standard parameter -> match if node type is equal
			{
				dynNode *x = (dynNode*)node::theNodes[*vi];
				if ( ((dynNode*)  n)->isStandard())
				{
					if (node::theNodes[*vi]->getNodeInfo().theNodeType == nodeType)
						res.insert(*vi);
				}
				else 																							// if n has	specified parameter -> match after node type and parameters
				{
					if ((node::theNodes[*vi]->getNodeInfo().theNodeType == nodeType) &&
							((  x-> row == ((dynNode*)n)-> params<baseType>::row) || ( x->compareSheets( x-> row    , ((dynNode*)n)-> params<baseType>::row)  )))   // match nodes, if their parameter are the same.
						res.insert(*vi);
				}
			}
		}
	}


	//		for (unsigned int i = 0; i < theNodes.size(); i++)
	//			if (theNodes[i]->equals(n))
	//				res.push_back(i);
	//	}

void network::verticesMatching(nodeList &res, nodeKind nodeKind)
{
	nodeIterator vi;
	for(vi = theNodes.begin(); vi != theNodes.end();vi++)
		if (node::theNodes[*vi]->getNodeInfo().theNodeKind & nodeKind)
			res.insert(*vi);
}

void network::edgesMatching (edgeList &res, networkElementType edgeType)
{
	node::edgeDescriptor ea,ee;
	nodeIterator vi;

	for (vi = theNodes.begin(); vi != theNodes.end();vi++)
	{
		ea = 0;
		ee = node::theNodes[*vi]->degree();
		for (; ea != ee; ea++)
			if (((edgeVirtual*)node::theNodes[*vi]->getEdge(ea)   )->getEdgeInfo().theEdgeType == edgeType)
				if (isInsideNetwork((node::theNodes[*vi])->getTarget(ea)))
					res.push_back (make_pair(*vi,ea));

	}
}

//! Fügt der Liste res alle Knoten vom Typ nodetyp hinzu.
void network::verticesMatching(nodeList &res, int networkElementType)
{
	nodeIterator vi;
	for(vi = theNodes.begin(); vi != theNodes.end();vi++)
		if (node::theNodes[*vi]->getNodeInfo().theNodeType == networkElementType)
			res.insert(*vi);
}



void network::addEdges (nodeDescriptor source, nodeKind targetNodeKind, edgeBlueprint *l)
{
	nodeIterator it;
	nodeList vl;
	verticesMatching(vl,targetNodeKind);
	for (it = vl.begin(); it != vl.end(); it++)
		addEdge(source, *it, l);



}


void network::addEdges (nodeKind sourceNodeKind, nodeDescriptor target, edgeBlueprint *l)
{
	nodeIterator it;
	nodeList vl;
	verticesMatching(vl,sourceNodeKind);
	for (it = vl.begin(); it != vl.end(); it++)
		addEdge(*it,target, l);



}



void network::addEdges (nodeDescriptor source, int targetNodeType, edgeBlueprint *l)
{
	nodeIterator it;
	nodeList vl;
	verticesMatching(vl,targetNodeType);
	for (it = vl.begin(); it != vl.end(); it++)
		addEdge(source, *it, l);




}

/*


	void network::edgeToHiddenVariable ( int s, int t, baseType weight )
	{
	if ( theNodes[t]->getNodeInfo().theNodeKind & _dynNode_ )
	{
	observeEdge <baseType> *e = new observeEdge<baseType> ( theNodes[s], theNodes[t],weight );
	theNodes[s]->addLink ( e );
	}
	else
	{
	cout << "Fehler! Node ist nicht vom Typ _dynNode_.";
	exit ( 1 );
	}
	}
	*/

bool network::isInsideNetwork (nodeDescriptor v)
{
	return theNodes.count(v);


}

void network::edgesBetween(edgeList &res, networkElementType sourceNodeType, networkElementType targetNodeType)
{
	nodeList vl;
	verticesMatching (vl, sourceNodeType);
	for (nodeIterator va = vl.begin(); va != vl.end(); va++)
			edgesBetween(res, node::theNodes[*va]->getNumber(), sourceNodeType);

}

void network::edgesBetween(list< edgeDescriptor > &res, nodeKind sourceNodeKind, nodeKind targetNodeKind)
{
	nodeIterator va;
	nodeList vl;
	verticesMatching (vl, sourceNodeKind);
	for (va = vl.begin(); va != vl.end(); va++)
			edgesBetween(res, node::theNodes[*va]->getNumber(), targetNodeKind);
}




void network::select ( string fileName)
{
	ifstream in(fileName.c_str());
	unsigned int i;
	theNodes.clear();
	while (in.peek() != -1)
	{
		in >> i;
		theNodes.insert(i);
	}
}
void network::edgesBetween(list< edgeDescriptor > &res, nodeDescriptor sourceNode, nodeKind targetNodeKind)
{
	node::edgeDescriptor ea,ee;

	ea = 0;
	ee = node::theNodes[sourceNode]->degree();
	for (; ea != ee; ea++)
		if (match (node::theNodes[sourceNode]->getTarget(ea), targetNodeKind))
			if (isInsideNetwork( node::theNodes[sourceNode]->getTarget(ea) ))
				res.push_back (make_pair(sourceNode,ea));
}


void network::edgesBetween(list< edgeDescriptor > &res, nodeDescriptor sourceNode, networkElementType targetNodeType)
{
	node::edgeDescriptor ea,ee;
	ea = 0;
	ee = node::theNodes[sourceNode]->degree();
	for (; ea != ee; ea++)
		if (match (node::theNodes[sourceNode]->getTarget(ea), targetNodeType))
			res.push_back (make_pair(sourceNode,ea));
}
void network::edgesBetween(list<edgeDescriptor> &res, nodeBlueprint *sourceNode, nodeBlueprint *targetNode)
{

	nodeIterator va;

	//		edgeIterator ea,ee;
	for (va = theNodes.begin(); va != theNodes.end(); va++)
	{
		if ( match ( sourceNode,*va ))
			edgesBetween(res, *va, targetNode);
	}
}

void network::edgesBetween(list<edgeDescriptor> &res, nodeDescriptor sourceNode, nodeBlueprint *targetNode)
{

	node::edgeDescriptor ea,ee;
	ea = 0;
	ee = node::theNodes[sourceNode]->degree();
	for (; ea != ee; ea++)
		if (match (node::theNodes[sourceNode]->getTarget(ea), targetNode))
			res.push_back (make_pair(sourceNode,ea));

}


void network::edgesBetween(list< edgeDescriptor > &res, nodeKind sourceNodeKind, nodeDescriptor targetNode)
{
	throw "edgesBetween for sourceNodkind and targetNode not implemented. ";
}



unsigned int network::numberVertices (nodeBlueprint * n )
{
	nodeList vl;
	verticesMatching (vl,n);
	return vl.size();
}


void network::removeNodes (nodeBlueprint *n)
{
	nodeList vl;

	verticesMatching (vl, n);
	nodeIterator vi;

	for (vi = vl.begin(); vi != vl.end(); vi++ )
	{
			delete node::theNodes[*vi];
			node::theNodes[*vi] = 0; // remove from lookup table in node
			theNodes.erase (*vi);  // remove from the network
	}
}



void network::remove ( nodeKind theNodeKind )
{
	nodeList vl;

	verticesMatching (vl, theNodeKind);
	nodeIterator vi;

	for (vi = vl.begin(); vi != vl.end(); vi++ )
	{
			delete node::theNodes[*vi];
			node::theNodes[*vi] = 0; // remove from lookup table in node
			theNodes.erase (*vi);  // remove from the network
	}

}











//

unsigned int network::randomNode(nodeKind nodeKind)
{
	int res;
	do			// Vorsicht Endlosschleife
	{
		res = noise.getUniformInt( 0, node::theNodes.size() -1);

	} while (node::theNodes[res] == NULL
			|| ( !(nodeKind & node::theNodes[res]->getNodeInfo().theNodeKind))
			|| (!isInsideNetwork(res)) );

	return	res;
}



void network::randomizeWeights (function<baseType()> r, nodeBlueprint *n1 , nodeBlueprint *n2 )

  {

	network::edgeList toChange;

	edgesBetween(toChange,n1, n2);
	edgeIterator it;
	for (it = toChange.begin(); it != toChange.end(); it++)
		if (getEdgeInfo(*it).theEdgeKind & _weighted_)
			setWeight(*it,r());
}





//
network::network(): directed(true)
{
	numberOfNodes = 0;
}


network::network(bool directedNess): directed(directedNess)
{
	numberOfNodes = 0;
}


network::~network()
{
	nodeIterator it;


	for ( it = theNodes.begin(); it != theNodes.end(); it++ )
		delete ( node::theNodes[*it] );
}



nodeDescriptor network::addNode ( nodeBlueprint *n )
{
	node  *newNode = n->construct();

	nodeDescriptor newNodeNumber = newNode->getNumber();
	if (n->getNodeInfo().theNodeKind & _inNode_)
		inOutNodeList.push_back (  (dynNode*)   node::theNodes[newNodeNumber]);


	//cout << ((cnnNode<baseType>*) n )-> row << endl;
	theNodes.insert ( newNodeNumber );
	numberOfNodes++;
	//cout << ((cnnNode<baseType>*) theNodes[theNodes.size() - 1] )-> row << endl;
	return  newNodeNumber;
}

void network::link ( nodeDescriptor s, nodeDescriptor t, baseType weight )
{

	nodeKind nk = node::theNodes[s]->getNodeInfo().theNodeKind;
	if (nk & _ode_ || nk & _sde_ || nk & _mapNode_)
		node::theNodes[t]->link ( s, weight );
	else
		node::theNodes[s]->link ( t, weight );


	//	networkType = networkType & ( 0 - 1 - directed );
}


baseType network::linkStrength ( nodeDescriptor i, nodeDescriptor j ) 
{
	nodeKind nk = node::theNodes[i]->getNodeInfo().theNodeKind;
	if (nk & _ode_ || nk & _sde_ || nk & _mapNode_)
		return node::theNodes[j]->linkStrength(i);
	else
		return node::theNodes[i]->linkStrength(j);
}



bool network::isLinked ( nodeDescriptor i, nodeDescriptor j)
{
	nodeKind nk = node::theNodes[i]->getNodeInfo().theNodeKind;
	if (nk & _ode_ || nk & _sde_ || nk & _mapNode_)
		return node::theNodes[j]-> isLinked (i);
	else
		return node::theNodes[i]-> isLinked (j);

}


void network::link ( nodeDescriptor s, nodeDescriptor t, edgeBlueprint *l )
{ // differential equations mirror the direction of coupling, for performance reasons.
	nodeKind nk = node::theNodes[s]->getNodeInfo().theNodeKind;
	if (nk & _ode_ || nk & _sde_ || nk & _mapNode_)
		node::theNodes[t]->link ( s, l );
	else
		node::theNodes[s]->link ( t, l );

}


void network::unlink ( nodeDescriptor s, nodeDescriptor t)
{ // differential equations mirror the direction of coupling, for performance reasons.
	nodeKind nk = node::theNodes[s]->getNodeInfo().theNodeKind;
	if (nk & _ode_ || nk & _sde_ || nk & _mapNode_)
		node::theNodes[t]->unlink (s);
	else
		node::theNodes[s]->unlink (t);

}



// edges are described by an integer for the source node and an identifier which is defined in node.
//			typedef pair<nodeDescriptor, node::edgeDescriptor> edgeDescriptor;



void network::clear ()
{
	nodeIterator it;
	for (it = theNodes.begin();it!= theNodes.end();it++)
		delete node::theNodes[*it];



	inOutNodeList.clear();
	upkeepList.clear();
	theNodes.clear();
	numberOfNodes = 0;
	dynNode::time = 0;

	containerNode<baseType,0>::clear();
	containerNode<baseType,1>::clear();
	containerNode<baseType,2>::clear();
	containerNode<baseType,3>::clear();

}





		baseType frontAndPop(queue<baseType> *s)
		{
			baseType res = s->front();
			s->pop();
			return res;

		}








	bool network::isGraph()
	{
		nodeList vl;
		nodeIterator vi;
		verticesMatching (vl, _dynNode_);
		edgeList el;

		for (vi = vl.begin(); vi != vl.end(); vi++)
		{
				edgesBetween (el, *vi, _dynNode_);
//				el.sort ([&](edgeDescriptor l, edgeDescriptor r) -> bool { return getTarget(l)  < getTarget (r); } )
				el.sort (compareByTargets);
							


				edgeIterator ePrev = el.begin();
				if (getTarget (*ePrev) == getSource(*ePrev))
						return 0;		
				
				edgeIterator eSucc  = el.begin(); eSucc ++;
				for (; eSucc != el.end(); ePrev++, eSucc++)
				{
					if ((getTarget(*ePrev) == getTarget (*eSucc)) ||
						(getTarget(*eSucc) == getSource (*eSucc)))
						return 0;	
					
				}
				el.clear();

		}
		return 1;




	}







edgeVirtual *network::stdEdge = new weightedEdge <edgeVirtual>(1);
dynNode *network::stdNode = new nodeVirtualEdges<dynNode>();










}
