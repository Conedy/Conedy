

#include "dynNode.h"


namespace conedy 
{
	baseType dynNode::time = 0.0;




    void dynNode::excite(baseType couplingStrength)
    {
        tmp[0]+= couplingStrength;
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
           	     cout << tmp[i]<<  " " ;
			  }

		  }
			os << endl;
    }

    dynNode::dynNode( const dynNode &b ) : node ( b ), params<baseType>(b)
    {
        if ( b.dimension() > 0 )
        {
            tmp = ( baseType* ) calloc ( b.dimension(),sizeof ( baseType ) );
            for (unsigned int i = 0; i < b.dimension(); i++)
                tmp[i] = 0;
        }
        else
            tmp = NULL;
    }

    void dynNode::randomizeState ( vector<boost::function<double () > > &r )
	 {
			vector<double> values (r.size());

        for ( unsigned int i = 0; i < r.size(); i++ )
				values[i]=r[i]();
		
		  setInitialCondition (values);
	 }


	void dynNode::setInitialCondition (vector <double> &r)
	{
		for (unsigned int i = 0 ; i < dimension(); i++)
				tmp[i] = r[i];

   }




gslNoise dynNode::random;

baseType dynNode::endTime = 0.0;

baseType dynNode::startTime = 0.0;

}
