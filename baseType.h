

#ifndef baseType_h
#define baseType_h baseType_h



//#include "realRational.h"

//#include "aquafixed.h"

//using namespace boost;



#define PRECALCULATEWEIGHTSUM


//#define CALENDARQUEUE


#ifdef DOUBLE
typedef double baseType;

#elif defined LDOUBLE
typedef long double baseType;
#else
typedef double baseType;

#endif




//typedef Aqua::fixed_t baseType;




//typedef rational<int> baseType;

#endif

