

#ifndef phaseResponseOscillators_h
#define phaseResponseOscillators_h phaseResponseOscillators_h


#include "pulseCoupledPhaseOscillator.h" 

namespace conedy
{
	//! Integrate-and-Fire oscillator mit exponentieller Ladekurve. 
/*	class pcoIFNeuronDelay : public pcoDelay
	{
		public:
			baseType privateLogarithm;
			baseType inline t_ref()  { return params<baseType>::getParams ( 3 ); }
//			baseType inline timeDelay() { return params<baseType>::getParams ( 2); }
			baseType inline alpha() { return params<baseType>::getParams ( 4 ); }
			baseType inline logAlpha() { return privateLogarithm; }

			virtual void clean ();
			static void registerStandardValues()
			{
				params<baseType>::registerStandard ( _pcoIFNeuronDelay_,"pcoIFNeuronDelay_noiseFrequency",0,params<baseType>::getStandardParameter ( _pco_, 0 ) );
				params<baseType>::registerStandard ( _pcoIFNeuronDelay_,"pcoIFNeuronDelay_noiseIntensity",1,params<baseType>::getStandardParameter ( _pco_, 1 ) );
				params<baseType>::registerStandard ( _pcoIFNeuronDelay_,"pcoIFNeuronDelay_timeDelay",2, params<baseType>::getStandardParameter ( _pcoDelay_, 2 ) );
				params<baseType>::registerStandard ( _pcoIFNeuronDelay_,"pcoIFNeuronDelay_t_ref",3, 0.05 );

				params<baseType>::registerStandard ( _pcoIFNeuronDelay_,"pcoIFNeuronDelay_alpha",4,0.9 );
			}
  			virtual const nodeInfo getNodeInfo() { nodeInfo n = {_pcoIFNeuronDelay_,_dynNode_,  "pcoIFNeuronDelay"};     return n; };
			pcoIFNeuronDelay () : pcoDelay ( _pcoIFNeuronDelay_ ) {};
			virtual void excite ( baseType c );



	};


*/	
 class pcoExponential : public pcoBase


	{
	public:

			baseType inline timeDelay() { return params<baseType>::getParams ( 2 ); }
			baseType inline t_ref()  { return params<baseType>::getParams ( 3 ); }

//			virtual void clean ();
			static void registerStandardValues()
			{
				params<baseType>::registerStandard ( _pcoExponential_,"pcoExponential_noiseFrequency",0,params<baseType>::getStandardParameter ( _pco_, 0 ) );
				params<baseType>::registerStandard ( _pcoExponential_,"pcoExponential_noiseIntensity",1,params<baseType>::getStandardParameter ( _pco_, 1 ) );
				params<baseType>::registerStandard ( _pcoExponential_,"pcoExponential_t_ref",3,0.05 );
				params<baseType>::registerStandard ( _pcoExponential_,"pcoExponential_timeDelay",2,0.01 );
			}

  			virtual const nodeInfo getNodeInfo() { nodeInfo n = {_pcoExponential_,_dynNode_,  "pcoExponential"};     return n; };
			pcoExponential () : pcoBase ( _pcoExponential_ ) {};
			virtual void excite ( baseType c );

	};
//! pco mit Dreieck
 class pcoTrapez : public pcoBase


	{
		public:


			baseType inline a() { return params<baseType>::getParams ( 2 ); }
			baseType inline b()  { return params<baseType>::getParams ( 3 ); }
			baseType inline c() { return params<baseType>::getParams ( 4 ); }
			baseType inline d()  { return params<baseType>::getParams ( 5 ); }
			baseType inline h1()  { return params<baseType>::getParams (6 ); }
			baseType inline h2()  { return params<baseType>::getParams ( 7 ); }

//			virtual void clean ();
			static void registerStandardValues()
			{
				params<baseType>::registerStandard ( _pcoTrapez_,"pcoTrapez_noiseFrequency",0,params<baseType>::getStandardParameter ( _pco_, 0 ) );
				params<baseType>::registerStandard ( _pcoTrapez_,"pcoTrapez_noiseIntensity",1,params<baseType>::getStandardParameter ( _pco_, 1 ) );

				params<baseType>::registerStandard ( _pcoTrapez_,"pcoTrapez_a",2,0.04 );
				params<baseType>::registerStandard ( _pcoTrapez_,"pcoTrapez_b",3,0.04 );
				params<baseType>::registerStandard ( _pcoTrapez_,"pcoTrapez_c",4,0.97 );
				params<baseType>::registerStandard ( _pcoTrapez_,"pcoTrapez_d",5,0.99 );
				params<baseType>::registerStandard ( _pcoTrapez_,"pcoTrapez_h1",6,0.02 );
				params<baseType>::registerStandard ( _pcoTrapez_,"pcoTrapez_h2",7,0.02 );
			}

  			virtual const nodeInfo getNodeInfo() { nodeInfo n = {_pcoTrapez_,_dynNode_,  "pcoTrapez"};     return n; };
			pcoTrapez () : pcoBase ( _pcoTrapez_ ) {};
			virtual void excite ( baseType c );



	};
	




	//! richtige Integrate-and-fire-neuronen mit delay und refraktärzeiten
/*	class pcoRealIFNeuronDelay : public pcoDelay
	{
		public:
			baseType privateLogarithm;
			baseType inline t_ref()  { return params<baseType>::getParams ( 3 ); }
//			baseType inline timeDelay() { return params<baseType>::getParams ( 2); }
			baseType inline alpha() { return params<baseType>::getParams ( 4 ); }
			baseType inline logAlpha() { return privateLogarithm; }

			virtual void clean ();
			static void registerStandardValues()
			{
				params<baseType>::registerStandard ( _pcoRealIFNeuronDelay_,"pcoRealIFNeuronDelay_noiseFrequency",0,params<baseType>::getStandardParameter ( _pco_, 0 ) );
				params<baseType>::registerStandard ( _pcoRealIFNeuronDelay_,"pcoRealIFNeuronDelay_noiseIntensity",1,params<baseType>::getStandardParameter ( _pco_, 1 ) );
				params<baseType>::registerStandard ( _pcoRealIFNeuronDelay_,"pcoRealIFNeuronDelay_timeDelay",2, params<baseType>::getStandardParameter ( _pcoDelay_, 2 ) );
				params<baseType>::registerStandard ( _pcoRealIFNeuronDelay_,"pcoRealIFNeuronDelay_t_ref",3, 0.05 );

				params<baseType>::registerStandard ( _pcoRealIFNeuronDelay_,"pcoRealIFNeuronDelay_alpha",4,0.9 );
			}

  			virtual const nodeInfo getNodeInfo() { nodeInfo n = {_pcoRealIFNeuronDelay_,_dynNode_,  "pcoRealIFNeuronDelay"};     return n; };
			pcoRealIFNeuronDelay () : pcoDelay ( _pcoRealIFNeuronDelay_ ) {};
			virtual void excite ( baseType c );



	};
*/

	//! Oscillator mit der Aufladekurve von Mirollo und Strogatz (lineare phase-response-curve)
/*	class pcoMirollo : public pcoBase
	{
		public:
			baseType privateLogarithm;

			baseType inline timeDelay() { return params<baseType>::getParams ( 2 ); }
			baseType inline t_ref()  { return params<baseType>::getParams ( 3 ); }
			baseType inline a() { return params<baseType>::getParams ( 4 ); }
			baseType inline b() { return params<baseType>::getParams ( 5 ); }
	

			static void registerStandardValues()
			{
				params<baseType>::registerStandard ( _pcoMirollo_,"pcoMirollo_noiseFrequency",0,params<baseType>::getStandardParameter ( _pco_, 0 ) );
				params<baseType>::registerStandard ( _pcoMirollo_,"pcoMirollo_noiseIntensity",1,params<baseType>::getStandardParameter ( _pco_, 1 ) );
				params<baseType>::registerStandard ( _pcoMirollo_,"pcoMirollo_timeDelay",2,0.01 );
				params<baseType>::registerStandard ( _pcoMirollo_,"pcoMirollo_t_ref",3, 0.05 );

				params<baseType>::registerStandard ( _pcoMirollo_,"pcoMirollo_a",4,0.01 );
				params<baseType>::registerStandard ( _pcoMirollo_,"pcoMirollo_b",5,0.0 );


			}

  			virtual const nodeInfo getNodeInfo() { nodeInfo n = {_pcoMirollo_,_dynNode_,  "pcoMirollo"};     return n; };
			pcoMirollo () : pcoBase ( _pcoMirollo_ ) {};
			virtual void excite ( baseType c );



	};
*/
/*	class pcoIFNeuron : public pcoBase
	{
		public:
			baseType privateLogarithm;

			baseType inline timeDelay() { return params<baseType>::getParams ( 2 ); }
			baseType inline t_ref()  { return params<baseType>::getParams ( 3 ); }
			baseType inline alpha() { return params<baseType>::getParams ( 4 ); }
			baseType inline logAlpha() { return privateLogarithm; }

			virtual void clean ();
			static void registerStandardValues()
			{
				params<baseType>::registerStandard ( _pcoIFNeuron_,"pcoIFNeuron_noiseFrequency",0,params<baseType>::getStandardParameter ( _pco_, 0 ) );
				params<baseType>::registerStandard ( _pcoIFNeuron_,"pcoIFNeuron_noiseIntensity",1,params<baseType>::getStandardParameter ( _pco_, 1 ) );
				params<baseType>::registerStandard ( _pcoIFNeuron_,"pcoIFNeuron_timeDelay",2,0.01 );
				params<baseType>::registerStandard ( _pcoIFNeuron_,"pcoIFNeuron_t_ref",3, 0.05 );

				params<baseType>::registerStandard ( _pcoIFNeuron_,"pcoIFNeuron_alpha",4,0.9 );


			}

  			virtual const nodeInfo getNodeInfo() { nodeInfo n = {_pcoIFNeuron_,_dynNode_,  "pcoIFNeuron"};     return n; };
			pcoIFNeuron () : pcoBase ( _pcoIFNeuron_ ) {};
			virtual void excite ( baseType c );



	};

*/

/*

	//! nonleaky Integrate-and-Fire-Oscillator mit Refraktärzeit und Time-Delay
	class pcoNonleaky : public pcoBase
	{
		public:


			baseType inline timeDelay() { return params<baseType>::getParams ( 2 ); }
			baseType inline t_ref()  { return params<baseType>::getParams ( 3 ); }

//			virtual void clean ();
			static void registerStandardValues()
			{
				params<baseType>::registerStandard ( _pcoNonleaky_,"pcoNonleaky_noiseFrequency",0,params<baseType>::getStandardParameter ( _pco_, 0 ) );
				params<baseType>::registerStandard ( _pcoNonleaky_,"pcoNonleaky_noiseIntensity",1,params<baseType>::getStandardParameter ( _pco_, 1 ) );
				params<baseType>::registerStandard ( _pcoNonleaky_,"pcoNonleaky_t_ref",3,0.05 );
				params<baseType>::registerStandard ( _pcoNonleaky_,"pcoNonleaky_timeDelay",2,0.01 );
			}

  			virtual const nodeInfo getNodeInfo() { nodeInfo n = {_pcoNonleaky_,_dynNode_,  "pcoNonleaky"};     return n; };
			pcoNonleaky () : pcoBase ( _pcoNonleaky_ ) {};
			virtual void excite ( baseType c );



	};

*/

}




#endif
