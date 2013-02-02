#ifndef gslOdeNode_h
#define gslOdeNode_h gslOdeNode_h

#include "baseType.h"
#include <iomanip>

#ifdef DOUBLE

#include "node.h"
#include "params.h"
#include <boost/function.hpp>
#include <gsl/gsl_errno.h>
#include <gsl/gsl_matrix.h>
#include "containerNode.h"
#include "globals.h"
#include <sstream>

#include <gsl/gsl_version.h>
#if GSL_MINOR_VERSION < 15
	#include <gsl/gsl_odeiv.h>
	#define gslode(x) gsl_odeiv_ ## x
#else
	#include <gsl/gsl_odeiv2.h>
	#define gslode(x) gsl_odeiv2_ ## x
#endif

namespace conedy
{

	//! Basisklasse für Nodes, die mit der GSL-integriert werden.
	class gslOdeNode : public containerNode<baseType,3>, private globals
	{
		private:

			// Hilfsfunktionen für die GSL:
			//! Endzeit der Integration
			//! Zeiger auf die Art der Stufenfunktion (hier kann die Stufenfunktion gewählt werden)
			static const gslode(step_type) * stepType;

			//! Zeiger auf den Speicher für die Stufenfunktion
			static gslode(step) * gslStep;

			//! Zeiger auf die Kontrollfunktion (überprüft Fehler der Stufenfunktion)
			static gslode(control) * gslControl;

			//! Zeiger auf die Evolutionsfuktion (diese vereint die Stufenfunktion mit der Kontrollfunktion)
			static gslode(evolve) * gslEvolve;

			//! Datentyp für das ODE-System
			static gslode(system) gslOdeSys;

			static bool alreadyInitialized;
			static bool gslFixedStepSizeWarningShown;


		public:

			static void registerStandardValues()
			{
				registerGlobal<string>("odeStepType", "gsl_rkf45");
				registerGlobal<double>("odeRelError", 0.00001);
				registerGlobal<double>("odeAbsError", 0.0);
				registerGlobal<baseType>("odeStepSize", 0.001);
				registerGlobal<baseType>("odeMinStepSize", 0.000001);
				registerGlobal<bool>("odeIsAdaptive", true);
			}

			gslOdeNode (networkElementType n , unsigned int dim) : containerNode<baseType,3> ( n, dim)
			{ };

			//! 1. und einizger Intergrationsschritt:
			virtual void evolve(double timeTilEvent);

			virtual ~gslOdeNode()
			{
				if (stepType != NULL)
				{
					// gsl aufräumen:
					gslode(evolve_free) (gslEvolve);
					gslode(control_free) (gslControl);
					gslode(step_free) (gslStep);
					stepType = NULL;
					alreadyInitialized = false;
				}
			}

			//! clean: wird vor der Integration aufgerufen und initialisiert diverse GSL-Parameter (Art der Stufenfunktion, Schrittweite usw.)
			virtual void clean ()
			{
				if ( (* containerNode<baseType,3>::nodeList.begin()) == this)  // only clean for the masternode ;-), which is the first one.
				{
					if (alreadyInitialized) // free gsl-objects
					{
						gslode(step_free) (gslStep);
 						gslode(evolve_free) (gslEvolve);
						gslode(control_free) (gslControl);
					}

					alreadyInitialized = true;

					string theStepType = getGlobal<string>("odeStepType");
					if (theStepType == "gsl_rk2")
						stepType = gslode(step_rk2) ;
					else if (theStepType == "gsl_rk4")
						stepType = gslode(step_rk4) ;
					else if (theStepType == "gsl_rkf45")
						stepType = gslode(step_rkf45) ;
					else if (theStepType == "gsl_rkck")
						stepType = gslode(step_rkck) ;
					else if (theStepType == "gsl_rk8pd")
						stepType = gslode(step_rk8pd) ;
					else if (theStepType == "gsl_rk2imp")
						stepType = gslode(step_rk2imp) ;
					else if (theStepType == "gsl_rk4imp")
						stepType = gslode(step_rk4imp) ;
					else
					{
						stringstream fehler;
						fehler << "unknown steptype for gslOdeNode: " << theStepType << endl;
						throw fehler.str().c_str();
					}

					unsigned int odeDimension = containerNode <baseType, 3> :: usedIndices ;

					gslStep = gslode(step_alloc) ( stepType, odeDimension);

					gslControl = gslode(control_y_new) (
							getGlobal<double>("odeAbsError"),
							getGlobal<double>("odeRelError")
						);

					gslEvolve = gslode(evolve_alloc) (odeDimension);
					gslode(system) sys = {&gslOdeNode::dgl, NULL, odeDimension, NULL};
					gslOdeSys = sys; //{NULL,NULL,usedIndices, NULL};
				}
			}

			virtual void operator() ( const baseType x[], baseType dydx[] ) = 0;

			//! Print the derivative of the node's state
			virtual void dynamics()
			{
				cout << this->dimension() << endl;

				double  * dxdt = (double*) calloc (this->dimension(), sizeof(double));
				(*(this))(x, dxdt);
				for (unsigned int i = 0; i < this->dimension(); i++)
					cout << i <<   setprecision (15) << " " << dxdt[i] << endl;

			}

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

			virtual node *construct() { return new node ( *this ); };

	};

}

#endif

#endif
