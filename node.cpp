

#include "node.h"
#include "edge.h"

#include "gslNoise.h"

namespace conedy
{

	 baseType edge::getTargetState() { return node::theNodes[targetNumber]->getState(); }

	node::node () { number = numeric_limits<nodeDescriptor>::max(); };

			node::~node() {
				if (number != numeric_limits<nodeDescriptor>::max())
					theNodes[number] = NULL;
			};

	vector<node *> node::theNodes;

	baseType edgeVirtual::getTargetState() { return node::theNodes[getTarget()]->getState();}
//	inline node* edge::getTarget() { return node::theNodes [targetNumber];}





	ostream& edge::printStatistics( ostream &os, int edgeVerbosity, int theEdgeKind, string theEdgeName, baseType weight)
			{
				if (edgeVerbosity >= 1)
				{
					os << node::theNodes[targetNumber]->getNumber() << "\t";
				}
				// Ausgabe Kind, Name
				if (edgeVerbosity >= 2)
				{
				  	cout << "(";

				edgeInfo ei = getEdgeInfo();

//					os << "EdgeKind = " << theEdgeKind << "\t";
					os << theEdgeName << ", ";

				// Ausgabe Gewicht
					os << weight;
				}
				if (edgeVerbosity >= 2)
					os <<  "), ";
				return os;
			};



	        ostream& edgeVirtual::printStatistics ( ostream &os, int edgeVerbosity)
			{
				edgeInfo ei = getEdgeInfo();
				edge::printStatistics(os, edgeVerbosity, ei.theEdgeKind, ei.theEdgeName,  getWeight());
				return os;
			}

	void node::printEdgeStatistics(ostream &os, int edgeVerbosity)
	{

	}


	void node::printStatistics(ostream &os, int nodeVerbosity, int edgeVerbosity)
	{
		if (nodeVerbosity >= 1)
		{
			cout << "nodeName:\t"<< getNodeInfo().theNodeName << endl;
//			cout << "nodeType:\t"<< (int)getNodeInfo().theNodeType << endl;
			cout << "nodeKind:\t" ;
			if (getNodeInfo().theNodeKind & _dynNode_)
				cout << "dynNode ";
			if (getNodeInfo().theNodeKind & _inNode_)
				cout << "inNode ";
			if (getNodeInfo().theNodeKind & _outNode_)
				cout << "outNode ";
			if (getNodeInfo().theNodeKind & _ode_)
				cout << "ode ";
			if (getNodeInfo().theNodeKind & _sde_)
				cout << "sde ";
			if (getNodeInfo().theNodeKind & _pco_)
				cout << "pco ";
			if (getNodeInfo().theNodeKind & _pcoDelay_)
				cout << "pcoDelay ";
			if (getNodeInfo().theNodeKind & _mapNode_)
				cout << "map ";
			cout << endl;
		}
		cout << "nodeNumber:\t" << getNumber() << endl;

		printEdgeStatistics(os, edgeVerbosity);
	}


	bool match (nodeDescriptor l, nodeDescriptor r) { return l == r; };	
	bool match (nodeKind l, nodeDescriptor r) { return node::theNodes[r]-> getNodeInfo().theNodeKind & l;  };	
	bool match (nodeDescriptor l, nodeKind r) { return node::theNodes[l]-> getNodeInfo().theNodeKind & r;  };	
	bool match (nodeDescriptor l, networkElementType r) { return node::theNodes[l]->getNodeInfo().theNodeType == r; };	
	bool match (networkElementType l, nodeDescriptor r) { return node::theNodes[r]->getNodeInfo().theNodeType == l;  };	



/*
	template <typename baseType>
	class timeCounter : public nodeVirtualEdges<baseType>
	{
		public:

			timeCounter() : nodeVirtualEdges<baseType> ( 0 ) { this->time = 0; };
			virtual void action() { this->time ++;}

			virtual int requiredTimeSteps() {return 1;};
			virtual void clean ( int timeSteps ) { this->time = 0;};
			int getTime() {return this->time; };

			virtual nodeVirtualEdges<baseType> *construct() { return new timeCounter<baseType> ( *this ); };
	};

*/


}
