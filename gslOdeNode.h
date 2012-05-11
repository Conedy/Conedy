


#ifndef gslOdeNode_h
#define gslOdeNode_h gslOdeNode_h



#include "node.h"
#include "params.h"
#include <boost/function.hpp>
#include <gsl/gsl_errno.h>
#include <gsl/gsl_matrix.h>
#include <gsl/gsl_odeiv2.h>
#include "containerNode.h"
// #include "baseType.h"

//typedef double baseType;


namespace conedy
{




	//! Basisklasse für Nodes, die mit der GSL-integriert werden.
	class gslOdeNode : public containerNode<baseType,3>
	{
		private:



			// Hilfsfunktionen für die GSL:
			//! Endzeit der Integration
			//! Zeiger auf die Art der Stufenfunktion (hier kann die Stufenfunktion gewählt werden)
			static const gsl_odeiv2_step_type * stepType;

			//! Zeiger auf den Speicher für die Stufenfunktion
			static gsl_odeiv2_step * gslStep;

			//! Zeiger auf die Kontrollfunktion (überprüft Fehler der Stufenfunktion)
			static gsl_odeiv2_control * gslControl;

			//! Zeiger auf die Evolutionsfuktion (diese vereint die Stufenfunktion mit der Kontrollfunktion)
			static gsl_odeiv2_evolve * gslEvolve;

			//! Datentyp für das ODE-System
			static gsl_odeiv2_system gslOdeSys;

			static baseType stepSize;

			static double * errors;

			static bool alreadyInitialized;

			inline string paramStepType() { return gslStepType->getParams(0); }
			inline double error_abs () { return gslParams->getParams(0); }
			inline double error_rel () { return gslParams->getParams(1); }
			inline double minStepSize () { return gslParams->getParams(3); }

//			inline double isAdaptive () { return gslBools->getParams(0); }
			inline double isAdaptive () { return gslParams->getParams(4); }

			static params<string> * gslStepType;
			static params<baseType> * gslParams;
			static params<bool> * gslBools;

		public:

			static void registerStandardValues()
			{
				params<string>::registerStandard(_gslOdeNode_, "odeStepType", 0, "gsl_odeiv2_step_rkf45");
				params<baseType>::registerStandard(_gslOdeNode_, "odeRelError", 0, 0.00001);
				params<baseType>::registerStandard(_gslOdeNode_, "odeAbsError", 1, 0.0);
				params<baseType>::registerStandard(_gslOdeNode_, "odeStepSize", 2, 0.001);
				params<baseType>::registerStandard(_gslOdeNode_, "odeMinStepSize", 3, 0.000001);
				params<baseType>::registerStandard(_gslOdeNode_, "odeIsAdaptive", 4, 1.0);
//				params<bool>::registerStandard(_gslOdeNode_, "odeIsAdaptive", 0, true);
				gslStepType = new params<string>(_gslOdeNode_);
				gslParams = new params<baseType>(_gslOdeNode_);
				gslBools = new params<bool>(_gslOdeNode_);
			}



			gslOdeNode (networkElementType n , unsigned int dim) : containerNode<baseType,3> ( n, dim)
		{

		};


			//! 1. und einizger Intergrationsschritt:
			virtual void evolve(double timeTilEvent);



			virtual ~gslOdeNode()
			{
				if (stepType != NULL)
				{
					// gsl aufräumen:
					gsl_odeiv2_evolve_free(gslEvolve);
					gsl_odeiv2_control_free(gslControl);
					gsl_odeiv2_step_free(gslStep);
					stepType = NULL;
				}
			}




			//! clean: wird vor der Integration aufgerufen und initialisiert diverse GSL-Parameter (Art der Stufenfunktion, Schrittweite usw.)
			virtual void clean ()
			{
				stepSize = gslParams->getParams(2);
				if ( (* containerNode<baseType,3>::nodeList.begin()) == this)   // only clean for the masternode ;-), which is the first one.
				{
					if (alreadyInitialized)  // free gsl-objects
					{
						gsl_odeiv2_step_free ( gslStep);
						gsl_odeiv2_evolve_free (gslEvolve);
						gsl_odeiv2_control_free(gslControl);
						free (errors);
					}

					alreadyInitialized = true;

					string theStepType = paramStepType();    // determine step-type

					if (theStepType == "gsl_odeiv2_step_rk2")
						stepType= gsl_odeiv2_step_rk2;
					else if (theStepType == "gsl_odeiv2_step_rk4")
						stepType= gsl_odeiv2_step_rk4;
					else if (theStepType == "gsl_odeiv2_step_rkf45")
						stepType= gsl_odeiv2_step_rkf45;
					else if (theStepType == "gsl_odeiv2_step_rkck")
						stepType= gsl_odeiv2_step_rkck;
					else if (theStepType == "gsl_odeiv2_step_rk8pd")
						stepType= gsl_odeiv2_step_rk8pd;
					else if (theStepType == "gsl_odeiv2_step_rk2imp")
						stepType= gsl_odeiv2_step_rk2imp;
					else if (theStepType == "gsl_odeiv2_step_rk4imp")
						stepType= gsl_odeiv2_step_rk4imp;
/*					else if (theStepType == "gsl_odeiv2_step_gear1")
						stepType = gsl_odeiv2_step_gear1;
					else if (theStepType == "gsl_odeiv2_step_gear2")
						stepType = gsl_odeiv2_step_gear2;*/
					else
					{	cout <<  theStepType << endl;
						throw "unknown steptype for gslOdeNode"  ;
					}

					unsigned int odeDimension = containerNode <baseType, 3> :: usedIndices ;

					errors = ( baseType* ) calloc (odeDimension ,sizeof ( baseType)  );

					gslStep = gsl_odeiv2_step_alloc ( stepType, odeDimension);

					gslControl = gsl_odeiv2_control_y_new ( error_abs(), error_rel()  );
					gslEvolve = gsl_odeiv2_evolve_alloc (odeDimension);

					gsl_odeiv2_system sys = {&gslOdeNode::dgl, NULL, odeDimension, NULL};
					gslOdeSys = sys; //{NULL,NULL,usedIndices, NULL};
				}

			}

			virtual void operator() ( const baseType x[], baseType dydx[] )  = 0;
			//! Bereitstellung des ODE-Systems: Ableitungen werden in Array geschrieben

			static int dgl ( baseType t,const baseType y[], baseType f[], void *params )
			{
				baseType * originalNodeStates = containerNode<baseType,3>::dynamicVariablesOfAllDynNodes;
				containerNode<baseType,3>::dynamicVariablesOfAllDynNodes = const_cast<baseType*> (y);

				list<containerNode<baseType,3>*>::iterator it;
				for ( it = containerNode<baseType,3>::nodeList.begin(); it != containerNode<baseType,3>::nodeList.end();it++ )
					( * ((gslOdeNode*)*it) )
							( &y[ ( *it )->startPosGslOdeNodeArray],
							  &f[ ( *it )->startPosGslOdeNodeArray] );
				return GSL_SUCCESS;
				containerNode<baseType,3>::dynamicVariablesOfAllDynNodes = originalNodeStates;

			}
			//! Kopieren der Temp-Zustände in den Zustand nach erfolgter Integration
			//			virtual void swap()
			//			{
			//				this->state = this->x[0];
			//
			//			};

			//	virtual void clean() {};

			//	virtual baseType getHiddenComponent(int component) { return x[component]; }


			//	virtual baseType getState();

			//	virtual streamIn(ifstream &in);
			//	virtual streamOut(ofstream &out);

			virtual node *construct() { return new node ( *this ); };



	};










}



#endif
