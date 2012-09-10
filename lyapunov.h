#ifndef lyapunov_h
#define lyapunov_h lyapunov_h


#include "network.h"
#include <fstream>
	struct meanVar {
		baseType mean;
		baseType var;
	};


	class realign
	{
		private:
			network::nodeList *vl;
			baseType eps;
			ifstream in;
			ofstream out;
			int counter;
			int skip;
		public:
			realign(string input, string output, network::nodeList *theList, baseType theEpsilon, int s)
			{
				in.open(input.c_str());
				out.open(output.c_str());
				vl = theList;
				eps= theEpsilon;
				skip = s;
				counter = skip;
			}
			meanVar  calculateDist(vector <baseType> &states);
			void realignNow ( vector <baseType> &states, baseType eps, meanVar dist);

			void realignPeriodically();
			void realignWhenDistant();
//			void	goForIt();
	};




#endif
