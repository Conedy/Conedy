

#ifndef pulseCoupledPhaseOscillator_h
#define pulseCoupledPhaseOscillator_h pulseCoupledPhaseOscillator_h

#include <math.h>
#include "node.h"
#include "params.h"
#include <boost/function.hpp>
#include <gsl/gsl_errno.h>
#include <gsl/gsl_matrix.h>
#include <gsl/gsl_odeiv.h>
#include "dynNode.h"
#include <limits.h>
#include <boost/pending/relaxed_heap.hpp>
#include "baseType.h"

#include "eventHandler.h"

#include "dynNode.h"

#include <queue>

#define __MAXNUMBEROFIFNEURONS

namespace conedy
{





	// Membranpotential ausrechnen aus dynNode::x[0]:



	//!
	//


	//! Basis-Klasse für alle pulsegekoppelten Oscillatoren
	class pcoBase : public  dynNode, public eventHandler
	{
		protected:
		public:        // x' = -ax+b
			static baseType timeOffset;
			static void registerStandardValues()
			{
				params<baseType>::registerStandard ( _pcoBase_,"pcoBase_noiseFrequency",0,0.0 );
				params<baseType>::registerStandard ( _pcoBase_,"pcoBase_noiseIntensity",1,1.0 );
			}



    virtual void setStateVec ( vector <double  >  &r );

			//			baseType inline dt () { return dynNode::dt; }
			baseType inline nextFiring() { return eventHandler::getKey ( _fire_ ); }
			baseType inline nextRandomExcitation() { return eventHandler::getKey ( _exciteRandomly_ ); }
			baseType inline noiseFrequency()	{ return params<baseType>::getParams ( 0 ); }
			baseType inline noiseIntensity()	{ return params<baseType>::getParams ( 1 ); }
			baseType inline omega() { return ( baseType ) 1;}

			virtual unsigned int numberOfEvents() const { return 2;};

	virtual void clean ();

		virtual void excite ( baseType c ) 
		{

				baseType phase = 1.0 + this->time - eventHandler::getKey ( _fire_ );
				double newPhase = phase + phaseResponse (c, phase);
		

				if ( newPhase > phase)
				{
//					if ( newPhase > 1  )
//						newPhase = 1;
					eventHandler::decreaseKey ( _fire_,1.0  + this->time - newPhase );
				}
				else if (newPhase < phase )
				{
//				if ( phase < 0)
//						newPhase = 0;
					eventHandler::increaseKey ( _fire_,1.0  + this->time - newPhase );
				}


		}

			virtual baseType phaseResponse(baseType c, baseType phi) { throw "phaseResponse of pcoBase called!";}


			//		virtual const nodeInfo getNodeInfo() { nodeInfo n = {_pcoBase_,_dynNode_};     return n; };
			virtual baseType callBack ( unsigned int eventSignature );
			virtual const unsigned int dimension() const { return 1;}


			virtual void printStatistics(ostream &os, double nodeVerbosity, double edgeVerbosity );



			pcoBase () : dynNode ( _pcoBase_ ) {};
			pcoBase ( networkElementType n ) : dynNode(n) {}
			pcoBase ( networkElementType n, unsigned int dim ) : dynNode(n, dim) {}

			pcoBase ( const pcoBase &b );
			virtual ~pcoBase();
			virtual bool timeEvolution () { return 0; };
			virtual baseType getState();



			//			virtual void fire ();

		protected:

	};


	//! Basisklasse für pulsegekoppelte Phasenoscillatoren mit Delay. Hat registriert beim Feuern in der Klasse eventhandler one time events bei denen die Anregungen verteilt werden.
	class pcoDelay : public pcoBase
	{
		public:
			baseType inline timeDelay() { return params<baseType>::getParams ( 2 ); }

			static void registerStandardValues()
			{
				params<baseType>::registerStandard ( _pcoDelay_,"pcoDelay_noiseFrequency",0,params<baseType>::getStandardParameter ( _pcoBase_, 0 ) );
				params<baseType>::registerStandard ( _pcoDelay_,"pcoDelay_noiseIntensity",1,params<baseType>::getStandardParameter ( _pcoBase_, 1 ) );
				//			params<baseType>::registerStandard ( _pcoDelay_,"pcoDelay_t_ref",2,params<baseType>::getStandardParameter ( _pcoBase_, 0 ) );
				params<baseType>::registerStandard ( _pcoDelay_,"pcoDelay_timeDelay",2,0.01);


			}

			virtual unsigned int numberOfOneTimeEvents() const { return 5;  }
			//			pcoDelay () : dynNode ( _pcoDelay_ ) {};
			pcoDelay ( networkElementType n, unsigned int dim ) : pcoBase ( n, dim ) {}

			//		pcoDelay ( const pcoDelay &b );

			//			pcoDelay () : pcoBase () {};
			//			virtual void excite ( baseType c );
			//			virtual void fire ();

			virtual unsigned int numberOfEvents() const { return 3;};

			virtual baseType callBack ( unsigned int eventSignature );
			//         virtual node *construct() { return new pcoDelay(*this);};



			void sendExcitations();


	};








	//! Oscillator, bei dem die Zeit zum feuern Poissontverteilt ist mit Rate e hoch Membranpotential.
	class escapeNoiseNeuron : public pcoBase
	{
		public:
			baseType inline t_ref()  { return params<baseType>::getParams ( 2 ); }
			baseType inline timeDelay() { return params<baseType>::getParams ( 3 ); }
			baseType inline escapeNoise_a()	{ return params<baseType>::getParams ( 4 ); }
			baseType inline escapeNoise_b()	{ return params<baseType>::getParams ( 5 ); }

			static void registerStandardValues()
			{
				params<baseType>::registerStandard ( _escapeNoiseNeuron_,"escapeNoiseNeuron_noiseFrequency",0,params<baseType>::getStandardParameter ( _pcoBase_, 0 ) );
				params<baseType>::registerStandard ( _escapeNoiseNeuron_,"escapeNoiseNeuron_noiseIntensity",1,params<baseType>::getStandardParameter ( _pcoBase_, 1 ) );				
				params<baseType>::registerStandard ( _escapeNoiseNeuron_,"escapeNoiseNeuron_timeDelay",2,0.01 );
				params<baseType>::registerStandard ( _escapeNoiseNeuron_,"escapeNoiseNeuron_t_ref",3, 0.05 );



				params<baseType>::registerStandard ( _escapeNoiseNeuron_,"escapeNoiseNeuron_escapeNoise_a",4,1.0 );
				params<baseType>::registerStandard ( _escapeNoiseNeuron_,"escapeNoiseNeuron_escapeNoise_b",5,1.0 );
			}
			baseType pot;
			baseType lastFiring;
			escapeNoiseNeuron () : pcoBase ( _escapeNoiseNeuron_ ) { pot = lastFiring = 0;};
			virtual const nodeInfo getNodeInfo() { nodeInfo n = {_escapeNoiseNeuron_,_dynNode_ , "escapeNoiseNeuron"}; return n; } 
			virtual baseType callBack ( unsigned int eventSignature );
			virtual void excite ( baseType c );
	};





	//! OBSOLETE Edge, die bei allen Pulsegekoppelten Oscillatoren, die Phase zurückgibt. Eventuell nicht mehr benötigt, wenn pcoBase mit getState, die Phase zurückgibt.
/*	template <typename EDGE>
		class phaseOfPCPO: public EDGE
	{
		private:
			baseType inline time() { return dynNode::time;}
			baseType inline nextEvent () { return ((pcoBase*) (EDGE::getTarget() ))-> nextFiring(); }

		public:

			const edgeInfo getEdgeInfo() {edgeInfo ei = {_phaseOfPCPO_,0,"phaseOfPCPO"}; return ei;}
			phaseOfPCPO (nodeDescriptor targetNumber) : EDGE (targetNumber) {};
			phaseOfPCPO (nodeDescriptor targetNumber, baseType w) : EDGE (targetNumber) {};
			phaseOfPCPO () {};
			baseType getTargetState()
			{
				return ( 1- nextEvent() + time() );
			}
			weightedEdge *construct() { return new phaseOfPCPO ( *this ); };


	};
*/




}







#endif
