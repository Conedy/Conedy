#include "dynNetwork.h"
#include "ioNode.h"
#include "containerNode.h"
#include "gslOdeNode.h"
#include "pco.h"
#include "stream.h"
#include "math.h"
#include "lyapunov.h"



namespace conedy
{
	void dynNetwork::removeObserver ()
	{
		remove (_outNode_);
		remove (_inNode_);
		inOutNodeList.clear();
	}

	baseType dynNetwork::callBack ( unsigned int eventSignature )
	{
		vector< dynNode *>::iterator it;
		for ( it= inOutNodeList.begin(); it != inOutNodeList.end(); it++ )
			( *it )->evolve(0.0);
		//				for ( it= inOutNodeList.begin(); it != inOutNodeList.end(); it++ )
		//					( *it )->swap();
		observationCounter++;

		streamOutNode::enter();

		baseType verb = getGlobal<baseType>("progressVerbosity");
		if ( ( verb != 0.0 ) && ( fmod(dynNode::time/( getGlobal<baseType> ("samplingTime") ), verb) < 0.9999 ) )
			cout <<"#------------Time:" << dynNode::time << endl;

		return dynNode::startTime + (observationCounter) * getGlobal<baseType> ("samplingTime");

	}

	void dynNetwork::dynamics(nodeDescriptor n)
	{
		((dynNode*)node::theNodes[n]) -> dynamics();
	}




	void dynNetwork::snapshotAtEventSignature ( nodeDescriptor eventSignature)
	{

		eventHandler::insertVisiterAtSignature(bind(&dynNetwork::snapshot,this),eventSignature);
	}


	void dynNetwork::snapshotAtEvent( nodeDescriptor eventNumber)
	{
		eventHandler::insertVisiter(bind(&dynNetwork::snapshot,this),eventNumber);
	}


	void dynNetwork::snapshotAtEventOfNode (nodeDescriptor nodeNumber, unsigned int eventSignature)
	{
		eventHandler * e = ( pcoBase * ) node::theNodes[nodeNumber];


		snapshotAtEvent ( e->myEventsStartAt + eventSignature);
	}





	dynNetwork::dynNetwork(const dynNetwork &b) : network (b), eventHandler(b)
	{

		eventHandler::registerCallBack ( _ioNode_, numeric_limits<baseType>::max() );
		//		eventHandler::registerCallBack ( _ioNode_, dynNode::time + (*samplingTime) );
	}







	baseType dynNetwork::getState (nodeDescriptor node, nodeDescriptor which)
	{
		if (which == 0)
			return node::theNodes[node]->getState();
		else
			return (( (dynNode* )node::theNodes[node])->getState(which));
	}

	void dynNetwork::evolveFor ( baseType duration )
	{
		evolve(dynNode::time, dynNode::time + duration);
	}

	void dynNetwork::evolve ( baseType startTime, baseType endTime )
	{




		if (dynNode::time < startTime)   // this probabliy does not work!
			pcoBase::timeOffset = startTime - dynNode::time;
		else
			pcoBase::timeOffset = 0;

		dynNode::startTime = startTime;
		dynNode::time = startTime;
		dynNode::endTime = endTime;

		eventHandler::registerCallBack ( _ioNode_, dynNode::time + getGlobal<baseType> ("samplingTime") );
//		eventHandler::registerCallBack ( _ioNode_, dynNode::time); // sdeNodes get a step of size 0 if this is used.


		observationCounter = 0;


		dynNetwork::clean (  );



// call possible visiters which may be at the snapshot event
		eventHandler::forceEvent (_ioNode_);

		vector< dynNode *>::iterator it;
		baseType timeTilEvent;
		while ( dynNode::time < endTime )
		{
			if ( eventHandler::nextEvent() >= endTime )
			{
				timeTilEvent = endTime - dynNode::time;
				for ( it = evolveList.begin(); it != evolveList.end(); it++ )
					( *it )->evolve ( timeTilEvent );
				for (it = upkeepList.begin(); it != upkeepList.end();it++)
					( *it) -> upkeep();

				dynNode::time += timeTilEvent;
				break;

			}
			else
				timeTilEvent = eventHandler::nextEvent() - dynNode::time;

#ifdef DEBUG
			if (timeTilEvent < -0.00000001)
				throw "Something seems to be wrang with the priorityqueue";
#endif




			for ( it = evolveList.begin(); it != evolveList.end(); it++ )
				( *it )->evolve ( timeTilEvent );
			for (it = upkeepList.begin(); it != upkeepList.end();it++)
				( *it) -> upkeep();

			dynNode::time += timeTilEvent;

			eventHandler::pop();

		}

		eventHandler::finalize();
	}


	void dynNetwork::realignAtEvent (string inputFilename, string outputFilename, networkElementType nt, baseType epsilon, unsigned int eventNumber, unsigned int skip)
	{
		nodeList * vl = new nodeList();
		verticesMatching(*vl, nt);
		realign *r = new realign ( inputFilename, outputFilename, vl, epsilon, skip);
		insertVisiter( bind(&realign::realignPeriodically, r), eventNumber);

		//		insertVisiter( bind(&dynNetwork::snapshot, this), eventNumber);



	}


	void dynNetwork::realignWhenDistant (string inputFilename, string outputFilename, networkElementType nt, baseType epsilon, unsigned int eventNumber, unsigned int multi)
	{
		nodeList * vl = new nodeList();
		verticesMatching(*vl, nt);
		realign *r = new realign ( inputFilename, outputFilename, vl, epsilon, multi);
		insertVisiter( bind(&realign::realignWhenDistant, r), eventNumber);

		//		insertVisiter( bind(&dynNetwork::snapshot, this), eventNumber);

	}




	void dynNetwork::realignAtEventSignature (string inputFilename, string outputFilename, networkElementType nt, baseType epsilon, unsigned int eventNumber, unsigned int skip)
	{
		nodeList * vl = new nodeList();
		verticesMatching(*vl, nt);
		realign *r = new realign ( inputFilename, outputFilename, vl, epsilon, skip);
		insertVisiterAtSignature( bind(&realign::realignPeriodically, r), eventNumber);



	}

		void dynNetwork::randomizeStates ( nodeBlueprint *n, function<baseType () > a1, function<baseType () > a2 , function<baseType () > a3 , function<baseType () > a4 , function<baseType () > a5 , function<baseType () > a6 , function<baseType () > a7 , function<baseType () > a8 , function<baseType () > a9 , function<baseType () > a10 , function<baseType () > a11 , function<baseType () > a12)
		{
				vector <function<baseType () > > argList;
				argList.push_back (a1);
				if (a2 == NULL)
				{
					randomizeStatesVec(n, argList);
					return;
				}
				argList.push_back (a2);
				if (a3 == NULL)
				{
					randomizeStatesVec(n, argList);
					return;
				}
				argList.push_back (a3);
				if (a4 == NULL)
				{
					randomizeStatesVec(n, argList);
					return;
				}
				argList.push_back (a4);
				if (a5 == NULL)
				{
					randomizeStatesVec(n, argList);
					return;
				}
				argList.push_back (a5);
				if (a6 == NULL)
				{
					randomizeStatesVec(n, argList);
					return;
				}
				argList.push_back (a6);
				if (a7 == NULL)
				{
					randomizeStatesVec(n, argList);
					return;
				}
				argList.push_back (a7);
				if (a8 == NULL)
				{
					randomizeStatesVec(n, argList);
					return;
				}
				argList.push_back (a8);
				if (a9 == NULL)
				{
					randomizeStatesVec(n, argList);
					return;
				}
				argList.push_back (a9);
				if (a10 == NULL)
				{
					randomizeStatesVec(n, argList);
					return;
				}
				argList.push_back (a10);
				if (a11 == NULL)
				{
					randomizeStatesVec(n, argList);
					return;
				}
				argList.push_back (a11);
				if (a12 == NULL)
				{
					randomizeStatesVec(n, argList);
					return;
				}
				argList.push_back (a12);
				randomizeStatesVec(n, argList);
				return;
		}



		void dynNetwork::setInitialCondition ( int n, baseType a1, baseType a2 , baseType a3 , baseType a4 , baseType a5 , baseType a6 , baseType a7 , baseType a8 , baseType a9 , baseType a10 , baseType a11 , baseType a12)
		{
				vector <baseType> argList;
				argList.push_back (a1);
				if (a2 == numeric_limits<baseType>::max())
				{
					setInitialConditionVec(n, argList);
					return;
				}
				argList.push_back (a2);
				if (a3 == numeric_limits<baseType>::max())
				{
					setInitialConditionVec(n, argList);
					return;
				}
				argList.push_back (a3);
				if (a4 == numeric_limits<baseType>::max())
				{
					setInitialConditionVec(n, argList);
					return;
				}
				argList.push_back (a4);
				if (a5 == numeric_limits<baseType>::max())
				{
					setInitialConditionVec(n, argList);
					return;
				}
				argList.push_back (a5);
				if (a6 == numeric_limits<baseType>::max())
				{
					setInitialConditionVec(n, argList);
					return;
				}
				argList.push_back (a6);
				if (a7 == numeric_limits<baseType>::max())
				{
					setInitialConditionVec(n, argList);
					return;
				}
				argList.push_back (a7);
				if (a8 == numeric_limits<baseType>::max())
				{
					setInitialConditionVec(n, argList);
					return;
				}
				argList.push_back (a8);
				if (a9 == numeric_limits<baseType>::max())
				{
					setInitialConditionVec(n, argList);
					return;
				}
				argList.push_back (a9);
				if (a10 == numeric_limits<baseType>::max())
				{
					setInitialConditionVec(n, argList);
					return;
				}
				argList.push_back (a10);
				if (a11 == numeric_limits<baseType>::max())
				{
					setInitialConditionVec(n, argList);
					return;
				}
				argList.push_back (a11);
				if (a12 == numeric_limits<baseType>::max())
				{
					setInitialConditionVec(n, argList);
					return;
				}
				argList.push_back (a12);
				setInitialConditionVec(n, argList);
				return;


		}





	void dynNetwork::randomizeParameter ( string s,function<baseType () > r )
	{
		networkElementType n = params<baseType>::getNodeTypeFromString ( s );
		nodeIterator it;
		nodeList vl;
		verticesMatching (vl, n);
		for (it = vl.begin();it != vl.end(); it ++)
			( ( dynamic_cast<dynNode*>( node::theNodes[*it] )->randomizeParameter ( s,n,r )));



	}



	void dynNetwork::readParameter ( string parameterString, string fileName )
	{
		cout << "Reading from:" << fileName << endl;
		cyclicStream *in = new cyclicStream ( fileName );
		boost::function<baseType () > r = boost::bind ( &cyclicStream::readDouble,in );
		networkElementType theNodeType = params<baseType>::getNodeTypeFromString ( parameterString );
		cout << "Reading parameter \"" << parameterString << "\" for NodeType " << theNodeType << endl;

		nodeList vl;
		nodeIterator vi;
		verticesMatching (vl, theNodeType);


		for (vi = vl.begin();vi!= vl.end(); vi ++)
		{

			// START Änderung by hdickten 08.06.2009
			// if (theNodes[i]->getNodeInfo().theNodeType == theNodeType)
			//	if ((theNodes[i]->getNodeInfo().theNodeKind & _dynNode_) != 0)                      // langsam, bin zu faul

			// ENDE Änderung
#ifdef debug
			cout << "Writing parameter \"" << parameterString << "\"["<< i <<"]=" << r << endl;
#endif
			// Änderung 10.06.2009: Pointertyp geändert (HD) -> funktioniert nun
			//((params<baseType>*)theNodes[i])->randomizeParameter(parameterString, theNodeType, r);
			( ( dynamic_cast<dynNode*>( node::theNodes[*vi] )->randomizeParameter ( parameterString, theNodeType, r )));
		}
		delete in;
	}


	void dynNetwork::smallDisturbance ( baseType radius, int posx, int posy, boost::function<baseType () > r )
	{
		queue<baseType> initialCond;

		unsigned int size = sqrt ( (baseType) network::theNodes.size() );
		for ( unsigned int i = 0; i < size; i++ )
			for ( unsigned int j = 0; j < size; j++ )
			{
				if ( ( i - posx ) * ( i - posx ) + ( j -posy ) * ( j - posy ) < radius )
				{
					initialCond.push ( r() );


					( ( dynamic_cast<dynNode*>(node::theNodes[i + size * j] )->randomizeState ( r )));

				}


			}
	}





	void dynNetwork::startingConditionOpenWaveEnding()
	{
		queue<baseType> initialCond;


		unsigned int size = sqrt ( (baseType) network::theNodes.size() );

		for ( unsigned int i = 0; i < size; i++ )
			for ( unsigned int j = 0; j < size; j++ )
			{
				if ( i< size/2 )
				{
					initialCond.push ( -1.0 );

					if ( node::theNodes[i + size *j]->getNodeInfo().theNodeKind & _dynNode_ )
						for ( unsigned int n = 0; n > ( ( dynamic_cast<dynNode*>( node::theNodes[i+size*j] )->dimension())) - 1; n = n + 1 )
							initialCond.push ( 40.0 );


				}
				else
				{
					if ( j < size/2 )
						initialCond.push ( 0.0 );


					else
						initialCond.push ( 1.0 );



					if ( node::theNodes[i + size *j]->getNodeInfo().theNodeKind & _dynNode_ )
						for ( unsigned int n = 0; n > ( ( dynamic_cast<dynNode*>( node::theNodes[i+size*j] )->dimension())) - 1; n = n + 1 )
							initialCond.push ( 0.0 );




				}



			}



		boost::function<baseType () > r = bind ( &frontAndPop,&initialCond );


		vector< node * >::iterator  it;

		for ( it = node::theNodes.begin(); it != node::theNodes.end(); it++ )
		{
			//			if ( ( *it )->getNodeInfo().theNodeKind & _dynNode_ == 0 )
			//				continue;
			////				continue;

			//			( ( dynamic_cast<dynNode*>( ( *it ) )->state = r();
			( ( dynamic_cast<dynNode*>( ( *it ) )))->randomizeState ( r );
		}





	}

	void dynNetwork::clean ( )
	{
		network::clean ( );
		containerNode<baseType, 1>::realign();
		eventHandler::clean();
	}



	void dynNetwork::startingConditionOpenWaveEndingMiddle()
	{
		queue<baseType> initialCond;


		unsigned int size = sqrt ( (baseType) node::theNodes.size() );

		for ( unsigned int i = 0; i < size; i++ )
			for ( unsigned int j = 0; j < size; j++ )
			{
				if ( i< size/3 || i > 2*size/3 )
				{
					initialCond.push ( -1.0 );
					if ( node::theNodes[i + size *j]->getNodeInfo().theNodeKind & _dynNode_ )
						for ( unsigned int n = 0; n >  dynamic_cast<dynNode*>(node::theNodes[i+size*j] )->dimension() - 1; n = n + 1 )
							initialCond.push ( 40.0 );
				}
				else
				{
					if ( j < size/3 || j > 2*size/3 )
						initialCond.push ( 0.0 );
					else
						initialCond.push ( 100.0 );



					if ( node::theNodes[i + size *j]->getNodeInfo().theNodeKind & _dynNode_ )
						for ( unsigned int n = 0; n > dynamic_cast<dynNode*>( node::theNodes[i+size*j] )->dimension() - 1; n = n + 1 )
							initialCond.push ( 0.0 );




				}



			}



		boost::function<baseType () > r = bind ( &frontAndPop,&initialCond );


		vector< node * >::iterator  it;

		for ( it = node::theNodes.begin(); it != node::theNodes.end(); it++ )
		{
			//			if ( ( *it )->getNodeInfo().theNodeKind & _dynNode_ == 0 )
			//				continue;
			////				continue;

			//			( ( dynamic_cast<dynNode*>( ( *it ) )->state = r();
			dynamic_cast<dynNode*>( ( *it ) )->randomizeState ( r );
		}





	}


	void dynNetwork::clear()
	{
		//		eventHandler::clear();
		network::clear();
		//		myEventsStartAt = numeric_limits<unsigned int>::max();

	}



	void dynNetwork::setInitialConditionVec ( int nodeNumber, vector <baseType> argList )
	{




		if ( node::theNodes[nodeNumber]->getNodeInfo().theNodeKind & _dynNode_ )
			dynamic_cast<dynNode*>( ( node::theNodes[nodeNumber] ) )->setStateVec(argList);
		else
			throw "Error. Der Knoten ist gar nicht vom Typ Dynnode.";


	}




	void dynNetwork::readInitialCondition ( string fileName, nodeBlueprint *n)
	{
		cout << "Reading from:" << fileName << endl;
		cyclicStream *in = new cyclicStream ( fileName );
		boost::function<baseType () > r = boost::bind ( &cyclicStream::readDouble,in );
		randomizeStates ( n, r );
		delete in;
	}

	void dynNetwork::noiseToStatesVec ( nodeBlueprint *n ,vector <boost::function<baseType () > > r )
	{
		if (r.size() == 1)
			while (r.size() < n->dimension())
				r.push_back(r[0]);
		
		if (r.size() !=  n->dimension())
			throw "wrong dimension for randomizeStates!";


				nodeList vl;
				verticesMatching (vl, n);
				nodeIterator vi;
				vector <baseType> argList(n->dimension());
				for (vi = vl.begin();vi != vl.end(); vi++ )
				{
					for (unsigned int i = 0; i < n->dimension() ; i++)
					{
						argList[i] = getState (*vi, i) + r[i]();	
					}
					setInitialConditionVec (*vi, argList);
				}
	}



	void dynNetwork::randomizeStatesVec ( nodeBlueprint *n ,vector <boost::function<baseType () > > r )
	{
		if (r.size() == 1)
			while (r.size() < n->dimension())
				r.push_back(r[0]);

		if (r.size() !=  n->dimension())
			throw "wrong dimension for randomizeStates!";


		nodeList vl;
		nodeIterator it;
		verticesMatching(vl,n);

		for ( it = vl.begin(); it != vl.end(); it ++)
			dynamic_cast<dynNode*>( node::theNodes[*it] ) ->randomizeState ( r );


	}















	unsigned int dynNetwork::observationCounter = 0;


}
