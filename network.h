

#ifndef __network
#define __network 0

//	Letzte Änderung:	10.06.2009	hdickten:	readParams fixed


#include "node.h"
#include "edge.h"

#include <list>
#include <set>

//#include "ioNode.h"
// verschiedene Nodearten includieren

#include <boost/bind.hpp>
using namespace boost;
#include "stream.h"

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
		private:
			bool directed;

		protected:
			//! Contains all nodes with time evolution 
			vector < dynNode *> evolveList;

			//! Contains all nodes which read/write data from/to files
			vector < dynNode *> inOutNodeList;



		public:
			//! parameter which determines how much date is written by printNodeStatistics about nodes 
			baseType nodeVerbosity() { return params<baseType>::getParams(0);};
			//! parameter which determines how much date is written by printNodeStatistics about edges 
			baseType edgeVerbosity() { return params<baseType>::getParams(1);};



			//! returns true if the node v is in this network. 
			bool isInsideNetwork ( nodeDescriptor v );

			static void registerStandardValues() 
			{ 
				params<baseType>::registerStandard(_network_,"network_nodeVerbosity",0,2.0);
				params<baseType>::registerStandard(_network_,"network_edgeVerbosity",1,2.0);
			}	

			// edges are described by an integer for the source node and an identifier which is defined in edge.	
			typedef pair<nodeDescriptor, node::edgeDescriptor> edgeDescriptor;

			// return the source of the edge.
			nodeDescriptor getSource(edgeDescriptor eD) { return eD.first; }

			nodeDescriptor getTarget(nodeDescriptor source,  nodeDescriptor edgeNumber)
			{ return node::theNodes[source]->getTarget(edgeNumber)->getNumber(); }
				typedef set<nodeDescriptor> nodeList;
			
			typedef nodeList::iterator nodeIterator;
			typedef list< edgeDescriptor >  edgeList;
			typedef edgeList::iterator edgeIterator;



			set<nodeDescriptor> theNodes;



			virtual void clean ( unsigned int timeSteps );


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
			network() ;                   // sinnloser Konstruktor
			network(bool directedNess) ;                   // sinnloser Konstruktor

			virtual ~network();


			//			baseType& getParam(nodeDescriptor nodeNumber,string name)
			//			{
			//					return ((dynNode*)(theNodes[nodeNumber]))->getParam(name);
			//			}


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
				clean(0);

			}



			//			void createFromAdjacencyList(string fileName, node * n);


			//! Besetzt die Kopplungsgewichte aller Links neu, die bei einem Knoten vom Typ sourceNodeKind beginnen und bei einem Knoten vom Typ targetNodeKind enden. Neue Kopplungsgewichte werden aus der Funktion r gezogen. r kann somit zum Beispiel auch Zahlen aus einer Datei lesen.
			void randomizeSomeWeights( function<double()> r, nodeKind sourceNodeKind, nodeKind targetNodeKind);

			//! Besetz die Kopplungsgewichte von Links, zwischen dynamischen Knoten neu.
			void randomizeWeights ( function<double () > r ) { randomizeSomeWeights(r,_dynNode_,_dynNode_); }


			//! Haut einen Zeiger auf den Knoten nodeNumber in die Liste res.
			void verticesMatching(nodeList &res, nodeDescriptor nodeNumber);

			//! Fügt der Liste res alle Knotem der Art nodeKind hinzu.
			void verticesMatching(nodeList &res, nodeKind nodeKind);

			//! Fügt alle Knoten hinzu, die "ähnlich" (n.equals(m) == true sind wie Knoten n.
			void verticesMatching(nodeList &res, node *n);

			//! Fügt der Liste res alle Knoten vom Typ nodetyp hinzu.
			void verticesMatching(nodeList &res, int networkElementType);

			void addEdges(nodeDescriptor source, nodeDescriptor target, edgeBlueprint *l);


			//! Verbindet sourceNode und targetNode bidirektional mit einer Verbindung vom Typ l 
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



			//!Löscht alle Knoten und gibt den Speicher (hoffentlich) wieder frei
			virtual void clear(); 		

			//! Verbinden Knoten source mit Knoten dest über eine Verbindung mit Gewicht weight vom Typ stdEdge 
			void addWeightedEdge ( nodeDescriptor source, nodeDescriptor dest, double weight);
			//! Verbindet s und t mit einer Verbindung vom Typ l
			void addEdge ( int s, int t, edgeBlueprint *l = stdEdge);
			//			void addEdge (nodeDescriptor s, nodeDescriptor t) { addEdge(s,t,stdEdge); }


			//			void addEdge (nodeDescriptor s, nodeDescriptor t, edge *l)
			//				{ addEdge(s,t,l); }	


			void addEdges (nodeKind sourceNodeKind, nodeDescriptor targetNode, edgeBlueprint *l = stdEdge);

			//			void addEdge ( nodeDescriptor s, nodeDescriptor t, baseType weight) 
			//				{ edge *l = new edge(NULL,NULL, weight);addEdge(s,t,l); } 

			//! Fügt einen Knoten vom Typ node, gibt die Nummer vom neuen Knoten zurück.
			//		virtual nodeDescriptor addNode();					
			//! fügt eine Kopie von *n zum Netzwerk hinzu, gibt die Nummer vom neuen Knoten zurück.
			virtual nodeDescriptor addNode ( nodeBlueprint *n );				

			//! tauscht einen Node aus
			void replace(nodeDescriptor nodeNumber, nodeBlueprint *n);

			//! Löscht alle Knoten vom Type theNodeKind.   
			void remove (nodeKind theNodeKind );			

			//! Löscht alle Verbindungen von Knoten source nach Knoten target.
			void unlink (nodeDescriptor source, nodeDescriptor target) { node::theNodes[source]->unlink(target); }


			//! macht dasselbe wie addEdge aber in beide Richtungen
			void link ( int s, int t, baseType weight = 1 );



			//! Gibt die Verbindungsstärke von Knoten i nach Knoten j zurück. 0 falls keine Verbindung besteht.
			baseType linkStrength ( int i, int j ) { return node::theNodes[i]->linkStrength ( node::theNodes[j] ); }

			//! Gibt TRUE zurück falls eine Verbindung zwischen Knoten i und j besteht.
			bool isLinked ( int i, int j ) { return node::theNodes[i]->isLinked ( node::theNodes[j] ); }


			//! Gibt die Anzahl der Nodes der Art theNodeKind zurück
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
