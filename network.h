

#ifndef __network
#define __network __network



#include "node.h"
#include "edge.h"

#include <list>
#include <set>

//#include "ioNode.h"
// verschiedene Nodearten includieren

#include <boost/bind.hpp>
using namespace boost;

#include "gslNoise.h"

#include "dynNode.h"

#include <queue>
#include "baseType.h"
#include "params.h"
#include <vector>
#define DIJKSTRA_INFINITY 999999
#define DIJKSTRA_ZERO 0

const int directed = 1 << 1;


const bool _directed_ = 1;
const bool _undirected_ = 1;


const int parallelEdges = 1 << 2;
using namespace std;
using namespace boost;


namespace conedy
{



	//double frontAndPop(queue<double> *s);

	double inline frontAndPop(queue<double> *s)
	{
		double res = s->front();
		s->pop();		
		return res;

	}


	/*!
	  \Brief Class which represents a network

	  Hier finden sich funktionen, die einzelne Nodes / Edges hinzufügen oder Nodes nach bestimmten Kriterien in Listen hinzufügen.
	  Dabei wird stets in die entsprechende Funktion eine Blaupausenzeiger node*n oder  edge<l> *l übergeben, der vorgibt welche Arte von Knoten/Verbindungen erzeugt werden sollen. Die hinzugefügten Knoten/Verbindungen werden mit n->construct() oder l->construct() erzeugt, welches den Copy-Konstruktor von sich selbst aufruft.


	  bei überladenen Funktionen haben die argumentTypen die folgenden Bedeutungen

	  int	networkElementType	(Nummer des NodeTypes - CNN, Rössler)
	  nodeKind	NodeKind		(Nummer der Nodeart - Input, Output)
	  nodeDescriptor	nodeNumber		(Nummer der Node - Wahl genau einer Node)


*/

	typedef dynNode nodeBlueprint;
	typedef edgeVirtual edgeBlueprint;




	class network: public params<baseType>
	{

		protected:
			//! Contains all nodes with time evolution 
			vector < dynNode *> evolveList;

			//! Contains all nodes which read/write data from/to files
			vector < dynNode *> inOutNodeList;
	
			//! Contains all nodes which receive a callback after each intergration step 
			vector < dynNode *> upkeepList;

		public:
			// edges are described by an integer for the source node and an identifier which is defined in node.	
			typedef pair<nodeDescriptor, node::edgeDescriptor> edgeDescriptor;

			//! typedefs for list of nodes and edges
			typedef set<nodeDescriptor> nodeList;			
			typedef nodeList::iterator nodeIterator;
			typedef list< edgeDescriptor >  edgeList;
			typedef edgeList::iterator edgeIterator;


			//! parameter which determines how much date is written by printNodeStatistics about nodes 
			baseType nodeVerbosity() { return params<baseType>::getParams(0);};
			//! parameter which determines how much date is written by printNodeStatistics about edges 
			baseType edgeVerbosity() { return params<baseType>::getParams(1);};


			//! returns true if the node v is in this network. 
			bool isInsideNetwork ( nodeDescriptor v );

			static void registerStandardValues() {
			  //! determines the verbosity when print node information after a call of  printNodeStatistics();	
				params<baseType>::registerStandard(_network_,"network_nodeVerbosity",0,2.0);
			  //! determines the verbosity when print edge information after a call of  printNodeStatistics();	
				params<baseType>::registerStandard(_network_,"network_edgeVerbosity",1,2.0);
			}	


			//! return the source of the edge.
			nodeDescriptor getSource(edgeDescriptor eD) { return eD.first; }
			


			// returns the target of the edge.
			nodeDescriptor getTarget(nodeDescriptor source,  nodeDescriptor edgeNumber)
			{ return node::theNodes[source]->getTarget(edgeNumber)->getNumber(); }




			set<nodeDescriptor> theNodes;


			//! prepare the network for numerical integration, calls clean for each node and updates evolveList, etc.
			virtual void clean ();


			//! restrict the network to the node number numbers which are in the file fileName
			void select (string fileName) ;

		
			nodeDescriptor getTarget(edgeDescriptor eD) { return node::theNodes[eD.first]->getTarget(eD.second)->getNumber(); }		


			baseType getWeight(edgeDescriptor eD) { return node::theNodes[eD.first]->getWeight(eD.second); }
			void setWeight(edgeDescriptor eD, baseType w) { 		 node::theNodes[eD.first]->setWeight(eD.second, w); }

			edgeInfo getEdgeInfo (edgeDescriptor eD) 		 { return node::theNodes[eD.first]->getEdgeInfo(eD.second);}
			edge * getEdge (edgeDescriptor eD) 				 { return node::theNodes [eD.first]->getEdge(eD.second); }

			dynNode* getNode (nodeDescriptor vd) { return (dynNode* )node::theNodes[vd];}


			static edgeVirtual * stdEdge;//# = new edge(NULL,NULL,1);
			static dynNode * stdNode;
			network() ;                   
			network(bool directedNess) ;   

			virtual ~network();


			//			baseType& getParam(nodeDescriptor nodeNumber,string name)
			//			{
			//					return ((dynNode*)(theNodes[nodeNumber]))->getParam(name);
			//			}

			//! 
			void removeEdge (edgeDescriptor e)
			{
				node::theNodes[e.first]-> removeEdge (e.second);
			}

			void removeEdges (edge * e)
			{
				edgeList el;
				networkElementType edgeType = ((edgeVirtual*) e) -> getEdgeInfo().theEdgeType;

				edgesMatching(el, edgeType);
				edgeIterator ei;
				for (ei = el.begin(); ei != el.end(); ei++)
					removeEdge(*ei);				
				clean();

			}



			//! Randomizes the coupling strengths for all edges which connect nodes of kind sourcenNodeKind to nodes of kind targetNodeKind. New weights are drawn from r.

			void randomizeSomeWeights( function<double()> r, nodeKind sourceNodeKind, nodeKind targetNodeKind);

			//! Randomizes the coupling strnegths for all dynamical nodes. New weights are drawn from r	
			void randomizeWeights ( function<double () > r ) { randomizeSomeWeights(r,_dynNode_,_dynNode_); }


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


			bool matches (nodeBlueprint *n1, nodeBlueprint *n2);


			void edgesBetween (edgeList &res, nodeDescriptor sourceNode, nodeBlueprint *targetNode);
			void edgesBetween (edgeList &res, nodeBlueprint * sourceNode, nodeBlueprint *targetNode);


			void edgesMatching (edgeList &res, networkElementType edgeType);
			//! Verbinden Knoten source mit Knoten target mit einer Verbindung vom Typ l
			//! Verbindet Knoten source mit allen Knoten der Art targedNodeKind
			void addEdges (nodeDescriptor source, nodeKind targetNodeKind, edgeBlueprint *l = stdEdge);
			//! Verbindet Knoten source mit allen Knoten vom Typ targetNodeType
			void addEdges (nodeDescriptor source, int targetNodeType, edgeBlueprint *l);

			//	void addEdges (nodeDescriptor source, nodeDescriptor targetNodeType, double w, edge *l) { };


			//	void edgesBetween(list< edge > res, int sourceNodeKini int targetNodeKind);







			// Interpreterfunktionen



			//! removes all nodes from the network 
			virtual void clear(); 		



			//! Verbinden Knoten source mit Knoten dest über eine Verbindung mit Gewicht weight vom Typ stdEdge 
			//! 
			void addWeightedEdge ( nodeDescriptor source, nodeDescriptor dest, double weight);

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
			baseType linkStrength ( nodeDescriptor i, nodeDescriptor j ) { return node::theNodes[i]->linkStrength ( node::theNodes[j] ); }

			//! returns true if there is a link between node i and j 
			bool isLinked ( nodeDescriptor i, nodeDescriptor j ) { return node::theNodes[i]->isLinked ( node::theNodes[j] ); }


			//! returns the number of nodes in the network of kind theNodeKind 
			unsigned int numberVertices ( nodeKind theNodeKind );





			unsigned int randomNode(nodeKind nodeKind = _dynNode_);





			//! gibt Anzahl der Knoten im Netzwerk zurück
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



		protected:

			unsigned int numberOfNodes;


			int getNetworkType () { return networkType; };
			gslNoise noise;


			void reset();





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
