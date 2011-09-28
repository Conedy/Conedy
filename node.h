#ifndef node_h
#define node_h node_h


#include "networkConstants.h"
#include "gslNoise.h"
#include "baseType.h"


#include <limits>
#include <cmath>
#include <complex>
#include <stdio.h>
#include <cmath>
#include <iostream>
#include <vector>




namespace conedy
{
	using namespace std;
	// Nodekind   : short
	// Nodetype   : int



	typedef char nodeKind;

	const nodeKind  _inNode_ = 1 << 1;
	const nodeKind  _outNode_ = 1 << 2;
	const nodeKind  _dynNode_ = 1 << 3;

	typedef char edgeKind;

	const edgeKind	_weighted_	= 1 << 1;
	const edgeKind	_polynomial_	= 1 << 2;  // erbt von params<vector<baseType>>

	//! identifier for nodes, determines the maximum number of nodes.
	typedef unsigned int nodeDescriptor;


	//! Info-object which is returned by all nodes.
	struct nodeInfo
	{	// a unique identifier for the node type
		networkElementType theNodeType;
		// a bit mask for booleans which specify the kind of the node. inNode | outNode | dynNode
		nodeKind  theNodeKind;
		// the node name. Is used by printNodeStatistics
		string theNodeName;
	};

	//! Info-Objekt, das alle Edges zurückgeben
	struct edgeInfo
	{	// unique identifier for the edgetype
		networkElementType theEdgeType;
		// bit mask with the node type, 
		edgeKind theEdgeKind;
		string theEdgeName;
	};


	class node;
	class dynNode;


	//! base class for all edges. Has no virtual functions. Specialized edges should be defined as template, such that the template parameter is the base class. In this way both edges with and without virtual functions can use the same code.
	class edge
	{

		public:
			// static 
			typedef dynNode targetNodeType;

			//! Number of the target node, pointer to the node is store in node::thenodes	
			nodeDescriptor targetNumber; 
			edge() : targetNumber(0) {};
			edge ( nodeDescriptor t) :targetNumber ( t ) {};

		public:
			//! Return pointer to the target node.
			node* getTarget();// { return node::theNodes [targetNumber];}

			//! Returns the state of the target node.
			baseType getTargetState();

			//! Return info-object for the edge.
			const edgeInfo getEdgeInfo() {edgeInfo ei = {_edge_,0}; return ei;}


			//			edge *construct() { return new edge ( *this ); };

			//! print information about the edge to the console. 
			ostream& printStatistics ( ostream &os, double edgeOptVerbosity, int theEdgeKind, string theEdgeName, baseType weight);

			//! Return the weight of the edge, 1 for unweighted edges.
			baseType getWeight() { return (baseType)1; }
			//! Set the weight of the edge, throw an exception for unweighted edges.
			void setWeight(baseType newWeight) { };
	};




	//! base class for edges with virtual functions.
	class edgeVirtual : public edge
	{
		public:
			edgeVirtual() :edge(0) {};
			edgeVirtual ( nodeDescriptor t) :edge(t ) {};

		public:
			virtual node* getTarget() { return edge::getTarget();}
			virtual baseType getTargetState(); 

			virtual const edgeInfo getEdgeInfo() {edgeInfo ei = {_edgeVirtual_,0, "edgeVirtual"}; return ei;}
			virtual edge *construct() { return new edgeVirtual ( *this ); };
			virtual ostream& printStatistics ( ostream &os, double edgeVirtualVerbosity=1.0);

			virtual baseType getWeight() { return (baseType)1; }
			virtual void setWeight(baseType newWeight) 
			{
				throw "Trying to set weight of unweighted edge!";
			}	

	};






	/*!
	  \Brief  Base class for all nodes.

	  Contains a list of edges and supplies functions like link and unlink, which change this list. Also contains a vector of pointer to all nodes, which serves as lookup table. In this way edges need only memorize a 32 bit node number instead of a 64 bit pointer.

*/
	class node
	{
		public:

			//! virtuelle Funktion, die state zurückgibt. Zur Performancesteigerung sollte vielleicht ein Macro definiert werden, dass entweder diese Funktione aufgerufen wird (mit sprungtabelle, langsam) oder direkt state zurückgegeben wird

			//! virtual function, which returns the standard node state.
			virtual baseType getState() { throw "getState von nodeVirtual aufgerufen !";}
			//! Variable, die von der Klasse offeriert wird, zum Beispiel zum Einkoppeln in andere Nodes 
			//			baseType state;


			//! gibt inen Struct zurück, der informationen über den Knoten enthält. Erster Parameter ist ein eindeutige Identifikationsnummer, für den Knoten Typ. Zweiter Parameter ist eine Bitmaske für die Knoten art. Bisher verwendet werden hierfür Eingabe- AusgabeKnoten und Dynamische Knoten. Diese (_dynNode_) Knoten  erben von dynNode und haben dynamische Variablen und Funktionen für Zeitentwicklung. 
			virtual const nodeInfo getNodeInfo() { nodeInfo n = {_node_,0};  return n;};


			//			virtual bool equals (node * n) { return n->getNodeInfo().theNodeType == getNodeInfo().theNodeType;}


			//! returns a copy of this node instance. All nodes which are added to networks are created by such a call. Nodes which are created by standard constructors serve as blueprints only.
			virtual node *construct()  { throw "unimplemented function of node called!"; };


			//! Identifizierungs-Objekt für die Edges des Knotens
			typedef unsigned int edgeDescriptor;			

			virtual ~node() {
				if (number != numeric_limits<nodeDescriptor>::max())
					theNodes[number] = NULL;
			};

		private:
			nodeDescriptor getTarget (edge * e) { return e->targetNumber; }
		public:

			virtual edgeInfo getEdgeInfo (edgeDescriptor) { throw "unimplemented function of node called!"; };

			//! setzt das Kopplungsgewicht der Egde edgeDescriptor auf den Wert w
			virtual void setWeight (edgeDescriptor ed, baseType w)  { throw "unimplemented function of node called!"; };

			//! gimt einen Zeiger auf den Zielknoten der Edge ed zurück.
			virtual node* getTarget(edgeDescriptor ed) { throw "unimplemented function of node called!"; };

			//! gibt das Kopplungsgewicht der Edge ed zurück
			virtual baseType getWeight (edgeDescriptor ed)  { throw "unimplemented function of node called!"; } ;

			//! ruft die getState-Funktion des Zielknotens von ed zurück
			virtual baseType getTargetState (edgeDescriptor ed)  { throw "unimplemented function of node called!"; } ;


			virtual edge * getEdge (edgeDescriptor)  { throw "unimplemented function of node called!"; };		

			//!  Copy-Konstructor, der die neu-erzeugte Instanz zusätzlich in den Statischen Zeiger-Vector einträgt.
			node( const node &b )	{
				theNodes.push_back ( this );
				number = theNodes.size() - 1;
			}

			node () { number = numeric_limits<nodeDescriptor>::max(); };  

			// Verbindungen hinzufügen, entfernen
			//! Entfernt alle Edges, die auf den Knoten target zeigen, aus der Adjazenzliste 
			virtual bool unlink (nodeDescriptor targetNumber)  { throw "unimplemented function of node called!"; };

			virtual void removeEdge (edgeDescriptor e)   { throw "unimplemented function of node called!"; };

			virtual void removeEdges ()  { throw "unimplemented function of node called!"; };

			//! fügt einen Standardlink (weightedEdge) hinzu, der auf den Knoten mit der Nummer targetNumber zeigt.			
			virtual void link (nodeDescriptor targetNumber, baseType weight)  { throw "unimplemented function of node called!"; };

			//! fügt einen Link zum Knoten targetNumber hinzu, der von l kopiert wird.
			virtual void link (nodeDescriptor targetNumber, edge *l)  { throw "unimplemented function of node called!"; };

			//! gibt TRUE zurück, falls mindestens ein Link existiert, der auf den Knoten target zeigt.
			virtual bool isLinked ( node *target )  { throw "unimplemented function of node called!"; };

			//! gobt das Verbindungsgewicht zurück, vom Link zurück, der auf target zeigt. Falls keiner existiert: Rückgabewert 0.	 Falls mehrere existieren, weiß nicht.
			virtual baseType linkStrength ( node *target )  { throw "unimplemented function of node called!"; };

			virtual void normalizeInWeightSum(baseType d)  { throw "unimplemented function of node called!"; };

			// Statistikkram

			//! Debug-funktion, die die Knotenart, sowie Parameter auf die Konsole gibt.
			virtual void printStatistics(ostream &os, double nodeVerbosity, double edgeVerbosity);


			virtual void printEdgeStatistics ( ostream &os, double edgeVirtualVerbosity=1.0);
			//! gibt die Anzahl der Verbindungen zurück
			virtual unsigned int degree()  { throw "unimplemented function of node called!"; };

			//! gibt den lokalen Clustering-coeffizient zurück vom Knoten
			virtual float clustering ()  { throw "unimplemented function of node called!"; };

			//! gibt die Summe der Verbindungsgewichte aller ausgehende Verbindungen zurück.
			virtual float weightSum()  { throw "unimplemented function of node called!"; };


			//! gibt die Summer der Verbindungsgewichte aller eingehenden Verbindungen zurück.
			virtual float inWeightSum()  { throw "unimplemented function of node called!"; };

			//! gibt die Nummer im statischen Vector theNodes zurück, andessen Stelle ein Zeiger auf den  momentanen Knotens gespeichert ist. 
			virtual nodeDescriptor getNumber() { return number; }

			//! Statischer Vector mit Zeigern zu allen Knoten, die mit construct erzeugt wurden. 
			static vector<node* > theNodes;


			virtual void clean () {};

		protected:
			//! so wie couplingSum. Allerdings werden die Zustände zirkulär addiert.
			inline baseType getMeanPhaseCoherence();
		private:
			//! die Nummer vom Knoten.  theNodes[number] = this!
			nodeDescriptor number;   


	};








	inline node* edge::getTarget() { return node::theNodes [targetNumber];};



}



#endif
