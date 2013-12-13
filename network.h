#ifndef __network
#define __network __network

#include "dynNode.h"
#include "edge.h"

#include <list>
#include <set>
#include <vector>

using namespace boost;
#include "gslNoise.h"

#include "baseType.h"
#include "globals.h"

#include <queue>



const bool _directed_ = 1;
const bool _undirected_ = 1;




namespace conedy
{


		baseType frontAndPop(queue<baseType> *s);

	/*!
	  \Brief Class which represents a network.

	  In this class are functions which add single nodes or edges. These are called with blueprints node * n or edge * l, which specify the type of adde node/edge. Added nodes/edges are then created by node::construct(), which calls the copy constructor.


	  for overloadad functions like addEdges, the argument types have the following meaning:

	  int	networkElementType	(identifying integer for the node type)
	  nodeKind	NodeKind		(kind of the node, e.g _dynNode_, _outNode)
	  nodeDescriptor	nodeNumber	 (identifying integer for the node)


*/

	typedef edgeVirtual edgeBlueprint;




	class network: protected globals
	{



		public:



			// edges are described by an integer for the source node and an identifier which is defined in node.
			typedef pair<nodeDescriptor, nodeDescriptor> edgeDescriptor;

			//! typedefs for lists of nodes and edges
			typedef set<nodeDescriptor> nodeList;
			typedef nodeList::iterator nodeIterator;
			typedef list< edgeDescriptor >  edgeList;
			typedef edgeList::iterator edgeIterator;





			// functions which are revealed to the interpreter/python bindings



			//! links s and t by an edge which is a copy of l
			void addEdge ( nodeDescriptor s, nodeDescriptor t, edgeBlueprint *l = stdEdge);
			void addWeightedEdge ( nodeDescriptor s, nodeDescriptor t, baseType weight);

			//! adds a node to the network, which is constructed by n->construct()
			virtual nodeDescriptor addNode ( nodeBlueprint *n=stdNode);
			
			//! Verbinden Knoten source mit Knoten dest über eine Verbindung mit Gewicht weight vom Typ stdEdge
//			void addWeightedEdge ( nodeDescriptor source, nodeDescriptor dest, baseType weight);

			//! removes all nodes from the network
			virtual void clear();


			//! replaces node nodeNumber with a newly created node constructed by n->construct() 
			void replaceNodes(nodeDescriptor nodeNumber, nodeBlueprint *n = stdNode);

			//! removes all nodes of type theNodeKind from the network
			void remove (nodeKind theNodeKind );

			//! remove all nodes from the network which match n	
			void removeNodes (nodeBlueprint *n = stdNode);

			//! removes all edges between source and target
			void removeEdge (nodeDescriptor source, nodeDescriptor target) { node::theNodes[source]->unlink(target); }



//			baseType meanDegree ();


			//! returns the connections strength between node i and j, returns 0 if no connection exists.
			baseType linkStrength ( nodeDescriptor i, nodeDescriptor j ) { return node::theNodes[i]->linkStrength ( j ); }

			//! returns true if there is a link between node i and j
			bool isLinked ( nodeDescriptor i, nodeDescriptor j );

			//! returns the number of nodes in the network
			unsigned int numberVertices() { return theNodes.size(); }

			unsigned int size() { return theNodes.size(); }



			void removeEdges (edgeBlueprint * e);



			//! Randomizes the coupling strengths for all edges which connect nodes of kind sourcenNodeKind to nodes of kind targetNodeKind. New weights are drawn from r.
			void randomizeWeights( function<baseType()> r, nodeBlueprint *n1 = stdNode, nodeBlueprint *n2 = stdNode);



			static void registerStandardValues() {
			  //! determines the verbosity when print node information after a call of printNodeStatistics();
				registerGlobal<int>("nodeVerbosity", 2);
			  //! determines the verbosity when print edge information after a call of printNodeStatistics();
				registerGlobal<int>("edgeVerbosity", 2);
			}


		public:
			//! restrict the network to the node number numbers which are in the file fileName
			void select (string fileName) ;

			// auxiliary functions to be used for the network generators in createNetwork.h


			void remove (edgeDescriptor e) { node::theNodes[e.first]-> removeEdge (e.second);}

			//! macht dasselbe wie addEdge aber in beide Richtungen
//			void link ( nodeDescriptor s, nodeDescriptor t, baseType weight = 1 );
			


			//! returns true if the node v is in this network.
			bool isInsideNetwork ( nodeDescriptor v );



			//! return the source of the edge.
			static nodeDescriptor getSource(edgeDescriptor eD) { return eD.first; }

			//! return the target of the edge.
			static nodeDescriptor getTarget(edgeDescriptor eD) { return node::theNodes[eD.first]->getTarget(eD.second); }

			//! returns the target of the edge.
			nodeDescriptor getTarget(nodeDescriptor source,  nodeDescriptor edgeNumber)		{ return node::theNodes[source]->getTarget(edgeNumber); }


			baseType getWeight(edgeDescriptor eD) { return node::theNodes[eD.first]->getWeight(eD.second); }
			void setWeight(edgeDescriptor eD, baseType w) { 		 node::theNodes[eD.first]->setWeight(eD.second, w); }



			//! prepare the network for numerical integration, calls clean for each node and updates evolveList, etc.		TODO move to dynNetwork ?	
			virtual void clean ();




			edgeInfo getEdgeInfo (edgeDescriptor eD) 		 { return node::theNodes[eD.first]->getEdgeInfo(eD.second);}


			edge * getEdge (edgeDescriptor eD) 				 { return node::theNodes [eD.first]->getEdge(eD.second); }



			static edgeVirtual * stdEdge;  
			static dynNode * stdNode;


			network() ;
			network(bool directedNess) ;

			virtual ~network();


			void addEdges (nodeKind sourceNodeKind, nodeDescriptor targetNode, edgeBlueprint *l = stdEdge);


			//! adds the node nodeNumber to the list res.
			void verticesMatching(nodeList &res, nodeDescriptor nodeNumber);
			//! adds all nodes of kind nodeKind to the list res.
			void verticesMatching(nodeList &res, nodeKind nodeKind);
			//! adds all nodes, which "match" node n.
			void verticesMatching(nodeList &res, node *n);
			//! adds all nodes of type nodeType
			void verticesMatching(nodeList &res, networkElementType nodeType);



			//! adds all edges which start at a node of kind sourceNodeKind and end at a node of kind targetNodeKind 
			void edgesBetween(edgeList &res, nodeKind sourceNodeKind, nodeKind targetNodeKind);
			//! adds all edges which start at a node sourceNode and end at a node of kind targetNodeKind 
			void edgesBetween(edgeList &res, nodeDescriptor sourceNode, nodeKind targetNodeKind);
			//! adds all edges which start at a node of kind sourceNodeKind and end at a node targetNode
			void edgesBetween(edgeList &res, nodeKind sourceNodeKind, nodeDescriptor targetNode);
			//! adds all edges which start at a node of type sourceNodeType and end at a node of type targetNodeType 
			void edgesBetween(edgeList &res, networkElementType sourceNodeType, networkElementType targetNodeType);
			//! adds all edges which start a node sourceNode and end at  
			void edgesBetween(edgeList &res, nodeDescriptor sourceNode, networkElementType targetNodeType);
			void edgesBetween (edgeList &res, nodeDescriptor sourceNode, nodeBlueprint *targetNode);
			void edgesBetween (edgeList &res, nodeBlueprint * sourceNode, nodeBlueprint *targetNode);

			void edgesMatching (edgeList &res, networkElementType edgeType);

			bool isGraph () ; // returns true if the network does not contain  double- or self-connections



			//! adds an edge between source and target. The new edge is copied from l.
			void addEdges(nodeDescriptor source, nodeDescriptor target, edgeBlueprint *l);
			void addEdges (nodeDescriptor source, nodeKind targetNodeKind, edgeBlueprint *l = stdEdge);
			//! Verbindet Knoten source mit allen Knoten vom Typ targetNodeType
			void addEdges (nodeDescriptor source, int targetNodeType, edgeBlueprint *l = stdEdge);


			void link( nodeDescriptor  sourceNode, nodeDescriptor targetNode, edgeBlueprint *l = stdEdge);
			void link( nodeDescriptor  sourceNode, nodeDescriptor targetNode, baseType weight);
			void unlink( nodeDescriptor  sourceNode, nodeDescriptor targetNode);



			//! return true, if for every edge between dynNodes in the network, there exist an edge with source and target interchanged.
			bool isDirected();

			//! Verbinde sourceNode mit allen Nodes der Art targetNodeKind bidirektional
			void link (nodeDescriptor sourceNode, nodeKind targetNodeKind, edge *l);







			//	void addEdges (nodeDescriptor source, nodeDescriptor targetNodeType, baseType w, edge *l) { };


			//	void edgesBetween(list< edge > res, int sourceNodeKini int targetNodeKind);











			//! returns the number of nodes in the network of kind theNodeKind
			unsigned int numberVertices ( nodeKind theNodeKind );

			void setDirected () { directed = true; };
				
			void setUndirected () { directed = false; };



			unsigned int randomNode(nodeKind nodeKind = _dynNode_);




			unsigned int numberVertices() { return theNodes.size(); }
			unsigned int size() { return theNodes.size(); }



			int getNodeKind ( int number ) { return node::theNodes[number]->getNodeInfo().theNodeKind; }






			bool directed;


		private:
			int networkType;

			
			//! The set of node numbers of all nodes which are in the network.
			set<nodeDescriptor> theNodes;

		protected:


			//! Contains all nodes with time evolution
			vector < dynNode *> evolveList;

			//! Contains all nodes which read/write data from/to files
			vector < dynNode *> inOutNodeList;

			//! Contains all nodes which receive a callback after each intergration step
			vector < dynNode *> upkeepList;

			unsigned int numberOfNodes;

			gslNoise noise;

	};

			bool compareByTargets (network::edgeDescriptor l, network::edgeDescriptor r); 

	//! Funktor, der einen zufälligen Knoten zurückgibt, der gleichverteilt aus einer Liste ausgewählt wird, die beim Konstruiren übergeben wird.
	class getRandomNode : public gslNoise {
		vector <nodeDescriptor> hashTable;

		public:
		getRandomNode (network::nodeList vl)
		{
			network::nodeIterator vi;
			for (vi = vl.begin(); vi != vl.end(); vi++ )
				hashTable.push_back(*vi);
		}
		nodeDescriptor operator() () { return  hashTable [getUniformInt( 0, hashTable.size() - 1) ] ; }

	};

}

#endif
