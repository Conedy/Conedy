

#ifndef fullNetwork_h
#define fullNetwork_h fullNetwork_h


#include "baseType.h"
#include "node.h"
#include "ioNode.h"
#include "createNetwork.h"
#include "spatialNetwork.h"
//#include "stdOdeIntegrator.h"

#include "sde.h"
#include "ode.h"
#include "mapNode.h" 
//#include "pulseCoupledExcitatoryNeuron.h" 
#include "pco.h"

//namespace conedy {
//typedef odeNode stdOdeIntegrator;   // Runge-Kutta Ord4



//typedef gslOdeNode stdOdeIntegrator;   // Runge-Kutta 8,9 mit adaptiver Schrittweite aus der GSL
//#define GSLODE
//}

#include "dynNetwork.h"
#include "statisticsNetwork.h"

// #include "dynNode.h" 
#include "nodeImplement.h"

// addNewNodes here
#include "generatedFullNetwork.h"

#define EVENTCOUNT












#if OPENGL

#include "glNetwork.h"


namespace  conedy {



template <typename T>
class MyNetwork :  public statisticsNetwork, public createNetwork,public GLNetwork<T>
{
	public :
		MyNetwork() {};
		

};

}

#else

namespace conedy {




//! MyNetwork ist die Netzwerk-Klasse, die vom Parser benutzt wird. Alle benötigten Funktionen werden haer han 
template <typename T>
class MyNetwork : public createNetwork, public statisticsNetwork, public spatialNetwork
{
	public :
		MyNetwork() {};
	

};

}
#endif



#endif
