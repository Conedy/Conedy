#ifndef pulseCoupledExcitatoryNeuron_h
#define pulseCoupledExcitatoryNeuron_h pulseCoupledExcitatoryNeuron_h

#include <math.h>
#include "node.h"
#include <boost/function.hpp>
#include "dynNode.h"
#include "eventHandler.h"

#include "baseType.h"
#include <queue>

#include "edge.h"

#define __MAXNUMBEROFIFNEURONS



namespace conedy
{
//! Excitatorisches Integrate-and-Fire-Neurons.
	class pulseCoupledExcitatoryNeuron : public dynNode, public eventHandler
        // Kopplungsrichtung ist andersrum als bei allen andere nodes !
	{
// 1 = Ja, 0 = nicht refraktär
		public:        // x' = -ax+b

			baseType lastFiring;
			bool refractory;

			baseType inline nextFiring() { return eventHandler::getKey(_fire_); }
			baseType inline nextRandomExcitation() { return eventHandler::getKey(_exciteRandomly_); }


			static unsigned int numberOfExcitations;

    		virtual void setInitialCondition ( vector <double  >  &r );

	//		virtual void randomizeState ( boost::function<baseType () > &r );
			baseType inline timeDelay()  { return params<baseType>::getParams ( 0 ); }
			baseType inline t_ref()  { return params<baseType>::getParams ( 1 ); }
//			baseType inline dt () { return this->dt; }
			baseType inline noiseFrequency()	{ return params<baseType>::getParams ( 2 ); }
			baseType inline noiseIntensity()	{ return params<baseType>::getParams ( 3 ); }
			baseType inline leakage()		{ return params<baseType>::getParams ( 4 ); }
		public:


			virtual void clean ();

			void excite ( baseType c ) ;          // gibt zurück, ob das Neuron sofort feuert.
			virtual baseType callBack(unsigned int eventSignature);

			virtual void fireN ();

			virtual const nodeInfo getNodeInfo() { nodeInfo n = {_pulseCoupledExcitatoryNeuron_,_dynNode_};     return n; };

			virtual baseType getState() ;
		public:

			virtual const unsigned int dimension() const { return 1;}
			virtual bool timeEvolution () { return 0; }
			virtual unsigned int numberOfEvents() const { return 2;  }



			pulseCoupledExcitatoryNeuron () : dynNode ( _pulseCoupledExcitatoryNeuron_)
			{



			};


// 			pulseCoupledExcitatoryNeuron() {};
			virtual ~pulseCoupledExcitatoryNeuron()
			{
			}

//	static void registerStandardValues() { params<baseType>::registerStandard(_pulseCoupledExcitatoryNeurontype_,"pulseCoupledExcitatoryNeuron_arraySize", 0, 1000); }
//	unsigned int dimension () { return x.size(); }

//	virtual void randomizeState(boost::function<baseType ()> &r) { for (unsigned int i = 0; i < x.size(); i++){ pulseCoupledExcitatoryNeuron<baseType>::x[i] = r();}}

			virtual void action1()
			{

	//			this->state = numberOfExcitations;
				numberOfExcitations = 0;

			}
			//			cout << endl;




			virtual int requiredTimeSteps ()
			{
					return 0;
			};
			virtual void swap()
			{
//				dynNode::this->state = dynNode::x[0];

			};
//	virtual void clean() {};

//	virtual baseType getHiddenComponent(int component) { return x[component]; }


//	virtual baseType getState();

//	virtual streamIn(ifstream &in);
//	virtual streamOut(ofstream &out);
			virtual void printStatistics()   { cout << params<baseType>::getParams ( 0 ) << " "<< params<baseType>::getParams ( 1 ) << " " << params<baseType>::getParams ( 2 ) << " " << params<baseType>::getParams ( 3 ) <<endl;cout << "pulseCoupledExcitatoryNeuron" << endl; this->printStatistics(); }



			static void registerStandardValues()
			{
				params<baseType>::registerStandard ( _pulseCoupledExcitatoryNeuron_,"pulseCoupledExcitatoryNeuron_timeDelay",0,0.01 );

				params<baseType>::registerStandard ( _pulseCoupledExcitatoryNeuron_,"pulseCoupledExcitatoryNeuron_t_ref",1,0.05 );


				params<baseType>::registerStandard ( _pulseCoupledExcitatoryNeuron_,"pulseCoupledExcitatoryNeuron_noiseFrequency",2,0.01 );
				params<baseType>::registerStandard ( _pulseCoupledExcitatoryNeuron_,"pulseCoupledExcitatoryNeuron_noiseIntensity",3,0.1 );
				params<baseType>::registerStandard ( _pulseCoupledExcitatoryNeuron_,"pulseCoupledExcitatoryNeuron_leakage",4,1.0 );
				params<baseType>::registerStandard ( _membranePotentialOfIFQ_,"membranePotentialOfIFQ_refractoryValue",5, - 1.0 );
				//		params<baseType>::registerStandard ( _pulseCoupledExcitatoryNeuron_,"pulseCoupledExcitatoryNeuron_exciteAllFrequency",9,0.0 );
				//		params<baseType>::registerStandard ( _pulseCoupledExcitatoryNeuron_,"pulseCoupledExcitatoryNeuron_exciteAllIntensity",10,1.0 );


			}


	};

	//! Gibt das MembranPotential von den pulseCoupledExcitatoryNeurons zurück.
/*	class membranePotentialOfIFQ: public weightedEdgeVirtual, params <baseType>
	{

			baseType inline nextFiring () { return (dynamic_cast< pulseCoupledExcitatoryNeuron*>( weightedEdge::getTarget() ))-> nextFiring(); }
			baseType inline time() { return dynNode::time;}
			baseType inline lastFiring() { return (dynamic_cast< pulseCoupledExcitatoryNeuron*>( weightedEdge::getTarget())) ->lastFiring; }
			baseType inline leakage() {return     (dynamic_cast< pulseCoupledExcitatoryNeuron*>( weightedEdge::getTarget()))-> leakage(); }
			baseType inline t_ref() {return       (dynamic_cast< pulseCoupledExcitatoryNeuron*>( weightedEdge::getTarget()))-> t_ref(); }

			bool inline refractory() {return      (dynamic_cast< pulseCoupledExcitatoryNeuron*>( weightedEdge::getTarget()))-> refractory; }

		public:


			static void registerStandardValues()
			{
			}

			membranePotentialOfIFQ () : params<baseType>(_membranePotentialOfIFQ_) {};
			virtual baseType getTargetState()
			{
				if (nextFiring() == numeric_limits<baseType>::max())
				{
					if (refractory())
					{
					       if (time() - lastFiring() < t_ref())
						       return params<baseType>::getParams(0);
					       else
						       return 0;
					}
					else
						return ( exp ( leakage() * ( -time() + lastFiring() )) );
				}
				else
					return 1.0;   // firing
			}


	};





*/




}







#endif
