

#include "dynNode.h"

#include "gslNoise.h"


namespace conedy
{
	baseType dynNode::time = 0.0;



		void dynNode::setState(  baseType a1, baseType a2 , baseType a3 , baseType a4 , baseType a5 , baseType a6 , baseType a7 , baseType a8 , baseType a9 , baseType a10 , baseType a11 , baseType a12 )
		{
				vector <baseType> argList;
				argList.push_back (a1);
				if (a2 == numeric_limits<baseType>::max())
				{
					setStateVec( argList);
					return;
				}
				argList.push_back (a2);
				if (a3 == numeric_limits<baseType>::max())
				{
					setStateVec( argList);
					return;
				}
				argList.push_back (a3);
				if (a4 == numeric_limits<baseType>::max())
				{
					setStateVec( argList);
					return;
				}
				argList.push_back (a4);
				if (a5 == numeric_limits<baseType>::max())
				{
					setStateVec( argList);
					return;
				}
				argList.push_back (a5);
				if (a6 == numeric_limits<baseType>::max())
				{
					setStateVec( argList);
					return;
				}
				argList.push_back (a6);
				if (a7 == numeric_limits<baseType>::max())
				{
					setStateVec( argList);
					return;
				}
				argList.push_back (a7);
				if (a8 == numeric_limits<baseType>::max())
				{
					setStateVec( argList);
					return;
				}
				argList.push_back (a8);
				if (a9 == numeric_limits<baseType>::max())
				{
					setStateVec( argList);
					return;
				}
				argList.push_back (a9);
				if (a10 == numeric_limits<baseType>::max())
				{
					setStateVec( argList);
					return;
				}
				argList.push_back (a10);
				if (a11 == numeric_limits<baseType>::max())
				{
					setStateVec( argList);
					return;
				}
				argList.push_back (a11);
				if (a12 == numeric_limits<baseType>::max())
				{
					setStateVec( argList);
					return;
				}
				argList.push_back (a12);
				setStateVec( argList);
				return;



		}


    void dynNode::excite(baseType couplingStrength)
    {
        x[0]+= couplingStrength;
    }



    void dynNode::printStatistics(ostream &os, int nodeVerbosity, int edgeVerbosity ) {
        node::printStatistics(os, nodeVerbosity, edgeVerbosity);
		  if (nodeVerbosity >= 2)
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

    void dynNode::randomizeState ( vector<boost::function<baseType () > > &r )
	 {
			vector<baseType> values (r.size());

        for ( unsigned int i = 0; i < r.size(); i++ )
				values[i]=r[i]();

		  setStateVec (values);
	 }

	void dynNode::setStateVec (vector <baseType> &r)
	{
		for (unsigned int i = 0 ; i < dimension(); i++)
				x[i] = r[i];
	}




baseType dynNode::endTime = 0.0;

baseType dynNode::startTime = 0.0;

}
