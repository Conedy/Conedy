

#ifndef __statisticsN
#define __statisticsN

#include "network.h"
#include <limits.h>
#include <boost/pending/relaxed_heap.hpp>
#include "limits"

#include <fstream>

#include "baseType.h"

namespace conedy
{


	class dijkstraCompare {
	
		public:
			static vector<baseType> weightMap;


		public:
			bool operator() ( const unsigned int  s1, const unsigned int s2 ) const { return weightMap[s1 - 1] < weightMap[s2 - 1]; }


	};


	//! Erbe von network mit Funktionen, die Netzwerkcharacteristiken ausrechnen
	class statisticsNetwork : public virtual network
	{
		public:

			void printStatistics ();
			void printNodeStatistics();
			
			bool isConnected();			

			nodeDescriptor degree (nodeDescriptor v) { return node::theNodes[v]->degree(); }
			double meanDegree() { return meanOutDegree();}

			float meanInDegree ();
			float meanOutDegree ();
			float meanClustering();
			void printStatistics ( string s );
			void dijkstra( vector<baseType>& ret, nodeList vl, unsigned int v);
			float meanPathLength();
//			float meanDistanceMult();
			void degreeCentrality ( string filename );
			void closenessCentrality ( string filename );
			void betweennessCentrality ( string filename );

			float meanWeight();

			unsigned int countEdges (edgeVirtual *e);


//			void weightDistribution ( string fileName)

			void inDegreeDistributionToFile ( string fileName )
			{
				ofstream out;
				out.open ( fileName.c_str() );
				vector<unsigned int> inDegrees = inDegreeDistribution();
				for ( unsigned int i = 0; i < inDegrees.size(); i++ )
					out << i << " " << inDegrees[i] << endl;
			}

			void saveAdjacencyList(string fileName);
			void saveGraphML(string fileName);
			
         void saveAdjacencyMatrix (string fileName);


			void loadGraphML(string fileName) { throw "loadGraphML is a stub !";}

			void printAdjacencyList();

			void outDegreeDistributionToFile ( string fileName )
			{
				ofstream out;
				out.open ( fileName.c_str() );
				vector<int> outDegrees = outDegreeDistribution();
				for ( unsigned int i = 0; i < outDegrees.size(); i++ )
					out << i << " " << outDegrees[i] << endl;
			}


			double networkSize()
			{
				network::nodeList vl;
				network::verticesMatching(vl, _dynNode_);
				network::nodeIterator it;
				int counter = 0;
				for (it = vl.begin(); it != vl.end(); it++)
					counter++;
				
				return (double)counter;
			}
			

			vector<unsigned int> inDegreeDistribution();
			vector<int> outDegreeDistribution();
			void print ( int s )
			{
				cout << s << flush; cout << ( char ) 8; if ( s > 9 ) cout << ( char ) 8;;


			};

			statisticsNetwork() {};

//		void components ( vector < statisticsNetwork <T> * > &res );


//			statisticsNetwork ( inStream &in ) : network ( in ) { };
//			statisticsNetwork ( int size, inStream &in ) : network ( size, in ) {};
	};


}

#endif

