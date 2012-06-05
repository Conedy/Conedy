#ifndef gslOdeNode_h
#define gslOdeNode_h gslOdeNode_h


#include "baseType.h"

#ifdef DOUBLE


#include "node.h"
#include "params.h"
#include <boost/function.hpp>
#include <gsl/gsl_errno.h>
#include <gsl/gsl_matrix.h>
#include "containerNode.h"
#include "globals.h"
#include <gsl/gsl_version.h>


#if GSL_MINOR_VERSION < 15
#include <gsl/gsl_odeiv.h>




namespace conedy
{




	//! Basisklasse f¸r Nodes, die mit der GSL-integriert werden.	
	class gslOdeNode : public containerNode<baseType,3>
	{    
		private:



			// Hilfsfunktionen f¸r die GSL:
			//! Endzeit der Integration
			//! Zeiger auf die Art der Stufenfunktion (hier kann die Stufenfunktion gew‰hlt werden)
			static const gsl_odeiv_step_type *stepType;

			//! Zeiger auf den Speicher f¸r die Stufenfunktion
			static gsl_odeiv_step *gslStep;

			//! Zeiger auf die Kontrollfunktion (¸berpr¸ft Fehler der Stufenfunktion)
			static gsl_odeiv_control *gslControl;

			//! Zeiger auf die Evolutionsfuktion (diese vereint die Stufenfunktion mit der Kontrollfunktion)
			static gsl_odeiv_evolve *gslEvolve;

			//! Datentyp f¸r das ODE-System
			static gsl_odeiv_system gslOdeSys;

			static baseType stepSize;

			static double * errors;

			inline string paramStepType() { return gslStepType->getParams(0); }
			inline double error_abs () { return gslErrors->getParams(0); }
			inline double error_rel () { return gslErrors->getParams(1); }

			static params<string> *gslStepType;
			static params<baseType> *gslErrors;

		public:

			static void registerStandardValues()
			{
				params<string>::registerStandard(_gslOdeNode_,   "odeStepType",0,"gsl_odeiv_step_rkf45");
				params<baseType>::registerStandard(_gslOdeNode_, "odeRelError",0,0.00001);
				params<baseType>::registerStandard(_gslOdeNode_, "odeAbsError",1,0.0);
				params<baseType>::registerStandard(_gslOdeNode_, "odeStepSize",2,0.001);
				gslStepType = new params<string>(_gslOdeNode_);
				gslErrors = new params<baseType>(_gslOdeNode_);
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
					// gsl aufr‰umen:
					gsl_odeiv_evolve_free(gslEvolve);
					gsl_odeiv_control_free(gslControl);
					gsl_odeiv_step_free(gslStep);
					stepType = NULL;
				}		
			}




			//! clean: wird vor der Integration aufgerufen und initialisiert diverse GSL-Parameter (Art der Stufenfunktion, Schrittweite usw.)
			virtual void clean ()
			{
				stepSize = gslErrors->getParams(2);
				if ( (* containerNode<baseType,3>::nodeList.begin()) == this)
				{
					string theStepType = paramStepType();    // determine step-type

					if (theStepType == "gsl_odeiv_step_rk2")
						stepType= gsl_odeiv_step_rk2;
					else if (theStepType == "gsl_odeiv_step_rk4")
						stepType= gsl_odeiv_step_rk4;
					else if (theStepType == "gsl_odeiv_step_rkf45")
						stepType= gsl_odeiv_step_rkf45;
					else if (theStepType == "gsl_odeiv_step_rkck")
						stepType= gsl_odeiv_step_rkck;
					else if (theStepType == "gsl_odeiv_step_rk8pd")
						stepType= gsl_odeiv_step_rk8pd;
					else if (theStepType == "gsl_odeiv_step_rk2imp")
						stepType= gsl_odeiv_step_rk2imp;
					else if (theStepType == "gsl_odeiv_step_rk4imp")
						stepType= gsl_odeiv_step_rk4imp;
					else if (theStepType == "gsl_odeiv_step_gear1")
						stepType = gsl_odeiv_step_gear1;
					else if (theStepType == "gsl_odeiv_step_gear2")
						stepType = gsl_odeiv_step_gear2;
					else
					{	cout <<  theStepType << endl;
						throw "unknown steptype for gslOdeNode"  ;
					}

					unsigned int odeDimension = containerNode <baseType, 3> :: usedIndices ;

					errors = ( baseType* ) calloc (odeDimension ,sizeof ( baseType)  );

					gslStep = gsl_odeiv_step_alloc ( stepType, odeDimension);

					gslControl = gsl_odeiv_control_y_new ( error_abs(), error_rel()  );
					gslEvolve = gsl_odeiv_evolve_alloc (odeDimension); 

					gsl_odeiv_system sys = {&gslOdeNode::dgl, NULL, odeDimension, NULL}; 
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
			//! Kopieren der Temp-Zust‰nde in den Zustand nach erfolgter Integration
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








#else
#include <gsl/gsl_odeiv2.h>

namespace conedy
{

	//! Basisklasse f√ºr Nodes, die mit der GSL-integriert werden.
	class gslOdeNode : public containerNode<baseType,3>, private globals
	{
		private:



			// Hilfsfunktionen f√ºr die GSL:
			//! Endzeit der Integration
			//! Zeiger auf die Art der Stufenfunktion (hier kann die Stufenfunktion gew√§hlt werden)
			static const gsl_odeiv2_step_type * stepType;

			//! Zeiger auf den Speicher f√ºr die Stufenfunktion
			static gsl_odeiv2_step * gslStep;

			//! Zeiger auf die Kontrollfunktion (√ºberpr√ºft Fehler der Stufenfunktion)
			static gsl_odeiv2_control * gslControl;

			//! Zeiger auf die Evolutionsfuktion (diese vereint die Stufenfunktion mit der Kontrollfunktion)
			static gsl_odeiv2_evolve * gslEvolve;

			//! Datentyp f√ºr das ODE-System
			static gsl_odeiv2_system gslOdeSys;

			static bool alreadyInitialized;

		public:

			static void registerStandardValues()
			{
				registerGlobal<string>("odeStepType", "gsl_odeiv2_step_rkf45");
				registerGlobal<double>("odeRelError", 0.00001);
				registerGlobal<double>("odeAbsError", 0.0);
				registerGlobal<baseType>("odeStepSize", 0.001);
				registerGlobal<baseType>("odeMinStepSize", 0.000001);
				registerGlobal<bool>("odeIsAdaptive", true);
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
					// gsl aufr√§umen:
					gsl_odeiv2_evolve_free(gslEvolve);
					gsl_odeiv2_control_free(gslControl);
					gsl_odeiv2_step_free(gslStep);
					stepType = NULL;
					alreadyInitialized = false;
				}
			}




			//! clean: wird vor der Integration aufgerufen und initialisiert diverse GSL-Parameter (Art der Stufenfunktion, Schrittweite usw.)
			virtual void clean ()
			{
				if ( (* containerNode<baseType,3>::nodeList.begin()) == this)   // only clean for the masternode ;-), which is the first one.
				{
					if (alreadyInitialized)  // free gsl-objects
					{
						gsl_odeiv2_step_free(gslStep);
 						gsl_odeiv2_evolve_free(gslEvolve);
						gsl_odeiv2_control_free(gslControl);
					}

					alreadyInitialized = true;

					string theStepType = getGlobal<string>("odeStepType");
					if (theStepType == "gsl_odeiv2_step_rk2")
						stepType = gsl_odeiv2_step_rk2;
					else if (theStepType == "gsl_odeiv2_step_rk4")
						stepType = gsl_odeiv2_step_rk4;
					else if (theStepType == "gsl_odeiv2_step_rkf45")
						stepType = gsl_odeiv2_step_rkf45;
					else if (theStepType == "gsl_odeiv2_step_rkck")
						stepType = gsl_odeiv2_step_rkck;
					else if (theStepType == "gsl_odeiv2_step_rk8pd")
						stepType = gsl_odeiv2_step_rk8pd;
					else if (theStepType == "gsl_odeiv2_step_rk2imp")
						stepType = gsl_odeiv2_step_rk2imp;
					else if (theStepType == "gsl_odeiv2_step_rk4imp")
						stepType = gsl_odeiv2_step_rk4imp;
/*					else if (theStepType == "gsl_odeiv2_step_gear1")
						stepType = gsl_odeiv2_step_gear1;
					else if (theStepType == "gsl_odeiv2_step_gear2")
						stepType = gsl_odeiv2_step_gear2;*/
					else
					{	cerr << "unknown steptype for gslOdeNode: " <<  theStepType;
						throw "\n";
					}

					unsigned int odeDimension = containerNode <baseType, 3> :: usedIndices ;

					gslStep = gsl_odeiv2_step_alloc ( stepType, odeDimension);

					gslControl = gsl_odeiv2_control_y_new (
							getGlobal<double>("odeAbsError"),
							getGlobal<double>("odeRelError")
						);

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
			//! Kopieren der Temp-Zust√§nde in den Zustand nach erfolgter Integration
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



#endif

#endif
