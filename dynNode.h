


#ifndef dynNodeInterface_h
#define dynNodeInterface_h  dynNodeInterface_h

#include "node.h"
#include "params.h"
#include "baseType.h"
//#include "edge.h"

#include <boost/function.hpp>



#ifndef M_PI
#define M_PI    3.14159265358979323846f
#endif


#define forEachEdge(whatToDo) node::edgeDescriptor ia, ie; \
	ia = 0; \
ie = degree(); \
for (;ia !=ie;ia++) { \
	baseType state = getTargetState(ia); \
	baseType weight = getWeight(ia); \
	whatToDo; }


namespace conedy
{
	//! Interface für die dynamischen Eigenschaften (Zeitentwicklung) der Knoten.
	class dynNode : public node, public params<baseType>

	{
			//! Zeiger auf Speicherplatz für die
		protected:
		public:

			baseType *  x;


			virtual const nodeInfo getNodeInfo() { nodeInfo n = {_dynNodeNodeType_,_dynNode_,"dynNode"};  return n;};


//			static gslNoise random;

			static baseType startTime;
			static baseType time;
			//! Ende der Integrationsperiode. Wird vor allem für gslodeNode benötigt.
			static baseType endTime;

			dynNode ( networkElementType n) : params<baseType>( n ) {}

			dynNode (networkElementType n, unsigned int dim);

			dynNode () : params <baseType> (_dynNodeNodeType_) {}

			virtual void evolve(baseType time) { cerr << this->getNodeInfo().theNodeName << endl;
				throw "evolve of dynNode called";}
			virtual bool timeEvolution () { return 0; };
			virtual bool requiresUpkeep() { return 0;};
			virtual const unsigned int dimension () const { return 0; }

			virtual baseType getHiddenComponent ( int component ) {return x[component];}
			virtual baseType getState() { return this->getState(0);  }

			virtual void upkeep() { throw "upkeep of dynNode called";}

			virtual node * construct () { throw "construct of dynNode called !"; }

			virtual void printStatistics(ostream &os, baseType nodeVerbosity, baseType edgeVerbosity);

			virtual  baseType getMeanPhaseCoherence() { throw "getMeanPhaseCoherence";}
			virtual	baseType couplingSum() { throw "couplingSum"; }
			virtual	void fire () { throw "fire"; }


			virtual void excite(baseType couplingStrength);

			dynNode( const dynNode &b);

			virtual void setStateVec (vector <baseType>  &r);
			virtual void randomizeState ( boost::function<baseType () > &r ) { vector <boost::function<baseType () > >  dummy; dummy.push_back(r); randomizeState(dummy); }

			virtual void randomizeState ( vector <boost::function<baseType () > > &r );

			virtual baseType getState (unsigned int component) { return x[component];}

			void setState(  baseType a1, baseType a2 = numeric_limits<baseType>::max(), baseType a3 = numeric_limits<baseType>::max(), baseType a4 = numeric_limits<baseType>::max(), baseType a5 = numeric_limits<baseType>::max(), baseType a6 = numeric_limits<baseType>::max(), baseType a7 = numeric_limits<baseType>::max(), baseType a8 = numeric_limits<baseType>::max(), baseType a9 = numeric_limits<baseType>::max(), baseType a10 = numeric_limits<baseType>::max(), baseType a11 = numeric_limits<baseType>::max(), baseType a12 = numeric_limits<baseType>::max());





	};



	//! Edge-Klasse, die n.te Komponente des dynamischen Knotens abfragt (dynNodeTemplate::x[n])




};



#endif





