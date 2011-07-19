

/* last modifier: js */

#ifndef odeNode_h
#define odeNode_h odeNode_h

#include "node.h"
#include "gslNoise.h"
#include <valarray>
#include <map>


#include "containerNode.h"

#include "params.h"
#include "baseType.h"

using namespace std;

// //typedef valarray<double>params;



namespace conedy {


//! Basis-Klasse, die Runge-Kutter 4. Ordnung implementiert.
class odeNode : public containerNode<baseType,1> {
	private:
		
	protected:
		valarray <baseType> tmp2, dydt, dyt, dym;
		
		//! Zwischenspeicher, der in der swap-Funktion nach dynNode::tmp geschrieben wird.
		baseType *odeNodeTmp;
		

	public:
//		odeNode()  {};

		odeNode ( const odeNode &b ) : containerNode<baseType,1>(b)
		{
			tmp2.resize((&b)->dimension());
			dydt.resize((&b)->dimension());
			dyt.resize((&b)->dimension());
			dym.resize((&b)->dimension());


			odeNodeTmp = ( baseType* ) calloc ( ( &b )->dimension(),sizeof ( baseType ) );

		}

	   	odeNode(networkElementType n) : // ngls: Anzahl der Gleichungen, NodeNumber,  h Schrittweite
						containerNode<baseType,1>(n) {}

		virtual ~odeNode() {}

		virtual void operator()(const baseType x [], baseType dydx [])  = 0;
		virtual int requiredTimeSteps() { return 4; }



			virtual void swap()
			{
				for ( unsigned int i = 0; i < this->dimension(); i++ )
					this->tmp[i] = odeNodeTmp [i];
			}


//		virtual void swap(short i) { state=tmp[i]; }
		virtual void clean(unsigned int timeSteps) {  };


// RUNGE KUTTA No. 4
		virtual void evolve(double time)
		{
			list<containerNode<baseType,1>*>::iterator it;

			for (it = containerNode<baseType,1>::nodeList.begin(); it != containerNode<baseType,1>::nodeList.end(); it++)
			{
				((odeNode *)(*it))->action1(time);
			}
			for (it = containerNode<baseType,1>::nodeList.begin(); it != containerNode<baseType,1>::nodeList.end(); it++)
			{
				((odeNode *)(*it))->swap();
			}

			for (it = containerNode<baseType,1>::nodeList.begin(); it != containerNode<baseType,1>::nodeList.end(); it++)
			{
				((odeNode *)(*it))->action2(time);
			}
			for (it = containerNode<baseType,1>::nodeList.begin(); it != containerNode<baseType,1>::nodeList.end(); it++)
			{
				((odeNode *)(*it))->swap();
			}

			for (it = containerNode<baseType,1>::nodeList.begin(); it != containerNode<baseType,1>::nodeList.end(); it++)
			{
				((odeNode *)(*it))->action3(time);
			}
			for (it = containerNode<baseType,1>::nodeList.begin(); it != containerNode<baseType,1>::nodeList.end(); it++)
			{
				((odeNode *)(*it))->swap();
			}

			for (it = containerNode<baseType,1>::nodeList.begin(); it != containerNode<baseType,1>::nodeList.end(); it++)
			{
				((odeNode *)(*it))->action4(time);
			}
			for (it = containerNode<baseType,1>::nodeList.begin(); it != containerNode<baseType,1>::nodeList.end(); it++)
			{
				((odeNode *)(*it))->swap();
			}

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




}


#endif
