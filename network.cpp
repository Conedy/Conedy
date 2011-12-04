

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


	//! Verbindet sourceNode und targetNode bidirektional mit einer Verbindung vom Typ l 
	void network::link( nodeDescriptor  sourceNode, nodeDescriptor targetNode, edgeBlueprint *l)
	{
		addEdge(sourceNode, targetNode, l);
		addEdge(targetNode, sourceNode, l);
	}

	void network::clean ( )
	{
		evolveList.clear();

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



	//! Verbinde sourceNode mit allen Nodes der Art targetNodeKind bidirektional
	void network::link (nodeDescriptor sourceNode, nodeKind targetNodeKind, edge *l)
	{
		nodeIterator it;
		nodeList vl;
		verticesMatching(vl,targetNodeKind);
		for (it = vl.begin(); it != vl.end(); it++)
		{
			link(sourceNode, *it,l);
		}
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
				if (isInsideNetwork( getTarget(*vi, ea)))
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

	nodeIterator va;


	//		edgeIterator ea,ee;
	for (va = theNodes.begin(); va != theNodes.end(); va++)
	{
		if (node::theNodes[*va]->getNodeInfo().theNodeType == sourceNodeType)
			edgesBetween(res, node::theNodes[*va]->getNumber(), sourceNodeType);

	}



}

bool network::matches (nodeBlueprint *n1, nodeBlueprint *n2)
{
	if ((n1 == stdNode) || (n2 ==stdNode))
		return  true;
	else return n1->getNodeInfo().theNodeType == n2->getNodeInfo().theNodeType;
}

void network::edgesBetween(list< edgeDescriptor > &res, nodeKind sourceNodeKind, nodeKind targetNodeKind)
{
	nodeIterator va;


	//		edgeIterator ea,ee;
	for (va = theNodes.begin(); va != theNodes.end(); va++)
	{
		if (node::theNodes[*va]->getNodeInfo().theNodeKind & sourceNodeKind)
			edgesBetween(res, node::theNodes[*va]->getNumber(), targetNodeKind);

	}
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
		if (node::theNodes[sourceNode]->getTarget(ea)->getNodeInfo().theNodeKind & targetNodeKind)
			if (isInsideNetwork( getTarget(sourceNode, ea)))
				res.push_back (make_pair(sourceNode,ea));
}


void network::edgesBetween(list< edgeDescriptor > &res, nodeDescriptor sourceNode, networkElementType targetNodeType)
{
	node::edgeDescriptor ea,ee;
	ea = 0;
	ee = node::theNodes[sourceNode]->degree();
	for (; ea != ee; ea++)
		if (node::theNodes[sourceNode]->getTarget(ea)->getNodeInfo().theNodeType == targetNodeType)
			res.push_back (make_pair(sourceNode,ea));
}
void network::edgesBetween(list<edgeDescriptor> &res, nodeBlueprint *sourceNode, nodeBlueprint *targetNode)
{

	nodeIterator va;

	//		edgeIterator ea,ee;
	for (va = theNodes.begin(); va != theNodes.end(); va++)
	{
		if ( matches ( sourceNode,(dynNode*) node::theNodes[*va] ))
			edgesBetween(res, *va, targetNode);	
	}
}

void network::edgesBetween(list<edgeDescriptor> &res, nodeDescriptor sourceNode, nodeBlueprint *targetNode)
{

	node::edgeDescriptor ea,ee;
	ea = 0;
	ee = node::theNodes[sourceNode]->degree();
	for (; ea != ee; ea++)
		if (matches ((dynNode *)node::theNodes[sourceNode]->getTarget(ea), targetNode))
			res.push_back (make_pair(sourceNode,ea));

}


void network::edgesBetween(list< edgeDescriptor > &res, nodeKind sourceNodeKind, nodeDescriptor targetNode)
{
	cout << "wo brauch ich das denn ?" << endl;
	exit(1);

}



unsigned int network::numberVertices (nodeKind theNodeKind )
{
	nodeList vl;
	verticesMatching (vl,theNodeKind);
	return vl.size();
}



void network::remove ( nodeKind theNodeKind )
{
	nodeList vl;

	verticesMatching (vl, theNodeKind);
	nodeIterator vi;

	for (vi = theNodes.begin(); vi != theNodes.end(); )
	{


		if (node::theNodes[*vi]->getNodeInfo().theNodeKind == theNodeKind)
		{
			delete node::theNodes[*vi];
			nodeIterator here = vi;
			vi++;
			theNodes.erase(here);
			numberOfNodes--;
		}
		else
			vi++;

	}


	//	quequeBuffer *buf = new quequeBuffer();
	//        streamOutSort(*buf);       Die beiden Zeilen sind notwendig, falls Knoten aus der Mitte vom Array gelÃÂÃÂ¶scht werden.
	//	streamIn(size,*buf); 	     Allerdings werden die Parameter von den Nodes dabei gelÃÂÃÂ¶scht
}




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




void network::randomizeSomeWeights ( boost::function<double () > r,nodeKind sourceNodeKind, nodeKind targetNodeKind )
{

	network::edgeList toChange;

	edgesBetween(toChange,sourceNodeKind, targetNodeKind);
	edgeIterator it;
	for (it = toChange.begin(); it != toChange.end(); it++)
		if (getEdgeInfo(*it).theEdgeKind & _weighted_)
			setWeight(*it,r());
}





//
network::network(): params<baseType>(_network_), directed(true)
{
	numberOfNodes = 0;
}


network::network(bool directedNess): params<baseType>(_network_), directed(directedNess)
{
	numberOfNodes = 0;
}

/*
	void network::streamOut(string s)
	{
	outStream *out = new outStream(s.c_str());
	streamOut (*out);
	delete out;
	}
	*/

network::~network()
{
	nodeIterator it;


	for ( it = theNodes.begin(); it != theNodes.end(); it++ )
		delete ( node::theNodes[*it] );
}


//	nodeDescriptor network::addNode()
//	{cout <<" das macht doch keinen Sinn.";
//		node *kno = new node ();
//		theNodes.push_back ( kno );
//return theNodes.size();
//	}

nodeDescriptor network::addNode ( nodeBlueprint *n )
{
	 node  *newNode = n->construct();

	nodeDescriptor newNodeNumber = newNode->getNumber();
	if (n->getNodeInfo().theNodeKind & _inNode_)
		inOutNodeList.push_back (  (dynNode*)   node::theNodes[newNodeNumber]);


	//cout << ((cnnNode<double>*) n )-> row << endl;
	theNodes.insert ( newNodeNumber );
	numberOfNodes++;
	//cout << ((cnnNode<double>*) theNodes[theNodes.size() - 1] )-> row << endl;
	return  newNodeNumber;
}

void network::addWeightedEdge ( nodeDescriptor s, nodeDescriptor t, double weight )
{

	nodeKind nk = node::theNodes[s]->getNodeInfo().theNodeKind;
	if (nk & _ode_ || nk & _sde_ || nk & _map_)
		node::theNodes[t]->link ( s, weight );
	else
		node::theNodes[s]->link ( t, weight );
	
	
	//	networkType = networkType & ( 0 - 1 - directed );
}


bool network::isLinked ( nodeDescriptor i, nodeDescriptor j)
{
	nodeKind nk = node::theNodes[i]->getNodeInfo().theNodeKind;
	if (nk & _ode_ || nk & _sde_ || nk & _map_)
		return node::theNodes[j]-> isLinked (node::theNodes[i]);
	else
		return node::theNodes[i]-> isLinked (node::theNodes[j]);

}		


void network::addEdge ( nodeDescriptor s, nodeDescriptor t, edgeBlueprint *l ) 
{ // differential equations mirror the direction of coupling, for performance reasons.
	nodeKind nk = node::theNodes[s]->getNodeInfo().theNodeKind;
	if (nk & _ode_ || nk & _sde_ || nk & _map_)
		node::theNodes[t]->link ( s, l );
	else
		node::theNodes[s]->link ( t, l );

}




			// edges are described by an integer for the source node and an identifier which is defined in node.	
//			typedef pair<nodeDescriptor, node::edgeDescriptor> edgeDescriptor;

void network::link ( nodeDescriptor s, nodeDescriptor t, baseType weight )
{

	node::theNodes[s]->link ( t, weight );
	node::theNodes[s]->link ( s ,weight );
}


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


















edgeVirtual *network::stdEdge = new weightedEdge <edgeVirtual>(1);
dynNode *network::stdNode = new nodeVirtualEdges<dynNode>();










}
