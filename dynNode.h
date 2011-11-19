


#ifndef dynNodeInterface_h
#define dynNodeInterface_h  dynNodeInterface_h

#include "node.h"
#include "params.h"
#include "baseType.h"
//#include "edge.h"
#include "params.h"

#include <boost/function.hpp>



#ifndef M_PI
#define M_PI    3.14159265358979323846f
#endif


#define FOREACHCONNECTEDNODE(whatToDo) node::edgeDescriptor ia, ie; \
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
  public:
    
    
    
	 virtual const nodeInfo getNodeInfo() { nodeInfo n = {_dynNodeNodeType_,_dynNode_,"dynNode"};  return n;};

	
	static gslNoise random;

	 static baseType startTime;
    static baseType time;
    //! Ende der Integrationsperiode. Wird vor allem für gslodeNode benötigt.
    static baseType endTime;
    
    dynNode ( networkElementType n) : params<baseType>( n ) {}

		dynNode (networkElementType n, unsigned int dim);

	dynNode () : params <baseType> (_dynNodeNodeType_) {}

    virtual void evolve(double time) { throw "evolve of dynNode called";}
    virtual bool timeEvolution () { return 0; };
	 virtual bool requiresUpkeep() { return 0;};
    virtual const unsigned int dimension () const { return 0; }
 
    virtual baseType getHiddenComponent ( int component ) {return x[component];}
    virtual baseType getState() {return x[0];  }

		virtual void upkeep() { throw "upkeep of dynNode called";}

	virtual node * construct () { throw "construct of dynNode called !"; }

    virtual void printStatistics(ostream &os, double nodeVerbosity, double edgeVerbosity);

	virtual	baseType getMeanPhaseCoherence() { throw "getMeanPhaseCoherence";}
	virtual	baseType couplingSum() { throw "couplingSum"; }
	virtual	void fire () { throw "fire"; }
  
    //! Zeiger auf Speicherplatz für die
    baseType *  x;
 
    virtual void excite(baseType couplingStrength);

    dynNode( const dynNode &b);

	 virtual void setStateVec (vector <double>  &r);
 	 virtual void randomizeState ( boost::function<double () > &r ) { vector <boost::function<double () > >  dummy; dummy.push_back(r); randomizeState(dummy); }

    virtual void randomizeState ( vector <boost::function<double () > > &r );
    

		void setState(  baseType a1, baseType a2 = numeric_limits<baseType>::max(), baseType a3 = numeric_limits<baseType>::max(), baseType a4 = numeric_limits<baseType>::max(), baseType a5 = numeric_limits<baseType>::max(), baseType a6 = numeric_limits<baseType>::max(), baseType a7 = numeric_limits<baseType>::max(), baseType a8 = numeric_limits<baseType>::max(), baseType a9 = numeric_limits<baseType>::max(), baseType a10 = numeric_limits<baseType>::max(), baseType a11 = numeric_limits<baseType>::max(), baseType a12 = numeric_limits<baseType>::max())
		{
				vector <baseType> argList;
				argList.push_back (a1);
				if (a2 == numeric_limits<baseType>::max())
				{	
					setStateVec( argList);
					return;
				}
				argList.push_back (a2);
				if (a3 == numeric_limits<baseType>::max())
				{	
					setStateVec( argList);
					return;
				}
				argList.push_back (a3);
				if (a4 == numeric_limits<baseType>::max())
				{	
					setStateVec( argList);
					return;
				}
				argList.push_back (a4);
				if (a5 == numeric_limits<baseType>::max())
				{	
					setStateVec( argList);
					return;
				}
				argList.push_back (a5);
				if (a6 == numeric_limits<baseType>::max())
				{	
					setStateVec( argList);
					return;
				}
				argList.push_back (a6);
				if (a7 == numeric_limits<baseType>::max())
				{	
					setStateVec( argList);
					return;
				}
				argList.push_back (a7);
				if (a8 == numeric_limits<baseType>::max())
				{	
					setStateVec( argList);
					return;
				}
				argList.push_back (a8);
				if (a9 == numeric_limits<baseType>::max())
				{	
					setStateVec( argList);
					return;
				}
				argList.push_back (a9);
				if (a10 == numeric_limits<baseType>::max())
				{	
					setStateVec( argList);
					return;
				}
				argList.push_back (a10);
				if (a11 == numeric_limits<baseType>::max())
				{	
					setStateVec( argList);
					return;
				}
				argList.push_back (a11);
				if (a12 == numeric_limits<baseType>::max())
				{	
					setStateVec( argList);
					return;
				}
				argList.push_back (a12);
				setStateVec( argList);
				return;



		}





};
  
  
  
  //! Edge-Klasse, die n.te Komponente des dynamischen Knotens abfragt (dynNodeTemplate::x[n])

  
  
  
};



#endif





