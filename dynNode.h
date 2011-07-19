


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
    
    
	virtual bool equals (node * n) { return node::equals(n)  && (params<baseType>::row ==  ((dynNode*)n)->row);  }
    
	 virtual const nodeInfo getNodeInfo() { nodeInfo n = {_dynNodeNodeType_,_dynNode_,"dynNode"};  return n;};

	
	static gslNoise random;

	 static baseType startTime;
    static baseType time;
    //! Ende der Integrationsperiode. Wird vor allem für gslodeNode benötigt.
    static baseType endTime;
    
    dynNode ( networkElementType n) : params<baseType>( n ) {}
	dynNode () : params <baseType> (_dynNodeNodeType_) {}

    virtual void evolve(double time) { throw "evolve of dynNode called";}
    virtual bool timeEvolution () { return 0; };
    virtual const unsigned int dimension () const { return 0; }
 
    virtual baseType getHiddenComponent ( int component ) {return tmp[component];}
    virtual baseType getState() {return tmp[0];  }


	virtual node * construct () { throw "construct of dynNode called !"; }

    virtual void printStatistics(ostream &os, double nodeVerbosity, double edgeVerbosity);

	virtual	baseType getMeanPhaseCoherence() { throw "getMeanPhaseCoherence";}
	virtual	baseType couplingSum() { throw "couplingSum"; }
	virtual	void fire () { throw "fire"; }
  
    //! Zeiger auf Speicherplatz für die
    baseType *  tmp;
 
    virtual void excite(baseType couplingStrength);

    dynNode( const dynNode &b);

	 virtual void setInitialCondition (vector <double> &r);
 	 virtual void randomizeState ( boost::function<double () > &r ) { vector <boost::function<double () > >  dummy; dummy.push_back(r); randomizeState(dummy); }

    virtual void randomizeState ( vector <boost::function<double () > > &r );
    



};
  
  
  
  //! Edge-Klasse, die n.te Komponente des dynamischen Knotens abfragt (dynNodeTemplate::tmp[n])

  
  
  
};



#endif





