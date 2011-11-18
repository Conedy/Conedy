

#ifndef dynNetwork_h
#define dynNetwork_h dynNetwork_h


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


		void setParam (nodeDescriptor nd, string parameterName, double value)
		{
			((dynNode *)node::theNodes[nd])-> setParam (parameterName, value);



		}

		void snapshotAtEvent( nodeDescriptor eventNumber);


		void snapshotAtEventOfNode (nodeDescriptor nodeNumber, unsigned int eventSignature); 


		static void registerStandardValues() 
		{ 
			params<baseType>::registerStandard(_dynNetwork_,"dynNetwork_ioNodeDt",0,0.01); 
//nn			params<baseType>::registerStandard ( _dynNetwork_,"streamOutNode_binary",1, 0.0 );
		}
		baseType inline ioNodeDt () { return p.getParams(0); }

		dynNetwork()  : p(_dynNetwork_) {};
		void evolveAll ( double );


		void realignAtEventSignature (string inputFilename, string outputFilename, networkElementType nt, baseType epsilon, unsigned int eventNumber, unsigned int skip);


		void realignAtEvent (string inputFilename, string outputFilename, networkElementType nt, baseType epsilon, unsigned int eventNumber, unsigned int skip);




	void realignWhenDistant (string inputFilename, string outputFilename, networkElementType nt, baseType epsilon, unsigned int eventNumber, unsigned int multi);

		void removeObserver ();

		void simulateOneStep ( int type );

		baseType getState (nodeDescriptor node);


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



		void randomizeStatesVec (nodeBlueprint *n, vector<function<double() > >r);





		void randomizeStates ( nodeBlueprint *n, function<double () > a1, function<double () > a2 = NULL, function<double () > a3 = NULL, function<double () > a4 = NULL, function<double () > a5 = NULL, function<double () > a6 = NULL, function<double () > a7 = NULL, function<double () > a8 = NULL, function<double () > a9 = NULL, function<double () > a10 = NULL, function<double () > a11 = NULL, function<double () > a12 = NULL)
		{
				vector <function<double () > > argList;
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


//		void randomizeStates ( nodeBlueprint *n,function<double () >r );
		
		
		void readInitialCondition ( string fileName, nodeBlueprint * n );

		void noiseToStates ( function<double () > r, networkElementType n = _undefinedNodeType_ );

		void randomizeParameter ( string s, function<double () > r );

		void readParameter ( string,string );

		void evolveAlong	( string InputFilename);

		void startingConditionOpenWaveEnding();
		void startingConditionOpenWaveEndingMiddle();
		void smallDisturbance ( double radius, int posx, int posy, boost::function<double () > r );

		   void smallDisturbance ( double radius, boost::function<double () > r )
			{			unsigned int size = sqrt ( (float) network::theNodes.size() );
					smallDisturbance ( radius, size/2, size/2, r );
				}
		

		void simulate (  int type );	// ruft zunächst clean von allen Knoten auf
		// dann timesteps mal action1, swap, action2, swap, action3, swap, action4, swap.
		virtual void clean ();
		void evolve ( double startTime, double endTime );
		void evolveFor ( double duration );
//		void evolve ( double time );
//		void evolve ( double startTime, double endTime) { evolve (startTime, endTime,_dynNode_);}

		void evolveAllAlong (string inputFilename, string outputFilename, baseType eps, networkElementType nt);


		void evolveAlong	(networkElementType n, baseType eps, string inputFilename, string outputFilename);

		void evolveAllAlong ( double endTime, string inputFilename, networkElementType nt);

		void snapshot () { 		clean ();  callBack (0); }
		void setTime( double newTime) 
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
				counter = 0;
			}
			double calculateDist(vector <double> &states);
			void realignNow ( vector <double> &states, double factor);

			void realignPeriodically();
			void realignWhenDistant();
//			void	goForIt();
	};



}
#endif

