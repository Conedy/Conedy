#ifndef node_h
#define node_h node_h


#include "networkConstants.h"
#include "baseType.h"

#include <iostream>
#include <vector>


namespace conedy
{
	using namespace std;
	// Nodetype   : int


	
	typedef short int nodeKind; // node kinds correspond to different kinds of dynamical systems or to special nodes for file input and output 
	

	const nodeKind  _inNode_ = 1 << 1;
	const nodeKind  _outNode_ = 1 << 2;
	const nodeKind  _dynNode_ = 1 << 3;
	const nodeKind  _ode_ = 1 << 4;
	const nodeKind  _sde_ = 1 << 5;
	const nodeKind  _pco_ = 1 << 6;
	const nodeKind  _pcoDelay_ = 1 << 7;
	const nodeKind  _mapNode_ = 1 << 8;



	typedef char edgeKind;

	const edgeKind	_weighted_	= 1 << 1;
	const edgeKind	_polynomial_	= 1 << 2;  // erbt von params<vector<baseType>>

	//! identifier for nodes, determines the maximum number of nodes.
	typedef unsigned int nodeDescriptor;


	//! info-object which is returned by all nodes.
	struct nodeInfo
	{	// a unique identifier for the node type
		networkElementType theNodeType;
		// a bit mask for booleans which specify the kind of the node. inNode | outNode | dynNode
		nodeKind  theNodeKind;
		// the node name. Is used by printNodeStatistics
		string theNodeName;
	};

	//! info-object which is returned by all edges
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
	//! The inheritance looks as following. For static edges:
	//!	 edge -> edge1 -> edge2 -> edge...
	//! 	edge1, edge2 are here different 'features' for edges like coupling weights, edges which point to specific components of nodes, etc.
	//! 	Filter chains can also be implemeted in this way, but is not at the moment.
	//! For virtual edges:
	//		 edge -> edgeVirtual -> edge1 -> dege2 -> edge...
	//		 Class which contain the edge features edge1, edge2, ... are the same as for static edges. However, functions like getWeight, getTarget and getTargetSTate are  differently interpreted by the compiler. For the static approach they are  overloadad funtcions, for the virtual approach they are virtual functions. This allows
	class edge
	{

		public:
			typedef dynNode targetNodeType;

			//! Number of the target node, pointer to the node is store in node::thenodes
			nodeDescriptor targetNumber;
			edge() : targetNumber(0) {};
			edge ( nodeDescriptor t) :targetNumber ( t ) {};

		public:
			//! Return pointer to the target node.
			nodeDescriptor getTarget();// { return node::theNodes [targetNumber];}


			void setParameter(vector < baseType > parameter)  { }
			void getParameter(vector < baseType > &parameter)  { }


			//! Returns the state of the target node.
			baseType getTargetState();

			//! Return info-object for the edge.
			const edgeInfo getEdgeInfo() {edgeInfo ei = {_edge_,0}; return ei;}


			//			edge *construct() { return new edge ( *this ); };

			//! print information about the edge to the console.
			ostream& printStatistics ( ostream &os, int edgeOptVerbosity, int theEdgeKind, string theEdgeName, baseType weight);

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
			virtual void setParameter(vector < baseType > parameter)  { }
			virtual void getParameter(vector < baseType > &parameter)  { }
			virtual nodeDescriptor getTarget() { return edge::getTarget();}
			virtual baseType getTargetState();
			virtual const edgeInfo getEdgeInfo() {edgeInfo ei = {_edgeVirtual_,0, "edgeVirtual"}; return ei;}
			virtual edgeVirtual *construct() { return new edgeVirtual ( *this ); };
			virtual ostream& printStatistics ( ostream &os, int edgeVirtualVerbosity = 1);
			virtual ~edgeVirtual() {}
			virtual baseType getWeight() { return (baseType)1; }
			virtual void setWeight(baseType newWeight) {throw "Trying to set weight of unweighted edge!";}

	};






	/*!
	  \Brief  Base class for all nodes.

	  Contains a list of edges and supplies functions like link and unlink, which change this list.
	  All these functions are only interface functions and are given two different implementations by nodeVirtualEdges and nodeTemplateEdges.
	  Also contains a vector of pointer to all nodes, which serves as lookup table. In this way edges need only memorize a 32 bit node number instead of a 64 bit pointer.

*/
	class node
	{
		public:


			//! virtual function, which returns the standard node state. don't use, its slow. Use specialized edges.
			virtual baseType getState() { throw "getState von nodeVirtual aufgerufen !";}


			//! returns a description object for the node. The object consists of an identifying integer, a bitmask for the node kind and a string for the node name
			virtual const nodeInfo getNodeInfo() { nodeInfo n = {_node_,0};  return n;};




			//! returns a copy of this node instance. All nodes which are added to networks are created by such a call. Nodes which are created by standard constructors serve as blueprints only.
			virtual node *construct()  { throw "unimplemented function construct of node called!"; };


			//! Identifizierungs-Objekt für die Edges des Knotens XXX obsolete ?
			typedef unsigned int edgeDescriptor;

			virtual ~node();

		private:

			//! return the identifying integer of the given edge.  XXX obsolete ?
			nodeDescriptor getTarget (edge * e) { return e->targetNumber; }
		public:

			//! return the description object for the edge.
			virtual edgeInfo getEdgeInfo (edgeDescriptor) { throw "unimplemented function getEdgeInfo of node called!"; };

			//! sets the weight of the edge ed to w.
			virtual void setWeight (edgeDescriptor ed, baseType w)  { throw "unimplemented function setWeight of node called!"; };

			//! returns a pointer to the target of edge ed XXX should be returning nodedescriptor ?
			virtual nodeDescriptor getTarget(edgeDescriptor ed) { throw "unimplemented function getTarget  of node called!"; };

			//! returns the weight of edge ed.
			virtual baseType getWeight (edgeDescriptor ed)  { throw "unimplemented function getWeight of node called!"; } ;

			//! returns the state of the target of edge ed XXX slow
			virtual baseType getTargetState (edgeDescriptor ed)  { throw "unimplemented function getTargetState of node called!"; } ;

			//! return a pointer to the edge with given edgeDescriptor XXX obsolete ?
			virtual edgeVirtual * getEdge (edgeDescriptor)  { throw "unimplemented function getEdge of node called!"; };

			//!  Copy-constructor. Constructed nodes are inserted into the lookup table node::theNodes
			node( const node &b )	{ theNodes.push_back ( this );   number = theNodes.size() - 1;}


			//! Construktor
			node ();

			// manage connections
			
			//! removes all edges pointing to targetNumber.
			virtual bool unlink (nodeDescriptor targetNumber)  { throw "unimplemented function unlink of node called!"; };

			//! remove edge e.
			virtual void removeEdge (edgeDescriptor e)   { throw "unimplemented function removeEdge of node called!"; };

			virtual void removeEdges ()  { throw "unimplemented function removeEdges of node called!"; };

			//! adds a link which points targetNumber with weight weight.
			virtual void link (nodeDescriptor targetNumber, baseType weight)  { throw "unimplemented function link of node called!"; };

			//! adds a link which is copied from l.
			virtual void link (nodeDescriptor targetNumber, edgeVirtual *l)  { throw "unimplemented function link of node called!"; };

			//! returns true if there is at least one link which points to target
			virtual bool isLinked ( nodeDescriptor target )  { throw "unimplemented function isLinked of node called!"; };

			//! returns the weight of a link which points to target. Returns 0 if no such link exists.
			virtual baseType linkStrength ( nodeDescriptor target )  { throw "unimplemented function linkStrength of node called!"; };


			//! 
			virtual void normalizeInWeightSum(baseType d)  { throw "unimplemented function normalizeInWeightSum of node called!"; };

			// Statistikkram

			//! debug-function which prints all connections and their type to os, depending on nodeVerbosity and edgeVerbosity
			virtual void printStatistics(ostream &os, int nodeVerbosity, int edgeVerbosity);

			virtual void printEdgeStatistics(ostream &os, int edgeVerbosity = 1);

			//! returns the number of connections 
			virtual unsigned int degree()  { throw "unimplemented function degree of node called!"; };

			//! gibt den lokalen Clustering-coeffizient zurück vom Knoten TODO move to statisticNetwork
			virtual baseType clustering ()  { throw "unimplemented function clustering of node called!"; };

			//! gibt die Summe der Verbindungsgewichte aller ausgehende Verbindungen zurück TODO move to statisticNetwork.
			virtual baseType weightSum()  { throw "unimplemented function weightSum of node called!"; };


			//! gibt die Summer der Verbindungsgewichte aller eingehenden Verbindungen zurück TODO move to statisticNetwork.
			virtual baseType inWeightSum()  { throw "unimplemented function inWeightSum of node called!"; };


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


	inline nodeDescriptor edge::getTarget() { return  targetNumber;};


	bool match (nodeDescriptor l, nodeDescriptor r); 
	bool match (nodeKind l, nodeDescriptor r) ;
	bool match (nodeDescriptor l, nodeKind r) ;
	bool match (nodeDescriptor l, networkElementType r) ;
	bool match (networkElementType l, nodeDescriptor r) ;


}



#endif
