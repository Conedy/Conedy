#include "odeNode.h"

#include <gsl/gsl_errno.h>


namespace conedy {

	int odeNode::dgl ( baseType t,const baseType y[], baseType f[], void *params )
	{
		list<containerNode<baseType,1>*>::iterator it;
		for ( it = nodeList.begin(); it != nodeList.end();it++ )
			( * ( (odeNode *)*it )) ( &y[ ( *it )->startPosGslOdeNodeArray], &f[ ( *it )->startPosGslOdeNodeArray] );
		return GSL_SUCCESS;
	}

	void odeNode::dgl (baseType *y, baseType* f)
	{
		list<containerNode<baseType,1>*>::iterator it;
		for ( it = nodeList.begin(); it != nodeList.end();it++ )
			( * ( (odeNode *)*it )) ( &y[ ( *it )->startPosGslOdeNodeArray], &f[ ( *it )->startPosGslOdeNodeArray] );
	}

}
