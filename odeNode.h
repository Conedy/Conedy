

/* last modifier: js */

#ifndef odeNode_h
#define odeNode_h odeNode_h

#include "node.h"
#include "gslNoise.h"
#include <valarray>
#include <map>


#include "containerNode.h"

#include "params.h"
#include "baseType.h"

using namespace std;

// //typedef valarray<double>params;



namespace conedy {


	//! Basis-Klasse, die Runge-Kutter 4. Ordnung implementiert.
	class odeNode : public containerNode<baseType,1> {
		private:

		protected:

			//! Zwischenspeicher, der in der swap-Funktion nach dynNode::tmp geschrieben wird.
			baseType *odeNodeTmp;


		public:
			//		odeNode()  {};


			odeNode(networkElementType n) : // ngls: Anzahl der Gleichungen, NodeNumber,  h Schrittweite
				containerNode<baseType,1>(n) {}

			virtual ~odeNode() {}

			virtual void operator()(const baseType x [], baseType dydx [])  = 0;

			static int func ( double t,const double y[], double f[], void *params )
			{
				list<containerNode<baseType,1>*>::iterator it;
				for ( it = nodeList.begin(); it != nodeList.end();it++ )
					( * ( (odeNode *)*it )) ( &y[ ( *it )->startPosGslOdeNodeArray], &f[ ( *it )->startPosGslOdeNodeArray] );
				return GSL_SUCCESS;
			}



	};




}


#endif
