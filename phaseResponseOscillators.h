#ifndef phaseResponseOscillators_h
#define phaseResponseOscillators_h phaseResponseOscillators_h


#include "pulseCoupledPhaseOscillator.h"

namespace conedy
{

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


}




#endif
