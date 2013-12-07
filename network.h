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


	  bei überladenen Funktionen haben die argumentTypen die folgenden Bedeutungen

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
			typedef pair<nodeDescriptor, node::edgeDescriptor> edgeDescriptor;

			//! typedefs for lists of nodes and edges
			typedef set<nodeDescriptor> nodeList;
			typedef nodeList::iterator nodeIterator;
			typedef list< edgeDescriptor >  edgeList;
			typedef edgeList::iterator edgeIterator;


			//! returns true if the node v is in this network.
			bool isInsideNetwork ( nodeDescriptor v );

			static void registerStandardValues() {
			  //! determines the verbosity when print node information after a call of printNodeStatistics();
				registerGlobal<int>("nodeVerbosity", 2);
			  //! determines the verbosity when print edge information after a call of printNodeStatistics();
				registerGlobal<int>("edgeVerbosity", 2);
			}


			//! return the source of the edge.
			nodeDescriptor getSource(edgeDescriptor eD) { return eD.first; }

			//! return the target of the edge.
			nodeDescriptor getTarget(edgeDescriptor eD) { return node::theNodes[eD.first]->getTarget(eD.second); }


			//! returns the target of the edge.
			nodeDescriptor getTarget(nodeDescriptor source,  nodeDescriptor edgeNumber)		{ return node::theNodes[source]->getTarget(edgeNumber); }


			baseType getWeight(edgeDescriptor eD) { return node::theNodes[eD.first]->getWeight(eD.second); }
			void setWeight(edgeDescriptor eD, baseType w) { 		 node::theNodes[eD.first]->setWeight(eD.second, w); }



			//! prepare the network for numerical integration, calls clean for each node and updates evolveList, etc.			
			virtual void clean ();


			//! restrict the network to the node number numbers which are in the file fileName
			void select (string fileName) ;


			edgeInfo getEdgeInfo (edgeDescriptor eD) 		 { return node::theNodes[eD.first]->getEdgeInfo(eD.second);}


			edge * getEdge (edgeDescriptor eD) 				 { return node::theNodes [eD.first]->getEdge(eD.second); }

//			dynNode* getNode (nodeDescriptor vd) { return (dynNode* )node::theNodes[vd];}


			static edgeVirtual * stdEdge;//# = new edge(NULL,NULL,1);
			static dynNode * stdNode;


			network() ;
			network(bool directedNess) ;

			virtual ~network();


			void removeEdge (edgeDescriptor e) { node::theNodes[e.first]-> removeEdge (e.second);}

			void removeEdges (edgeBlueprint * e);



			//! Randomizes the coupling strengths for all edges which connect nodes of kind sourcenNodeKind to nodes of kind targetNodeKind. New weights are drawn from r.

			void randomizeSomeWeights( function<baseType()> r, nodeKind sourceNodeKind, nodeKind targetNodeKind);

			//! Randomizes the coupling strnegths for all dynamical nodes. New weights are drawn from r
			void randomizeWeights ( function<baseType () > r ) { randomizeSomeWeights(r,_dynNode_,_dynNode_); }


			//! Haut einen Zeiger auf den Knoten nodeNumber in die Liste res.

			//! adds the node nodeNumber to the list res.
			void verticesMatching(nodeList &res, nodeDescriptor nodeNumber);


			//! adds all nodes of kind nodeKind to the list res.
			void verticesMatching(nodeList &res, nodeKind nodeKind);


			//! adds all nodes, which "match" node n.
			void verticesMatching(nodeList &res, node *n);

			//! Fügt der Liste res alle Knoten vom Typ nodetyp hinzu.
			void verticesMatching(nodeList &res, int networkElementType);


			//! adds an edge between source and target. The new edge is copied from l.
			void addEdges(nodeDescriptor source, nodeDescriptor target, edgeBlueprint *l);


			// adds edges in each direction between sourceNode and targetNode of type l.
			void link( nodeDescriptor  sourceNode, nodeDescriptor targetNode, edgeBlueprint *l);

			//! return true, if for every edge between dynNodes in the network, there exist an edge with source and target interchanged.
			bool isDirected();

			//! Verbinde sourceNode mit allen Nodes der Art targetNodeKind bidirektional
			void link (nodeDescriptor sourceNode, nodeKind targetNodeKind, edge *l);


			//! Fügt der Liste res alle Verbindungen hinzu, die bei einem Knoten der Art sourceNodeKind starten und bei einem Knoten der Art targetNodeKind enden.
			void edgesBetween(edgeList &res, nodeKind sourceNodeKind, nodeKind targetNodeKind);
			//! Fügt der Liste res alle Verbindungen hinzu, die beim Knoten mit der Nummer sourceNode starten und bei einem Knoten der Arte targetNodeKind enden.
			void edgesBetween(edgeList &res, nodeDescriptor sourceNode, nodeKind targetNodeKind);
			//! Fügt der Liste res alle Verbindungen hinzu, die bei einem Knoten der Art sourceNodeKind starten und beim Knoten mit der Nummer targedNode enden.
			void edgesBetween(edgeList &res, nodeKind sourceNodeKind, nodeDescriptor targetNode);


			void edgesBetween(edgeList &res, networkElementType sourceNodeType, networkElementType targetNodeType);


			void edgesBetween(edgeList &res, nodeDescriptor sourceNode, networkElementType targetNodeType);


//			bool matches (nodeBlueprint *n1, nodeBlueprint *n2);


			void edgesBetween (edgeList &res, nodeDescriptor sourceNode, nodeBlueprint *targetNode);
			void edgesBetween (edgeList &res, nodeBlueprint * sourceNode, nodeBlueprint *targetNode);


			void edgesMatching (edgeList &res, networkElementType edgeType);
			//! Verbinden Knoten source mit Knoten target mit einer Verbindung vom Typ l
			//! Verbindet Knoten source mit allen Knoten der Art targedNodeKind


			void addEdges (nodeDescriptor source, nodeKind targetNodeKind, edgeBlueprint *l = stdEdge);
			//! Verbindet Knoten source mit allen Knoten vom Typ targetNodeType
			void addEdges (nodeDescriptor source, int targetNodeType, edgeBlueprint *l = stdEdge);

			//	void addEdges (nodeDescriptor source, nodeDescriptor targetNodeType, baseType w, edge *l) { };


			//	void edgesBetween(list< edge > res, int sourceNodeKini int targetNodeKind);







			// Interpreterfunktionen



			//! removes all nodes from the network
			virtual void clear();



			//! Verbinden Knoten source mit Knoten dest über eine Verbindung mit Gewicht weight vom Typ stdEdge
			//!
			void addWeightedEdge ( nodeDescriptor source, nodeDescriptor dest, baseType weight);

			//! links s and t by an edge which is a copy of l
			void addEdge ( nodeDescriptor s, nodeDescriptor t, edgeBlueprint *l = stdEdge);


			void addEdges (nodeKind sourceNodeKind, nodeDescriptor targetNode, edgeBlueprint *l = stdEdge);



			//! adds a node to the network, which is constructed by n->construct()
			virtual nodeDescriptor addNode ( nodeBlueprint *n );

			//! tauscht einen Node aus
			void replace(nodeDescriptor nodeNumber, nodeBlueprint *n);

			//! removes all nodes of type theNodeKind from the network
			void remove (nodeKind theNodeKind );

			//! removes all edges between source and target
			void unlink (nodeDescriptor source, nodeDescriptor target) { node::theNodes[source]->unlink(target); }


			//! macht dasselbe wie addEdge aber in beide Richtungen
			void link ( nodeDescriptor s, nodeDescriptor t, baseType weight = 1 );



			//! Gibt die Verbindungsstärke von Knoten i nach Knoten j zurück. 0 falls keine Verbindung besteht.
			baseType linkStrength ( nodeDescriptor i, nodeDescriptor j ) { return node::theNodes[i]->linkStrength ( j ); }

			//! returns true if there is a link between node i and j
			bool isLinked ( nodeDescriptor i, nodeDescriptor j );


			//! returns the number of nodes in the network of kind theNodeKind
			unsigned int numberVertices ( nodeKind theNodeKind );

			void setDirected () { directed = true; };
				
			void setUndirected () { directed = false; };



			unsigned int randomNode(nodeKind nodeKind = _dynNode_);




			unsigned int numberVertices() { return theNodes.size(); }
			unsigned int size() { return theNodes.size(); }



			int getNodeKind ( int number ) { return node::theNodes[number]->getNodeInfo().theNodeKind; }

			//			pair<edgeIterator, edgeIterator> out_edges ( nodeDescriptor u ) { return theNodes[u]->getEdges();};
			//! gibt ein Iteratorpaar auf die Verbindungen vom u.ten Knoten zurück.


			//			pair<nodeIterator, nodeIterator> vertices () {



			//				return std::make_pair ( theNodes.begin(),theNodes.end() );} // gibt ein Iteratorpaar auf die Knoten im Netzwerk zurck
			void repair();


		private:
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

//			int getNetworkType () { return networkType; };


			gslNoise noise;

//			void reset();
	};


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
