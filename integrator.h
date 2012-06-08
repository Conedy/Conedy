#ifndef integrator_h
#define integrator_h integrator_h



#include "baseType.h"
#include "gslNoise.h"

using namespace std;


#ifndef M_PI
#define M_PI    3.14159265358979323846f
#endif


class odeIntegrator
{
	protected:
		baseType * dxdt;

	public:
		odeIntegrator (unsigned int size) {
			dxdt = (baseType *) calloc (size, sizeof(baseType));		
			for (unsigned int i = 0; i < size; i++)
			{
				dxdt[i] = 0;
			}
		}
		virtual ~ odeIntegrator () {
			free (dxdt);
		}	

};



class sdeIntegrator
{
	protected:
		baseType *dxdt;
		baseType *s;
		baseType *dsdx;

	public:
		sdeIntegrator ( unsigned int size) {
			dxdt = (baseType *) calloc (size, sizeof(baseType));	
			s = (baseType *) calloc (size, sizeof(baseType));	
			dsdx = (baseType *) calloc (size, sizeof(baseType));

			for (unsigned int i = 0; i < size; i++)
			{
				s[i] = 0;
				dsdx[i] = 0;
			}

		}
		virtual ~sdeIntegrator ()	{
			free (dxdt);
			free (s);
			free (dsdx);
		}

};





class euler : public odeIntegrator

{

	public:
	euler (unsigned int size) : odeIntegrator( size) {	}

	template <typename dgl>
		void step (double dt, baseType *state, dgl &func, unsigned int size)		{
			func.dgl(state,dxdt);
			for (unsigned int i = 0; i < size; i++)
				state[i] = state[i] + dt * dxdt[i];
		}
};



class eulerMaruyama : public sdeIntegrator
{
	public:
		eulerMaruyama( unsigned int size) : sdeIntegrator (size)	{}


		template <typename dgl>
			void step (double dt, baseType *state, dgl &func, unsigned int size)			{
				func.dgl (state, dxdt, s, dsdx);
				for (unsigned int i = 0; i < size ; i++)
					state[i] = state[i] + dxdt[i] * dt + s[i] * sqrt (dt) * gslNoise::getGaussian();
			}
};


class milsteinIto	: public sdeIntegrator
{
	public:
		milsteinIto( unsigned int size) : sdeIntegrator (size){}

		template <typename dgl>
			void step (double dt, baseType *state, dgl &func, unsigned int size)		{
				double W;
				func.dgl (state, dxdt, s, dsdx);
				for (unsigned int i = 0; i < size ; i++)			{
					W = gslNoise::getGaussian();
					state [i] = state [i] + dxdt[i] * dt + s[i] * sqrt ( dt) * W + 0.5 * s[i] * dsdx[i] * ( dt * W *W - dt);
				}
			}
};


class milsteinStrato	: public sdeIntegrator
{
	public:

		milsteinStrato( unsigned int size) : sdeIntegrator (size)	{}
		template <typename dgl>
			void step (double dt, baseType *state, dgl &func, unsigned int size)
			{
				double W;
				func.dgl (state, dxdt, s, dsdx);
				for (unsigned int i = 0; i < size ; i++)
				{
					W = gslNoise::getGaussian();
					state [i] = state [i] + dxdt[i] * dt + s[i] * sqrt ( dt) * W + 0.5 * s[i] * dsdx[i] * ( dt * W *W );

				}

			}
};








class strongTaylor : public sdeIntegrator
{
	baseType dW, dZ;
	baseType zeta;
	baseType dt2, sqdt, sqdt2, a10, rho;
	baseType * tmp2, * dxdt, *dyt, *dym, *dydW;


	const unsigned int approxOrder;

	public:
	strongTaylor (unsigned int size) : sdeIntegrator (size), approxOrder(20) {

		tmp2 = (baseType *) calloc (size, sizeof(baseType));	
		dxdt = (baseType *) calloc (size, sizeof(baseType));	
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

			func.dgl(state, dxdt, dydW);														


			for (unsigned int i = 0; i < size; i++)
				tmp2[i] = state[i] + dxdt[i]*dt + dydW[i]*sqdt;																                        

			//second step

			func.dgl			(tmp2, dyt, dydW);																
			for (unsigned int i = 0; i < size; i++)					                                    
				tmp2[i] = state[i] + dxdt[i]*dt - dydW[i]*sqdt;																                        

			//third step

			func.dgl(tmp2, dym, dydW);
			for (unsigned int i = 0; i < size; i++)					                                    
				state[i] += dydW[i]*dW + (dyt[i] - dym[i])/((baseType)2.0*sqdt)*dZ + (dyt[i] + dym[i] + (baseType)2.0*dxdt[i])/(baseType)4.0*dt;	




		}


};

#endif
