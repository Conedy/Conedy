

#include "statisticsNetwork.h"

#include <limits.h>
#include "globals.h"

#include <boost/pending/relaxed_heap.hpp>
#include <fstream>


namespace conedy
{
			void statisticsNetwork::inDegreeDistributionToFile ( string fileName )
			{
				ofstream out;
				out.open ( fileName.c_str() );
				vector<unsigned int> inDegrees = inDegreeDistribution();
				for ( unsigned int i = 0; i < inDegrees.size(); i++ )
					out << i << " " << inDegrees[i] << endl;
			}


			void statisticsNetwork::outDegreeDistributionToFile ( string fileName )
			{
				ofstream out;
				out.open ( fileName.c_str() );
				vector<int> outDegrees = outDegreeDistribution();
				for ( unsigned int i = 0; i < outDegrees.size(); i++ )
					out << i << " " << outDegrees[i] << endl;
			}



			int statisticsNetwork::inDegree( nodeDescriptor n)
	{


		node::edgeDescriptor ea;
		node::edgeDescriptor ee;

		network::nodeIterator ia;
		network::nodeList vl;
		network::verticesMatching ( vl,_dynNode_ );
		int res = 0;

		for ( ia = vl.begin(); ia != vl.end(); ia++ )
		{
			ea = 0;
			ee = node::theNodes[*ia] ->degree();

			for ( ; ea != ee; ea++ )
				if (node::theNodes[(*ia)] ->getTarget(ea) == n)
					res++;

		}
		return res;
	}



			double statisticsNetwork::networkSize()
			{
				network::nodeList vl;
				network::verticesMatching(vl, _dynNode_);
				network::nodeIterator it;
				int counter = 0;
				for (it = vl.begin(); it != vl.end(); it++)
					counter++;

				return (double)counter;
			}







	class dijkstraCompare {

		public:
			static vector<baseType> weightMap;


		public:
			bool operator() ( const unsigned int  s1, const unsigned int s2 ) const { return weightMap[s1 - 1] < weightMap[s2 - 1]; }


	};

	void statisticsNetwork::printNodeStatistics()
	{
		nodeIterator it;
		nodeList vl;
		verticesMatching(vl,_dynNode_);
		verticesMatching(vl,_outNode_);
		verticesMatching(vl,_inNode_);

		for (it = vl.begin(); it != vl.end(); it++)
		{
			node::theNodes[ *it] ->printStatistics(cout, getGlobal<int>("nodeVerbosity"), getGlobal<int>("edgeVerbosity"));
			cout << endl;
		}
	}



	bool statisticsNetwork::isConnected()
	{
		if( isDirected() )
		{
			cout << "Warning! This network is directed. This function cannout make a statement about connectivity.";
			cout << "\n";
			return false;
		}

		network::nodeList vl;
		network::nodeIterator vi;
		verticesMatching(vl, _dynNode_ );
		unsigned	int n,i;
		n = vl.size();

		vector<unsigned int> connect;
		connect.resize(n);
		nodeDescriptor v,t;

		for (vi=vl.begin(); vi!=vl.end(); vi++)
		{
			connect[0]=1;
			for( i=1; i<n; i++)
			{
				connect[i]=0;
			}

			vector<unsigned int> Sub;
			Sub.push_back(*vi+1); // Knotennummern um +1 verschoben um nicht 0 zu pushen
			for( i=0; i<Sub.size(); i++)
			{
				v = Sub[i]-1;
				for( node::edgeDescriptor l=0; l<node::theNodes[v]->degree() ; l++)
				{
					t = node::theNodes[v]->getTarget(l);
					if (connect[ t - *vl.begin()] == 0)
					{
						connect[ t - *vl.begin() ] = 1;
						Sub.push_back(t+1);
					}
				}
			}

			if( n!=Sub.size() )
				return false;
		}
		return true;
	}




	baseType statisticsNetwork::meanDegree ()
	{
		baseType f= 0 ;
		network::nodeIterator ia;
		network::nodeList vl;
		network::verticesMatching ( vl,_dynNode_ );
		for ( ia = vl.begin(); ia != vl.end(); ia++ )
			f = f +node::theNodes[*ia] ->degree();
		f = f / network::numberVertices();
		return f;
	}



	baseType statisticsNetwork::meanWeight()
	{
		baseType f = 0.0;
		int degreeSum = 0;

		network::nodeIterator ia;
		network::nodeList vl;
		network::verticesMatching ( vl, _dynNode_ );
		clean();
		for ( ia = vl.begin(); ia != vl.end(); ia++ )
		{
			f = f + node::theNodes[*ia]->weightSum();
			degreeSum = degreeSum + node::theNodes[*ia]->degree();
		}
		f = f / degreeSum;
		return f;
	}


	vector<int> statisticsNetwork::outDegreeDistribution()
	{
		vector <int> res;

		unsigned int deg;

		network::nodeIterator ia;
		network::nodeList vl;
		network::verticesMatching ( vl,_dynNode_ );
		for ( ia = vl.begin(); ia != vl.end(); ia++ )

		{
			deg = node::theNodes[*ia]->degree();


			if ( deg +1 > ( res.size() ) )
				res.resize ( deg + 1, 0 );
			res[deg] = res[deg] + 1;
		}

		return res;
	}


	vector<unsigned int> statisticsNetwork::inDegreeDistribution()
	{
		vector <unsigned int> res;

		unsigned int deg;


		vector <int> inDegree;
		inDegree.resize ( network::numberVertices() );


		node::edgeDescriptor ea;
		node::edgeDescriptor ee;

		network::nodeIterator ia;
		network::nodeList vl;
		network::verticesMatching ( vl,_dynNode_ );
		for ( ia = vl.begin(); ia != vl.end(); ia++ )
		{
			ea = 0;
			ee = node::theNodes[*ia] ->degree();

			for ( ; ea != ee; ea++ )
				inDegree[node::theNodes[(*ia)] ->getTarget(ea)] ++;
		}


		for ( unsigned int i = 0; i < network::numberVertices();i++ )
		{
			deg = inDegree[i];

			if ( deg +1 > ( res.size() ) )
				res.resize ( deg + 1, 0 );
			res[deg] = res[deg] + 1;
		}

		return res;
	}


	baseType statisticsNetwork::meanClustering()
	{

		baseType f, linkedFriends= 0;

		network::nodeIterator ia;
		network::nodeList vl;
		network::verticesMatching ( vl,_dynNode_ );
		for ( ia = vl.begin(); ia != vl.end(); ia++ )
		{
			edgeIterator s,t;
			edgeList el;
			edgesBetween (el, *ia, _dynNode_);
			for (s = el.begin(); s != el.end();s++)
				for (t = el.begin(); t != el.end();t++)
					linkedFriends+= linkStrength (getTarget (*s), getTarget (*t)); 
	
			if ( el.size() > 1 )
				return ( baseType ) linkedFriends / ( el.size() * ( el.size() -1 ) );
		
			f = f + linkedFriends; 
		}
		f = f / network::numberVertices();
		return f;
	}




	void statisticsNetwork::degreeCentrality( string filename )
	{
		network::nodeIterator it;
		network::nodeList vl;
		verticesMatching(vl, _dynNode_);

		ofstream out (filename.c_str() );
		for( it = vl.begin(); it != vl.end(); it++)
			out << node::theNodes[*it]->degree() <<endl;

		out.close();
	}



vector<baseType> dijkstraCompare::weightMap;

	void statisticsNetwork::dijkstra( vector<baseType>& distance, network::nodeList vl, unsigned int v )
	{

		dijkstraCompare dC;
		relaxed_heap <nodeDescriptor, dijkstraCompare > theQueue (vl.size()+3, dC);
		dC.weightMap.resize(vl.size());

		unsigned int i;
		for( i=0 ; i<vl.size() ; i++ )
			dC.weightMap[i] = numeric_limits<baseType>::infinity();

		dC.weightMap[ v-*vl.begin() ]=0;

		nodeDescriptor j, k;
		double d;

		theQueue.push ( v+1 -*vl.begin() ); // um nicht 0 zu pushen sind die Knotennrn in theQueue um 1 verschoben

		while (!theQueue.empty())
		{
			j = theQueue.top()-1 +*vl.begin();
			theQueue.pop();

			for (node::edgeDescriptor l=0 ; l < node::theNodes[j]->degree() ; l++ )
			{
				k = node::theNodes[j]->getTarget(l); // alle Nachbarn k von j
				d = 1/(node::theNodes[j]->getWeight(l)); // d misst die Entfernung zwischen k und j

				if ( (dC.weightMap[ j-*vl.begin() ] + d) < dC.weightMap[ k-*vl.begin() ]  &&  dC.weightMap[ k-*vl.begin() ] == numeric_limits<baseType>::infinity() )
				{
					dC.weightMap[ k-*vl.begin() ] = dC.weightMap[ j-*vl.begin() ] + d;
					theQueue.push( k+1-*vl.begin() );
				}
				else if ( (dC.weightMap[ j-*vl.begin() ] + d) < dC.weightMap[ k-*vl.begin() ]  &&  dC.weightMap[ k-*vl.begin() ] < numeric_limits<baseType>::infinity() )
				{
					dC.weightMap[ k-*vl.begin() ] = dC.weightMap[ j-*vl.begin() ] + d;
					theQueue.update( k+1-*vl.begin() );
				}
			}
		}

		for( i=0 ; i<vl.size() ; i++)
			distance[i] = dC.weightMap[i];

	}




	baseType statisticsNetwork::meanPathLength() // funktioniert nur für komplett verbundene Netzwerke korrekt
	{
		network::nodeIterator vi;
		network::nodeList vl;
		verticesMatching(vl, _dynNode_);

		unsigned int i;
		double distSum=0;
		vector<baseType> distance;
		distance.resize(vl.size());

		for( vi=vl.begin() ; vi!=vl.end() ; vi++ )
		{
			dijkstra( distance, vl, *vi);
			for( i=0 ; i< vl.size() ; i++)
				distSum = distSum + distance[i];
		}

		return distSum / (vl.size()-1) / vl.size();
	}




	void statisticsNetwork::closenessCentrality ( string filename ) // funktioniert nur für komplett verbundene Netzwerke korrekt
	{

		nodeIterator vi;
		network::nodeList vl;
		verticesMatching(vl, _dynNode_);

		unsigned int i;
		double distSum;
		vector <double> CC (vl.size());


		vector<baseType> distance;
		distance.resize(vl.size());

		for( vi=vl.begin() ; vi!=vl.end() ; vi++ )
		{
			dijkstra( distance, vl, *vi );
			distSum=0;
			for ( i=0 ; i<vl.size() ; i++ )
				distSum = distSum + distance[i];

			CC[ *vi -*vl.begin() ] = (vl.size()-1) / distSum ;
		}

		ofstream out(filename.c_str());
		for( i=0 ; i<vl.size() ; i++)
			out << CC[i] << endl ;

	}





	void statisticsNetwork::betweennessCentrality( string filename )
	// uses the algorithm provided by U. Brandes in "A faster algorithm for betweenness Centrality",
	// J. Math. Sociol., 25:163-177, 2001
	{
		network::nodeIterator ia;
		nodeList vl;
		verticesMatching(vl, _dynNode_);
		unsigned int t;
		nodeDescriptor v, w;
		double d;
		vector <double> CB (vl.size()); // array CB[v] für alle v in n

		for ( t=0 ; t<vl.size() ; t++)
			CB[t]=0.0;

		list<int> S;
		vector < list<int> > P (vl.size());   // listen P[w] für jedes w aus n

		vector <double> sigma (vl.size());  // array sigma der Länge vl.size()

		dijkstraCompare dC;
		relaxed_heap < nodeDescriptor, dijkstraCompare > Q (vl.size()+3, dC); // queue Q
		dC.weightMap.resize(vl.size());

		vector <double> delta (vl.size());// array delta der Länge vl.size()

		for ( ia=vl.begin() ; ia!=vl.end() ; ia++ )
		{
			while(!S.empty())  // S leeren
				S.pop_back();

 			for ( t=0 ; t<vl.size() ; t++) // alle P[t] leeren
 				while( !P[t].empty() )
 					P[t].pop_back();

			for ( t=0 ; t<vl.size() ; t++ )
				sigma[t]=0;

			sigma[*ia -*vl.begin()]=1;

			for ( t=0 ; t<vl.size() ; t++ )
				dC.weightMap[t]=numeric_limits<baseType>::infinity();

			dC.weightMap[*ia -*vl.begin()]=0;

			while(!Q.empty()) // Q leeren
				Q.pop();

			Q.push( *ia+1 -*vl.begin() ); // +1 um nicht 0 zu pushen, daher sind die Knotennrn in Q um 1 verschoben

			while(!Q.empty())
			{
				v = Q.top()-1 +*vl.begin();
				Q.pop();

				S.push_back( v+1 -*vl.begin() );

				for ( node::edgeDescriptor l=0 ; l<node::theNodes[v]->degree() ; l++ ) //weightMap aktualisieren
				{
					w = node::theNodes[v]->getTarget(l); // alle Nachbarn w von v
					d = 1/( node::theNodes[v]->getWeight(l) ); // d misst die Entfernung zwischen w und v

					if ( dC.weightMap[w -*vl.begin()] == numeric_limits<baseType>::infinity() ) // zum ersten Mal entdeckt?
					{
						dC.weightMap[w -*vl.begin()] = dC.weightMap[v -*vl.begin()] + d;
						Q.push(w+1 -*vl.begin());
					}

					else if ( dC.weightMap[w -*vl.begin()] > (dC.weightMap[v -*vl.begin()] + d) && dC.weightMap[w -*vl.begin()] < numeric_limits<baseType>::infinity() )
					{
						dC.weightMap[w -*vl.begin()] = dC.weightMap[v -*vl.begin()] + d;
						Q.update(w+1 -*vl.begin());
					}
				}

				for ( node::edgeDescriptor l=0 ; l<node::theNodes[v]->degree() ; l++ ) // Prezedessoren checken
				{
					w = node::theNodes[v]->getTarget(l); // alle Nachbarn w von v
					d = 1/( node::theNodes[v]->getWeight(l) ); // d misst die Entfernung zw w und v

// hier soll auf gleichheit kontrolliert werden...
					if ( dC.weightMap[v -*vl.begin()] == dC.weightMap[w -*vl.begin()] + d ) // kürzester Weg nach v via w?
					{
						sigma[v -*vl.begin()] = sigma[v -*vl.begin()] + sigma[w -*vl.begin()];
						P[v -*vl.begin()].push_back(w+1 -*vl.begin()); // ggf w Prezedessor von v
					}
	// Ähnlichkeitsvergleich für d!= integer: relative Abweicheichung
					else if ( dC.weightMap[v -*vl.begin()] > dC.weightMap[w -*vl.begin()] )
					{
						double relativeError = 0.001;
						if( fabs(dC.weightMap[v -*vl.begin()] - dC.weightMap[w -*vl.begin()] - d) / dC.weightMap[v -*vl.begin()] < relativeError )
						{
							sigma[v -*vl.begin()] = sigma[v -*vl.begin()] + sigma[w -*vl.begin()];
							P[v -*vl.begin()].push_back(w+1 -*vl.begin()); // ggf w Prezedessor von v
						}
					}
				}
			}

			for ( t=0 ; t<vl.size() ; t++ )
				delta[t]=0;

			while(!S.empty())
			{
				w = S.back() -1;
				S.pop_back();

				while ( !P[w].empty() )
				{
					v = P[w].back() -1;
					P[w].pop_back();
					delta[v] = delta[v] + (1+delta[w])*sigma[v]/sigma[w];
				}

				if ( w != *ia  -*vl.begin())
					CB[w] = CB[w] + delta[w];
			}
		}

		for( t=0 ; t<vl.size() ; t++ ) // Normierung auf [0;1]
			CB[t] = CB[t] / vl.size() / (vl.size()-1);

		ofstream out(filename.c_str());

		for( t=0 ; t<vl.size() ; t++ ){
			out << CB[t] << endl ; }

		out.close();
	}



	unsigned int statisticsNetwork::countEdges (edgeVirtual * e)
	{
		edgeList el;
		edgesMatching (el, e->getEdgeInfo().theEdgeType);
		return el.size();
	}


   void statisticsNetwork::saveAdjacencyMatrix (string fileName)
	{
		nodeIterator vi;
		nodeIterator vj;
		nodeList vl;
		verticesMatching(vl, _dynNode_);

		ofstream out(fileName.c_str());

		for (vi = vl.begin(); vi != vl.end(); vi++)
	{
			for (vj = vl.begin(); vj != vl.end(); vj++)
			{
					out << linkStrength(*vi, *vj) << " ";
			}
			out << "\n";
	}
	}

	void statisticsNetwork::saveAdjacencyList(string fileName)
	{
		ofstream out(fileName.c_str());

		network::nodeIterator it;
		network::nodeList vl;
		verticesMatching(vl, _dynNode_);

		out << vl.size() << "\n";

		for( it = vl.begin(); it != vl.end(); it++)
			for( node::edgeDescriptor l=0; l<node::theNodes[*it]->degree() ;l++)
				if (isInsideNetwork(   getTarget (*it, l)	))
				out << *it <<' '<< node::theNodes[*it]->getTarget(l) <<' '<< node::theNodes[*it]->getWeight(l) <<"\n";


		out.close();
	}


	void statisticsNetwork::printAdjacencyList()
	{

		node::edgeDescriptor ea, ee;


//			out << "#source target weight\n";
		cout << node::theNodes.size()  << "\n";

		for (unsigned int i = 0; i < node::theNodes.size(); i++)
		{


			ea = 0;
			ee = node::theNodes[i] ->degree();


			for (; ea != ee; ea++)
			{
				// Ausgabe der Nodenummer:
				cout << i << " ";

				//Ausgabe der jeweiligen Edge
//				node::theNodes[i]->getEdge(ea)->printStatistics(cout,  network::edgeVerbosity());
				throw "statisticsNetwork::printAdjacencyList. repair me!";
				// ENDE
				cout << endl;
				/*
				cout << i << " "<<(*ea)->target->getNumber() << " ";
				if ((*ea)->getEdgeInfo().theEdgeKind & _weighted_)
					cout << ((weightedEdge*)(*ea))->getWeight() << "\n";
				else
					cout << "\n";
				*/

			}
		}

	}




	// Funktion für den Export nach GraphML


			void statisticsNetwork::saveGraphML(string fileName)
	{
		ofstream out(fileName.c_str());		// Datei für Export

		node::edgeDescriptor ea, ee;			// Iterator für die Edges
		int edge=0;

		//out << theNodes.size()  << "\n";	// gibt Anzahl der Nodes aus

		// Ausgabe header
		//
		out << "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n";
		out << "<graphml xmlns=\"http://graphml.graphdrawing.org/xmlns\"\n";
		out <<	'\t'<< "xmlns:xsi=\"http://www.w3.org/2001/XMLSchema-instance\"\n";
		out <<	'\t'<< "xsi:schemaLocation=\"http://graphml.graphdrawing.org/xmlns\n";
		out <<	'\t'<< '\t'<<"http://graphml.graphdrawing.org/xmlns/1.0/graphml.xsd\">\n";

		out << '\t' << "<graph id=\"Graph\" edgedefault=\"directed\">\n";

		// Erstelle nodes in Datei:

		for (unsigned int i = 0; i < node::theNodes.size(); i++)
		{
			out << '\t' << '\t' << "<node id=\"n"<< i << "\"/>\n";
		}

		// Erstelle edges in Datei:
		for (unsigned int i = 0; i < node::theNodes.size(); i++)
		{

			ea = 0;
			ee = node::theNodes[i]->degree();

			for (; ea != ee; ea++, edge++)
				out << '\t' << '\t' << "<edge id=\"e"<< edge << "\"\tsource=\"n" << i << '\"' << "\ttarget =\"n" << node::theNodes[i]->getTarget(ea) << "\"/>\n";
		}

		// Ausgabe footer
		//
		out << "\t</graph>\n" << "</graphml>";

	}

}
