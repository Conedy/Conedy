

#ifndef neuronModels_h
#define neuronModels_h neuronModels_h


#include "odeNode.h"
#include "sdeNode.h"
#include <boost/function.hpp>


#include <complex>
#include <stdio.h>
#include <cmath>


namespace conedy
{

//! integrate-and-fire-neuronen numerisch integriert. Braucht man eigentlich nicht, weil pcos viel schlauer sind.
class integrateAndFire : public odeNode
{
	private:

		baseType lastFiring;
		gslNoise noise;

	public:
		virtual const unsigned int dimension() const { return 1;}

		integrateAndFire() : odeNode (_integrateAndFire_ ) {};
		virtual void operator() ( const baseType x[], baseType dydx[] );
		virtual ~integrateAndFire() { }
		virtual const nodeInfo getNodeInfo() { nodeInfo n = {_integrateAndFire_,_dynNode_,"integrateAndFire"};     return n; };

		inline bool t_ref () { return getParams(3); }
		inline bool threshold () { return getParams(3); }


		static void registerStandardValues()
		{
			params<baseType>::registerStandard ( _integrateAndFire_,"integrateAndFire_I",0,0.25 );
			params<baseType>::registerStandard ( _integrateAndFire_,"integrateAndFire_gamma",1,0.5 );
			params<baseType>::registerStandard ( _integrateAndFire_,"integrateAndFire_threshold",2,1.85 );
			params<baseType>::registerStandard ( _integrateAndFire_,"integrateAndFire_t_ref",3,0.25 );
			params<baseType>::registerStandard ( _integrateAndFire_,"integrateAndFire_p_endo",4,0.000 );
		}
};

//		virtual void printStatistics() { cout << getParams(0) << "," << getParams(1) << ","<< getParams(2) << ","<< getParams(3) << ","<< getParams(4) << "," << endl;

//cout << "row ist:"; test();
//}


class gaussianFHN	: public sdeNode
{
	private: /*aus Izhikevich S. 106, jetzt mit Rauschen*/
		inline baseType a() {return -1*params<baseType>::getParams ( 0 );} //Achtung a ist immer negativ!
		inline baseType b() {return params<baseType>::getParams ( 1 );}
		inline baseType c() {return params<baseType>::getParams ( 2 );}
		inline baseType I() {return params<baseType>::getParams ( 3 );}
		inline baseType sigmaNoise() {return params<baseType>::getParams ( 4 );}
	public:
		virtual const unsigned int dimension() const { return 2;}

		gaussianFHN() : sdeNode (_gaussianFHN_ ) { }
//		hodgkinHuxley(inStream& in) : odeNode(4), params(_hodgkinHuxley_) { setParams(in);}
		virtual void operator() ( valarray<baseType>& y, valarray<baseType>& dxdt, valarray<baseType>& dxdW );
		virtual ~gaussianFHN() { }
		virtual const nodeInfo getNodeInfo() { nodeInfo n = {_gaussianFHN_,_dynNode_,"gaussianFHN"};     return n; };
		static void registerStandardValues()
		{
			params<baseType>::registerStandard ( _gaussianFHN_,"gaussianFHN_a",0,0.1 );
			params<baseType>::registerStandard ( _gaussianFHN_,"gaussianFHN_b",1,0.01 );
			params<baseType>::registerStandard ( _gaussianFHN_,"gaussianFHN_c",2,0.02 );
			params<baseType>::registerStandard ( _gaussianFHN_,"gaussianFHN_I",3,0.0 );
			params<baseType>::registerStandard ( _gaussianFHN_,"gaussianFHN_sigmaNoise",4,0.0 );

		}

		virtual void clean ( unsigned int timeSteps ) {sdeNode::clean ( timeSteps ); this->tmp[0]=0; this->tmp[1]=0;};

};

//! Hindmarsh Rose Neuron
/*class hindmarshRose	: public odeNode
{
	private: aus Innocenti et al Chaos 2007
		inline baseType r() {return params<baseType>::getParams ( 0 );}
		inline baseType I() {return params<baseType>::getParams ( 1 );}
	public:

		virtual const unsigned int dimension() const { return 3;}

		hindmarshRose() : odeNode (_hindmarshRose_ ) { }
//		hodgkinHuxley(inStream& in) : odeNode(4), params(_hodgkinHuxley_) { setParams(in);}
		virtual void operator() ( const baseType x[], baseType dydx[] );
		virtual ~hindmarshRose() { }
		virtual const nodeInfo getNodeInfo() { nodeInfo n = {_hindmarshRose_,_dynNode_,"hindmarshRose"};     return n; };
		static void registerStandardValues()
		{
			params<baseType>::registerStandard ( _hindmarshRose_,"hindmarshRose_r",0,0.001 );
			params<baseType>::registerStandard ( _hindmarshRose_,"hindmarshRose_I",1,0.0 );
		}

		virtual void clean ( unsigned int timeSteps ) {odeNode::clean ( timeSteps ); this->tmp[0]=0; this->tmp[1]=0; this->tmp[2]=0;};


};
//! Hindemark-Rose-Neuron mit Gaussschem Rauschen als Input
class gaussianHR	: public sdeNode
{
	private: aus Innocenti et al Chaos 2007
		inline baseType r() {return params<baseType>::getParams ( 0 );}
		inline baseType I() {return params<baseType>::getParams ( 1 );}
		inline baseType sigmaNoise() {return params<baseType>::getParams ( 2 );}
	public:
		virtual const unsigned int dimension() const { return 3;}

		gaussianHR() : sdeNode (_gaussianHR_ ) { }
//		hodgkinHuxley(inStream& in) : odeNode(4), params(_hodgkinHuxley_) { setParams(in);}
		virtual void operator() ( valarray<baseType>& x, valarray<baseType>& dxdt, valarray<baseType>& dxdW );
		virtual ~gaussianHR() { }
		virtual const nodeInfo getNodeInfo() { nodeInfo n = {_gaussianHR_,_dynNode_,"gaussienHR"};     return n; };
		static void registerStandardValues()
		{
			params<baseType>::registerStandard ( _gaussianHR_,"gaussianHR_r",0,0.001 );
			params<baseType>::registerStandard ( _gaussianHR_,"gaussianHR_I",1,0.0 );
			params<baseType>::registerStandard ( _gaussianHR_, "gaussianHR_sigmaNoise",2, 0.0 );
		}

		virtual void clean ( unsigned int timeSteps ) {sdeNode::clean ( timeSteps ); this->tmp[0]=0; this->tmp[1]=0; this->tmp[2]=0;};


};*/
		/*! Aus Izhikevich S. 89, äquivalent zu Morris-Lecar*/
class napK		: public odeNode
{
	private:
		inline baseType gl() {return params<baseType>::getParams ( 0 );}
		inline baseType el() {return params<baseType>::getParams ( 1 );}
		inline baseType gna() {return params<baseType>::getParams ( 2 );}
		inline baseType ena() {return params<baseType>::getParams ( 3 );}
		inline baseType gk() {return params<baseType>::getParams ( 4 );}
		inline baseType ek() {return params<baseType>::getParams ( 5 );}
		inline baseType c() {return params<baseType>::getParams ( 6 );}
		inline baseType km() {return params<baseType>::getParams ( 7 );}
		inline baseType vhm() {return params<baseType>::getParams ( 8 );}
		inline baseType kn() {return params<baseType>::getParams ( 9 );}
		inline baseType vhn() {return params<baseType>::getParams ( 10 );}
		inline baseType I() {return params<baseType>::getParams ( 11 );}
		inline baseType tau ( baseType v ) {return 1;}
		//diese Parameter auch noch frei waehlbar machen???
		inline baseType minf ( baseType v ) {return ( 1.0/ ( 1+exp ( ( vhm()-v ) /km() ) ) );}
		inline baseType ninf ( baseType v ) {return ( 1.0/ ( 1+exp ( vhn()-v ) /kn() ) );}
	public:
		virtual const unsigned int dimension() const { return 2;}

		napK() : odeNode (_napK_ ) { }
//		hodgkinHuxley(inStream& in) : odeNode(4), params(_hodgkinHuxley_) { setParams(in);}
		virtual void operator() ( const baseType x[], baseType dydx[] );
		virtual ~napK() { }
		virtual const nodeInfo getNodeInfo() { nodeInfo n = {_napK_,_dynNode_, "napK"};     return n; };
		static void registerStandardValues()
		{
			params<baseType>::registerStandard ( _napK_,"napK_gl",0,8.0 );
			params<baseType>::registerStandard ( _napK_,"napK_el",1,-80.0 );
			params<baseType>::registerStandard ( _napK_,"napK_gna",2,20.0 );
			params<baseType>::registerStandard ( _napK_,"napK_ena",3,60.0 );
			params<baseType>::registerStandard ( _napK_,"napK_gk",4,10.0 );
			params<baseType>::registerStandard ( _napK_,"napK_ek",5,-90.0 );
			params<baseType>::registerStandard ( _napK_,"napK_c",6,1.0 );
			params<baseType>::registerStandard ( _napK_, "napK_km", 7, 15.0 );
			params<baseType>::registerStandard ( _napK_, "napK_vhm", 8, -20.0 );
			params<baseType>::registerStandard ( _napK_, "napK_kn", 9, 5.0 );
			params<baseType>::registerStandard ( _napK_, "napK_vhn", 10, -25.0 );
			params<baseType>::registerStandard ( _napK_,"napK_constCurrent",11,0.0 );
		}

		virtual void clean ( unsigned int timeSteps )
		{

			odeNode::clean ( timeSteps ); this->tmp[0]=-70.0; this->tmp[1]=ninf ( -70.0 );
		};

};
//! Aus Izhikevich S. 89, äquivalent zu Morris-Lecar
class gaussianNapK		: public sdeNode
{
		
	private:
		inline baseType gl() {return params<baseType>::getParams ( 0 );}
		inline baseType el() {return params<baseType>::getParams ( 1 );}
		inline baseType gna() {return params<baseType>::getParams ( 2 );}
		inline baseType ena() {return params<baseType>::getParams ( 3 );}
		inline baseType gk() {return params<baseType>::getParams ( 4 );}
		inline baseType ek() {return params<baseType>::getParams ( 5 );}
		inline baseType c() {return params<baseType>::getParams ( 6 );}
		inline baseType km() {return params<baseType>::getParams ( 7 );}
		inline baseType vhm() {return params<baseType>::getParams ( 8 );}
		inline baseType kn() {return params<baseType>::getParams ( 9 );}
		inline baseType vhn() {return params<baseType>::getParams ( 10 );}
		inline baseType I() {return params<baseType>::getParams ( 11 );}
		inline baseType sigmaNoise() {return params<baseType>::getParams ( 12 );}
		inline baseType tau ( baseType v ) {return 1;}
		//diese Parameter auch noch frei waehlbar machen???
		inline baseType minf ( baseType v ) {return ( 1.0/ ( 1+exp ( ( vhm()-v ) /km() ) ) );}
		inline baseType ninf ( baseType v ) {return ( 1.0/ ( 1+exp ( vhn()-v ) /kn() ) );}
	public:
		virtual const unsigned int dimension() const { return 2;}

		gaussianNapK() : sdeNode (_gaussianNapK_ ) { }
//		hodgkinHuxley(inStream& in) : odeNode(4), params(_hodgkinHuxley_) { setParams(in);}
		virtual void operator() ( valarray<baseType>& x, valarray<baseType>& dxdt, valarray<baseType>& dxdW );
		virtual ~gaussianNapK() { }
		virtual const nodeInfo getNodeInfo() { nodeInfo n = {_gaussianNapK_,_dynNode_,"gaussianNapK"};     return n; };
		static void registerStandardValues()
		{
			params<baseType>::registerStandard ( _gaussianNapK_,"gaussianNapK_gl",0,8.0 );
			params<baseType>::registerStandard ( _gaussianNapK_,"gaussianNapK_el",1,-80.0 );
			params<baseType>::registerStandard ( _gaussianNapK_,"gaussianNapK_gna",2,20.0 );
			params<baseType>::registerStandard ( _gaussianNapK_,"gaussianNapK_ena",3,60.0 );
			params<baseType>::registerStandard ( _gaussianNapK_,"gaussianNapK_gk",4,10.0 );
			params<baseType>::registerStandard ( _gaussianNapK_,"gaussianNapK_ek",5,-90.0 );
			params<baseType>::registerStandard ( _gaussianNapK_,"gaussianNapK_c",6,1.0 );
			params<baseType>::registerStandard ( _gaussianNapK_, "gaussianNapK_km", 7, 15.0 );
			params<baseType>::registerStandard ( _gaussianNapK_, "gaussianNapK_vhm", 8, -20.0 );
			params<baseType>::registerStandard ( _gaussianNapK_, "gaussianNapK_kn", 9, 5.0 );
			params<baseType>::registerStandard ( _gaussianNapK_, "gaussianNapK_vhn", 10, -25.0 );
			params<baseType>::registerStandard ( _gaussianNapK_,"gaussianNapK_constCurrent",11,0.0 );
			params<baseType>::registerStandard ( _gaussianNapK_, "gaussianNapK_sigmaNoise", 12,0.0 );
		}

		virtual void clean ( unsigned int timeSteps )
		{

			sdeNode::clean ( timeSteps ); this->tmp[0]=-70.0; this->tmp[1]=ninf ( -70.0 );
		};

};
		/*!Aus Izhikevich S. 253, ein minimal bursting model*/
class napKKm		: public odeNode
{
	private:
		inline baseType gl() {return params<baseType>::getParams ( 0 );}
		inline baseType el() {return params<baseType>::getParams ( 1 );}
		inline baseType gna() {return params<baseType>::getParams ( 2 );}
		inline baseType ena() {return params<baseType>::getParams ( 3 );}
		inline baseType gkfast() {return params<baseType>::getParams ( 4 );}
		inline baseType ek() {return params<baseType>::getParams ( 5 );}
		inline baseType gkslow() {return params<baseType>::getParams ( 6 );}
		inline baseType c() {return params<baseType>::getParams ( 7 );}
		inline baseType km() {return params<baseType>::getParams ( 8 );}
		inline baseType vhm() {return params<baseType>::getParams ( 9 );}
		inline baseType knfast() {return params<baseType>::getParams ( 10 );}
		inline baseType vhnfast() {return params<baseType>::getParams ( 11 );}
		inline baseType knslow() {return params<baseType>::getParams ( 12 );}
		inline baseType vhnslow() {return params<baseType>::getParams ( 13 );}
		inline baseType I() {return params<baseType>::getParams ( 14 );}
		inline baseType taufast ( baseType v ) {return 0.152;}
		inline baseType tauslow ( baseType v ) {return 20.0;}
		//diese Parameter auch noch frei waehlbar machen???
		inline baseType minf ( baseType v ) {return ( 1.0/ ( 1+exp ( ( vhm()-v ) /km() ) ) );}
		inline baseType ninf ( baseType v ) {return ( 1.0/ ( 1+exp ( vhnfast()-v ) /knfast() ) );}
		inline baseType n_slowinf ( baseType v ) {return ( 1.0/ ( 1+exp ( vhnslow()-v ) /knslow() ) );}
	public:
		virtual const unsigned int dimension() const { return 3;}

		napKKm() : odeNode (_napKKm_ ) { }
//		hodgkinHuxley(inStream& in) : odeNode(4), params(_hodgkinHuxley_) { setParams(in);}
		virtual void operator() ( const baseType x[], baseType dydx[] );
		virtual ~napKKm() { }
		virtual const nodeInfo getNodeInfo() { nodeInfo n = {_napKKm_,_dynNode_,"napKKm"};     return n; };
		static void registerStandardValues()
		{
			params<baseType>::registerStandard ( _napKKm_,"napKKm_gl",0,8.0 );
			params<baseType>::registerStandard ( _napKKm_,"napKKm_el",1,-80.0 );
			params<baseType>::registerStandard ( _napKKm_,"napKKm_gna",2,20.0 );
			params<baseType>::registerStandard ( _napKKm_,"napKKm_ena",3,60.0 );
			params<baseType>::registerStandard ( _napKKm_,"napKKm_gkfast",4,9.0 );
			params<baseType>::registerStandard ( _napKKm_,"napKKm_ek",5,-90.0 );
			params<baseType>::registerStandard ( _napKKm_,"napKKm_gkslow", 6,5.0 );
			params<baseType>::registerStandard ( _napKKm_,"napKKm_c",7,1.0 );
			params<baseType>::registerStandard ( _napKKm_,"napKKm_km", 8, 15.0 );
			params<baseType>::registerStandard ( _napKKm_,"napKKm_vhm", 9, -20.0 );
			params<baseType>::registerStandard ( _napKKm_,"napKKm_knfast", 10, 5.0 );
			params<baseType>::registerStandard ( _napKKm_,"napKKm_vhnfast", 11, -25.0 );
			params<baseType>::registerStandard ( _napKKm_,"napKKm_knslow", 12, 5.0 );
			params<baseType>::registerStandard ( _napKKm_,"napKKm_vhnslow", 13, -20.0 );
			params<baseType>::registerStandard ( _napKKm_,"napKKm_constCurrent",14,0.0 );
		}

		virtual void clean ( unsigned int timeSteps )
		{

			odeNode::clean ( timeSteps ); this->tmp[0]=-70.0; this->tmp[1]=ninf ( -70.0 );
		};

};


		/*!Aus Izhikevich S. 253, ein minimal bursting model*/
class gaussianNapKKm		: public sdeNode
{
	private:
		inline baseType gl() {return params<baseType>::getParams ( 0 );}
		inline baseType el() {return params<baseType>::getParams ( 1 );}
		inline baseType gna() {return params<baseType>::getParams ( 2 );}
		inline baseType ena() {return params<baseType>::getParams ( 3 );}
		inline baseType gkfast() {return params<baseType>::getParams ( 4 );}
		inline baseType ek() {return params<baseType>::getParams ( 5 );}
		inline baseType gkslow() {return params<baseType>::getParams ( 6 );}
		inline baseType c() {return params<baseType>::getParams ( 7 );}
		inline baseType km() {return params<baseType>::getParams ( 8 );}
		inline baseType vhm() {return params<baseType>::getParams ( 9 );}
		inline baseType knfast() {return params<baseType>::getParams ( 10 );}
		inline baseType vhnfast() {return params<baseType>::getParams ( 11 );}
		inline baseType knslow() {return params<baseType>::getParams ( 12 );}
		inline baseType vhnslow() {return params<baseType>::getParams ( 13 );}
		inline baseType I() {return params<baseType>::getParams ( 14 );}
		inline baseType sigmaNoise() {return params<baseType>::getParams ( 15 );}
		inline baseType taufast ( baseType v ) {return 0.152;}
		inline baseType tauslow ( baseType v ) {return 20.0;}
		//diese Parameter auch noch frei waehlbar machen???
		inline baseType minf ( baseType v ) {return ( 1.0/ ( 1+exp ( ( vhm()-v ) /km() ) ) );}
		inline baseType ninf ( baseType v ) {return ( 1.0/ ( 1+exp ( vhnfast()-v ) /knfast() ) );}
		inline baseType n_slowinf ( baseType v ) {return ( 1.0/ ( 1+exp ( vhnslow()-v ) /knslow() ) );}
	public:
		virtual const unsigned int dimension() const { return 3;}

		gaussianNapKKm() : sdeNode (_gaussianNapKKm_ ) { }
//		hodgkinHuxley(inStream& in) : odeNode(4), params(_hodgkinHuxley_) { setParams(in);}
		virtual void operator() ( valarray<baseType>& x, valarray<baseType>& dxdt, valarray<baseType>& dxdW );
		virtual ~gaussianNapKKm() { }
		virtual const nodeInfo getNodeInfo() { nodeInfo n = {_gaussianNapKKm_,_dynNode_,"gaussianNapKKm"};     return n; };
		static void registerStandardValues()
		{
			params<baseType>::registerStandard ( _gaussianNapKKm_,"gaussianNapKKm_gl",0,8.0 );
			params<baseType>::registerStandard ( _gaussianNapKKm_,"gaussianNapKKm_el",1,-80.0 );
			params<baseType>::registerStandard ( _gaussianNapKKm_,"gaussianNapKKm_gna",2,20.0 );
			params<baseType>::registerStandard ( _gaussianNapKKm_,"gaussianNnapKKm_ena",3,60.0 );
			params<baseType>::registerStandard ( _gaussianNapKKm_,"gaussianNapKKm_gkfast",4,9.0 );
			params<baseType>::registerStandard ( _gaussianNapKKm_,"gaussianNapKKm_ek",5,-90.0 );
			params<baseType>::registerStandard ( _gaussianNapKKm_,"gaussianNapKKm_gkslow", 6,5.0 );
			params<baseType>::registerStandard ( _gaussianNapKKm_,"gaussianNapKKm_c",7,1.0 );
			params<baseType>::registerStandard ( _gaussianNapKKm_,"gaussianNapKKm_km", 8, 15.0 );
			params<baseType>::registerStandard ( _gaussianNapKKm_,"gaussianNapKKm_vhm", 9, -20.0 );
			params<baseType>::registerStandard ( _gaussianNapKKm_,"gaussianNapKKm_knfast", 10, 5.0 );
			params<baseType>::registerStandard ( _gaussianNapKKm_,"gaussianNapKKm_vhnfast", 11, -25.0 );
			params<baseType>::registerStandard ( _gaussianNapKKm_,"gaussianNapKKm_knslow", 12, 5.0 );
			params<baseType>::registerStandard ( _gaussianNapKKm_,"gaussianNapKKm_vhnslow", 13, -20.0 );
			params<baseType>::registerStandard ( _gaussianNapKKm_,"gaussianNapKKm_constCurrent",14,0.0 );
			params<baseType>::registerStandard ( _gaussianNapKKm_,"gaussianNapKKM_sigmaNoise", 15, 0.0 );
		}

		virtual void clean ( unsigned int timeSteps )
		{

			sdeNode::clean ( timeSteps ); this->tmp[0]=-70.0; this->tmp[1]=ninf ( -70.0 );
		};

};
/*
//! HodgkinHuxley-Neuron
class hodgkinHuxley    : public odeNode
{
	private:
		inline baseType cm() { return params<baseType>::getParams ( 0 ); }
		inline baseType gna() {return params<baseType>::getParams ( 1 );}
		inline baseType gk() {return params<baseType>::getParams ( 2 );}
		inline baseType gpas() {return params<baseType>::getParams ( 3 );}
		inline baseType ena() {return params<baseType>::getParams ( 4 );}
		inline baseType ek() {return -params<baseType>::getParams ( 5 );}
		inline baseType vpas() {return params<baseType>::getParams ( 6 );}
		inline baseType alpham ( baseType v ) {return ( 25-v ) / ( 10* ( exp ( ( 25-v ) /10 )-1 ) );}
		inline baseType betam ( baseType v ) {return 4*exp ( -v/18 );}
		inline baseType alphah ( baseType v ) {return 0.07*exp ( -v/20 );}
		inline baseType betah ( baseType v ) {return 1/ ( exp ( ( 30-v ) /10 ) +1 );}
		inline baseType alphan ( baseType v ) {return ( 10-v ) / ( 100* ( exp ( ( 10-v ) /10 )-1 ) );}
		inline baseType betan ( baseType v ) {return 0.125*exp ( -v/80 );}
		inline baseType constCurrent() { return params<baseType>::getParams ( 7 ); }
	public:
		virtual const unsigned int dimension() const { return 4;}
		

		hodgkinHuxley() : odeNode ( _hodgkinHuxley_ ) { }
//		hodgkinHuxley(inStream& in) : odeNode(4), params(_hodgkinHuxley_) { setParams(in);}
		virtual void operator() ( const baseType x[], baseType dydx[] );
		virtual ~hodgkinHuxley() { }
		virtual const nodeInfo getNodeInfo() { nodeInfo n = {_hodgkinHuxley_,_dynNode_,"hodgkinHuxley"};     return n; };
		static void registerStandardValues()
		{
			params<baseType>::registerStandard ( _hodgkinHuxley_,"hodgkinHuxley_cm",0,1.0 );
			params<baseType>::registerStandard ( _hodgkinHuxley_,"hodgkinHuxley_gna",1,120.0 );
			params<baseType>::registerStandard ( _hodgkinHuxley_,"hodgkinHuxley_gk",2,36 );
			params<baseType>::registerStandard ( _hodgkinHuxley_,"hodgkinHuxley_gpas",3,0.3 );
			params<baseType>::registerStandard ( _hodgkinHuxley_,"hodgkinHuxley_ena",4,110 );
			params<baseType>::registerStandard ( _hodgkinHuxley_,"hodgkinHuxley_ek",5,12 ); // Vorsicht minuszeichen
			params<baseType>::registerStandard ( _hodgkinHuxley_,"hodgkinHuxley_vpas",6,10.613 );
			params<baseType>::registerStandard ( _hodgkinHuxley_,"hodgkinHuxley_constCurrent",7,100 );

		}

		virtual void clean ( unsigned int timeSteps )
		{

//		odeNode::clean(timeSteps); dynNode::tmp[0]=0; dynNode::tmp[1]=alpham(0)/(alpham(0)+betam(0));
//		dynNode::tmp[2]=alphah(0)/(alphah(0)+betah(0));
//		dynNode::tmp[3]=alphan(0)/(alphan(0)+betan(0));
		};





};

//! Hodgkin-Huxley-Neuron mit Gausschem Rauschen als Input
class gaussianHH : public sdeNode
{
	private:
		inline baseType cm() { return params<baseType>::getParams ( 0 ); }
		inline baseType gna() {return params<baseType>::getParams ( 1 );}
		inline baseType gk() {return params<baseType>::getParams ( 2 );}
		inline baseType gpas() {return params<baseType>::getParams ( 3 );}
		inline baseType ena() {return params<baseType>::getParams ( 4 );}
		inline baseType ek() {return -params<baseType>::getParams ( 5 );}
		inline baseType vpas() {return params<baseType>::getParams ( 6 );}
		inline baseType alpham ( baseType v ) {return ( 25-v ) / ( 10* ( exp ( ( 25-v ) /10 )-1 ) );}
		inline baseType betam ( baseType v ) {return 4*exp ( -v/18 );}
		inline baseType alphah ( baseType v ) {return 0.07*exp ( -v/20 );}
		inline baseType betah ( baseType v ) {return 1/ ( exp ( ( 30-v ) /10 ) +1 );}
		inline baseType alphan ( baseType v ) {return ( 10-v ) / ( 100* ( exp ( ( 10-v ) /10 )-1 ) );}
		inline baseType betan ( baseType v ) {return 0.125*exp ( -v/80 );}
		inline baseType constCurrent() { return params<baseType>::getParams ( 7 ); }
		inline baseType sigmaNoise() {return params<baseType>::getParams ( 8 );}
	public:
		virtual const unsigned int dimension() const{return 4; }

		gaussianHH() : sdeNode (_gaussianHH_ ) { }
		//gaussianHH(baseType h) : sdeNode(1 ), params(_gaussianHH_) { }
//		ornUhl(inStream &in) :sdeNode(1), params
		virtual void operator() ( valarray<baseType>& y, valarray<baseType>& dxdt, valarray<baseType>& dxdW );
		virtual ~gaussianHH() { }
		static void registerStandardValues()
		{
			params<baseType>::registerStandard ( _gaussianHH_,"gaussianHH_cm",0,1.0 );
			params<baseType>::registerStandard ( _gaussianHH_,"gaussianHH_gna",1,120.0 );
			params<baseType>::registerStandard ( _gaussianHH_,"gaussianHH_gk",2,36 );
			params<baseType>::registerStandard ( _gaussianHH_,"gaussianHH_gpas",3,0.3 );
			params<baseType>::registerStandard ( _gaussianHH_,"gaussianHH_ena",4,110 );
			params<baseType>::registerStandard ( _gaussianHH_,"gaussianHH_ek",5,12 ); // Vorsicht minuszeichen
			params<baseType>::registerStandard ( _gaussianHH_,"gaussianHH_vpas",6,10.613 );
			params<baseType>::registerStandard ( _gaussianHH_,"gaussianHH_constCurrent",7,100 );
			params<baseType>::registerStandard ( _gaussianHH_, "gaussianHH_sigmaNoise",8,0 );

		}

		virtual void clean ( unsigned int timeSteps )
		{

			sdeNode::clean ( timeSteps ); this->tmp[0]=0; this->tmp[1]=alpham ( 0 ) / ( alpham ( 0 ) +betam ( 0 ) );
			this->tmp[2]=alphah ( 0 ) / ( alphah ( 0 ) +betah ( 0 ) );
			this->tmp[3]=alphan ( 0 ) / ( alphan ( 0 ) +betan ( 0 ) );
		};
		//Klammer zu viel

		virtual const nodeInfo getNodeInfo() { nodeInfo n = {_gaussianHH_,_dynNode_,"gaussianHH"};     return n; };


};*/

//! Knoten, der periodischen Abständen 1 und 0 zurüchgibt. Funktioniert wohl nicht mehr.
class periodicNode : public dynNode
{
		inline baseType period() {return params<baseType>::getParams ( 0 );}

		int step;

	public:

		virtual const unsigned int dimension() const{ return 1;}
    		virtual bool timeEvolution () { return 1;}
		periodicNode() : dynNode ( _periodicNode_ ), step ( 0 ) {  };
		virtual int requiredTimeSteps() { return 1; };

		virtual const nodeInfo getNodeInfo() { nodeInfo n = {_periodicNode_,_dynNode_|_inNode_,"periodicNode"};     return n; };

		static void registerStandardValues()
		{
			params<baseType>::registerStandard ( _periodicNode_,"periodicNode_per",0,10 );
		}

		virtual void action1()
		{
			if ( step > period() )
			{
				step = 1;
				tmp[0] = 1.0;
			}
			else if ( step == 1 )
			{
				tmp[0] = 0;
				step++;
			}
			else
			{
				step++;
			}
		}



		virtual void randomizeState ( boost::function<baseType () > &r )
		{
			step = ( baseType )    r();
		}


};




	//! Node, die als Status, die momentane Simulationszeit zurückgibt. Zweg fraglich. Eventuell kann die weg.










class randomWalkNeuron : public dynNode
{
	private:

	public:
		int fire;
		int pause;

		gslNoise noise;




//		inline baseType threshold() {return params<baseType>::getParams(0);}
		inline baseType t_fire() {return params<baseType>::getParams ( 0 );}
		inline baseType t_ref() {return params<baseType>::getParams ( 1 );}
		inline baseType inc() {return params<baseType>::getParams ( 2 );}
		inline baseType p_endo() {return params<baseType>::getParams ( 3 );}
//		inline baseType decay() {return params<baseType>::getParams(5);}


		virtual const unsigned int dimension() const { return 1;}

		randomWalkNeuron() : dynNode ( _randomWalkNeuron_ ), fire ( 0 ), pause ( 0 ) {  };
		virtual int requiredTimeSteps() { return 1; };
 		virtual bool timeEvolution () {return 1;}
		void virtual action1();
		virtual const nodeInfo getNodeInfo() { nodeInfo n = {_randomWalkNeuron_,_dynNode_,"randomWalkNeuron"};     return n; };
		static void registerStandardValues()
		{
//			params<baseType>::registerStandard(_randomWalkNeuron_,"randomWalkNeuron_threshold",0,10);
			params<baseType>::registerStandard ( _randomWalkNeuron_,"randomWalkNeuron_t_fire",0,1 );
			params<baseType>::registerStandard ( _randomWalkNeuron_,"randomWalkNeuron_t_ref",1,15 );
			params<baseType>::registerStandard ( _randomWalkNeuron_,"randomWalkNeuron_inc",2,0.0 );
			params<baseType>::registerStandard ( _randomWalkNeuron_,"randomWalkNeuron_p_endo",3,0.001 );
//			params<baseType>::registerStandard(_randomWalkNeuron_,"randomWalkNeuron_decay",4,1);
		}
		virtual void randomizeState ( boost::function<baseType () > &r )
		{
			baseType zufallsWert = r();
			tmp[0] = zufallsWert;
		};



};


}


#endif
