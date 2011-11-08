

#include "dynNode.h"


namespace conedy 
{
	baseType dynNode::time = 0.0;




    void dynNode::excite(baseType couplingStrength)
    {
        x[0]+= couplingStrength;
    }



    void dynNode::printStatistics(ostream &os, double nodeVerbosity, double edgeVerbosity ) {
        node::printStatistics(os, nodeVerbosity, edgeVerbosity);
		  if (nodeVerbosity > 1.5)
		  {
	        params<baseType>::printStatistics();
			  if (dimension() > 0)
			  {	  
	        	cout << "state: " ;
	        	for (unsigned int i = 0; i <dimension(); i++)
           	     cout << x[i]<<  " " ;
			  }

		  }
			os << endl;
    }


	 dynNode::dynNode ( networkElementType n, unsigned int dim): params<baseType>(n)
	{
		x = (baseType* ) calloc ( dim, sizeof (baseType));
	}
		


    dynNode::dynNode( const dynNode &b ) : node ( b ), params<baseType>(b)
    {
        if ( b.dimension() > 0 )
        {
            x = ( baseType* ) calloc ( b.dimension(),sizeof ( baseType ) );
            for (unsigned int i = 0; i < b.dimension(); i++)
                x[i] = b.x[i];
        }
        else
            x = NULL;
    }

/*	void dynNode::setInitialConditionVec (  vector <baseType> argList )
	{
			dynamic_cast<dynNode*>( ( node::theNodes[nodeNumber] ) )->setInitialCondition(argList);
		else
			throw "Error. Der Knoten ist gar nicht vom Typ Dynnode.";


	}
*/

    void dynNode::randomizeState ( vector<boost::function<double () > > &r )
	 {
			vector<double> values (r.size());

        for ( unsigned int i = 0; i < r.size(); i++ )
				values[i]=r[i]();
		
		  setStateVec (values);
	 }
	
	void dynNode::setStateVec (vector <double> &r)
	{
		for (unsigned int i = 0 ; i < dimension(); i++)
				x[i] = r[i];
	}



gslNoise dynNode::random;

baseType dynNode::endTime = 0.0;

baseType dynNode::startTime = 0.0;

}
