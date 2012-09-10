#ifndef dynNetwork_h
#define dynNetwork_h dynNetwork_h

#include <fstream>
#include "network.h"

#include "eventHandler.h"
#include "dynNode.h"
#include "globals.h"
//#include "ioNode.h"


namespace conedy
{

	//! Class, which supplies network function, which control features of the network related to dynamics... setting initial conditions, parameters, starting numerical integration
	class dynNetwork : public virtual network, eventHandler
	{

		// integer, which counts the number of periodical observations of the network.
		static unsigned int observationCounter;
		public:

		virtual void clear();

		dynNetwork ( const dynNetwork &b);

		
		void setParam (nodeDescriptor nd, string parameterName, baseType value)
		{
			((dynNode *)node::theNodes[nd])-> setParam (parameterName, value);
		}

		//! do a snapshot of all observables in the incidence of  event <eventNumber> 
		void snapshotAtEvent( nodeDescriptor eventNumber);
		//! do a snapshot of all observables in the incidence of an  event  with signature <eventSignature> 
		void snapshotAtEventSignature( nodeDescriptor eventSignature);
		//! do a snapshot of all observables in the incidence of an event with signature <eventSignature> of node <nodeNumber>
		void snapshotAtEventOfNode (nodeDescriptor nodeNumber, unsigned int eventSignature);

		static void registerStandardValues()
		{
			registerGlobal<baseType>("samplingTime", 0.01);
			registerGlobal<baseType>("progressVerbosity", 100.0);
		}

		dynNetwork()  {};
		void evolveAll ( baseType );
	
		baseType time () { return dynNode::time; }

		void realignAtEventSignature (string inputFilename, string outputFilename, networkElementType nt, baseType epsilon, unsigned int eventNumber, unsigned int skip);


		void realignAtEvent (string inputFilename, string outputFilename, networkElementType nt, baseType epsilon, unsigned int eventNumber, unsigned int skip);




		void realignWhenDistant (string inputFilename, string outputFilename, networkElementType nt, baseType epsilon, unsigned int eventNumber, unsigned int multi);


		//! remove all registered observables. This also closes all open files.
		void removeObserver ();

		//! return component <component> of node <node>
		baseType getState (nodeDescriptor node, nodeDescriptor component = 0);

		//! set state of node n with the values given in the vector <argList>
		void setInitialConditionVec ( int n, vector <baseType> argList );

		//! Does the same as setInitialConditionVec. However, values are given seperately. Is used to generate function wrappers for the python interface in a simple way.
		void setInitialCondition ( int n, baseType a1, baseType a2 = numeric_limits<baseType>::max(), baseType a3 = numeric_limits<baseType>::max(), baseType a4 = numeric_limits<baseType>::max(), baseType a5 = numeric_limits<baseType>::max(), baseType a6 = numeric_limits<baseType>::max(), baseType a7 = numeric_limits<baseType>::max(), baseType a8 = numeric_limits<baseType>::max(), baseType a9 = numeric_limits<baseType>::max(), baseType a10 = numeric_limits<baseType>::max(), baseType a11 = numeric_limits<baseType>::max(), baseType a12 = numeric_limits<baseType>::max());

		//! Sets random states for all nodes in the network which match the blueprint n. 
		void randomizeStatesVec (nodeBlueprint *n, vector<function<baseType() > >r);

		//! Does the same as randomizeStatesVec. However, values are given seperately. Is used to generate function wrappers for the python interface in a simple way.
		void randomizeStates ( nodeBlueprint *n, function<baseType () > a1, function<baseType () > a2 = NULL, function<baseType () > a3 = NULL, function<baseType () > a4 = NULL, function<baseType () > a5 = NULL, function<baseType () > a6 = NULL, function<baseType () > a7 = NULL, function<baseType () > a8 = NULL, function<baseType () > a9 = NULL, function<baseType () > a10 = NULL, function<baseType () > a11 = NULL, function<baseType () > a12 = NULL);

//		void randomizeStates ( nodeBlueprint *n,function<baseType () >r );


		void readInitialCondition ( string fileName, nodeBlueprint * n );

		void noiseToStates ( function<baseType () > r, networkElementType n = _undefinedNodeType_ );

		void randomizeParameter ( string s, function<baseType () > r );

		void readParameter ( string,string );

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


		void snapshot () { //		clean ();

			callBack (0); }
		void setTime( baseType newTime)
		{
			dynNode::time = newTime;
			eventHandler::registerCallBack ( _ioNode_, dynNode::time + getGlobal<baseType> ("samplingTime") );
		}
		baseType getParam(nodeDescriptor nodeNumber,string name)
		{
			return ((dynNode*) (node::theNodes[nodeNumber]))->getParam(name);
		}
		virtual baseType callBack ( unsigned int eventSignature );

		virtual unsigned int numberOfEvents() const { return 3; }
	};




}
#endif

