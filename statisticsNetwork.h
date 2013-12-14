

#ifndef __statisticsN
#define __statisticsN

#include "network.h"
#include "baseType.h"
#include "globals.h"

namespace conedy
{

	//! Contains functions, which calculate network characteristics
	class statisticsNetwork : public virtual network 
	{
		public:
			
//			void printStatistics ();


			void printNodeStatistics();

			//! returns true if the network has only one connected component. (works only for undirected networks at the moment.)
			bool isConnected();

			//! returns the degree of node v
			nodeDescriptor degree (nodeDescriptor v) { return node::theNodes[v]->degree(); }

			//! returns the mean degree of the network
			baseType meanDegree ();

			//! return the in-degree of node n
			int inDegree(nodeDescriptor n);

			//! return the out-degree of node n
			int outDegree(nodeDescriptor n);

			//! returns the mean clustering coefficient
			baseType meanClustering();

			void printStatistics ( string s );


			baseType meanPathLength();

			baseType meanWeight();

			void degreeCentrality ( string filename );
			void closenessCentrality ( string filename );
			void betweennessCentrality ( string filename );

			//			baseType meanDistanceMult();


			unsigned int countEdges (edgeVirtual *e);


//			void weightDistribution ( string fileName)

			void inDegreeDistributionToFile ( string fileName );

			void saveAdjacencyList(string fileName);
			void saveGraphML(string fileName);

         void saveAdjacencyMatrix (string fileName);

//			void loadGraphML(string fileName) { throw "loadGraphML is a stub !";}

			void printAdjacencyList();

			void outDegreeDistributionToFile ( string fileName );

			double networkSize();

			void dijkstra( vector<baseType>& ret, nodeList vl, unsigned int v);

			vector<unsigned int> inDegreeDistribution();
			vector<int> outDegreeDistribution();


			statisticsNetwork() {};

	};


}

#endif

