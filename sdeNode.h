

#ifndef sdeNode_h
#define sdeNode_h sdeNode_h

#include <cmath>
#include "node.h"
#include "gslNoise.h"
#include <valarray>

#include "params.h"

#include "containerNode.h"



#ifndef M_PI
#define M_PI    3.14159265358979323846f
#endif

using namespace std;

#include "dynNode.h"
namespace conedy
{

//! --------------------------Node for Stochastic Differential Equations------------------------ //
class sdeNode : public containerNode<baseType, 4> {
	private:
		gslNoise noise;


//		static params <double> p(_sdeNode_);
	protected:
	public:

//   		 virtual bool timeEvolution () {return 1;}
  	
	//	sdeNode() {};




			sdeNode ( networkElementType n) : containerNode<baseType, 4> ( n )
			{
				/*		if (nDgls >0)
				n			x = (baseType*)calloc(nDgls,sizeof(baseType));
						else
							x = NULL;*/
			}

		sdeNode ( const sdeNode &b ) : containerNode<baseType, 4>(b)
		{
		}


//		sdeNode (networkElementType n, unsigned short strat = 20) : dynNode(n)
//			{ 
//aa				setSeed(in);
	//			for (unsigned int i = 0; i < Ngls; i++) this->x[i]=noise.getGaussian(); 
	//			getRho();
	//		}

		virtual ~sdeNode() {};

		virtual void operator()(baseType x[], baseType  dxdt[], baseType dxdW[]) {throw "differential equation not defined for";};

			static void dgl (baseType *x, baseType* dxdt, baseType *dxdW)
			{
				list<containerNode<baseType,4>*>::iterator it;
				for ( it = nodeList.begin(); it != nodeList.end();it++ )
					( * ( (sdeNode *)*it )) ( &x[ ( *it )->startPosGslOdeNodeArray], &dxdt[ ( *it )->startPosGslOdeNodeArray] , &dxdW[ (*it)->startPosGslOdeNodeArray]) ;
			}





//		virtual void swap() {};



// ->DIRTY<- Explicit Strong Scheme O(dt^1.5)             ___ auskommentiert: der Algorithmus mit dem Wendling arbeitet!!!
///	void action1() {
///		double phi = noise.getGaussian();
///		dW = sqdt*zeta;
///		(*this)(x, dydt, dydW);																				                                    
///		x = x + dydt*dt + dydW*sqdt*(phi - zeta);																                        
///		zeta = phi;
///	};
//
//
//
//
//
//


};

//! Ornstein Uhlenberg
//class ornUhl : public sdeNode {
//	public:
//		virtual const unsigned int dimension() const { return 1;}
//
//		ornUhl() : sdeNode(_ornUhl_) {};
//	//	ornUhl(double h) : sdeNode(1 ), params<double>(_ornUhl_) { }
////		ornUhl(inStream &in) :sdeNode(1), params
//		virtual void operator()(baseType x[], baseType  dxdt[], baseType dxdW[]);
//		virtual ~ornUhl() { }
//
//
//		static void registerStandardValues() 
//		{ 
//			params<baseType>::registerStandard(_ornUhl_,"ornUhl_0",0,0.2); 
//			params<baseType>::registerStandard(_ornUhl_,"ornUhl_1",1,0.1); 
//		}
//		virtual const nodeInfo getNodeInfo() { nodeInfo n = {_ornUhl_,_dynNode_,"ornUhl"};     return n; };
//
//
//};
/*
class wendling : public sdeNode {
	private: 
		
 sigmoid (double signal) { return 2.0*getParams(3)/(1.0 + exp(getParams(5)*(getParams(4) - signal) ) ); }

	protected:
		valarray<double> state;

	public:
		wendling(double h, int n, inStream& in) : sdeNode(8, 14, n, h, in), state(8) { };
		virtual void operator()(valarray<double>& x, valarray<double>& dxdt, valarray<double>& dxdW);
		virtual ~wendling() { }
		virtual node<double> *construct() { return new wendling(*this); };
//		virtual void printStatistics()   { cout << "wendling" << endl; node<double>::printStatistics();}
		virtual void swap() { state=x; node<double>::state=state[0]; };


		virtual double& getState(const unsigned short which) { return state[which]; };
		double couplingSum() {
			double re;	
			edgeIterator i;
			for (i = outEdges.begin(); i != outEdges.end(); i++) 
				re += (*i).getTargetState(6);
			return re;
		};

		virtual void registerStandardValues() 
		{ 
			registerStandard(_ornUhl_,"ornUhl.0",0,0.2); 
			registerStandard(_ornUhl_,"ornUhl.1",1,0.1); 
		}


};*/
/*
class coloredWendling : public sdeNode, public params {
	private: 
		double sigmoid (double signal) { return 2.0*getParams(3)/(1.0 + exp(getParams(5)*(getParams(4) - signal) ) ); }

	protected:
		valarray<double> state;

	public:
//		coloredWendling(inStream& in) : sdeNode(9, 15, n, h, in), state(9) { };
		coloredWendling() : sdeNode(9), params(_coloredWendling_), state(9) {};

		virtual void operator()(valarray<double>& x, valarray<double>& dxdt, valarray<double>& dxdW);
		virtual ~coloredWendling() { }
		virtual node<double> *construct() { return new coloredWendling(*this); };
		virtual void printStatistics()   { cout << "coloredWendling" << endl; cout << getParams(0) << " " << getParams(1) << " " <<getParams(2) << " " <<getParams(3) << " " <<getParams(4) << " " <<getParams(5) << " " <<getParams(6) << " " <<getParams(7) << " " <<getParams(8) << " " <<getParams(9) << " " <<getParams(10) << " " <<getParams(11) << " " <<getParams(12) << " " <<getParams(13) << " " <<getParams(14) << " " <<getParams(15) << endl; sdeNode::printStatistics();node<double>::printStatistics();}
		virtual void swap() { state[0]=x[0]; state[6] = x[6]; node<double>::state=state[0]; };
		virtual void registerStandardValues() 
		{ 
			registerStandard(_coloredWendling_,"coloredWendling.0",0,30); 
			registerStandard(_coloredWendling_,"coloredWendling.1",1,90); 
			registerStandard(_coloredWendling_,"coloredWendling.2",2,33); 
			registerStandard(_coloredWendling_,"coloredWendling.3",3,2.5); 
			registerStandard(_coloredWendling_,"coloredWendling.4",4,6); 
			registerStandard(_coloredWendling_,"coloredWendling.5",5,0.56); 
			registerStandard(_coloredWendling_,"coloredWendling.6",6,135); 
			registerStandard(_coloredWendling_,"coloredWendling.7",7,108); 
			registerStandard(_coloredWendling_,"coloredWendling.8",8,33.75); 
			registerStandard(_coloredWendling_,"coloredWendling.9",9,33.75); 
			registerStandard(_coloredWendling_,"coloredWendling.10",10,3.25); 
			registerStandard(_coloredWendling_,"coloredWendling.11",11,100); 
			registerStandard(_coloredWendling_,"coloredWendling.12",12,22); 
			registerStandard(_coloredWendling_,"coloredWendling.13",13,50); 
			registerStandard(_coloredWendling_,"coloredWendling.14",14,0.001); 
			registerStandard(_coloredWendling_,"coloredWendling.15",15,0); 
		}
		double getState(const unsigned short which) { return state[which]; };
		double couplingSum() {
			double re;	
			edgeIterator i;
			for (i = outEdges.begin(); i != outEdges.end(); i++) 
				re += ((coloredWendling*)((**i).target))->getState(6) * (*i)->weight;
			return re;
		};
		virtual const nodeInfo getNodeInfo() { nodeInfo n = {_coloredWendling_,_dynNode_};     return n; };

};

class breakspear : public sdeNode {
	private: 
		double S (double& signal, double& V0, double& sigma) { return 1.0/(1 + exp(2.0*(V0 - signal)/sigma)); };
		double Qtmp, Qstate;

	public:
		breakspear(double h, int n, inStream& in) : sdeNode(3, 30, n, h, in) { };
		virtual void operator()(valarray<double>& x, valarray<double>& dxdt, valarray<double>& dxdW);
		virtual ~breakspear() { }
		virtual node<double> *construct() { return new breakspear(*this); };
		virtual void printStatistics()   { cout << "breakspear" << endl; node<double>::printStatistics();}

		virtual void swap() { Qstate=Qtmp; state=x[0]; };
		virtual double& getState(const unsigned short which) { return Qstate; };
		double couplingSum() {
			double re;	
			edgeIterator i;
			for (i = outEdges.begin(); i != outEdges.end(); i++) 
				re += (*i).getTargetState(0);
			return re;
		};
};

class coloredBreakspear : public sdeNode {
	private: 
		double S (double& signal, double& V0, double& sigma) { return 1.0/(1 + exp(2.0*(V0 - signal)/sigma)); };
		double Qtmp, Qstate;

	public:
		coloredBreakspear(double h, int n, inStream& in) : sdeNode(4, 31, n, h, in) { };
		virtual void operator()(valarray<double>& x, valarray<double>& dxdt, valarray<double>& dxdW);
		virtual ~coloredBreakspear() { }
		virtual node<double> *construct() { return new coloredBreakspear(*this); };
		virtual void printStatistics()   { cout << "coloredBreakspear" << endl; node<double>::printStatistics();}

		virtual void swap() { Qstate=Qtmp; state=x[0]; };
		virtual double& getState(const unsigned short which) { return Qstate; };
		double couplingSum() {
			double re;	
			edgeIterator i;
			for (i = outEdges.begin(); i != outEdges.end(); i++) 
				re += (*i).getTargetState(0);
			return re;
		};
};
// Node for Stochastic Differential Equations //

*/
}
#endif
