



#include "stdToyModels.h"



namespace conedy
{



void stdKuramoto::operator()(const baseType x[], baseType dxdt[]) 
{
	node::edgeDescriptor ia, ie;
	ia =0; 
	ie = degree();

    	dxdt[0] = omega();
	for (; ia != ie; ia++)
		dxdt[0] += getWeight(ia) * sin ( 2 * M_PI*(getTargetState(ia) - x[0] ));

}



void stdVanDerPol::operator()(const baseType x[], baseType dxdt[]) 
{
	dxdt[0] = x[1];
	dxdt[1] = -x[0] - mu()*x[1]*(x[0]*x[0] -1);
}


void stdRoessler::operator()(const baseType x[], baseType dxdt[]) 
{
	dxdt[0] = - omega() * x[1] - x[2]+ this->couplingSum() - this->weightSum()*x[0];
	dxdt[1] = x[0] + a() * x[1];
	dxdt[2] = b() + x[2] *( x[0] - c() );

}


void stdLorenz::operator()(const baseType x[], baseType dxdt[])
{
	dxdt[0] = s() *( x[1] - x[0] );
	dxdt[1] = x[0] *( r() - x[2] ) - x[1];
	dxdt[2] = x[0] * x[1] - b() * x[2] +this->couplingSum() - this->weightSum()*x[2];
}


}
