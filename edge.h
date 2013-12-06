

#ifndef edge_h
#define edge_h edge_h

#include <boost/function.hpp>
#include <iostream>
//#include <boost/bind.hpp>
#include "params.h"
#include "dynNode.h"

#include "gslNoise.h"

using namespace std;


#include "node.h"
#define Getarget(type,pointer) (bind(&expression<type>::evaluate,(pointer)))





namespace conedy
{


	//! gewichtete Edge, bei der das Kopplungsgewicht in einer privaten Variable gespeichert wird
	template <typename EDGE>
		class weightedEdge : public EDGE
	{
		private:  // private

			baseType weight;

		public:
			weightedEdge() :  weight ( ( baseType ) 1 ) {};
			weightedEdge(baseType w) : weight (w) {};
			weightedEdge (nodeDescriptor targetNumber, baseType newWeight) : EDGE (targetNumber), weight(newWeight) {};

			const edgeInfo getEdgeInfo() {edgeInfo ei = {_weightedEdge_,_weighted_,"weightedEdge"};return ei;}
			baseType getWeight() { return weight; }
			//			baseType getTargetState();
			void setWeight(baseType newWeight) { weight = newWeight; }


			void setParameter(vector < baseType > parameter)
			{
				EDGE::setParameter(parameter);
				if (parameter.size() == 0)					return ;  // not all parameter have been specified. Stopping.
				weight = parameter[parameter.size() -1];
				parameter.pop_back();
			}
			void getParameter(vector < baseType > &parameter)
			{
				EDGE::getParameter(parameter);
				parameter.push_back(weight);
			}

			edgeVirtual *construct() { return new weightedEdge<EDGE> ( *this ); };

			ostream& printStatistics ( ostream &os, int edgeVerbosity)
			{
				edgeInfo ei = getEdgeInfo();
				edge::printStatistics(os, edgeVerbosity, ei.theEdgeKind, ei.theEdgeName,  getWeight());
				return os;
			}

	};

	typedef weightedEdge < edgeVirtual > weightedEdgeVirtual;


	//   template <typename EDGE>
	//	baseType weightedEdge<EDGE>::getTargetState() { return EDGE::getTarget()->getState(    ) ; }

	//! edge,
	template <typename EDGE>
		class staticWeightedEdge : public EDGE
	{
		public:  // private
			static baseType weight;

		public:
			staticWeightedEdge() {};
			//			staticWeightedEdge ( node* t ) : weightedEdge(t) {};
			staticWeightedEdge (baseType newWeight)  {    weight = newWeight;};

			staticWeightedEdge (nodeDescriptor targetNumber, baseType newWeight) : EDGE (targetNumber)  {    weight = newWeight;};
			const edgeInfo getEdgeInfo() {edgeInfo ei = {_staticWeightedEdge_,_weighted_,"staticWeightedEdge"}; return ei;}
			baseType getWeight() { return weight; }
			void  setWeight(baseType newW) { weight = newW; }
			//			baseType getTargetState() { return EDGE::getTarget()->getState (); }
			edgeVirtual *construct() { return new staticWeightedEdge ( *this ); };

			ostream& printStatistics ( ostream &os, int edgeVerbosity)
			{
				edgeInfo ei = getEdgeInfo();
				edge::printStatistics(os, edgeVerbosity, ei.theEdgeKind, ei.theEdgeName,  getWeight());
				return os;
			}

			void getParameter(vector < baseType > &parameter)
			{
				EDGE::getParameter(parameter);
				parameter.push_back(weight);
			}
			void setParameter(vector < baseType > parameter)
			{
				EDGE::setParameter(parameter);
				if (parameter.size() == 0)					return ;  // not all parameter have been specified. Stopping.
				weight = parameter[parameter.size() -1];
				parameter.pop_back();
			}




	};

	template <class EDGE>
		class staticComponent: public EDGE
	{
		static unsigned int which;
		public:


		staticComponent ( int c) {  which = c;}
		staticComponent ( )  { which = 0;}

		const edgeInfo getEdgeInfo() {
			edgeInfo ancestor = EDGE::getEdgeInfo();
			edgeInfo ei = {_staticComponent_,(edgeKind)(_weighted_ | ancestor.theEdgeKind), ancestor.theEdgeName + "_staticComponent" }; return ei;
		}

		baseType getTargetState()
		{
			return (  (dynNode*)  ( node::theNodes[EDGE::getTarget()] ) ) ->getState(which)   ;

		}
		edgeVirtual *construct() {
			return new staticComponent( *this );
		};

		void getParameter(vector < baseType > &parameter)
		{
			EDGE::getParameter(parameter);
			parameter.push_back(which);
		}

		void setParameter(vector < baseType > parameter)
		{
			EDGE::setParameter(parameter);
			if (parameter.size() == 0)					return ;  // not all parameter have been specified. Stopping.
			which = parameter[parameter.size() -1];
			parameter.pop_back();
		}



	};


	typedef staticWeightedEdge < edgeVirtual > staticWeightedEdgeVirtual;


	template <typename EDGE>
		baseType staticWeightedEdge<EDGE>::weight;

	template <typename EDGE>
		unsigned int staticComponent<EDGE>::which;

	template <class EDGE>
		class randomTarget : public EDGE
	{
		private:
			nodeDescriptor lower;
			nodeDescriptor upper;

		public:
			const edgeInfo getEdgeInfo() {
				edgeInfo ancestor = EDGE::getEdgeInfo();
				edgeInfo ei = {_randomTarget_, (char) ( _weighted_ | ancestor.theEdgeKind) ,  ancestor.theEdgeName + "_randomTarget"};  return ei;
			}


			void getParameter(vector < baseType> & parameter)
			{
				EDGE::getParameter(parameter);
				parameter.push_back(upper);
				parameter.push_back(lower);
			}

			void setParameter(vector < baseType > parameter)
			{
				EDGE::setParameter(parameter);
				if (parameter.size() == 0)					return ;  // not all parameter have been specified. Stopping.
				lower = parameter[parameter.size() -1];

				parameter.pop_back();
				upper = parameter[parameter.size() -1];
				parameter.pop_back();
			}

			nodeDescriptor getTarget() { return  gslNoise::getUniform(lower,upper); }
			randomTarget(nodeDescriptor l, nodeDescriptor u) : lower(l), upper(u) { }
			randomTarget() { }
			edgeVirtual *construct() { return new randomTarget<EDGE> ( *this ); };

	};


// 	};

	//! edge-Klasse, die nur States weitergibt, wenn sie einin bestimmten Wert überschreiten.
	template <class EDGE>
		class stepEdge: public EDGE
	{
		double threshold;
		public:
		stepEdge ( double t ) : threshold ( t )  {};
		stepEdge ( ){};
		const edgeInfo getEdgeInfo() {
			edgeInfo ancestor = EDGE::getEdgeInfo();
			edgeInfo ei = {_pulseCouple_,(char)( _weighted_ | ancestor.theEdgeKind),  ancestor.theEdgeName + "_step"};  return ei;}
			void setParameter(vector < baseType > parameter)
			{
				EDGE::setParameter(parameter);
				if (parameter.size() == 0)					return ;  // not all parameter have been specified. Stopping.
				threshold = parameter[parameter.size() -1];
				parameter.pop_back();
			}

			baseType getTargetState()
			{
				if ( EDGE::getTargetState()  >= threshold )
					return 1;
				else
					return 0;
			}
			edgeVirtual *construct() { return new stepEdge<EDGE> ( *this ); };


			/* void printStatistics()
				{
				cout << "(stepEdge,";
				weightedEdgeVirtual<baseType>::printStatistics();
				}*/

			// Überladung des Ausgabestreams
			//
			//
			//

			ostream& printStatistics ( ostream &os, int edgeVerbosity)
			{
				edgeInfo ei = getEdgeInfo();
				edge::printStatistics(os, edgeVerbosity, ei.theEdgeKind, ei.theEdgeName,  EDGE::getWeight());
				return os;
			}


	};

	//! edge-Klasse, die auf die die Einträge von x zeigt.


	template <class EDGE>
		class component: public EDGE
	{
		unsigned int which;

		public:

		void setParameter(vector < baseType > parameter)
		{
			EDGE::setParameter(parameter);
			if (parameter.size() == 0)					return ;  // not all parameter have been specified. Stopping.
			which = parameter[parameter.size() -1];
			parameter.pop_back();
		}

		component ( int c) :  which ( c ) {}
		component ( ) :  which ( 0 ) {}

		const edgeInfo getEdgeInfo() {
			edgeInfo ancestor = EDGE::getEdgeInfo();
			edgeInfo ei = {_component_,(edgeKind) (_weighted_ | ancestor.theEdgeKind), ancestor.theEdgeName + "_component" }; return ei;
		}

		baseType getTargetState()
		{
			return (  (dynNode*)  (node::theNodes[ EDGE::getTarget()] ) ) ->getState(which)   ;

		}
		edgeVirtual *construct() {
			return new component( *this );
		};





	};

	//! Edge mit Pulsekopplung und delay
	class pulsecoupleDelayEdge: public weightedEdgeVirtual
	{
		double threshold;
		int nextFiring;
		int timeDelay;
		public:
		pulsecoupleDelayEdge ( double th, double tD ) : threshold ( th ), timeDelay ( tD )  {};
		const edgeInfo getEdgeInfo() {edgeInfo ei = {_pulsecoupleDelayEdge_,_weighted_}; return ei;}
		baseType getTargetState()
		{
			if ( nextFiring == 0 )
			{
				if ( weightedEdgeVirtual::getTargetState() >= threshold )
					nextFiring = timeDelay;
				return 0;
			}
			else
			{
				if ( nextFiring == 1 )
				{
					nextFiring--;
					return this->getWeight();
				}
				else
				{
					nextFiring--;
					return 0;
				}
			}
		}
		edgeVirtual *construct() { return new pulsecoupleDelayEdge ( *this ); };


		/* void printStatistics()
			{
			cout << "(pulsecoupleDelayEdge,";
			weightedEdgeVirtual<baseType>::printStatistics();
			}*/

		// Überladung des Ausgabestreams
		//
		//

		ostream& printStatistics ( ostream &os, int edgeVerbosity)
		{
			edgeInfo ei = getEdgeInfo();
			edge::printStatistics(os, edgeVerbosity, ei.theEdgeKind, ei.theEdgeName,  getWeight());
			return os;
		}
	};




	//! Edge mit Delay
	class delayEdge : public weightedEdgeVirtual
	{
		vector <baseType> memory;
		int delay;
		int counter;

		public:

		const edgeInfo getEdgeInfo() {edgeInfo ei = {_delayEdge_,_weighted_}; return ei;}
		delayEdge ( int d ) : memory ( d+1 ), delay ( d ), counter ( 0 ) {};
		baseType getTargetState()
		{
			memory[counter] = weightedEdgeVirtual::getTargetState();
			counter++;
			if ( counter == delay +1 )
				counter = 0;
			return memory[counter];
		}
		edgeVirtual *construct() { return new delayEdge ( *this ); };

		// Überladung des Ausgabestreams
		ostream& printStatistics ( ostream &os, int edgeVerbosity)
		{
			// Ausgabe Header:
			//
			//
			//
			edgeInfo ei = getEdgeInfo();
			edge::printStatistics(os, edgeVerbosity, ei.theEdgeKind, ei.theEdgeName,  getWeight());

			if (edgeVerbosity>=2)
			{
				os << "delay = " << delay << "\t";
				os << "counter = " << counter << "\t";
				os << "size(memory) = " << memory.size() << "\t";
			}


			// Ausgabe Gewicht
			os << this->getWeight();

			return os;
		}
	};


	}


#endif

