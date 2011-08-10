

#include "dynNetwork.h"
#include "ioNode.h"

#include "containerNode.h"

#include "pcoBase.h"


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

		if (( dynNode::time /	ioNodeDt()/ 100.0) -  (int)(dynNode::time / ioNodeDt() / 100.0)    < 0.9999 / 100.0 )
			cout <<"#------------Time:" << dynNode::time << endl;

		return dynNode::startTime + observationCounter * ioNodeDt();

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





	dynNetwork::dynNetwork(const dynNetwork &b) : network (b), eventHandler(b), p(b.p)
	{
		eventHandler::registerCallBack ( _ioNode_, dynNode::time + ioNodeDt() ); 
	}

	void dynNetwork::noiseToStates ( function<double () > r, networkElementType n )
	{
		throw "fixme dynNetwork::nouseToStates";

/*		queue<double> initialCond;
		nodeList vl;
		verticesMatching (vl, n);
		nodeIterator vi;

		for (vi = vl.begin();vi != vl.end(); vi++ )


			dynamic_cast<dynNode*>( node::theNodes[*vi] )->setInitial ( r1 );

			initialCond.push ( node::theNodes[*vi]->getState() + r() );

		boost::function<double () > r1 = bind ( &frontAndPop,&initialCond );

		for (vi = vl.begin();vi != vl.end(); vi++)
			dynamic_cast<dynNode*>( node::theNodes[*vi] )->randomizeState ( r1 );
*/
	}





//	void dynNetwork::evolve ( double time )
//	{
//		evolve ( dynNode::time, dynNode::time + time, _dynNode_ );
//	}


		baseType dynNetwork::getState (nodeDescriptor node)
		{
			return (( node::theNodes[node])->getState());
		}

	void dynNetwork::evolveFor ( double duration )
	{
		evolve(dynNode::time, dynNode::time + duration);
	}

	void dynNetwork::evolve ( double startTime, double endTime )
	{


		dynNode::startTime = startTime;
		dynNode::time = startTime;
		dynNode::endTime = endTime;
		clean (  );     // Dreckige 0 TODO Prüfenvi 


		observationCounter = 0; 
		snapshot();
		updateKey(_ioNode_, dynNode::time + ioNodeDt());

		evolveAll ( endTime );

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


	void dynNetwork::evolveAlong	(networkElementType n, baseType eps,  string inputFilename, string outputFilename)
	{

		dynNode::startTime = 0.0;
		observationCounter = 1;
		dynNode::time = 0.0;


		clean (  );     // Dreckige 0 TODO Prüfenvi 

		nodeList dynNodes;

		//	realign r(inputFilename, outputFilename, l);
		//		evolveAllAlong (inputFilename, outputFilename, eps ,n);

	}







	void dynNetwork::evolveAll ( double endTime )
	{
		vector< dynNode *>::iterator it;


		double timeTilEvent;
		while ( dynNode::time <= endTime )
		{




			if ( eventHandler::nextEvent() >= endTime )
			{
				timeTilEvent = endTime - dynNode::time;
				for ( it = evolveList.begin(); it != evolveList.end(); it++ )
				{
					( *it )->evolve ( timeTilEvent );
				}
				dynNode::time += timeTilEvent;
				break;

			}
			else
				timeTilEvent = eventHandler::nextEvent() - dynNode::time;

			for ( it = evolveList.begin(); it != evolveList.end(); it++ )
			{
				( *it )->evolve ( timeTilEvent );
			}
			dynNode::time += timeTilEvent;

			eventHandler::pop();

		}
	}


	void dynNetwork::evolveAllAlong (string inputFilename, string outputFilename, baseType eps, networkElementType nt)
	{

		/*		ifstream in(inputFilename.c_str());
				vector< dynNode *>::iterator it;
				nodeList dynNodes;
				nodeIterator vi;
				verticesMatching(dynNodes, nt);


				double timeTilEvent;

				ofstream out(outputFilename.c_str());
				while ( true )
				{


				timeTilEvent = eventHandler::nextEvent() - dynNode::time;

				for ( it = evolveList.begin(); it != evolveList.end(); it++ )
				( *it )->evolve ( timeTilEvent );
				dynNode::time += timeTilEvent;


				if (top() == 1)
				{




				dist = 0;
				i = 0;
				for (vi = dynNodes.begin(); vi != dynNodes.end();vi++)
				{
				double diff = abs (along[i] - theNodes[*vi]->getState()  );

				if (diff > abs (1.0 - diff ))
				diff = abs ( 1.0 - diff );
				dist += diff * diff;
				i++;
				}
				dist = sqrt(dist)/ dynNodes.size();
				cout << "nachher:" << dist << endl;








				eventHandler::pop();

				}
				else
				{
				eventHandler::pop();

				}


				}
				*/

	}





	void dynNetwork::randomizeParameter ( string s,function<double () > r )
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
		boost::function<double () > r = boost::bind ( &cyclicStream::readDouble,in );
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


	void dynNetwork::smallDisturbance ( double radius, int posx, int posy, boost::function<double () > r )
	{
		queue<double> initialCond;

		unsigned int size = sqrt ( (float) network::theNodes.size() );
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
		queue<double> initialCond;


		unsigned int size = sqrt ( (float) network::theNodes.size() );
		cout << "Size:" << size << endl;

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



		boost::function<double () > r = bind ( &frontAndPop,&initialCond );


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

		eventClean();

	}



	void dynNetwork::startingConditionOpenWaveEndingMiddle()
	{
		queue<double> initialCond;


		unsigned int size = sqrt ( (float) node::theNodes.size() );
		cout << "Size:" << size << endl;

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



		boost::function<double () > r = bind ( &frontAndPop,&initialCond );


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
			dynamic_cast<dynNode*>( ( node::theNodes[nodeNumber] ) )->setInitialCondition(argList);
		else
			throw "Error. Der Knoten ist gar nicht vom Typ Dynnode.";


		}




		void dynNetwork::readInitialCondition ( string fileName, nodeBlueprint *n)
		{
			cout << "Reading from:" << fileName << endl;
			cyclicStream *in = new cyclicStream ( fileName );
			boost::function<double () > r = boost::bind ( &cyclicStream::readDouble,in );
			randomizeStates ( n, r );
			delete in;
		}


		
		void dynNetwork::randomizeStatesVec ( nodeBlueprint *n ,vector <boost::function<double () > > r )
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



		double realign::calculateDist(vector <double> &states)
		{

			network::nodeIterator vi;
			double dist = 0;
			double diff = 0;
			unsigned int i=0;
			for (vi = vl->begin(); vi != vl->end();vi++)
			{
				diff = abs (states[i] - node::theNodes[*vi]->getState()  );

				if (diff > abs (1.0 - diff ))
					diff = abs ( 1.0 - diff );
				dist += diff * diff;
				i++;
			}
			dist = sqrt(dist)/ vl->size();
			return dist;

		}
//		void	realign::goForIt(  )
//		{



			void realign::realignPeriodically()
			{


				vector <double> along(vl->size());
				for (unsigned int i = 0; i < vl->size(); i++ )
					in >>along[i];

				double dist = calculateDist(along);
				if (counter==skip)
				{
					counter = 0;
					out << dynNode::time << " " << dist << endl;
					cout << "vorher:" << dist << endl;
					realignNow(along, eps/dist);
					cout << "nachher:" << calculateDist(along) << endl;
				}
				else
				{
					counter++;
					out << "#" << dynNode::time << " " << dist << endl;

				}

			}


			void realign::realignWhenDistant()
			{



				vector <double> along(vl->size());
				for (unsigned int i = 0; i < vl->size(); i++ )
					in >>along[i];

				double dist = calculateDist(along);

				if (dist > eps* skip)
				{
					out << dynNode::time << " " << dist << endl;
					cout << "vorher:" << dist << endl;
					realignNow(along, eps/dist);
					cout << "nachher:" << calculateDist(along) << endl;
				}
				else
				{


					out << "#" << dynNode::time << " " << dist << endl;





				}
			}

				void realign::realignNow(vector <double> &along, double factor)
				{

					network::nodeIterator vi;
					queue <double> states;
					unsigned int i = 0;

					for (vi = vl->begin(); vi != vl->end();vi++)
					{
						//				double stat = theNodes[*vi]->getState();
						double diff =  along[i] - node::theNodes[*vi]->getState()  ;

						if (diff > 0.5)
							diff = diff - 1;
						else if (diff < -0.5)
							diff = diff + 1;

						diff = diff *  factor;

						if (diff > 0.5  || diff < -0.5)
							throw "Fehler Abstand zu groß für den Raum (evolveAlong)";

						double n;
						if (diff > 0)
						{
							n = along[i] - diff;
							if (n < 0)
								n=n + 1;
						}
						else
						{
							n = along[i] + diff;
							if ( n > 1)
								n = n - 1;
						}

						states.push (n);	
						i++;
					}
					boost::function<double () > r =  bind(&frontAndPop, &states);
					for (vi = vl->begin(); vi != vl->end();vi++)
						((dynNode*)  node::theNodes[*vi]) ->	randomizeState( r) ;

				}











				void dynNetwork::simulate (  int type = _dynNode_ )
				{
					/*
					//	((streamInNodeBinary<baseType>*)theNodes[0])->test();
					clean ( timeSteps,type );

					//			try {

					eventHandler::registerCallBack ( _ioNode_, numeric_limits<double>::max());

					for ( unsigned int i = 0; i< ( unsigned int ) timeSteps; i++ )
					{


					if ( i % 500 == 0 )
					cout << "------------Zeit" << i << endl;

					simulateOneStep ( type );
					dynNode::time =dynNode::time + dynNode::dt;
					}

					//			}
					//			catch (...) { cout << "Nu is aber Schluß" << endl;}
					*/

				}


				unsigned int dynNetwork::observationCounter = 0;


			}
