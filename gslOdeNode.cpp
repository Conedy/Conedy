


#include "gslOdeNode.h"



namespace conedy 
{


	params<string> * gslOdeNode::gslStepType;

	params<baseType> *gslOdeNode::gslErrors;


	double * gslOdeNode::errors;



	double gslOdeNode::stepSize = 0.001;


	void gslOdeNode::evolve(double timeTilEvent)
	{
		//			dynNode::time = time;
		//				if ( endTime <= dynNode::time )
		//					throw "Fertig!";

		//			cout << this->time << endl;

		//double endTime = dynNode::time + timeTilEvent;
		//			while (dynNode::time <  endTime)
		//			{
		double dt = timeTilEvent;


		// adaptive stepsize has valgrind errors, don't know why
		//				if ( gsl_odeiv_evolve_apply ( gslEvolve,gslControl,gslStep,&gslOdeSys,&dynNode::time,endTime ,&dt,containerNode<baseType,3>::dynamicVariablesOfAllDynNodes ) !=GSL_SUCCESS )
		//				  throw "gslError!";
//		baseType *errors = ( baseType* ) calloc (p.getParams(0) ,sizeof ( baseType)  );
//				cout << stepSize << "\n";

		if ( error_abs() == 0.0 && error_rel() == 0.0)
		{									// without stepsize control

			if ( gsl_odeiv_step_apply ( gslStep,dynNode::time,
						dt,
						containerNode<baseType,3>::dynamicVariablesOfAllDynNodes, 
						errors,
						NULL,
						NULL, 
						&gslOdeSys) !=GSL_SUCCESS )
				throw "gslError!";


			// with stepsize control
		}
		else 
		{	


			baseType  startTime = dynNode::time;
			baseType endTime = dynNode::time + timeTilEvent;


			while ( dynNode::time < endTime)
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
			dynNode::time = startTime;    // changing the time is handled by the evolve-loop in dynNetwork.cpp

		} 



		//


		//			   list<containerNode<baseType,3> *>::iterator it;
		//				 for (it = containerNode<baseType,3>::nodeList.begin(); it != containerNode<baseType,3>::nodeList.end(); it++)
		//				    (*it)->swap();

		//			dynNode::time -= timeTilEvent;

		//			}

	}

	const gsl_odeiv_step_type* gslOdeNode::stepType = NULL;

	//! Zeiger auf den Speicher für die Stufenfunktion

	gsl_odeiv_step *gslOdeNode::gslStep;

	//! Zeiger auf die Kontrollfunktion (überprüft Fehler der Stufenfunktion)

	gsl_odeiv_control *gslOdeNode::gslControl;

	//! Zeiger auf die Evolutionsfuktion (diese vereint die Stufenfunktion mit der Kontrollfunktion)

	gsl_odeiv_evolve *gslOdeNode::gslEvolve;

	//! Datentyp für das ODE-System

	gsl_odeiv_system gslOdeNode::gslOdeSys;


}


