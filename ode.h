



#ifndef ode_h
#define ode_h ode_h






#ifdef DOUBLE
#include "gslOdeNode.h"
namespace conedy {
typedef gslOdeNode ode;
}
#endif


#ifdef LDOUBLE
#include "stdOdeIntegrator.h"
namespace conedy {
typedef stdOdeIntegrator ode;
}
#endif



#endif
