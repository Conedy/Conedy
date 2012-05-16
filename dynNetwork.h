

#ifndef dynNetwork_h
#define dynNetwork_h dynNetwork_h

#include <fstream>
#include "network.h"

#include "eventHandler.h"
#include "dynNode.h"
//#include "ioNode.h"


namespace conedy
{



	//! Class, which supplies network function, which control features of the network related to dynamics... setting initial conditions, parameters, starting numerical integration
	class dynNetwork : public virtual network, eventHandler
	{


		int counter;

		// integer, which counts the number of periodical observations of the network.
		static unsigned int observationCounter;
		public:

		params <baseType> p;
		virtual void clear();

		dynNetwork ( const dynNetwork &b);


		void setParam (nodeDescriptor nd, string parameterName, baseType value)
		{
			((dynNode *)node::theNodes[nd])-> setParam (parameterName, value);



		}

		void snapshotAtEvent( nodeDescriptor eventNumber);


		void snapshotAtEventOfNode (nodeDescriptor nodeNumber, unsigned int eventSignature);


		static void registerStandardValues()
		{
			params<baseType>::registerStandard(_dynNetwork_,"samplingTime",0,0.01);
			params<baseType>::registerStandard(_dynNetwork_,"progressVerbosity",1,100.0);
		}
		baseType inline ioNodeDt () { return p.getParams(0); }
		baseType inline progressVerbosity () { return p.getParams(1); }

		dynNetwork()  : p(_dynNetwork_) {};
		void evolveAll ( baseType );


		void realignAtEventSignature (string inputFilename, string outputFilename, networkElementType nt, baseType epsilon, unsigned int eventNumber, unsigned int skip);


		void realignAtEvent (string inputFilename, string outputFilename, networkElementType nt, baseType epsilon, unsigned int eventNumber, unsigned int skip);




	void realignWhenDistant (string inputFilename, string outputFilename, networkElementType nt, baseType epsilon, unsigned int eventNumber, unsigned int multi);

		void removeObserver ();


		baseType getState (nodeDescriptor node, nodeDescriptor component = 0);


		void setInitialConditionVec ( int n, vector <baseType> argList );

		void setInitialCondition ( int n, baseType a1, baseType a2 = numeric_limits<baseType>::max(), baseType a3 = numeric_limits<baseType>::max(), baseType a4 = numeric_limits<baseType>::max(), baseType a5 = numeric_limits<baseType>::max(), baseType a6 = numeric_limits<baseType>::max(), baseType a7 = numeric_limits<baseType>::max(), baseType a8 = numeric_limits<baseType>::max(), baseType a9 = numeric_limits<baseType>::max(), baseType a10 = numeric_limits<baseType>::max(), baseType a11 = numeric_limits<baseType>::max(), baseType a12 = numeric_limits<baseType>::max())
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



		void randomizeStatesVec (nodeBlueprint *n, vector<function<baseType() > >r);





		void randomizeStates ( nodeBlueprint *n, function<baseType () > a1, function<baseType () > a2 = NULL, function<baseType () > a3 = NULL, function<baseType () > a4 = NULL, function<baseType () > a5 = NULL, function<baseType () > a6 = NULL, function<baseType () > a7 = NULL, function<baseType () > a8 = NULL, function<baseType () > a9 = NULL, function<baseType () > a10 = NULL, function<baseType () > a11 = NULL, function<baseType () > a12 = NULL)
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


//		void randomizeStates ( nodeBlueprint *n,function<baseType () >r );


		void readInitialCondition ( string fileName, nodeBlueprint * n );

		void noiseToStates ( function<baseType () > r, networkElementType n = _undefinedNodeType_ );

		void randomizeParameter ( string s, function<baseType () > r );

		void readParameter ( string,string );

		void evolveAlong	( string InputFilename);

		void startingConditionOpenWaveEnding();
		void startingConditionOpenWaveEndingMiddle();
		void smallDisturbance ( baseType radius, int posx, int posy, boost::function<baseType () > r );

		   void smallDisturbance ( baseType radius, boost::function<baseType () > r )
			{			unsigned int size = sqrt ( (baseType) network::theNodes.size() );
					smallDisturbance ( radius, size/2, size/2, r );
				}


		virtual void clean ();
		void evolve ( baseType startTime, baseType endTime );
		void evolveFor ( baseType duration );
//		void evolve ( baseType time );
//		void evolve ( baseType startTime, baseType endTime) { evolve (startTime, endTime,_dynNode_);}

		void evolveAllAlong (string inputFilename, string outputFilename, baseType eps, networkElementType nt);


		void evolveAlong	(networkElementType n, baseType eps, string inputFilename, string outputFilename);

		void evolveAllAlong ( baseType endTime, string inputFilename, networkElementType nt);

		void snapshot () { //		clean (); 
		  
			callBack (0); }
		void setTime( baseType newTime)
		{
			dynNode::time = newTime;
			eventHandler::registerCallBack ( _ioNode_, dynNode::time + ioNodeDt() );
		}
		baseType getParam(nodeDescriptor nodeNumber,string name)
		{
			return ((dynNode*) (node::theNodes[nodeNumber]))->getParam(name);
		}
		virtual baseType callBack ( unsigned int eventSignature );

		virtual unsigned int numberOfEvents() const { return 3; }
	};


	struct meanVar {
		baseType mean;
		baseType var;
	};


	class realign
	{
		private:
			network::nodeList *vl;
			baseType eps;
			ifstream in;
			ofstream out;
			int counter;
			int skip;
		public:
			realign(string input, string output, network::nodeList *theList, baseType theEpsilon, int s)
			{
				in.open(input.c_str());
				out.open(output.c_str());
				vl = theList;
				eps= theEpsilon;
				skip = s;
				counter = skip;
			}
			meanVar  calculateDist(vector <baseType> &states);
			void realignNow ( vector <baseType> &states, baseType eps, meanVar dist);

			void realignPeriodically();
			void realignWhenDistant();
//			void	goForIt();
	};



}
#endif

