

#ifndef specialNodes_h 
#define specialNodes_h  specialNodes_h


#include "dynNode.h"




namespace conedy 
{


#ifdef EVENTCOUNT

	class eventCountNode : public dynNode
	{
		private:
			unsigned int signature;

		public:
			virtual bool timeEvolution() { return 0; }
			virtual const nodeInfo getNodeInfo() { nodeInfo n = {_eventCountNode_,_outNode_,"eventCountNode"};     return n; };

			virtual const unsigned int dimension() const{ return 0;}

			eventCountNode(unsigned int theSignature) :  dynNode ( _eventCountNode_ ), signature(theSignature){};
			virtual void clean ( unsigned int timeSteps ) {};
			virtual baseType getState()
			{	
				baseType res = eventHandler::eventCount[signature];
				eventHandler::eventCount[signature] = 0;
				return res;

			}
			virtual int requiredTimeSteps() { return 0; }
	};

#endif

	//! Node, der die momentane Integrationszeit als status zurückgibt
	template <typename T>
		class timeNode : public dynNode 


	{

		public:
			virtual bool timeEvolution() { return 0; }
			virtual const nodeInfo getNodeInfo() { nodeInfo n = {_timeNode_,_outNode_ ,  "timeNode"};     return n; };

			virtual const unsigned int dimension() const{ return 0;}

			timeNode() : dynNode ( _timeNode_ ) {};
			virtual void clean ( unsigned int timeSteps ) {};
			virtual T getState()
			{
				return this->time;
			}
			virtual int requiredTimeSteps() { return 0; }
	};



	//!
	//
	//
	//
	//

	template <typename T>
		class phaseCorrelation : public dynNode 
	{
		list <pair <nodeDescriptor, nodeDescriptor>  >el;

		public:
		virtual bool timeEvolution() { return 0; }
		virtual const nodeInfo getNodeInfo() { nodeInfo n = {_phaseCorrelation_,_dynNode_,"phaseCorrelation"};     return n; };

		virtual const unsigned int dimension() const{ return 0;}

		phaseCorrelation( ) :   dynNode ( _phaseCorrelation_ ) {};
		
		void setList (network::edgeList * newEdgeList) {
			network::edgeIterator ei;
		 	for (ei = newEdgeList->begin(); ei != newEdgeList->end();ei ++)
				el.push_back(std::make_pair<nodeDescriptor, nodeDescriptor> (ei->first, node::theNodes[ei->first] ->getTarget(ei->second)->getNumber()  ));
		}
		virtual void clean ( unsigned int timeSteps ) {};
		virtual T getState()
		{
			list <pair <nodeDescriptor,nodeDescriptor> >::iterator ei;
			baseType d;
			complex<double> sum (( double)0, (double)0);
			for (ei = el.begin(); ei != el.end();ei ++)
			{
				d =	(node::theNodes[ei->first]->getState()  )  -  ( node::theNodes[ei->second] ->getState()  );
      		complex<double> dummy (( double)0, d * 2 * M_PI);
		      sum = sum + exp (dummy);
			}	
			return abs(sum);
	
		}
		virtual int requiredTimeSteps() { return 0; }
	};
	//
	//
	template <typename T>
		class phaseDistance : public dynNode 
	{
		list <pair <nodeDescriptor, nodeDescriptor>  >el;

		public:
		virtual bool timeEvolution() { return 0; }
		virtual const nodeInfo getNodeInfo() { nodeInfo n = {_phaseDistance_,_dynNode_,"phaseDistance"};     return n; };

		virtual const unsigned int dimension() const{ return 0;}

		phaseDistance( ) :   dynNode ( _phaseDistance_ ) {};
		
		void setList (network::edgeList * newEdgeList) {
			network::edgeIterator ei;
		 	for (ei = newEdgeList->begin(); ei != newEdgeList->end();ei ++)
				el.push_back(std::make_pair<nodeDescriptor, nodeDescriptor> (ei->first, node::theNodes[ei->first] ->getTarget(ei->second)->getNumber()  ));
		}
		virtual void clean ( unsigned int timeSteps ) {};
		virtual T getState()
		{
			list <pair <nodeDescriptor,nodeDescriptor> >::iterator ei;
			baseType d;
			baseType sum = 0;
			for (ei = el.begin(); ei != el.end();ei ++)
			{
				d =	(node::theNodes[ei->first]->getState()  )  -  ( node::theNodes[ei->second] ->getState()  );
					if (abs(d) < abs(1.0-abs(d)))
						d = abs(d);
					else
						d = abs(1.0 - abs(d));
				sum += d;
			}	
			return sum;
	
		}
		virtual int requiredTimeSteps() { return 0; }
	};




	//! Knoten, dessen getState-Funktion zufällige Zahlen ausspuckt. 
	template <typename T>
		class randomNode : public dynNode

	{  
		function<T () > r;
		public:

		virtual const unsigned int dimension() const{ return 0;}

		virtual const nodeInfo getNodeInfo() { nodeInfo n = {_randomNode_,_dynNode_|_inNode_};     return n; };

		randomNode ( boost::function <double() > noise ) : dynNode ( _randomNode_ ), r ( noise ) {};
		virtual void clean ( unsigned int timeSteps ) {};
		virtual void printStatistics()   {cout << "randomNode" << endl;this->printStatistics();}
		virtual T getState()	{return r();}
		virtual int requiredTimeSteps() { return 0; }
		virtual bool timeEvolution () {return 0;}
	};

	//! obsolete or unused ?
	template <class T>
		class distributeRandomelyNode :  public dynNode 
	{
		unsigned int networksize;

		T firingRate;
		function<T () > r;
		function<T () > weight;
		public:
		virtual const nodeInfo getNodeInfo() { nodeInfo n = {_distributeRandomelyNode_,_dynNode_|_inNode_};     return n; };

		virtual const unsigned int dimension() const{ return 0;}
		virtual bool timeEvolution () {return 0;}
		distributeRandomelyNode ( unsigned int n, function <T() > newWeight ) : dynNode(_calculateMeanPhaseCoherence_)
		{
			networksize = n;
			weight = newWeight;
			r = boost::bind ( &gslNoise::getBimodal,0,1,0.001 );

		}

		virtual int requiredTimeSteps() { return 2; };

		virtual T getState()
		{

			return weight() * r();


		}

		virtual void printStatistics()   {cout << "distributeRandomelyNode" << endl;this->printStatistics();}

		virtual void action1() {} ;

		virtual void action2()
		{
			firingRate = this->couplingSum();
			r = boost::bind ( &gslNoise::getPoisson, ( T ) firingRate/ ( T ) networksize );

		}
		virtual void swap()
		{
			//		r = boost::bind(&gslNoise::getBimodal,0,1,(T)firingRate/(T)networksize);
			//			r = boost::bind ( &gslNoise::getPoisson, ( T ) firingRate/ ( T ) networksize );

			//		cout << "Firingrate:" << firingRate << endl;
		}




	};


}


#endif
