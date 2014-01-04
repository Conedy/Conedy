#include "odeNode.h"


#include <gsl/gsl_errno.h>

#include "ode.h"

namespace conedy {

	int odeNode::dgl ( baseType t,const baseType y[], baseType f[], void *params )
	{

				baseType * originalNodeStates = containerNode<baseType,1>::dynamicVariablesOfAllDynNodes;
				containerNode<baseType,1>::dynamicVariablesOfAllDynNodes = const_cast<baseType*> (y);

				list<containerNode<baseType,1>*>::iterator it;
				for ( it = containerNode<baseType,1>::nodeList.begin(); it != containerNode<baseType,1>::nodeList.end();it++ )
					( * ((odeNode*) * it) )
							( &y[ ( *it )->startPosGslOdeNodeArray],
							 &f[ ( *it )->startPosGslOdeNodeArray] );
				return SUCCESS;
				containerNode<baseType,1>::dynamicVariablesOfAllDynNodes = originalNodeStates;

	}

	void odeNode::dgl (baseType *y, baseType* f)
	{

				baseType * originalNodeStates = containerNode<baseType,1>::dynamicVariablesOfAllDynNodes;
				containerNode<baseType,1>::dynamicVariablesOfAllDynNodes = const_cast<baseType*> (y);

				list<containerNode<baseType,1>*>::iterator it;
				for ( it = containerNode<baseType,1>::nodeList.begin(); it != containerNode<baseType,1>::nodeList.end();it++ )
					(* ((odeNode*) *it) ) 
							( &y[ ( *it )->startPosGslOdeNodeArray],
							 &f[ ( *it )->startPosGslOdeNodeArray] );
				return;
				containerNode<baseType,1>::dynamicVariablesOfAllDynNodes = originalNodeStates;


	}

}
