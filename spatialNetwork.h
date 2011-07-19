

#ifndef spatialNetwork_h
#define spatialNetwork_h spatialNetwork_h


#include "dynNetwork.h"

namespace conedy
{
		
	//! Basisklasse für verschiedene Funktionen, die Neuronenpositionen zurückgeben.
	class determineNodePositions
	{
		public:
			determineNodePositions() {};
			virtual vector <double> getNodePosition() = 0;
	};

	//! Funktionsklasse die 2-dimensional gleichverteilte Vektoren zurückgibt.
	class randomPositions : public determineNodePositions
	{
		public:
			randomPositions() {};
			virtual vector <double> getNodePosition()
			{
				vector <double> res(3);
				res[0] = gslNoise::getUniform(-0.5,0.5);
				res[1] = gslNoise::getUniform(-0.5,0.5);
				res[2] = 0.0;
				return res;
			}

	};
	//! Funktionsklasse, die (reihenweise) Vectoren auf einem Gitter zurückgibt
	class squareLatticePositions : public determineNodePositions
	{
		private:
			unsigned int sizex, sizey;
			unsigned int countx, county;


		public:
			squareLatticePositions(unsigned int sx, unsigned int sy) : sizex(sx), sizey(sy), countx(0), county(0) {};
			virtual vector <double> getNodePosition()
			{
				unsigned int size;
				if (sizex > sizey)
					size = sizex;
				else
					size = sizey;

				vector <double> res(3);
				res[0] = countx / ((double) size) - 0.5;
				res[1] = county / ((double) size) - 0.5;
				res[2] = 0.0;

				countx++;
				if (countx == sizex)
				{
					county++;
					countx = 0;
					if (county == sizey)
					{
						county = 0;
					}
				}
				return res;
			}

	};

	//! Netzerk, das zusätzlich zu den Verbindungen 3-dimensionale Koordinaten für jeden Knoten speichert. Wird unter anderem für neuro3d verwendet.
	class spatialNetwork : public dynNetwork
	{


		private:

			determineNodePositions *nodePositioner;

		public:
			double rectSize;


			typedef vector<double> pos;
			typedef vector <pos> nodePositions;
			nodePositions nodePos;


			spatialNetwork() : nodePositioner(NULL) {};


			void connectCloseNodes( node * source, node *target, baseType dist, edgeBlueprint * l);
			void connectCloseNodesTorus( node * source, node *target, baseType dist, edgeBlueprint * l);


			baseType torifyDistance(baseType d)
			{
				if (abs(d) < abs(1.0-abs(d)))
					return d;
				else	
					return abs(1.0 - abs(d));

			}

			baseType euclidianDistanceTorus(nodeDescriptor node1, nodeDescriptor node2)
			{

				pos diff(3);
				diff[0] = torifyDistance((nodePos[node1][0] - nodePos[node2][0]));
				diff[1] = torifyDistance((nodePos[node1][1] - nodePos[node2][1]));
				diff[2] = torifyDistance((nodePos[node1][2] - nodePos[node2][2]));

				return diff[0] * diff[0] + diff[1] * diff[1] + diff[2] * diff[2];
			}
			

			baseType euclidianDistance(nodeDescriptor node1, nodeDescriptor node2)
			{
				pos diff(3);
				diff[0] = (nodePos[node1][0] - nodePos[node2][0]);
				diff[1] = (nodePos[node1][1] - nodePos[node2][1]);
				diff[2] = (nodePos[node1][2] - nodePos[node2][2]);

				return diff[0] * diff[0] + diff[1] * diff[1] + diff[2] * diff[2];

			}
			void useRandomPositioning()
			{
				if (nodePositioner == NULL)
					nodePositioner = new randomPositions ();
				rectSize = 0.99 / 100;
					
			}

			void useLatticePositioning(unsigned int sizex, unsigned int sizey)
			{
				if (nodePositioner == NULL)
					nodePositioner = new squareLatticePositions(sizex,sizey);
				if (sizex > sizey)
					rectSize = 0.99 / sizex;
				else
					rectSize = 0.99 / sizey;
			}


			
	//		virtual nodeDescriptor addNode();					
			//! fügt eine Kopie von *n zum Netzwerk hinzu, gibt die Nummer vom neuen Knoten zurück.
			virtual nodeDescriptor addNode ( nodeBlueprint *n );				

/*			void randomize ( vector<pos> &theNodePos, double sigma )
			{
				uniform<double> rn ( -sigma,sigma );
				pos newPos ( 3 );

				for ( unsigned int i = 0; i < theNodePos.size(); i++ )
				{
//				cout << "Vorher:" << theNodePos[i][0] << endl;
					newPos[0]  = rn();
					newPos[1]  =rn();
					newPos[2] = rn();
//				cout << newPos[0] << ":" << endl;

//				theNodePos[i]= theNodePos[i] + newPos;
//				cout << "Nachher:" << theNodePos[i][0] << endl;
				}
			}
			void circle ( vector <pos> &theNodePos )
			{
				unsigned int N = nodePos.size();
				for ( unsigned int i=0;i<N;i++ )
				{
					nodePos[i][0]=cos ( ( 2.0* ( double ) i*M_PI/ ( double ) N ) );
					nodePos[i][1]=sin ( ( 2.0* ( double ) i*M_PI/ ( double ) N ) );
					nodePos[i][2]=0.0;
				}
			}
			void squareLattice ( vector <pos> &theNodePos )
			{
				unsigned int N = ( unsigned int ) sqrt ( nodePos.size() );
				//			cout << "Groesse:" << N << endl;
				for ( unsigned int i = 0; i < N ; i++ )
					for ( unsigned int j = 0; j < N ; j++ )
					{
						theNodePos[i+N*j][0] = i/ ( ( double ) N ) - 0.5;
						theNodePos[i+N*j][1] = j/ ( ( double ) N ) - 0.5;
						theNodePos[i+N*j][2] = 0;
					}

				rectSize = 0.99/N;
				cout << "Lattice Fertig " << endl;
			}
			void randomPos ( vector <pos> &theNodePos )
			{
				uniform<double> rn ( -0.5,0.5 );

				for ( unsigned int i = 0; i < network::numberVertices(); i++ )
				{
					nodePos[i][0] = rn();
					nodePos[i][1] = rn();
					nodePos[i][2] = rn();
				}

				rectSize = 0.99/network::numberVertices();
				cout << "Lattice Fertig " << endl;
			}
*/
	};		











};

#endif
