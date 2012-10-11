#include "gslOdeNode.h"



#ifdef DOUBLE

#include <gsl/gsl_errno.h>

namespace conedy
{
	void gslOdeNode::evolve(double timeTilEvent)
	{
		baseType startTime = dynNode::time;
		unsigned int gslStatus;

		if (getGlobal<bool>("odeIsAdaptive"))
		{
			// with stepsize control
			while ( dynNode::time < startTime + timeTilEvent)
			{
			
				if ( (gslStatus = gslode(evolve_apply) (
							gslEvolve,
							gslControl,
							gslStep,
							&gslOdeSys,
							&dynNode::time,
							startTime + timeTilEvent,
							getPointerToGlobal<baseType>("odeStepSize"),
							containerNode<baseType,3>::dynamicVariablesOfAllDynNodes))
						!= GSL_SUCCESS)
				{
					printf ("error: %s\n", gsl_strerror (gslStatus));
					throw "gslError!";
				}
				if (getGlobal<baseType>("odeStepSize") < getGlobal<baseType>("odeMinStepSize"))
					throw "Stepsize crossed specified minimum (odeMinStepSize). Aborting!";
			}
		}
		else
		{
			// without stepsize control
			int stepCount = timeTilEvent/getGlobal<baseType>("odeStepSize") + 1.0 - 1e-8 ;
			double dt = timeTilEvent / stepCount;

			#if GSL_MINOR_VERSION < 15
			if (not gslOdeNode::gslFixedStepSizeWarningShown)
			{
				cerr << "---------------------------\nCaveat:\nThough integrating with fixed step size seems to be working correctly with GSL 1.14, or lower, this is only by bizarre means. It is therefore recommended to treat its results with high caution (or to upgrade to GSL 1.15, or higher).\n------------------------------" << endl;
				gslOdeNode::gslFixedStepSizeWarningShown = true;
			}

			double *yerr =  (double*) calloc (containerNode <baseType, 3> :: usedIndices, sizeof(double));
			double *dydt =  (double*) calloc (containerNode <baseType, 3> :: usedIndices, sizeof(double));
			#endif

			for (int i = 0; i < stepCount; i++)
			{
				#if GSL_MINOR_VERSION < 15

				if ( gslode(step_apply) (
							gslStep,
							dynNode::time,
							dt,
							containerNode<baseType,3>::dynamicVariablesOfAllDynNodes,
							yerr,
							(i==0?NULL:dydt),
							dydt,
							&gslOdeSys)
						!=GSL_SUCCESS )
					throw "gslError!";
				dynNode::time += dt;

				#else

				if ( gslode(evolve_apply_fixed_step) (
							gslEvolve,
							gslControl,
							gslStep,
							&gslOdeSys,
							&dynNode::time,
							dt,
							containerNode<baseType,3>::dynamicVariablesOfAllDynNodes)
						!= GSL_SUCCESS)
					throw "gslError! This most likely means, that the estimated error exceeded the error level as defined by odeRelError and odeAbsError.";

				#endif
			}

			#if GSL_MINOR_VERSION < 15
			free (yerr);
			free (dydt);
			#endif
		}

		dynNode::time = startTime;  // changing the time is handled by the evolve-loop in dynNetwork.cpp
	}

	const gslode(step_type) * gslOdeNode::stepType = NULL;

	//! Zeiger auf den Speicher für die Stufenfunktion

	gslode(step) * gslOdeNode::gslStep;

	//! Zeiger auf die Kontrollfunktion (überprüft Fehler der Stufenfunktion)

	gslode(control) * gslOdeNode::gslControl;

	//! Zeiger auf die Evolutionsfuktion (diese vereint die Stufenfunktion mit der Kontrollfunktion)

	gslode(evolve) * gslOdeNode::gslEvolve;

	//! Datentyp für das ODE-System

	gslode(system) gslOdeNode::gslOdeSys;

	bool gslOdeNode::alreadyInitialized = false;
	bool gslOdeNode::gslFixedStepSizeWarningShown = false;

}

#endif
