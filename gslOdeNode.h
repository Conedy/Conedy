


#ifndef gslOdeNode_h
#define gslOdeNode_h gslOdeNode_h



#include "node.h"
#include "params.h"
#include <boost/function.hpp>
#include <gsl/gsl_errno.h>
#include <gsl/gsl_matrix.h>
#include <gsl/gsl_odeiv.h>
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
			static const gsl_odeiv_step_type *stepType;
			
			//! Zeiger auf den Speicher für die Stufenfunktion
			static gsl_odeiv_step *gslStep;
			
			//! Zeiger auf die Kontrollfunktion (überprüft Fehler der Stufenfunktion)
			static gsl_odeiv_control *gslControl;
		
			//! Zeiger auf die Evolutionsfuktion (diese vereint die Stufenfunktion mit der Kontrollfunktion)
			static gsl_odeiv_evolve *gslEvolve;
		
			//! Datentyp für das ODE-System
			static gsl_odeiv_system gslOdeSys;


			inline string paramStepType() { return gslStepType->getParams(0); }

			static params<string> *gslStepType;

		public:

			static void registerStandardValues()
			{
				params<string>::registerStandard(_gslOdeNode_, "gslOdeNode_stepType",0,"gsl_odeiv_step_rk4");
				gslStepType = new params<string>(_gslOdeNode_);
			}	


			gslOdeNode (networkElementType n ) : containerNode<baseType,3> ( n)
			{
				
			};
			
			
			//! 1. und einizger Intergrationsschritt:
		virtual void evolve(double timeTilEvent);
				

			
			virtual ~gslOdeNode()
			{
				if (stepType != NULL)
				{
				// gsl aufräumen:
					gsl_odeiv_evolve_free(gslEvolve);
					gsl_odeiv_control_free(gslControl);
					gsl_odeiv_step_free(gslStep);
					stepType = NULL;
				}		
			}
	
		
		
			
			//! clean: wird vor der Integration aufgerufen und initialisiert diverse GSL-Parameter (Art der Stufenfunktion, Schrittweite usw.)
			virtual void clean ( unsigned int timesteps )
			{

			if ( (* containerNode<baseType,3>::nodeList.begin()) == this)
			{
				//! Wahl der Stufenfunktion: Runge-Kutta Prince Dormand (8,9)
				//stepType = gsl_odeiv_step_rk8pd;

				//! Wahl der Stufenfunktion:	Runge-Kutta 4. Ordnung: Halving the stepsizew

				// this is really stupid, but what can I do ?

				string theStepType = paramStepType();

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
//				if (theStepType() == "gsl_odeiv_step_gear1imp")
//					stepType = gsl_odeiv_step_gear1imp;
//				if (theStepType() == "gsl_odeiv_step_gear2")
//					stepType = gsl_odeiv_step_gear2;
				else
				{	cout <<  theStepType << endl;
					throw "unknown steptype for gslOdeNode"  ;
				}
				//! Wahl der Stufenfunktion:	Runge-Kutta 4. Ordnung, Fehldberg-Meth für Fehler
				//stepType = gsl_odeiv_step_rkf45;
				
				//! Reservierung von Speicher
				gslStep = gsl_odeiv_step_alloc ( stepType, containerNode<baseType,3>::usedIndices );

				gslControl = gsl_odeiv_control_y_new ( 0.0,0.4 );
				gslEvolve = gsl_odeiv_evolve_alloc ( containerNode<baseType,3>::usedIndices );

				gsl_odeiv_system sys = {&gslOdeNode::func, NULL, containerNode<baseType,3>::usedIndices, NULL}; //usedIndices war "2". fixed by HD

				gslOdeSys = sys; //{NULL,NULL,usedIndices, NULL};
			}

			}

			virtual void operator() ( const baseType x[], baseType dydx[] )  = 0;
		
			//! Bereitstellung des ODE-Systems: Ableitungen werden in Array geschrieben
			static int func ( baseType t,const baseType y[], baseType f[], void *params )
			{
				 list<containerNode<baseType,3>*>::iterator it;
				for ( it = containerNode<baseType,3>::nodeList.begin(); it != containerNode<baseType,3>::nodeList.end();it++ )
					( * ((gslOdeNode*)*it) ) ( &y[ ( *it )->startPosGslOdeNodeArray], &f[ ( *it )->startPosGslOdeNodeArray] );
				return GSL_SUCCESS;
			}
			//! Kopieren der Temp-Zustände in den Zustand nach erfolgter Integration
//			virtual void swap()
//			{
//				this->state = this->tmp[0];
//
//			};
		
//	virtual void clean(unsigned int timeSteps) {};

//	virtual baseType getHiddenComponent(int component) { return tmp[component]; }


//	virtual baseType getState();

//	virtual streamIn(ifstream &in);
//	virtual streamOut(ofstream &out);

			virtual node *construct() { return new node ( *this ); };



	};










}



#endif
