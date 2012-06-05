
#include "gslOdeNode.h"



#ifdef DOUBLE

#if GSL_MINOR_VERSION < 15


namespace conedy
{


	params<string> * gslOdeNode::gslStepType;

	params<baseType> *gslOdeNode::gslErrors;


	double * gslOdeNode::errors;



	double gslOdeNode::stepSize = 0.001;


	void gslOdeNode::evolve(double timeTilEvent)
	{


		baseType startTime = dynNode::time;
		baseType endTime = dynNode::time + timeTilEvent;


		if (error_abs() == 0.0 && error_rel() == 0.0)
		{									// without stepsize control

			throw "fixed stepsize seems to be broken at the moment.";

			int stepCount = timeTilEvent/stepSize + 1.0 - 1e-8 ;
			double dt = timeTilEvent / stepCount;


				if ( gsl_odeiv_step_apply ( gslStep,dynNode::time,
							timeTilEvent,
							containerNode<baseType,3>::dynamicVariablesOfAllDynNodes,
							errors,
							NULL,
							NULL,
							&gslOdeSys) !=GSL_SUCCESS )
					throw "gslError!";


//			for (int i = 0; i < stepCount; i++)
//			{
//				if ( gsl_odeiv_step_apply ( gslStep,dynNode::time,
//							dt,
//							containerNode<baseType,3>::dynamicVariablesOfAllDynNodes,
//							errors,
//							NULL,
//							NULL,
//							&gslOdeSys) !=GSL_SUCCESS )
//					throw "gslError!";
////				dynNode::time += dt;
//#ifdef DEBUG
//								cout << dt << "\n";
//#endif
//			}
//


		}
		else
		{									// with stepsize control
			while(dynNode::time < endTime)
			{
				int status = gsl_odeiv_evolve_apply (gslEvolve,
						gslControl,
						gslStep,
						&gslOdeSys,
						&dynNode::time,
						endTime,
						&stepSize,
						containerNode<baseType,3>::dynamicVariablesOfAllDynNodes) ;
				if (status != GSL_SUCCESS)
					break;

#ifdef DEBUG
								cout << stepSize << "\n";
#endif
			}
		}

		dynNode::time = startTime;    // changing the time is handled by the evolve-loop in dynNetwork.cpp



	}

	const gsl_odeiv_step_type* gslOdeNode::stepType = NULL;

	//! Zeiger auf den Speicher f¸r die Stufenfunktion

	gsl_odeiv_step *gslOdeNode::gslStep;

	//! Zeiger auf die Kontrollfunktion (¸berpr¸ft Fehler der Stufenfunktion)

	gsl_odeiv_control *gslOdeNode::gslControl;

	//! Zeiger auf die Evolutionsfuktion (diese vereint die Stufenfunktion mit der Kontrollfunktion)

	gsl_odeiv_evolve *gslOdeNode::gslEvolve;

	//! Datentyp f¸r das ODE-System

	gsl_odeiv_system gslOdeNode::gslOdeSys;


}




#else


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

	//! Zeiger auf den Speicher f√ºr die Stufenfunktion

	gsl_odeiv2_step * gslOdeNode::gslStep;

	//! Zeiger auf die Kontrollfunktion (√ºberpr√ºft Fehler der Stufenfunktion)

	gsl_odeiv2_control * gslOdeNode::gslControl;

	//! Zeiger auf die Evolutionsfuktion (diese vereint die Stufenfunktion mit der Kontrollfunktion)

	gsl_odeiv2_evolve * gslOdeNode::gslEvolve;

	//! Datentyp f√ºr das ODE-System

	gsl_odeiv2_system gslOdeNode::gslOdeSys;

	bool gslOdeNode::alreadyInitialized = false;

}
#endif
#endif
