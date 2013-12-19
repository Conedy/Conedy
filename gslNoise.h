

/* last modifier: js */

#ifndef gslNoise_h
#define gslNoise_h gslNoise_h
#include <cmath>
#include<gsl/gsl_rng.h>
#include<gsl/gsl_randist.h> 
#include <iostream>


#include <boost/bind.hpp>
#include <boost/function.hpp>


#define STRINGIFY2( x) #x
#define STRINGIFY(x) STRINGIFY2(x)

#ifdef _WIN32
#include <time.h>
#else
#include <sys/time.h>
#include <time.h>
#endif



using namespace std;
using namespace boost;
//! Wrapper-klasse für die Zufallszahlen der GSL
class gslNoise {
	private:

		static gsl_rng *static_r;
		static unsigned long theSeed;
	public:
		gslNoise() {
		};
		/*		gslNoise(unsigned long seed) 
				{
				gsl_rng_env_setup();
				r=gsl_rng_alloc(gsl_rng_default);
				theSeed = seed;
				gsl_rng_set(r, seed);
				}*/
		static void initialise(unsigned long seed) { 
			gsl_rng_env_setup();
			static_r=gsl_rng_alloc(gsl_rng_default);
			gsl_rng_set(static_r, seed);
		};
		static void initialise() {

#ifdef _WIN32									

				//TODO better way to determine system time under windows and generate a random seed.
			theSeed = rand();
#else

			struct timeval tv;
			gettimeofday(&tv, NULL);
			srand((unsigned int)(tv.tv_sec + tv.tv_usec));
			theSeed = rand();

#endif

			gsl_rng_env_setup();
			static_r=gsl_rng_alloc(gsl_rng_default);
			cout << "#Using random Seed:" << theSeed << endl;
#ifdef SVN_REV
			//			printf( "Using svn Rev.: %s\n", STRINGIFY(SVN_REV)); // FIXME
			cout << "#Version: " << STRINGIFY( SVN_REV) << endl; //FIXME
#endif

#ifdef ARCHITECTURE

			cout << "#Architecture: " << STRINGIFY( ARCHITECTURE) << endl;
#endif


			//			gsl_rng_set(static_r, 3);

			gsl_rng_set(static_r, theSeed);
		};

		static unsigned long getSeed() {  return theSeed; };


		//		static void setSeed(unsigned long seed) { gsl_rng_set(static_r, seed); };
		static void setSeed(long seed) { theSeed = seed; gsl_rng_set(static_r, seed); };


		static double getUniform(double lower, double upper) {return gsl_rng_uniform(static_r) * (upper-lower) + lower; };
		static double getGaussian(double mean, double sigma) { return gsl_ran_gaussian(static_r, 1.0)* sigma + mean; }
		static double getBimodal(double lower, double upper, double prob) { 	return (gsl_rng_uniform(static_r) > prob) ? lower:upper; }
		static double getPowerLaw(double exponent, double min) { double  bound = pow(min, exponent+1)/fabs(exponent+1);  	return pow (fabs((exponent + 1))*(bound *getUniform(0.0,1.0)), 1/(exponent+1)); }

			
			
			

		static double getConstant (double value) { return value; }

		static int getUniformInt(int a, int b) { return (a+  (int)gsl_rng_uniform_int (static_r, b-a + 1)  ); };

		// Funktions

		static function<double () > functionUniform (double lower, double upper) { return bind(&gslNoise::getUniform, lower, upper); }
		static function<double () > functionGaussian (double mean, double sigma) { return bind(&gslNoise::getGaussian, mean, sigma); }
		static function<double () > functionConstant (double mean) { return bind(&gslNoise::getConstant, mean); }
		static function<double () > functionBimodal (double lower, double upper, double prob) { return bind (&gslNoise::getBimodal, lower, upper, prob); }
		static function<double () > functionPowerLaw (double exponent, double bound) {  return bind (&gslNoise::getPowerLaw, exponent, bound); }
			
			

		static double getGaussian() { return gsl_ran_gaussian(static_r, 1.0); };
		static double getUniform() { return gsl_rng_uniform(static_r); }
		static double getExponential(double lambda) { return (gsl_ran_exponential (static_r, lambda)); }

		static int getPoisson (double mu) {return gsl_ran_poisson(static_r,mu); }
		static double getPoisson (double mu,double faktor) {
			double re = ((double)gsl_ran_poisson(static_r,mu)) * faktor;
			return re;
		}
		static void free()
		{
			gsl_rng_free(static_r);
		}

		

};



//! Abstrakte Basisklasse für Zufallszahl-objekte. Der Klammeroperator gibt die nächste Zufallszahl zurück. Unterschiedliche Arten von Zufallszahlen (gauss-verteilt, poissonverteilt) werden in Erben von randomNumber implementiert.
template <typename T>
class randomNumber
{
	protected:
		static gslNoise noise;

	public:
		randomNumber() {};
		virtual T operator() () { return (T)0;};
		virtual ~randomNumber() {};
};


//! Funktionsobjekt, das  gleichverteilte Zufallszahlen zurückgibt.
template <typename T>
class uniform : public randomNumber<T>
{
	private:
		T lower, upper;
	public:
		uniform (T a, T b) : randomNumber<T>(), lower(a), upper(b)  {};
		T operator()() { return ((T) (lower + (upper-lower)*randomNumber<T>::noise.getUniform())); }
		virtual ~uniform() {};

};


template <typename T>
class bimodal : public randomNumber<T>
{
	private:
		T lower;
		T upper;
		double prob;
	public:
		bimodal (T l, T u, double p): randomNumber<T>(), lower(l), upper(u), prob(p) {};
		T operator()()
		{


			if (randomNumber<T>::noise.getUniform() < prob)
				return lower;
			else 
				return upper;
		}
};



template <typename T>
class binary : public randomNumber<T>
{
	private:
		T value;
		double prob;
	public:
		binary (T v, double p) : randomNumber<T>(), value(v), prob(p)  {};
		T operator()() 
		{
			if (randomNumber<T>::noise.getUniform() < prob)		
				return 0;
			else 	return value; 
		}

};
//#
//#template <typename T>
//#class gaussian : public randomNumber<T>
//#{
//#	private:
//#	T mean, sigma;
//#	public:
//#
//#	static void * operator new (size_t size);
//#	gaussian (T a, T b) : randomNumber<T>(), mean(a), sigma(b)  {};
//#	T operator()() { return ((T) (mean + sigma*randomNumber<T>::noise.getGaussian())); }
//#	virtual ~gaussian() {};
//#
//#};
//#
//


class uniformInt
{
	private:
		gslNoise noise;
		int lower, upper;
	public:
		uniformInt(int a, int b) : lower(a), upper(b) {};
		int operator()() { return noise.getUniformInt(lower,upper);}

};

class uniformDouble
{
	private:
		gslNoise noise;
		double lower, upper;
	public:
		uniformDouble(int a, int b) : lower(a), upper(b) {};
		double operator()() { return (lower + (upper-lower)*noise.getUniform()) ; };

};

//! gibt mit Wahrscheinlichkeit a 1 zurück, andernfalls 0
class uniformBool
{
	private:
		gslNoise noise;
		double prop;
	public:
		uniformBool(double a) : prop(a) {};
		bool operator()() { return    ((noise.getUniform() < prop) ? 1:0); }

};


	class xToTheAlpha
	{
	private:
	gslNoise noise;
	double alpha;
	double bound;
	public:
	xToTheAlpha(double a, int min) : alpha(a) { bound = pow(min, alpha+1)/fabs(alpha+1);   };           // a: obere Grenze
	double operator()() { return pow (fabs((alpha + 1))*(bound *noise.getUniform()), 1/(alpha+1)); }
	};




template <class T>
gslNoise randomNumber<T>::noise;












#endif
