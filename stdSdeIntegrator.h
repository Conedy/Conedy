

#ifndef stdSdeIntegrator_h
#define stdSdeIntegrator_h stdSdeIntegrator_h


#include "integrator.h"
#include "sdeNode.h"
#include "gslNoise.h"

#include "networkConstants.h"

namespace conedy {


	class stdSdeIntegrator : public sdeNode 
	{
		public:
				integrator *integ;

		stdSdeIntegrator (networkElementType n) : sdeNode (n)    {}

		stdSdeIntegrator ( const stdSdeIntegrator &b ): sdeNode (b)
		{		}

			static unsigned int stepType_int;
			static params<string> *stepType;

			static void registerStandardValues()
			{
				params<string>::registerStandard(_stdSdeIntegrator_, "stdSdeIntegrator_stepType",0,"strongTaylor");
				stepType = new params<string> (_stdSdeIntegrator_);
			}


//		virtual void swap(short i) { state=x[i]; }
		virtual void clean() {

	if (amIFirst())
	{

			if (stepType->getParams(0)  == "strongTaylor")
			{
				integ = new strongTaylor (containerDimension() );
				stepType_int = 0;
			}
			else
	
				throw "unknown steptype for stdSdeIntegrator!";
	}
	};



// RUNGE KUTTA No. 4
		virtual void evolve(double time)
		{
			switch (stepType_int)
			{
				case 0:
					((strongTaylor *) integ)->step (time, dynamicVariablesOfAllDynNodes, *this, containerDimension());
					break;

			}

		}




	};





//	typedef odeNode stdSdeIntegrator;   // Runge-Kutta Ord4

}

#endif
