#ifndef stdOdeIntegrator_h
#define stdOdeIntegrator_h stdOdeIntegrator_h

#include "integrator.h"
#include "odeNode.h"
#include "networkConstants.h"
#include "globals.h"
#include <valarray>

namespace conedy {

	//! implements two simple ode solver  (euler and runge-kutta 4th order) mainly for test purposes.
	class stdOdeIntegrator : public odeNode, private globals
	{
		public:

		valarray <baseType> tmp2, dydt, dyt, dym;
		odeIntegrator *integ;

		stdOdeIntegrator (networkElementType n, unsigned int dim) : odeNode (n, dim)    {}

		stdOdeIntegrator ( const stdOdeIntegrator &b ): odeNode (b)
		{
			tmp2.resize((&b)->dimension());
			dydt.resize((&b)->dimension());
			dyt.resize((&b)->dimension());
			dym.resize((&b)->dimension());

			odeNodeTmp = ( baseType* ) calloc ( ( &b )->dimension(),sizeof ( baseType ) );

		}

		static unsigned int stepType_int;

		static void registerStandardValues()
		{
			registerGlobal<string>("odeStepType","euler");
		}

		virtual void swap()
		{
			for ( unsigned int i = 0; i < this->dimension(); i++ )
				this->x[i] = odeNodeTmp [i];
		}


//		virtual void swap(short i) { state=x[i]; }
		virtual void clean()
		{
			if (amIFirst())
			{
				string stepType = getGlobal<string>("odeStepType");
				if (stepType == "euler")
				{
					stepType_int = 0;
					integ = new euler (containerDimension() );
				}
				else if (stepType == "rk4")
					stepType_int = 1;
				else
				throw "unknown steptype for odeStepType!";
			}
	}

		};


// RUNGE KUTTA No. 4
		virtual void evolve(baseType time)
		{
			switch (stepType_int)
			{
				case 0:
					((euler *) integ)->step (time, dynamicVariablesOfAllDynNodes, *this, containerDimension());
					break;
				case 1:
					rungeKutta4Step(time);
					break;

			}

		}

		void rungeKutta4Step (baseType time)
		{


			list<containerNode<baseType,1>*>::iterator it;

			for (it = containerNode<baseType,1>::nodeList.begin(); it != containerNode<baseType,1>::nodeList.end(); it++)
				((stdOdeIntegrator *)(*it))->action1(time);
			for (it = containerNode<baseType,1>::nodeList.begin(); it != containerNode<baseType,1>::nodeList.end(); it++)
				((stdOdeIntegrator *)(*it))->swap();

			for (it = containerNode<baseType,1>::nodeList.begin(); it != containerNode<baseType,1>::nodeList.end(); it++)
				((stdOdeIntegrator *)(*it))->action2(time);
			for (it = containerNode<baseType,1>::nodeList.begin(); it != containerNode<baseType,1>::nodeList.end(); it++)
				((stdOdeIntegrator *)(*it))->swap();

			for (it = containerNode<baseType,1>::nodeList.begin(); it != containerNode<baseType,1>::nodeList.end(); it++)
				((stdOdeIntegrator *)(*it))->action3(time);
			for (it = containerNode<baseType,1>::nodeList.begin(); it != containerNode<baseType,1>::nodeList.end(); it++)
				((stdOdeIntegrator *)(*it))->swap();

			for (it = containerNode<baseType,1>::nodeList.begin(); it != containerNode<baseType,1>::nodeList.end(); it++)
				((stdOdeIntegrator *)(*it))->action4(time);
			for (it = containerNode<baseType,1>::nodeList.begin(); it != containerNode<baseType,1>::nodeList.end(); it++)
				((stdOdeIntegrator *)(*it))->swap();

		}


		void eulerStep (baseType dt)
		{
			list<containerNode<baseType,1>*>::iterator it;
			for (it = containerNode<baseType,1>::nodeList.begin(); it != containerNode<baseType,1>::nodeList.end(); it++)
			{
				odeNode * n = (odeNode*) *it;
				(*n)(n->x, &dydt[0]);
				for (unsigned int i = 0;i < n->dimension(); i++)
				 n->odeNodeTmp[i] = n->x[i]  + dydt[i] * dt ;
			}
			for (it = containerNode<baseType,1>::nodeList.begin(); it != containerNode<baseType,1>::nodeList.end(); it++)
				((stdOdeIntegrator *)(*it))->swap();

		}


		//! erster schritt im Runge-Kutter 4.Ordnung
		virtual void action1(baseType dt) {
			(*this)(this->x, &dydt[0]);

			for (unsigned int i = 0;i < this->dimension(); i++)
				tmp2[i] = this->x[i];
//								tmp2 = this->x);
			for (unsigned int i = 0; i < this->dimension(); i++)
				this->odeNodeTmp[i] = this->x[i] +  dt/2.0 * dydt[i];

		}
		//! zweiter schritt
		virtual void action2(baseType dt) {
			(*this)(this->x, &dyt[0]);
			for (unsigned int i = 0; i < this->dimension(); i++)
				this->odeNodeTmp[i] = tmp2[i] + dt/2.0*dyt[i];

		}
		//! dritter Schritt
		virtual void action3(baseType dt) {
			(*this)(this->x, &dym[0]);
			for (unsigned int i = 0; i < this->dimension(); i++)
				this->odeNodeTmp[i] = tmp2[i] + dt*dym[i];
			dym += dyt;
		}
		//! vierter Schritt
		virtual void action4(baseType dt) {
			(*this)(this->x, &dyt[0]);
			for (unsigned int i = 0; i <this->dimension(); i++)
				this->odeNodeTmp[i] = tmp2[i] + dt/6.0*(dydt[i] + dyt[i] + ((baseType)2.0)*dym)[i];
		}

	};

//	typedef odeNode stdOdeIntegrator;   // Runge-Kutta Ord4

}

#endif
