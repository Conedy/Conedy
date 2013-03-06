#ifndef ode_h
#define ode_h ode_h


#ifdef LDOUBLE
#include "stdOdeIntegrator.h"
namespace conedy {
typedef stdOdeIntegrator ode;
}
#elif defined (DOUBLE)
#include "gslOdeNode.h"
namespace conedy {
typedef gslOdeNode ode;
}

#elif defined FLOAT


#include "stdOdeIntegrator.h"
namespace conedy {
typedef stdOdeIntegrator ode;
}


#else
#define DOUBLE
#include "gslOdeNode.h"
namespace conedy {
typedef gslOdeNode ode;
}
#endif


#endif
