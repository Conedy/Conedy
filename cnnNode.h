

#ifndef cnnNode_h
#define cnnNode_h cnnNode_h

#include "gslOdeIntegrator.h"
#include "baseType.h"
#include "sdeNode.h"
#include "mapNode.h"
#include <boost/function.hpp>


#include <complex>
#include <stdio.h>
#include <cmath>


namespace conedy
{

// letzte Modifikation:	23.11.2010	hdickten:	Aufgeräumt

/*! \brief CNN-Node Basisklasse
 *
 *
 *  In dieser Klasse befindet sich die Definiton einer CNN-Zelle: \n
 *
 *	Eingang u=                __________________ \n
 *	α_kl*y_kl + β_kl*u_kl ---|Status x_ij[0](t) \ \n
 *	                         |FeedForward ff     >---	Ausgang y_ij \n
 *	Bias b:               ---|__________________/		mittels \n Übertragungsfunktion y_ij=f(x_ij(t)) \n
 * \n
 *	Die Übertratungsfunktion kann über zwei Wege realisiert werden: \n
 *		1. Verwendung einer Ü-Fkt in "swap() = f(x[0])" (veraltet)\n
 *		2. Verwendung von weightedEdges -> Überladen von "virtual baseType getTargetState()" aus edge.h \n
 *	\n
 *	
 *	Bias und Feedforward: \n
 *	- Der Bias b ist für alle Zellen gleich \n
 *	- Die Feedforward-Kopplung Σ(β_kl u_kl)= Summe(Gewichte * Eingänge der Nachbarn) ist konstant und wird daher einmalig im ersten Schritt berechnet. Danach erhalten die Zellen einen individuellen zusätzlichen "Bias" ff, der die Summe enthält.
*/
class cnnNode: public gslOdeNode
{
	private:
		// Inline-Funktionen zum einfacheren Aufruf der Parameter
		inline baseType bias() {return params<baseType>::getParams ( 0 );}	//!< Parameter-Getter für Bias
		inline baseType ff() {return params<baseType>::getParams ( 1 );}	//!< Parameter-Getter für FeedForward
		
	public:
		// Konstruktor der 1-dim-Node
		cnnNode() :gslOdeNode (_cnnNode_ , 1){}

		//! Gibt die Dimension (1) zurück
		virtual const unsigned int dimension() const { return 1;}
		
		//! Deklaration der NodeDynamik
		virtual void operator() ( const baseType x[], baseType dxdt[] );
		
		//! Gibt den Zelltyp zurück
		virtual const nodeInfo getNodeInfo();

		//! Registriert Standard-Parameter für die cnnNode:
		static void registerStandardValues();
		
		//! Gibt die Parameter der Zellen aus
		virtual void printStatistics();
};


/*!	\brief Hilfsnode für Berechnung des FeedForward:
 *
 *	Diese Nodes sind Nodes, die nur die Ausgaben aller Nachbarn sammeln und ausgeben.\n
 *	Sie werden vor der Simulation einmal verwendet und ihre Ausgabe entspricht direkt dem ff-Anteil der cnnNodes und kann mit der Funktion
 *	\p m.readParams("cnnNode_ff","feedforward.txt"); eingelesen werden.
 */ 
class couplingSumNode: public mapNode
{
	public:

		//! Leerer Konstruktor der 1-dim. Node
		couplingSumNode() : mapNode(_couplingSumNode_, 1){}

		//! Gibt den Zelltyp zurück
		virtual const nodeInfo getNodeInfo();
	
		//! Gibt die Dimension der Node zurück
		virtual const unsigned int dimension() const { return 1;}

		//! Action1 für die Integration
		void operator()(baseType xprime [], baseType x[]);

		//! Clean macht genau nichts.
		virtual void clean () {};
};

} // ende namespace >conedy<




// #### Definition cnnStd ###################################################################
/* Definition eines StandardCNN mit %sizex% x %sizey% mit Nachbarschaften aus %params%:
	/  params: "params_a": enthält die Koordinaten und Gewichte für Nachbarschaft. z.B.:
	/
	/	"-3	-4	0.8"
	/
	/	entspricht:
	/	Die Zelle 3 nach links, 4 nach unten ist mit 0.8 in aktuelle Zelle gekoppelt:
	/
	/	# # # # # #	Syntax:
	/	# +---> baseType #
	/	# | # # # #	"addWeightedEdge ( nodeDescriptor source, nodeDescriptor dest, double weight);"
	/	# | # # # #
	/	# | # # # #
	/	# S # # # #
	/	# # # # # #
	/
	*/




// Definition eines Standard-CNN-Netzwerkes (Polynomial gewichtet) mit Zyklischen Randb.: geschlossene Spirale+1 in x-Richtung und y-Richtung


void createNetwork::cnnStd ( int sizex, int sizey, string parameter, nodeBlueprint *n, edgeBlueprint *l )
{




	//cout << ((cnnNode<baseType>*) n )-> row << endl;
	ifstream in ( parameter.c_str() );		// liest Datei %parameter% ein


	// Erstelle Grundgitter mit %sizex% x %sizey% = j x i
	//
	for ( int i=0; i< sizey; i++ )			// i Zeilen
	{
		for ( int j = 0; j < sizex; j++ )	// j Spalten
		{
			addNode ( n );
		}
	}

	int distx, disty;	// Abstand Source->Target x und y
	double weight;		// Kopplungsgewicht
	int source;		// Zellennummer der Quellzelle, die in die Zielzelle einkoppeln soll

	// Auslesen der Koordinaten / Gewichte der Nachbarn bis EOF (peek() != -1)
	//
	while ( in.peek() != -1 )
	{
		string linebuffer;
		vector <baseType> buffer;

		in >> distx;
		in >> disty;

		// Einlesen der Gewichte (1. bis n. Ordnung):
		getline ( in,linebuffer );

		// zerlegen des Puffers:
		istringstream isstr ( linebuffer );

		// Einlesen der Einzelgewichte für m. Koordinate in Vector buffer

		while ( isstr.peek() != -1 )
		{
			isstr >> weight;
			buffer.push_back ( weight );
		}


		if ( in.eof() )
			break;

		// Spirale in x - Zyklisch in y:
		for ( int j = 0; j < sizex; j++ )		// Zellen in x-Richtung durchlaufen
			for ( int i = 0; i < sizey; i++ )	// Zellen in y-Richtung durchlaufen
			{
				// Zellennummer der aktuellen Zelle = i*sizex + j
				// -> neu	= alt + distx	+ disty*sizex
				source 		= i*sizex + j 	+ distx + disty*sizex;
				/*
					while ( source<0 )
					source = source + ( sizex*sizey );
					while ( source> ( sizex*sizey-1 ) )
					source = source - ( sizex*sizey );
					*/
				while ( source<0 )
					source = source + ( sizex*sizey -1);
				while ( source> ( sizex*sizey-1 ) )
					source = source - ( sizex*sizey -1);


				// Füge Verbindung hinzu:
				// source = siehe oben
				// target = aktuelle Zelle = i * sizex + j

				// Fall: edge polynomial:
//				if ( l->getEdgeInfo().theEdgeKind & _polynomial_ )
//				{
//					( ( weightedPolyEdge* ) l )->setWeight (buffer);
//				}

				// Fall: edge weighted:
				if ( l->getEdgeInfo().theEdgeKind & _weighted_ )
				{
					  l ->setWeight ( buffer.at(0) );
				}

				//network::addEdge ( source, i*sizex + j, l );
				network::addEdge ( i*sizex + j, source, l );
			}
	} // Auslesen ENDE

	in.close();

} // ENDE cnnStd


// Definition eines cnn-Netzwerkes (Polynomial gewichtet) mit NEUTRALEN RANDBEDINGUNGEN
//
void createNetwork::cnnNeutral ( int sizex, int sizey, string params, nodeBlueprint *n, edgeBlueprint *l )
{
	ifstream in ( params.c_str() );		// liest Datei %params% ein

	// Erstelle Grundgitter mit %sizex% x %sizey% = j x i
	//
	for ( int i=0; i< sizey; i++ )			// i Zeilen
	{
		for ( int j = 0; j < sizex; j++ )	// j Spalten
		{
			addNode ( n );
		}
	}

	int distx, disty;	// Abstand Source->Target x und y
	double weight;		// Kopplungsgewicht
	int source;		// Zellennummer der Quellzelle, die in die Zielzelle einkoppeln soll

	// Auslesen der Koordinaten / Gewichte der Nachbarn bis EOF (peek() != -1)
	//
	while ( in.peek() != -1 )
	{
		string linebuffer;
		vector <baseType> buffer;

		in >> distx;
		in >> disty;

		// Einlesen der Gewichte (1. bis n. Ordnung):
		getline ( in,linebuffer );

		// zerlegen des Puffers:
		istringstream isstr ( linebuffer );

		// Einlesen der Einzelgewichte für m. Koordinate in Vector buffer

		while ( isstr.peek() != -1 )
		{
			isstr >> weight;
			buffer.push_back ( weight );
		}


		if ( in.eof() )
			break;

		// Neutrale Randbedingung
		for ( int j = 0; j < sizex; j++ )		// Zellen in x-Richtung durchlaufen
			for ( int i = 0; i < sizey; i++ )	// Zellen in y-Richtung durchlaufen
			{
				// Zellennummer der aktuellen Zelle = i*sizex + j
				// -> neu	= alt + distx	+ disty*sizex
				source 		= i*sizex + j 	+ distx + disty*sizex;

				// Prüfung, ob source-Zelle noch innerhalb CNN:
				if ( ( i+disty>=sizey ) || ( i+disty<0 ) )
					continue;
				if ( ( j+distx>=sizex ) || ( j+distx<0 ) )
					continue;

				// Wenn im Bereich: füge Verbindung hinzu:
				// source = siehe oben
				// target = aktuelle Zelle = i * sizex + j

				// Fall: edge polynomial:
				if ( l->getEdgeInfo().theEdgeKind & _polynomial_ )
				{
					( ( weightedPolyEdge* ) l )->setWeight (buffer);
				}

				// Fall: edge weighted:
				else if ( l->getEdgeInfo().theEdgeKind & _weighted_ )
				{
					( l )->setWeight ( buffer.at(0) );
					//( ( weightedEdge* ) l )->setWeight ( buffer.at ( 0 ) );
				}
				//	network::addEdge ( source, i*sizex + j, l );
				network::addEdge ( i*sizex + j, source, l );
			}
	} // Auslesen ENDE

	in.close();

} // ENDE cnnNeutral



#endif
