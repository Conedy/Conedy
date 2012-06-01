#ifndef stdSdeIntegrator_h
#define stdSdeIntegrator_h stdSdeIntegrator_h

#include "integrator.h"
#include "sdeNode.h"
#include "gslNoise.h"
#include "globals.h"
#include "networkConstants.h"

namespace conedy {


	class stdSdeIntegrator : public sdeNode, private globals
	{
		public:
				sdeIntegrator *integ;

		stdSdeIntegrator (networkElementType n, unsigned int dim) : sdeNode (n, dim)    {}

		stdSdeIntegrator ( const stdSdeIntegrator &b ): sdeNode (b) {}

		static unsigned int stepType_int;

		static void registerStandardValues()
		{
			registerGlobal<string>("sdeStepType", "euler");
		}


//		virtual void swap(short i) { state=x[i]; }
		virtual void clean() {

	if (amIFirst())
	{
			string stepType = getGlobal<string>("sdeStepType");

			if (stepType == "euler")
			{
				integ = new eulerMaruyama (containerDimension() );
				stepType_int = 0;
			}
			else if (stepType == "milsteinIto")
			{
				integ = new milsteinIto (containerDimension() );
				stepType_int = 1;
			}
			else if (stepType == "milsteinStrato")
			{
				integ = new milsteinStrato (containerDimension() );
				stepType_int = 2;
			}

			else
				throw "unknown steptype for SDE Integrator!";
	}
	};



// RUNGE KUTTA No. 4
		virtual void evolve(baseType time)
		{
			switch (stepType_int)
			{
				case 0:
					((eulerMaruyama *) integ)->step (time, dynamicVariablesOfAllDynNodes, *this, containerDimension());
					break;
				case 1:
					((milsteinIto *) integ)->step (time, dynamicVariablesOfAllDynNodes, *this, containerDimension());
					break;
				case 2:
					((milsteinStrato *) integ)->step (time, dynamicVariablesOfAllDynNodes, *this, containerDimension());
					break;
			}

		}




	};



	typedef stdSdeIntegrator sde;


//	typedef odeNode stdSdeIntegrator;   // Runge-Kutta Ord4

}

#endif
