#ifndef ode_h
#define ode_h ode_h


#ifdef LDOUBLE
#include "stdOdeIntegrator.h"
namespace conedy {
typedef stdOdeIntegrator ode;
#define SUCCESS 1
}
#elif defined (DOUBLE)
#include "gslOdeNode.h"
namespace conedy {
typedef gslOdeNode ode;
#define SUCCESS GSL_SUCCESS 
}

#elif defined FLOAT

#define SUCCESS 1
#include "stdOdeIntegrator.h"
namespace conedy {
typedef stdOdeIntegrator ode;
}


#else
#define DOUBLE
#define SUCCESS 1
#include "gslOdeNode.h"
namespace conedy {
typedef gslOdeNode ode;
}
#endif


#endif
