

#ifndef stdOdeIntegrator_h
#define stdOdeIntegrator_h stdOdeIntegrator_h


#include "integrator.h"
#include "odeNode.h"

#include "networkConstants.h"

namespace conedy {


	class stdOdeIntegrator : public odeNode 
	{
		public:
				valarray <baseType> tmp2, dydt, dyt, dym;
				odeIntegrator *integ;

		stdOdeIntegrator (networkElementType n) : odeNode (n)    {}

		stdOdeIntegrator ( const stdOdeIntegrator &b ): odeNode (b)
		{
			tmp2.resize((&b)->dimension());
			dydt.resize((&b)->dimension());
			dyt.resize((&b)->dimension());
			dym.resize((&b)->dimension());

			odeNodeTmp = ( baseType* ) calloc ( ( &b )->dimension(),sizeof ( baseType ) );

		}

			static unsigned int stepType_int;
			static params<string> *stepType;

			static void registerStandardValues()
			{
				params<string>::registerStandard(_stdOdeIntegrator_, "stdOdeIntegrator_stepType",0,"euler");
				stepType = new params<string> (_stdOdeIntegrator_);
			}
			virtual void swap()
			{
				for ( unsigned int i = 0; i < this->dimension(); i++ )
					this->x[i] = odeNodeTmp [i];
			}


//		virtual void swap(short i) { state=x[i]; }
		virtual void clean() {

	if (amIFirst())	
	{
			if (stepType->getParams(0)  == "euler")
			{
				stepType_int = 0;
				integ = new euler (containerDimension() );
			}	
			else if (stepType->getParams(0)  == "rk4")
				stepType_int = 1;
			else
				throw "unknown steptype for stdOdeIntegrator!";
	}

		};


// RUNGE KUTTA No. 4
		virtual void evolve(double time)
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

		void rungeKutta4Step (double time)
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


		void eulerStep (double dt)
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
		virtual void action1(double dt) { 
			(*this)(this->x, &dydt[0]);

			for (unsigned int i = 0;i < this->dimension(); i++)
				tmp2[i] = this->x[i];
//								tmp2 = this->x);
			for (unsigned int i = 0; i < this->dimension(); i++)
				this->odeNodeTmp[i] = this->x[i] +  dt/2.0 * dydt[i];

		}
		//! zweiter schritt
		virtual void action2(double dt) {
			(*this)(this->x, &dyt[0]);
			for (unsigned int i = 0; i < this->dimension(); i++)
				this->odeNodeTmp[i] = tmp2[i] + dt/2.0*dyt[i];

		}
		//! dritter Schritt
		virtual void action3(double dt) {
			(*this)(this->x, &dym[0]);
			for (unsigned int i = 0; i < this->dimension(); i++)
				this->odeNodeTmp[i] = tmp2[i] + dt*dym[i];
			dym += dyt;
		}
		//! vierter Schritt
		virtual void action4(double dt) {
			(*this)(this->x, &dyt[0]);
			for (unsigned int i = 0; i <this->dimension(); i++)
				this->odeNodeTmp[i] = tmp2[i] + dt/6.0*(dydt[i] + dyt[i] + ((baseType)2.0)*dym)[i];
		}




	};





//	typedef odeNode stdOdeIntegrator;   // Runge-Kutta Ord4

}

#endif
