

#ifndef __createNetwork_h
#define __createNetwork_h __createNetwork_h

#include "network.h"







namespace conedy
{


	/*!

	  contains implementations of network generators, e.g. lattices, random networks, rewiring, ...

	  uses only functions from network.h like (addNode, addEdge)




	  int	networkElementType	(Nummer des NodeTypes - CNN, Rössler ... - wird automatisch in nodeBlueprint.h vergeben)
	  nodeKind	NodeKind	(Nummer der Nodeart - Input, Output ... - wird automatisch in nodeBlueprint.h vergeben)
	  nodeDescriptor	nodeNumber	(Nummer der Node - Wahl genau einer Node)

*/


	class createNetwork : public virtual network
	{

		public:

			static void registerStandardValues()
			{
				//! true when output should be written to binary files.
				globals::registerGlobal<bool> ("outputBinary", false );
			}


			//			createNetwork()  {};

			//undirected- network generators


			//! creates a chain in which nodes are connected to its a nearest neighbors
			nodeDescriptor line ( unsigned int number, unsigned int a, nodeBlueprint *n = stdNode, edgeBlueprint *l=stdEdge);

			//! Creates a ring consisting of n copies of n, in which every node is connected to its a nearest neighbors to the left and right.
			nodeDescriptor cycle ( int number, int a,nodeBlueprint *n = stdNode, edgeBlueprint *l= stdEdge );

			//! Erzeugt einen Ring mit zuerst <number1> Kopien von *n1, dann <number2> Kopien von *n2; bei dem jeder Knoten mit den <a> nächsten Nachbarn nach links und recht verbunden ist.
			nodeDescriptor cycleCluster (int number1, nodeBlueprint *n1, int number2, nodeBlueprint *n2, int a);

			//! Erzeugt ein Gitter mit x * y Knoten vom Typ *n. Zwei Knoten werden über einen Link vom Typ *l verbunden, falls ihr Abstand  kleiner sqrt(a) ist. Randknoten haben entsprechend weniger Verbindungen.
			nodeDescriptor lattice ( int sizex, int sizey, double a = 1.01, nodeBlueprint *n = stdNode, edgeBlueprint *l = stdEdge );

			//! Wie Gitter, jedoch werden die Ränder zyklisch verbunden (links mit rechts, oben mit unten).
			nodeDescriptor torus ( int sizex, int sizey, double a, nodeBlueprint *n = stdNode, edgeBlueprint *l= stdEdge );

			//! Erzeugt ein Gitter der größe x * y aus streamInNodes, die alle aus der Datei s lesen. Funktioniert gut mit Dateien, die von observeAll erzeugt wurden
			nodeDescriptor streamInLattice ( int sizex, int sizey, string s );

			//! Erzeugt ein Gitter mit x * y Knoten vom Typ *n. Jeder Knoten wir mit seinen c nächsten Nachbarn verbunden. Gleichweit entfernte Nachbarn werden zufällig ausgewählt.
			nodeDescriptor torusNearestNeighbors ( int sizex, int sizey, double c, nodeBlueprint *n, edgeBlueprint *l );

			//! ein Netzwerk aus x * y Knoten vom Typ n
			nodeDescriptor beeWeb ( int x, int y, nodeBlueprint *n );

			//! Netzwerk mit number Knoten vom Typ *n, bei dem jeder mit jeden verbunden ist über einen Link vom Typ *l
			nodeDescriptor completeNetwork ( int number, nodeBlueprint *n =stdNode ,edgeBlueprint *l =stdEdge );               // number = Anzahl der Knoten




			//! Normalisiert die Summe der eingehenden Kopplungsgewichte jedes Knotens au den Wert r

			//! normalizes the sum of ingoing coupling weights to r.
			void normalizeInputs (baseType r);

			//! normalizes the sum of outgoing coupling weights to r.
			void normalizeOutputs (baseType r);

			//			void createFromMatrix ( inStream & in, unsigned int size, nodeBlueprint *n );

			//! Fügt Kopien der Knoten aus nodes zum Netzwerk hinzu und verbindet mit Kopplungsgewichten aus der Matrix weights.
			//nodeDescriptor createFromMatrix ( vector <nodeBlueprint *> * nodes, vector <vector<baseType> > weights );

			//! creates a network of nodes of type n and edges of type e according to a whitespace-separated adjacency matrix provided in a txt-file of name fileName.
			nodeDescriptor createFromAdjacencyMatrix (string fileName, nodeBlueprint * n = stdNode, edgeBlueprint *e=stdEdge);

			//! Erstellt ein Netzwerk aus Knoten vom Typ n, und verbindet mit Kopplungsgewichten aus der adjacenzmatrix weights  XXX obsolete ?
			nodeDescriptor createFromMatrix ( vector <vector<baseType> > weights, nodeBlueprint *n );

			//! creates a network of nodes of type n and edges of type e according to a whitespace-separated adjacency list provided in a txt-file of name fileName.
			nodeDescriptor createFromAdjacencyList ( string fileName, nodeBlueprint * n = stdNode, edgeBlueprint *l= stdEdge );


			//! Ersetzt Verbindungen mit Start- und Zielknoten der Art theNodeKind, durch ähnliche (kopierte) Verbindungen mit zufällig gewählten Start- und Zielknoten

			//! Replaces edges with source and target nodes of type _dynNode_ by similar (copied) edges with randomly chosen source and target nodes. Weights are drawn from r.
			void rewireWeights ( double prop ,boost::function<double () > r,nodeKind theNodeKind = _dynNode_ );




			// only consider edges which start and end at nodes of type n
			void rewire (double prop, nodeBlueprint *n = stdNode) { directed ? rewireDirected (prop, n) : rewireUndirected (prop,n); }
			void rewireUndirected (double prop, nodeBlueprint *n = stdNode); // Rewire mit einem ungerichteten Netzwerk im Nachhinein
			void rewireDirected (double prop, nodeBlueprint *n = stdNode); // Rewire mit einem ungerichteten Netzwerk im Nachhinein

			nodeDescriptor randomNetwork ( int number, double prop, nodeBlueprint *n = stdNode, edgeBlueprint *l = network::stdEdge ) {return directed ? randomNetworkDirected (number, prop , n, l) : randomNetworkUndirected (number,prop, n, l); }
			nodeDescriptor randomNetworkUndirected ( int number, double prop, nodeBlueprint *n = stdNode, edgeBlueprint *l = network::stdEdge );
			nodeDescriptor randomNetworkDirected ( int number, double prop, nodeBlueprint *n = stdNode, edgeBlueprint *l = network::stdEdge );

			void replaceEdges (double prop, edgeBlueprint *l = stdEdge, nodeBlueprint *n = stdNode);



			//! Erzeugt ein skalenfreies Netzwerk nach Barabasi und Albert
			nodeDescriptor scaleFreeNetwork ( int size, int c, nodeBlueprint *n, edgeBlueprint *l );

			void rewireSourcePerTimestep ( double prop,function <baseType() > r, nodeKind theNodeKind = _dynNode_ );

			//! Ersetzt Verbindungen mit Start- und Zielknoten der Art theNodeKind, durch ähnliche (kopierte) Verbindungen mit zufällig gewählten Zielknoten und unverändertem  Startknoten
			void rewireTarget ( double prop ,nodeKind theNodeKind = _dynNode_ );


			void rewireTargetUndirected ( double prop, nodeKind theNodeKinde = _dynNode_ );



			void addRandomEdgesDegreeDistribution ( function <double () > r, edgeBlueprint *l = stdEdge ) { directed ? addRandomEdgesDegreeDistributionDirected(r,l): addRandomEdgesDegreeDistributionUndirected(r,l); }
			void addRandomEdgesDegreeDistributionUndirected ( function <double () > r, edgeBlueprint *l = stdEdge );
			void addRandomEdgesDegreeDistributionDirected ( function <double () > r, edgeBlueprint *l = stdEdge );


			void removeRandomEdges ( double meanOutDegree, edgeBlueprint * l = stdEdge ) {directed ? removeRandomEdgesDirected (meanOutDegree, l) : removeRandomEdgesUndirected (meanOutDegree,l); }
			void removeRandomEdgesUndirected ( double meanOutDegree, edgeBlueprint * l = stdEdge );
			void removeRandomEdgesDirected ( double meanOutDegree, edgeBlueprint * l = stdEdge );

			void addRandomEdges ( double meanOutDegree, edgeBlueprint * l = stdEdge ) { directed ? addRandomEdgesDirected (meanOutDegree, stdEdge) : addRandomEdgesUndirected (meanOutDegree, stdEdge); }
			void addRandomEdgesUndirected ( double meanOutDegree, edgeBlueprint * l = stdEdge );
			void addRandomEdgesDirected ( double meanOutDegree, edgeBlueprint * l = stdEdge );


			//			template <typename RANDOM>
			//				void randomOutDegreeDistribution ( int number, RANDOM &r, nodeBlueprint *n );
			//
			//			template <typename RANDOM>
			//				void randomInDegreeDistribution ( int number, RANDOM &r, nodeBlueprint *n );
			//






			//! Ersetzt Verbindungen mit Start- und Zielknoten der Art theNodeKind, durch ähnliche (kopierte) Verbindungen mit zufällig gewählten Startknoten und unverändertem  Zielknoten
			void rewireSource ( double prop ,nodeKind theNodeKind = _dynNode_ );


			// observe commands.


			void observeWithoutCheck (nodeDescriptor number, string s, edgeBlueprint *l);

			void observeEventTimes( string fileName,nodeDescriptor eventNumber );
			void observeEventTimesEquals ( string fileName, nodeDescriptor eventNumber );
			void observeEventSignatureTimes( string fileName,nodeDescriptor eventNumber );
			void observeComponents (nodeDescriptor n, string fileName);

			void observeTime ( string s );

			//! observiert den Knoten number über eine Edge vom Typ l und  schreibt in die Datei s
			void observe (  nodeDescriptor number, string s,edgeBlueprint * l  = stdEdge);



			void observeEventCounter ( string s, unsigned int signature);

			//! wie oben. Phasen werden von Edges vom Typ l übergeben.
			void observeMeanPhase ( string s, edgeBlueprint *l );


			void observeMeanPhase ( string s );


			//! wie oben mit links vom Typ l
			void observeSum ( string s, edgeBlueprint *l = stdEdge );

			void observeEvent (string s, nodeDescriptor signature);


			//! wie oben allerdings wird die Phasenkohärenz r der States s_i weggeschrieben: r = 1/N \sum\limits_i exp( 2 * PI * s_i). Phasen gehen von 0 bis 1 !!! TODO: vielleicht von streamOutNode erben ??


			//! wie oben. Phasen werden von Edges vom Typ l übergeben.
			void observeAllPhaseCoherence ( string s, edgeBlueprint *l );



			void observePhaseCoherence ( string s, edgeBlueprint *l = stdEdge, nodeBlueprint *n = stdNode, nodeDescriptor lower = 0, nodeDescriptor upper = numeric_limits<nodeDescriptor>::max());


			void observeHist ( string s,    nodeBlueprint *n);

			void observePhaseCorrelation ( string s, nodeBlueprint *n);
			void observePhaseDistance ( string s, nodeBlueprint *n);



			void streamInBinary ( string s );

			void streamOutBinary ( string s, char flags = 24 );


			void addEnterNode ( string s );

			void observeHidden ( string s, int number );



//			void observeAll ( string s, edgeBlueprint *l = stdEdge, nodeBlueprint *n = stdNode, nodeDescriptor lower = 0, nodeDescriptor upper = numeric_limits<nodeDescriptor>::max());

			void observeAll ( string s, edgeBlueprint *l = stdEdge, nodeBlueprint *n = stdNode);


			void observeAllHiddenVariables ( string s );

			void observeRandom ( string s );

			//			template <typename NODETYPE>
			//				void dummy();





	};






}
#endif
