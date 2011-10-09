

#ifndef sdeNode_h
#define sdeNode_h sdeNode_h

#include <cmath>



#include "gslNoise.h"
#include "containerNode.h"


using namespace std;

#include "dynNode.h"
namespace conedy
{

	//! --------------------------Node for Stochastic Differential Equations------------------------ //
	class sdeNode : public containerNode<baseType, 4> {


		public:


			sdeNode ( networkElementType n) : containerNode<baseType, 4> ( n ) { }

			virtual void operator()(baseType x[], baseType  dxdt[], baseType s[], baseType dsdx []) {throw "differential equation not defined for";};

			static void dgl (baseType *x, baseType* dxdt, baseType *s, baseType *dsdx )

			{
				list<containerNode<baseType,4>*>::iterator it;
				for ( it = nodeList.begin(); it != nodeList.end();it++ )
					( * ( (sdeNode *)*it )) ( &x[ ( *it )->startPosGslOdeNodeArray], &dxdt[ ( *it )->startPosGslOdeNodeArray] , &s[ (*it)->startPosGslOdeNodeArray], &dsdx[ (*it)->startPosGslOdeNodeArray] ) ;
			}






	};

}
#endif
