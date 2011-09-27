

#include "neuronModels.h"


namespace conedy {



void randomWalkNeuron::action1()
{
//	cout << "Neuron number:" << this->getNumber() << "\n";
//	cout << "pot vorher:" << pot << "\n";

	if ( x[0] >= 10.0 )
		x[0] = -t_ref();
	else if ( x[0] < 0 )
		x[0]++;
	else if ( noise.getUniform() < p_endo() )
		x[0] =  10.0;
	else
		x[0] = x[0] + this->couplingSum() + inc();

//	cout << "pot nachher:" << pot << "\n";

}







/*void integrateAndFire::operator() ( const baseType x[], baseType dxdt[] )
{
	dxdt[0] = params<baseType>::getParams ( 0 ) - params<baseType>::getParams ( 1 ) *x[0] + this->couplingSum();

}*/
/*void integrateAndFire::swap()
{
//	cout << getNumber() << ":" << dynNode::state << endl;
//	dynNode::state = dynNode::getParams[0];

//cout << dynNode::getParams[0] << endl;


	if (time - lastFiring < t_ref())
		return;

	else if ( x[0] > threshold())
	{
			registerOneTimeCallBack(_fire_, dynNode::time + timeDelay() );				
			lastFiring = time;
			x[0] = 0;
	}

	else if 


	if ( fire > 0 )
	{
		if ( fire > params<baseType>::getParams ( 5 ) )
		{
//			this->x[0] = this->state = 0;
			fire = 0;
			pause = 1;
		}
		else
		{
			fire++;
			this->x[ 0 ] = params<baseType>::getParams ( 3 );
		}
	}
	else if ( pause > 0 )
	{
		if ( pause > params<baseType>::getParams ( 4 ) )
			pause = 0;

		else
		{
			pause++;
			x[0]= 0;
		}

	}



	else if ( this->x [0] > params<baseType>::getParams ( 2 ) || noise.getUniform() < params<baseType>::getParams ( 6 ) )
	{
	//	this->state = params<baseType>::getParams ( 3 );
		this->x[0] = params<baseType>::getParams ( 3 );
		fire = 1;
	}

	else;
//		this->state = this->x[0];

*/

void gaussianFHN::operator() ( valarray<baseType>& x, valarray<baseType>& dxdt, valarray<baseType>& dxdW )
{
	dxdt[0] = x[0]* ( a()-x[0] ) * ( x[0]-1.0 )-x[1]+I() +this->couplingSum();
	dxdt[1] = b() *x[0]-c() *x[1];
	dxdW[0] = sigmaNoise();
}

//void hindmarshRose::operator() ( const baseType x[], baseType dxdt[] )
//{
//	dxdt[0] = 3.0*x[0]*x[0]-x[0]*x[0]*x[0] + x[1] - x[2] + I() + this->couplingSum();
//	dxdt[1] = 1.0-5*x[0]*x[0]-x[1];
//	dxdt[2] = r() * ( 4* ( x[0]+1.6 )-x[2] );
//}
//
//void gaussianHR::operator() ( valarray<baseType>& x, valarray<baseType>& dxdt, valarray<baseType>& dxdW )
//{
//	dxdt[0] = 3.0*x[0]*x[0]-x[0]*x[0]*x[0] + x[1] - x[2] + I() +this->couplingSum();
//	dxdt[1] = 1.0-5*x[0]*x[0]-x[1];
//	dxdt[2] = r() * ( 4* ( x[0]+1.6 )-x[2] );
//	dxdW[0] = sigmaNoise();
//}
//
void napK::operator() ( const baseType x[], baseType dxdt[] )
{
	dxdt[0] = I() /c() - ( gl() /c() ) * ( x[0]-el() ) - ( gna() /c() ) *minf ( x[0] ) * ( x[0]-ena() )- ( gk() /c() ) *x[1]* ( x[0]-ek() ) + ( this->couplingSum() /c() );
	dxdt[1] = ( ninf ( x[0] )-x[1] ) /tau ( x[0] );

}

void gaussianNapK::operator() ( valarray<baseType>& x, valarray<baseType>& dxdt, valarray<baseType>& dxdW )
{
	dxdt[0] = I() /c() - ( gl() /c() ) * ( x[0]-el() ) - ( gna() /c() ) *minf ( x[0] ) * ( x[0]-ena() )- ( gk() /c() ) *x[1]* ( x[0]-ek() ) + ( this->couplingSum() /c() );
	dxdt[1] = ( ninf ( x[0] )-x[1] ) /tau ( x[0] );
	dxdW[0] = sigmaNoise();

}

void napKKm::operator() ( const baseType x[], baseType dxdt[] )
{
	dxdt[0] = I() /c() - ( gl() /c() ) * ( x[0]-el() ) - ( gna() /c() ) *minf ( x[0] ) * ( x[0]-ena() )- ( gkfast() /c() ) *x[1]* ( x[0]-ek() ) + ( gkslow() /c() ) *x[2]* ( x[0]-ek() ) + ( this->couplingSum() /c() );
	dxdt[1] = ( ninf ( x[0] )-x[1] ) /taufast ( x[0] );
	dxdt[2] = ( n_slowinf ( x[0] )-x[1] ) /tauslow ( x[0] );

}

void gaussianNapKKm::operator() ( valarray<baseType>& x, valarray<baseType>& dxdt, valarray<baseType>& dxdW )
{
	dxdt[0] = I() /c() - ( gl() /c() ) * ( x[0]-el() ) - ( gna() /c() ) *minf ( x[0] ) * ( x[0]-ena() )- ( gkfast() /c() ) *x[1]* ( x[0]-ek() ) + ( gkslow() /c() ) *x[2]* ( x[0]-ek() ) + ( this->couplingSum() /c() );
	dxdt[1] = ( ninf ( x[0] )-x[1] ) /taufast ( x[0] );
	dxdt[2] = ( n_slowinf ( x[0] )-x[1] ) /tauslow ( x[0] );
	dxdW[0] = sigmaNoise();

}
/*
void hodgkinHuxley::operator() ( const baseType x[], baseType dxdt[] )
{
	dxdt[0] = ( gna() /cm() ) *x[1]*x[1]*x[1]*x[2]* ( ena()-x[0] ) + ( gk() /cm() ) *x[3]*x[3]*x[3]*x[3]* ( ek()-x[0] ) + ( gpas() /cm() ) * ( vpas()-x[0] ) + ( this->couplingSum() /cm() ) + ( constCurrent() /cm() );
	dxdt[1] = alpham ( x[0] ) * ( 1-x[1] )-betam ( x[0] ) *x[1];
	dxdt[2] = alphah ( x[0] ) * ( 1-x[2] )-betah ( x[0] ) *x[2];
	dxdt[3] = alphan ( x[0] ) * ( 1-x[3] )-betan ( x[0] ) *x[3];
}


void gaussianHH::operator() ( valarray<baseType>& x, valarray<baseType>& dxdt, valarray<baseType>& dxdW )
{
	dxdt[0] = ( gna() /cm() ) *x[1]*x[1]*x[1]*x[2]* ( ena()-x[0] ) + ( gk() /cm() ) *x[3]*x[3]*x[3]*x[3]* ( ek()-x[0] ) + ( gpas() /cm() ) * ( vpas()-x[0] ) +this->couplingSum() /cm() + constCurrent() /cm();
	dxdt[1] = alpham ( x[0] ) * ( 1-x[1] )-betam ( x[0] ) *x[1];
	dxdt[2] = alphah ( x[0] ) * ( 1-x[2] )-betah ( x[0] ) *x[2];
	dxdt[3] = alphan ( x[0] ) * ( 1-x[3] )-betan ( x[0] ) *x[3];
	dxdW[0] = sigmaNoise();
}
*/

}


