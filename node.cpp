

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

	baseType edgeVirtual::getTargetState() { return getTarget()->getState();}
//	inline node* edge::getTarget() { return node::theNodes [targetNumber];}


	ostream& edge::printStatistics( ostream &os, double edgeVerbosity, int theEdgeKind, string theEdgeName, baseType weight)
			{
				if (edgeVerbosity > 0.9)
				{
					os << node::theNodes[targetNumber]->getNumber() << "\t";
				}
				// Ausgabe Kind, Name
				if (edgeVerbosity> 1.9)
				{ 
				  	cout << "(";

				edgeInfo ei = getEdgeInfo();
					
//					os << "EdgeKind = " << theEdgeKind << "\t";
					os << theEdgeName << ", ";


				// Ausgabe Gewicht
					os << weight;
				}
				if (edgeVerbosity > 1.9)
					os <<  "), ";
				return os;
			};



	        ostream& edgeVirtual::printStatistics ( ostream &os, double edgeVerbosity) 
			  {
				edgeInfo ei = getEdgeInfo();
				edge::printStatistics(os, edgeVerbosity, ei.theEdgeKind, ei.theEdgeName,  getWeight());
				return os;
			}


	void node::printEdgeStatistics(ostream &os, double edgeVerbosity) {

throw "printEdgeStatistics OBSOLETE";

//		edgeDescriptor eit = 0;
//		edgeDescriptor oit = degree();
//
//		cout << "Anzahl Verbindungen:\t" << degree() << endl;
/*		cout << "Verbindung nach:\t";
		for ( ;eit != oit; eit++ )
		{
			getEdge(eit)->printStatistics( os, edgeVerbosity);
			cout << ",\t";
			// VERALTET( *eit )->printStatistics();

		}
		cout << endl;
*/


	}


	void node::printStatistics(ostream &os, double nodeVerbosity, double edgeVerbosity)
	{
		if (nodeVerbosity > 0.5)
		{	
			cout << "nodeName:\t"<< getNodeInfo().theNodeName << endl;
//			cout << "nodeType:\t"<< (int)getNodeInfo().theNodeType << endl;
			cout << "nodeKind:\t" ;
			if (getNodeInfo().theNodeKind & _dynNode_)
				cout << "dynNode ";
			if (getNodeInfo().theNodeKind & _inNode_)
				cout << "inNode ";
			if (getNodeInfo().theNodeKind & _outNode_)
				cout << "outNode";
			cout << endl;
		}
		cout << "nodeNumber:\t" << getNumber() << endl;
	
		printEdgeStatistics(os, edgeVerbosity);
	}

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
