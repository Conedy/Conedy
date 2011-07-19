

#include "cnnNode.h"



namespace conedy
{
	//! Deklaration der NodeDynamik
	/*!
		dx(t)/dt = -x(t) + Summe(gewichtete Nachbarn: Ausgabe) + Summe(gewichtete Nachbarn: Eingang)\n
		dot x_{ij}(t) = -x_{ij}(t) + \sum_{Nachbarn x_{ij}} (\alpha_{kl} y_{kl}) + \sum_{Nachbarn x_{ij}} (\beta_{kl} u_{kl}) + b_{ij}
	*/
	void cnnNode::operator() ( const baseType x[], baseType dxdt[] )
	{
		dxdt[0] = this->couplingSum() + ff() + bias() - x[0];
	}
	
	//! Registriert Standard-Parameter für die cnnNode:
	/*! 
		Diese Methode wird zu Programmbegin aufgerufen, um Speicherplatz für die Parameter zu reservieren.
		\param cnnNode_bias double, gibt den Schwellenwert für die Zelle an
		\param cnnNode_ff double, hier wird die feedforward-Kopplung (= Summe(Gewicht * Eingang der Nachbarn) =konst.) der Nachbarzellen gespeichert.
	*/
	void cnnNode::registerStandardValues()
	{
		// HOWTO: params<baseType>::registerStandard ( %enum Zellenname aus node.h%, "%Name für script%", %paramNummer%, %Std.Wert);
		params<baseType>::registerStandard ( _cnnNode_,"cnnNode_bias",0,0.0 );
		params<baseType>::registerStandard ( _cnnNode_,"cnnNode_ff",1,0.0 );
	}

	//! Gibt die Parameter der Zellen aus
	/*!
		Gibt die Parameter Bias und FF aus.
	*/
	void cnnNode::printStatistics()
	{
			cout << "bias=" << params<baseType>::getParams ( 0 ) << " ff="<<  params<baseType>::getParams ( 1 ) <<endl;
			params<baseType>::printStatistics();
			cout << "cnnNode" << endl; 
	}

		
	//! Gibt den Zelltyp zurück                          }
	/*!
		\return nodeInfo n = {_cnnNode_,_dynNode_,"cnnNode"};
	*/
	const nodeInfo cnnNode::getNodeInfo() 
	{
		nodeInfo n = {_cnnNode_,_dynNode_,"cnnNode"};
		return n;
	}



//
// Implementierung couplingSumNode
//

		
		//! Gibt den Zelltyp zurück
		/*!
			\return nodeInfo n = {_couplingSumNode_,_dynNode_};
		*/
		const nodeInfo couplingSumNode::getNodeInfo()
		{
			nodeInfo n = {_couplingSumNode_,_dynNode_,"couplingSumNode"};
			return n;
		}
	

		//! Action1 für die Integration
		/*!
			Es werden pro Intetrationsschritt nur die gewichteten Ausgänge der Nachbarn abgeholt und in den Temp-State geschrieben
		*/
		void couplingSumNode::operator()(baseType xprime [], baseType x[])
		{
			xprime[0] = couplingSum();
		}



}
