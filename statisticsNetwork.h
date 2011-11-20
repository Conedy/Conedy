

#ifndef __statisticsN
#define __statisticsN

#include "network.h"
#include "baseType.h"

namespace conedy
{




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

			void inDegreeDistributionToFile ( string fileName );

			void saveAdjacencyList(string fileName);
			void saveGraphML(string fileName);
			
         void saveAdjacencyMatrix (string fileName);


			void loadGraphML(string fileName) { throw "loadGraphML is a stub !";}

			void printAdjacencyList();

			void outDegreeDistributionToFile ( string fileName );

			double networkSize();
			

			vector<unsigned int> inDegreeDistribution();
			vector<int> outDegreeDistribution();
			void print ( int s )
			{
				cout << s << flush; cout << ( char ) 8; if ( s > 9 ) cout << ( char ) 8;;


			};

			statisticsNetwork() {};

	};


}

#endif

