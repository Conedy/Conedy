#ifndef integrator_h
#define integrator_h integrator_h



#include <valarray>
#include "baseType.h"
#include "gslNoise.h"

using namespace std;




class integrator
{

	public:
		integrator (unsigned int size) {}
//		template <typename dgl>
//		virtual void step (double time, baseType *state, dgl&func, unsigned int size) = 0;


};


class euler : public integrator

{
	baseType * tmp;
	baseType * dydt;

	public:
	euler (unsigned int size) : integrator( size) {
		tmp = (baseType *) calloc (size, sizeof(baseType));	
		dydt = (baseType *) calloc (size, sizeof(baseType));	

	}

	~euler()
	{
		free (tmp);
		free (dydt);
	}

	template <typename dgl>
		void step (double dt, baseType *state, dgl &func, unsigned int size)
		{
			func.dgl(state,dydt);
			for (unsigned int i = 0; i < size; i++)
				state[i] = state[i] + dt * dydt[i];
		}
};




class strongTaylor : public integrator
{
	baseType dW, dZ;
	baseType zeta;
	baseType dt2, sqdt, sqdt2, a10, rho;
	baseType * tmp2, * dydt, *dyt, *dym, *dydW;

	
	const unsigned int approxOrder;

	public:
	strongTaylor (unsigned int size) : integrator (size), approxOrder(20) {

		tmp2 = (baseType *) calloc (size, sizeof(baseType));	
		dydt = (baseType *) calloc (size, sizeof(baseType));	
		dyt = (baseType *) calloc (size, sizeof(baseType));	
		dym = (baseType *) calloc (size, sizeof(baseType));	
		dydW = (baseType *) calloc (size, sizeof(baseType));	


		double r2, pi2=1.0/(2.0*pow(M_PI, 2)), tp1=0.0;
		rho=1.0/12.0;
		for (unsigned short i = 1; i <= approxOrder; i++) {
			r2 = pow(1.0/(double)i, 2.0);
			tp1 += r2;
		}
		rho   -= pi2*tp1;

	}

	
	template <typename dgl>
	void step (double dt, baseType *state, dgl &func, unsigned int size)	{
			dt2=dt/2.0; sqdt=sqrt(dt); sqdt2 = sqdt/2.0;

			//first step

			zeta = gslNoise::getGaussian();
			dW = sqdt*zeta;

			double r;
				// Berrechne a10 und b1
			a10=0.0;
			for (unsigned short j = 0; j < approxOrder; j++) {
			r=(double)(j+1);
			a10 -= gslNoise::getGaussian()/r;
			}
			a10 = a10*sqrt(2.0*dt)/M_PI - 2*sqrt(dt*rho)*gslNoise::getGaussian();
			dZ = 0.5*dt*(dW + a10);

			func.dgl(state, dydt, dydW);														


			for (unsigned int i = 0; i < size; i++)
			tmp2[i] = state[i] + dydt[i]*dt + dydW[i]*sqdt;																                        

			//second step

			func.dgl			(tmp2, dyt, dydW);																
			for (unsigned int i = 0; i < size; i++)					                                    
				tmp2[i] = state[i] + dydt[i]*dt - dydW[i]*sqdt;																                        

				//third step
			
			func.dgl(tmp2, dym, dydW);
			for (unsigned int i = 0; i < size; i++)					                                    
				state[i] += dydW[i]*dW + (dyt[i] - dym[i])/((baseType)2.0*sqdt)*dZ + (dyt[i] + dym[i] + (baseType)2.0*dydt[i])/(baseType)4.0*dt;	




	}


};

#endif
