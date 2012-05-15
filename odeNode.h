#ifndef odeNode_h
#define odeNode_h odeNode_h

//#include "gslNoise.h"
//#include <valarray>
//#include <map>


#include "containerNode.h"

//#include "params.h"
#include "baseType.h"

using namespace std;





// using baseType instead of basetype here, as the gsl does not support long baseType anyway

namespace conedy {


	//! Basis-Klasse, die Runge-Kutter 4. Ordnung implementiert.
	class odeNode : public containerNode<baseType,1> {
		private:

		protected:

			//! Zwischenspeicher, der in der swap-Funktion nach dynNode::x geschrieben wird.


		public:
			//		odeNode()  {};
			baseType *odeNodeTmp;


			odeNode(networkElementType n) : // ngls: Anzahl der Gleichungen, NodeNumber,  h Schrittweite
				containerNode<baseType,1>(n) {}

			odeNode(networkElementType n, unsigned int dim) : // ngls: Anzahl der Gleichungen, NodeNumber,  h Schrittweite
				containerNode<baseType,1>(n, dim) {}
			virtual ~odeNode() {}

//			virtual void operator()(valarray <baseType> & y , valarray <baseType> & f);


			virtual void operator() (const baseType  x[], baseType  dydx[]) = 0;



			

			static int dgl ( baseType t,const baseType y[], baseType f[], void *params );

	

			static void dgl (baseType *y, baseType* f);



	};




}


#endif
