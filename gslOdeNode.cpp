
#include "gslOdeNode.h"


#ifdef DOUBLE



namespace conedy
{
	void gslOdeNode::evolve(double timeTilEvent)
	{
		baseType startTime = dynNode::time;

		if (getGlobal<bool>("odeIsAdaptive"))
		{									// with stepsize control
			while ( dynNode::time < startTime + timeTilEvent)
			{
				if ( gsl_odeiv2_evolve_apply (
							gslEvolve,
							gslControl,
							gslStep,
							&gslOdeSys,
							&dynNode::time,
							dynNode::time + timeTilEvent,
							getPointerToGlobal<baseType>("odeStepSize"),
							containerNode<baseType,3>::dynamicVariablesOfAllDynNodes)
						!= GSL_SUCCESS)
					throw "gslError!";

				if (getGlobal<baseType>("odeStepSize") < getGlobal<baseType>("odeMinStepSize"))
					throw "Stepsize crossed specified minimum (odeMinStepSize). Aborting!";
			}
		}
		else
		{									// without stepsize control
			int stepCount = timeTilEvent/getGlobal<baseType>("odeStepSize") + 1.0 - 1e-8 ;
			double dt = timeTilEvent / stepCount;

			for (int i = 0; i < stepCount; i++)
				if ( gsl_odeiv2_evolve_apply_fixed_step (
							gslEvolve,
							gslControl,
							gslStep,
							&gslOdeSys,
							&dynNode::time,
							dt,
							containerNode<baseType,3>::dynamicVariablesOfAllDynNodes)
						!= GSL_SUCCESS)
					throw "gslError! This most likely means, that the estimated error exceeded the error level as defined by odeRelError and odeAbsError.";
		}


		dynNode::time = startTime;    // changing the time is handled by the evolve-loop in dynNetwork.cpp
	}

	const gsl_odeiv2_step_type * gslOdeNode::stepType = NULL;

	//! Zeiger auf den Speicher für die Stufenfunktion

	gsl_odeiv2_step * gslOdeNode::gslStep;

	//! Zeiger auf die Kontrollfunktion (überprüft Fehler der Stufenfunktion)

	gsl_odeiv2_control * gslOdeNode::gslControl;

	//! Zeiger auf die Evolutionsfuktion (diese vereint die Stufenfunktion mit der Kontrollfunktion)

	gsl_odeiv2_evolve * gslOdeNode::gslEvolve;

	//! Datentyp für das ODE-System

	gsl_odeiv2_system gslOdeNode::gslOdeSys;

	bool gslOdeNode::alreadyInitialized = false;

}

#endif
