

#ifndef cnnNode_h
#define cnnNode_h cnnNode_h

#include "stdOdeIntegrator.h"
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
 *		1. Verwendung einer Ü-Fkt in "swap() = f(tmp[0])" (veraltet)\n
 *		2. Verwendung von weightedEdges -> Überladen von "virtual baseType getTargetState()" aus edge.h \n
 *	\n
 *	
 *	Bias und Feedforward: \n
 *	- Der Bias b ist für alle Zellen gleich \n
 *	- Die Feedforward-Kopplung Σ(β_kl u_kl)= Summe(Gewichte * Eingänge der Nachbarn) ist konstant und wird daher einmalig im ersten Schritt berechnet. Danach erhalten die Zellen einen individuellen zusätzlichen "Bias" ff, der die Summe enthält.
*/
class cnnNode: public stdOdeIntegrator
{
	private:
		// Inline-Funktionen zum einfacheren Aufruf der Parameter
		inline baseType bias() {return params<baseType>::getParams ( 0 );}	//!< Parameter-Getter für Bias
		inline baseType ff() {return params<baseType>::getParams ( 1 );}	//!< Parameter-Getter für FeedForward
		
	public:
		// Konstruktor der 1-dim-Node
		cnnNode() :stdOdeIntegrator (_cnnNode_ ){}

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
		couplingSumNode() : mapNode(_couplingSumNode_){}

		//! Gibt den Zelltyp zurück
		virtual const nodeInfo getNodeInfo();
	
		//! Gibt die Dimension der Node zurück
		virtual const unsigned int dimension() const { return 1;}

		//! Action1 für die Integration
		void operator()(baseType xprime [], baseType x[]);

		//! Clean macht genau nichts.
		virtual void clean ( unsigned int timeSteps ) {};
};

} // ende namespace >conedy<

#endif
