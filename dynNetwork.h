#ifndef dynNetwork_h
#define dynNetwork_h dynNetwork_h

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

		public:

			static void registerStandardValues()
			{
				registerGlobal<baseType>("samplingTime", 0.01);
				registerGlobal<baseType>("progressVerbosity", 100.0);
				globals::registerGlobal<bool> ("outputBinary", false );
			}

			// Functions which are reavealed to the interpreter


			//! Evolve the system time from startTime to endTime
			void evolve ( baseType startTime, baseType endTime );

			baseType getParam(nodeDescriptor nodeNumber,string name) {	return ((dynNode*) (node::theNodes[nodeNumber]))->getParam(name); }

			//! return component <component> of node <node>
			baseType getState (nodeDescriptor node, nodeDescriptor component = 0);


			//! observe node number via an edge of type l 
			void observe (  nodeDescriptor number, string s,edgeBlueprint * l  = stdEdge);

			void observeAll ( string s, edgeBlueprint *l = stdEdge, nodeBlueprint *n = stdNode);

			//! Observe all components of a node (e.g. all three variables of a roessler oscillator)
			void observeComponents (nodeDescriptor n, string fileName);

			void observeHist ( string s,    nodeBlueprint *n);

			//! wie oben. Phasen werden von Edges vom Typ l übergeben.
			void observeMeanPhase ( string s, edgeBlueprint *l=stdEdge );

			void observePhaseCoherence ( string s, edgeBlueprint *l = stdEdge, nodeBlueprint *n = stdNode);

			//! wie oben mit links vom Typ l
			void observeSum ( string s, edgeBlueprint *l = stdEdge );

			//! Observe the system time
			void observeTime ( string s );

			//! remove all registered observables. This also closes all open files.
			void removeObserver ();

			//! Sets random states for all nodes in the network which match the blueprint n. 
			void randomizeStatesVec (nodeBlueprint *n, vector<function<baseType() > >r);

			//! Does the same as randomizeStatesVec. However, values are given seperately. Is used to generate function wrappers for the python interface in a simple way.
			void randomizeStates ( nodeBlueprint *n, function<baseType () > a1, function<baseType () > a2 = NULL, function<baseType () > a3 = NULL, function<baseType () > a4 = NULL, function<baseType () > a5 = NULL, function<baseType () > a6 = NULL, function<baseType () > a7 = NULL, function<baseType () > a8 = NULL, function<baseType () > a9 = NULL, function<baseType () > a10 = NULL, function<baseType () > a11 = NULL, function<baseType () > a12 = NULL);

			//! Set states of all nodes which match n. Values are read from a file with name fileName.
			void readInitialCondition ( string fileName, nodeBlueprint * n );


			//! Draw a random value for parameter s for each node in the network to which s belongs.
			void randomizeParameter ( string s, function<baseType () > r );

			void readParameter ( string,string );

			//! Print the value of all registered observables to files.
			void snapshot () { callBack (0); }

			void setParam (nodeDescriptor nd, string parameterName, baseType value) { ((dynNode *)node::theNodes[nd])-> setParam (parameterName, value); }

			//! set state of node n with the values given in the vector <argList>
			void setInitialConditionVec ( int n, vector <baseType> argList );

			//! Does the same as setInitialConditionVec. However, values are given seperately. Is used to generate function wrappers for the python interface in a simple way.
			void setInitialCondition ( int n, baseType a1, baseType a2 = numeric_limits<baseType>::max(), baseType a3 = numeric_limits<baseType>::max(), baseType a4 = numeric_limits<baseType>::max(), baseType a5 = numeric_limits<baseType>::max(), baseType a6 = numeric_limits<baseType>::max(), baseType a7 = numeric_limits<baseType>::max(), baseType a8 = numeric_limits<baseType>::max(), baseType a9 = numeric_limits<baseType>::max(), baseType a10 = numeric_limits<baseType>::max(), baseType a11 = numeric_limits<baseType>::max(), baseType a12 = numeric_limits<baseType>::max());




			// inofficial functions (atm)

			void noiseToStatesVec (nodeBlueprint *n,      vector<function<baseType() > >r);

			//! Set states of all nodes which match n. Such that newstate = oldstate + r(). 
			void noiseToStates ( function<baseType () > r, networkElementType n = _undefinedNodeType_ );


			//! obsolete ?
			void startingConditionOpenWaveEnding();
			//! obsolete ?
			void startingConditionOpenWaveEndingMiddle();
			//! obsolete ?
			void smallDisturbance ( baseType radius, int posx, int posy, boost::function<baseType () > r );

			//! obsolete ?
			void smallDisturbance ( baseType radius, boost::function<baseType () > r ) {			unsigned int size = sqrt ( numberVertices() ); smallDisturbance ( radius, size/2, size/2, r ); }

			void observeEvent (string s, nodeDescriptor signature);
			void observeEventTimes( string fileName,nodeDescriptor eventNumber );
			void observeEventTimesEquals ( string fileName, nodeDescriptor eventNumber );
			void observeEventSignatureTimes( string fileName,nodeDescriptor eventNumber );
			void observeEventCounter ( string s, unsigned int signature);

			//! do a snapshot of all observables in the incidence of  event <eventNumber> 
			void snapshotAtEvent( nodeDescriptor eventNumber);
			//! do a snapshot of all observables in the incidence of an  event  with signature <eventSignature> 
			void snapshotAtEventSignature( nodeDescriptor eventSignature);
			//! do a snapshot of all observables in the incidence of an event with signature <eventSignature> of node <nodeNumber>
			void snapshotAtEventOfNode (nodeDescriptor nodeNumber, unsigned int eventSignature);

			//! rescale all nodestates of nodes which match nt, such that they have a distance of epsilon from nodestates which are read from file (filename input=ilename). Rescaling is done at every skip-th event with signature eventNumber
			void realignAtEventSignature (string inputFilename, string outputFilename, networkElementType nt, baseType epsilon, unsigned int eventNumber, unsigned int skip);
			//! rescale all nodestates of nodes which match nt, such that they have a distance of epsilon from nodestates which are read from file (filename input=ilename). Rescaling is done at every skip-th event with number eventNumber
			void realignAtEvent (string inputFilename, string outputFilename, networkElementType nt, baseType epsilon, unsigned int eventNumber, unsigned int skip);


			//! rescale all nodestates of nodes which match nt, such that they have a distance of epsilon from nodestates which are read from file (filename input=ilename). Rescaling is done whenever distance reaches epsilon * mult. This is checked at every periodic snapshot of observables.
			void realignWhenDistant (string inputFilename, string outputFilename, networkElementType nt, baseType epsilon, unsigned int eventNumber, unsigned int multi);


			void setTime( baseType newTime) { dynNode::time = newTime; eventHandler::registerCallBack ( _ioNode_, dynNode::time + getGlobal<baseType> ("samplingTime") ); }


			//! return the system time. 
			baseType time () { return dynNode::time; }



			void dynamics (nodeDescriptor n);

			//! Event-callback function, we use here _ioNode_ for snapshot of observables.
			virtual baseType callBack ( unsigned int eventSignature );


			virtual unsigned int numberOfEvents() const { return 3; }

			virtual void clear();


			dynNetwork()  {};
			dynNetwork ( const dynNetwork &b);

			void evolveFor ( baseType duration );

		protected:
			//! Evolve the system time for a time of length duration

			nodeDescriptor addStreamOutNode (string s);
			virtual void clean ();



			void evolveAll ( baseType );

		private:

			// integer, which counts the number of periodical observations of the network.
			static unsigned int observationCounter;


	};

	double readDouble (istream *is);



}
#endif

