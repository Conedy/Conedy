

#ifndef stdToyModels_h
#define stdToyModels_h stdToyModels_h

#include <math.h>




//#include "gslOdeNode.h"
#include "stdOdeIntegrator.h"


namespace conedy
{

//! Der Standard-Roessler-Oscillator. Den kennt ja nu jeder.
class stdRoessler : public stdOdeIntegrator
//class stdRoessler : public odeNode<baseType>
{
	private:
        // Std.Parameter für den Oszi
		inline baseType omega() {return params<baseType>::getParams(0);}
		inline baseType a() {return params<baseType>::getParams(1);}
		inline baseType b() {return params<baseType>::getParams(2);}
		inline baseType c() {return params<baseType>::getParams(3);}
		
		
	public:
        // Konstruktor ohne Parameter:
		virtual const unsigned int dimension() const { return 3;}

		stdRoessler() : stdOdeIntegrator(_stdRoessler_) {};
		//stdRoessler() : odeNode<baseType>(3,_stdRoessler_) {};
		virtual void operator() (const baseType  x[], baseType  dydx[]);
		virtual ~stdRoessler() { }


        virtual const nodeInfo getNodeInfo() { nodeInfo n = {_stdRoessler_,_dynNode_};     return n; };

		static void registerStandardValues() 
		{ 
			params<baseType>::registerStandard(_stdRoessler_,"stdRoessler_omega",0,0.89);
			params<baseType>::registerStandard(_stdRoessler_,"stdRoessler_a",1,0.165);
			params<baseType>::registerStandard(_stdRoessler_,"stdRoessler_b",2,0.2);
			params<baseType>::registerStandard(_stdRoessler_,"stdRoessler_c",3,10.0);
	
		}	

};


// n.addNode<stdRoessler(0.09,0.17,0.2,10)>();

//! Standard-Lorenz-Oscillator
class stdLorenz : public stdOdeIntegrator 
{
	private:
        // Std.Parameter für den Oszi
		inline baseType s() {return params<baseType>::getParams(0);}
		inline baseType r() {return params<baseType>::getParams(1);}
		inline baseType b() {return params<baseType>::getParams(2);}
		
		
	public:
        // Konstruktor ohne Parameter:
		virtual const unsigned int dimension() const { return 3;}

		stdLorenz() : stdOdeIntegrator(_stdLorenz_) {};
		virtual void operator() (const baseType  x[], baseType  dydx[]);
		virtual ~stdLorenz() { }


        virtual const nodeInfo getNodeInfo() { nodeInfo n = {_stdLorenz_,_dynNode_};     return n; };

		static void registerStandardValues() 
		{ 
			params<baseType>::registerStandard(_stdLorenz_,"stdLorenz_s",0,10.0);
			params<baseType>::registerStandard(_stdLorenz_,"stdLorenz_r",1,28.0);
			params<baseType>::registerStandard(_stdLorenz_,"stdLorenz_b",2,8/3);
	
		}	

};



//! Standard-Kuramoto-Oscillator mit sinus-Kopplung
class stdKuramoto : public stdOdeIntegrator
{
	private:

		inline baseType omega() {return params<baseType>::getParams(0);}
		
	public:
		virtual const unsigned int dimension() const { return 1;}

		stdKuramoto() : stdOdeIntegrator(_stdKuramoto_) {};
		virtual void operator() (const baseType  x[], baseType  dydx[]);


		virtual ~stdKuramoto() { }
//		virtual void swap();
		virtual const nodeInfo getNodeInfo() { nodeInfo n = {_stdKuramoto_,_dynNode_};     return n; };

		static void registerStandardValues() 
		{ 
			params<baseType>::registerStandard(_stdKuramoto_,"stdKuramoto_omega",0,1.0);

		}
		

		virtual baseType getState()
		{
			return fmod (this->x[0], 1);
		};



	
};



//! Van-der-Pol-Oscillator
class stdVanDerPol : public stdOdeIntegrator
{
	private:

		inline baseType mu() {return params<baseType>::getParams(0);}

		
		
	public:
		virtual const unsigned int dimension() const { return 2;}
		stdVanDerPol() : stdOdeIntegrator(_stdVanDerPol_) {};
		virtual void operator() (const baseType  x[], baseType  dydx[]);
		virtual ~stdVanDerPol() { }
//		virtual void swap();
		virtual const nodeInfo getNodeInfo() { nodeInfo n = {_stdVanDerPol_,_dynNode_};     return n; };

		static void registerStandardValues() 
		{ 
			params<baseType>::registerStandard(_stdVanDerPol_,"stdVanDerPol_mu",0,10.0);
	
	
		}	
};






}



#endif
