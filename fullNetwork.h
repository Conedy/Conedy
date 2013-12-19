

#ifndef fullNetwork_h
#define fullNetwork_h fullNetwork_h

#include "fullNetwork.h"

#include "baseType.h"
#include "createNetwork.h"
#include "spatialNetwork.h"
#include "dynNetwork.h"
#include "statisticsNetwork.h"

#include "ioNode.h"
#include "sde.h"
#include "ode.h"
#include "mapNode.h" 
#include "pco.h"
#include "nodeImplement.h"





#define EVENTCOUNT


#if OPENGL

#include "glNetwork.h"


namespace  conedy {


class networkTemplate :  public statisticsNetwork, public createNetwork,public GLNetwork
{
	public :
		networkTemplate() {} 
		

};

}

#else

namespace conedy {





//! networkTemplate ist die Netzwerk-Klasse, die vom Parser benutzt wird. Alle benötigten Funktionen werden haer han 
class networkTemplate : public createNetwork, public statisticsNetwork, public spatialNetwork
{
	public :
		networkTemplate() {}  
	

};

class directedNetwork : public networkTemplate
{
	public:
		directedNetwork();// { network::setDirected(); }
};


class undirectedNetwork : public networkTemplate
{
	public:
		undirectedNetwork();// { network::setUndirected(); }
};


}
#endif



#endif
