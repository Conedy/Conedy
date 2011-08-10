

#ifndef stdOdeIntegrator_h
#define stdOdeIntegrator_h stdOdeIntegrator_h


#include "odeNode.h"

#include "networkConstants.h"

namespace conedy {


	class stdOdeIntegrator : public odeNode 
	{
		public:
				valarray <baseType> tmp2, dydt, dyt, dym;

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
					this->tmp[i] = odeNodeTmp [i];
			}


//		virtual void swap(short i) { state=tmp[i]; }
		virtual void clean() {
			if (stepType->getParams(0)  == "euler")
				stepType_int = 0;
			else if (stepType->getParams(0)  == "rk4")
				stepType_int = 1;
		};


// RUNGE KUTTA No. 4
		virtual void evolve(double time)
		{
			switch (stepType_int)
			{
				case 0:
					eulerStep(time);
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
				(*n)(n->tmp, &dydt[0]); 
				for (unsigned int i = 0;i < n->dimension(); i++)
				 n->odeNodeTmp[i] = n->tmp[i]  + dydt[i] * dt ;
			}
			for (it = containerNode<baseType,1>::nodeList.begin(); it != containerNode<baseType,1>::nodeList.end(); it++)	
				((stdOdeIntegrator *)(*it))->swap();

		}	



		//! erster schritt im Runge-Kutter 4.Ordnung
		virtual void action1(double dt) { 
			(*this)(this->tmp, &dydt[0]);

			for (unsigned int i = 0;i < this->dimension(); i++)
				tmp2[i] = this->tmp[i];
//								tmp2 = this->tmp);
			for (unsigned int i = 0; i < this->dimension(); i++)
				this->odeNodeTmp[i] = this->tmp[i] +  dt/2.0 * dydt[i];

		}
		//! zweiter schritt
		virtual void action2(double dt) {
			(*this)(this->tmp, &dyt[0]);
			for (unsigned int i = 0; i < this->dimension(); i++)
				this->odeNodeTmp[i] = tmp2[i] + dt/2.0*dyt[i];

		}
		//! dritter Schritt
		virtual void action3(double dt) {
			(*this)(this->tmp, &dym[0]);
			for (unsigned int i = 0; i < this->dimension(); i++)
				this->odeNodeTmp[i] = tmp2[i] + dt*dym[i];
			dym += dyt;
		}
		//! vierter Schritt
		virtual void action4(double dt) {
			(*this)(this->tmp, &dyt[0]);
			for (unsigned int i = 0; i <this->dimension(); i++)
				this->odeNodeTmp[i] = tmp2[i] + dt/6.0*(dydt[i] + dyt[i] + ((baseType)2.0)*dym)[i];
		}




	};





//	typedef odeNode stdOdeIntegrator;   // Runge-Kutta Ord4

}

#endif
