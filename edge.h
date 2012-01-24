

#ifndef edge_h
#define edge_h edge_h

#include <boost/function.hpp>
#include <iostream>
#include <boost/bind.hpp>
#include "params.h"
#include "dynNode.h"

#include "gslNoise.h"
//	Letzte Änderung:	27.07.2009	hdickten:	weightedEdgeVirtual: weightedEdgeVirtual hinzugefügt!

using namespace std;


#include "node.h"
#define Getarget(type,pointer) (bind(&expression<type>::evaluate,(pointer)))





namespace conedy
{


	//! gewichtete Edge, bei der das Kopplungsgewicht in einer privaten Variable gespeichert wird
	template <typename EDGE>
		class weightedEdge : public EDGE
	{
		private:  // private

			baseType weight;

		public:
			weightedEdge() :  weight ( ( baseType ) 1 ) {};
			weightedEdge(baseType w) : weight (w) {};
			weightedEdge (nodeDescriptor targetNumber, baseType newWeight) : EDGE (targetNumber), weight(newWeight) {};

			const edgeInfo getEdgeInfo() {edgeInfo ei = {_weightedEdge_,_weighted_,"weightedEdge"};return ei;}
			baseType getWeight() { return weight; }
			//			baseType getTargetState();
			void setWeight(baseType newWeight) { weight = newWeight; }


			void setParameter(vector < baseType > parameter)
			{
				EDGE::setParameter(parameter);
				if (parameter.size() == 0)					return ;  // not all parameter have been specified. Stopping.
				weight = parameter[parameter.size() -1];
				parameter.pop_back();
			}
			void getParameter(vector < baseType > &parameter)
			{
				cout <<"getParameter of weighetdEdge called";
				EDGE::getParameter(parameter);
				parameter.push_back(weight);
			}

			edgeVirtual *construct() { return new weightedEdge<EDGE> ( *this ); };

			ostream& printStatistics ( ostream &os, double edgeVerbosity) 
			{
				edgeInfo ei = getEdgeInfo();
				edge::printStatistics(os, edgeVerbosity, ei.theEdgeKind, ei.theEdgeName,  getWeight());
				return os;
			}



	};

	typedef weightedEdge < edgeVirtual > weightedEdgeVirtual;


	//   template <typename EDGE>
	//	baseType weightedEdge<EDGE>::getTargetState() { return EDGE::getTarget()->getState(    ) ; }

	//! edge,
	template <typename EDGE>
		class staticWeightedEdge : public EDGE
	{
		public:  // private
			static baseType weight;

		public:
			staticWeightedEdge() {};
			//			staticWeightedEdge ( node* t ) : weightedEdge(t) {};
			staticWeightedEdge (baseType newWeight)  {    weight = newWeight;};

			staticWeightedEdge (nodeDescriptor targetNumber, baseType newWeight) : EDGE (targetNumber)  {    weight = newWeight;};
			const edgeInfo getEdgeInfo() {edgeInfo ei = {_staticWeightedEdge_,_weighted_,"staticWeightedEdge"}; return ei;}
			baseType getWeight() { return weight; }
			void  setWeight(baseType newW) { weight = newW; }
			//			baseType getTargetState() { return EDGE::getTarget()->getState (); }
			edgeVirtual *construct() { return new staticWeightedEdge ( *this ); };

			ostream& printStatistics ( ostream &os, double edgeVerbosity) 
			{
				edgeInfo ei = getEdgeInfo();
				edge::printStatistics(os, edgeVerbosity, ei.theEdgeKind, ei.theEdgeName,  getWeight());
				return os;
			}

			void getParameter(vector < baseType > &parameter)
			{
				EDGE::getParameter(parameter);
				parameter.push_back(weight);
			}
			void setParameter(vector < baseType > parameter)
			{
				EDGE::setParameter(parameter);
				if (parameter.size() == 0)					return ;  // not all parameter have been specified. Stopping.
				weight = parameter[parameter.size() -1];
				parameter.pop_back();
			}




	};



	template <class EDGE>
		class staticComponent: public EDGE
	{
		static unsigned int which;
		public:


		staticComponent ( int c) {  which = c;}
		staticComponent ( )  { which = 0;}

		const edgeInfo getEdgeInfo() {
			edgeInfo ancestor = EDGE::getEdgeInfo();
			edgeInfo ei = {_staticComponent_,_weighted_ | ancestor.theEdgeKind, ancestor.theEdgeName + "_staticComponent" }; return ei;
		}

		baseType getTargetState()
		{
			return (  (dynNode*)  ( EDGE::getTarget() ) ) ->getState(which)   ;

		}
		edgeVirtual *construct() {
			return new staticComponent( *this );
		};

		void getParameter(vector < baseType > &parameter)
		{
			EDGE::getParameter(parameter);
			parameter.push_back(which);
		}

		void setParameter(vector < baseType > parameter)
		{
			EDGE::setParameter(parameter);
			if (parameter.size() == 0)					return ;  // not all parameter have been specified. Stopping.
			which = parameter[parameter.size() -1];        
			parameter.pop_back();
		}



	};


	typedef staticWeightedEdge < edgeVirtual > staticWeightedEdgeVirtual;


	template <typename EDGE>
		baseType staticWeightedEdge<EDGE>::weight;

	template <typename EDGE>
		unsigned int staticComponent<EDGE>::which;

	//! Template-Klasse für Edges mit polinomiellen-Gewichten (vector < baseType >)
	class weightedPolyEdge : public edgeVirtual
	{
		public:
			weightedPolyEdge()  {};
			weightedPolyEdge ( nodeDescriptor targetNumber) : edgeVirtual (targetNumber) {};

			const edgeInfo getEdgeInfo() 
			{
				edgeInfo ei = {_weightedEdge_,_polynomial_};
				return ei;
			}

			// void printStatistics() = 0;

			virtual void setWeight(vector<baseType> newWeight) = 0;
			virtual baseType getWeight()= 0;

			edgeVirtual *construct()= 0;
	};


	//! Verbindungsklasse, die das Kopplungsgewicht statisch speichert. Damit haben alle Edges dieses Typs dasselbe Gewicht und verbrauchen nicht so viel Speicherplatz

	/*	class staticWeightedEdge : public weightedEdge
		{
		public:  // private

		static baseType weight;

		public:
		staticWeightedEdge() {};
	//			staticWeightedEdge ( node* t ) : weightedEdge(t) {};
	const edgeInfo getEdgeInfo() {edgeInfo ei = {_staticWeightedEdge_,_weighted_}; return ei;}
	void printStatistics()
	{
	cout << "("<< edge<baseType>::target->getNumber() << "," << weight << ");";

	}
	baseType getWeight() { return weight; }
	void  setWeight(baseType newW) { weight = newW; }
	baseType getTargetState() { return getTarget()->getState () * weight; }

	edge *construct() { return new staticWeightedEdge ( *this ); };
	//			 ~staticWeightedEdge() { cout << "Edge Destruktor called!" << endl; }

	// Überladung des Ausgabestreams
	ostream& printStatistics ( ostream &os, double edgeVerbosity)
	{
	// Ausgabe Header:
	edge::printStatistics(os);

	// Ausgabe Kind, Name
	if (edgeVerbosity>=1)
	{
	edgeInfo ei = getEdgeInfo();

	os << "EdgeKind = " << ei.theEdgeKind << "\t";
	os << "EdgeName = " << ei.theEdgeName << "\t";
	}	

	// Ausgabe Gewicht
	os << weight;

	return os;
	}
	};
	*/


	template <class EDGE>
		class randomTarget : public EDGE
	{
		private:
			nodeDescriptor lower;
			nodeDescriptor upper;

		public:
			const edgeInfo getEdgeInfo() {
				edgeInfo ancestor = EDGE::getEdgeInfo();
				edgeInfo ei = {_randomTarget_,_weighted_ | ancestor.theEdgeKind,  ancestor.theEdgeName + "_randomTarget"};  return ei;
			}


			void getParameter(vector < baseType> & parameter)
			{
				EDGE::getParameter(parameter);
				parameter.push_back(lower);
				parameter.push_back(upper);
			}

			void setParameter(vector < baseType > parameter)
			{
				EDGE::setParameter(parameter);
				if (parameter.size() == 0)					return ;  // not all parameter have been specified. Stopping.
				lower = parameter[parameter.size() -1];
				parameter.pop_back();
				upper = parameter[parameter.size() -1];
				parameter.pop_back();
			}





			dynNode* getTarget() { return  (dynNode*)  node::theNodes[gslNoise::getUniform(lower,upper)]; }
			randomTarget(nodeDescriptor l, nodeDescriptor u) : lower(l), upper(u) { }
			randomTarget() { }
			edgeVirtual *construct() { return new randomTarget<EDGE> ( *this ); };

	};


	//! gewichtete Edge, die das Kopplungsgewicht mit Param speichert
	/*	class weightedEdgeParams : public weightedEdge, public params<baseType>
		{
		public:  // private



		static void registerStandardValues()
		{
		params<baseType>::registerStandard ( _weightedEdgeParams_,"weightedEdgeParams",0,1.0 );
		}
		public:

		void setWeight(baseType newWeight)
		{
		vector <baseType> n;
		n.push_back(newWeight);
		if (params<baseType>::isStandard())
		rerouteParams(n);
		else	
		setParams(0,newWeight);
		}

		weightedEdgeParams() :params<baseType>(_weightedEdgeParams_) {};
	//			weightedEdgeParams ( node* t, baseType w ) : weightedEdge(t) {};
	const edgeInfo getEdgeInfo() {edgeInfo ei = {_weightedEdgeParams_,_weighted_}; return ei;}

	void printStatistics()
	{
	cout << "("<< edge<baseType>::target->getNumber() << "," << params<baseType>::getParams(0) << ");";

	}

	baseType getWeight() { return params<baseType>::getParams(0); }

	//			 baseType getTargetState() { return edge::target->getState() * params<baseType>::getParams(0); }
	edge *construct() { return new weightedEdgeParams ( *this ); };
	//			 ~weightedEdgeParams() { cout << "Edge Destruktor called!" << endl; }

	// Überladung des Ausgabestreams
	//
	//
	//



	ostream& printStatistics ( ostream &os, double edgeVerbosity) 
	{
	edgeInfo ei = getEdgeInfo();
	edge::printStatistics(os, edgeVerbosity, ei.theEdgeKind, ei.theEdgeName,  getWeight());
	return os;
	}



	};
	*/
	//! edge-Klasse, die nur States weitergibt, wenn sie einin bestimmten Wert überschreiten.
	template <class EDGE>
		class stepEdge: public EDGE
	{
		double threshold;
		public:
		stepEdge ( double t ) : threshold ( t )  {};
		stepEdge ( ){};
		const edgeInfo getEdgeInfo() {
			edgeInfo ancestor = EDGE::getEdgeInfo();
			edgeInfo ei = {_pulseCouple_,_weighted_ | ancestor.theEdgeKind,  ancestor.theEdgeName + "_step"};  return ei;}
			void setParameter(vector < baseType >& parameter)
			{
				EDGE::setParameter(parameter);
				if (parameter.size() == 0)					return ;  // not all parameter have been specified. Stopping.
				threshold = parameter[parameter.size() -1];
				parameter.pop_back();
			}

			baseType getTargetState()
			{
				if ( EDGE::getTargetState()  >= threshold )
					return 1;
				else
					return 0;
			}
			edgeVirtual *construct() { return new stepEdge<EDGE> ( *this ); };


			/* void printStatistics()
				{
				cout << "(stepEdge,";
				weightedEdgeVirtual<baseType>::printStatistics();
				}*/

			// Überladung des Ausgabestreams
			//
			//
			//

			ostream& printStatistics ( ostream &os, double edgeVerbosity) 
			{
				edgeInfo ei = getEdgeInfo();
				edge::printStatistics(os, edgeVerbosity, ei.theEdgeKind, ei.theEdgeName,  EDGE::getWeight());
				return os;
			}


	};

	//! edge-Klasse, die auf die die Einträge von x zeigt.


	template <class EDGE>
		class component: public EDGE
	{
		unsigned int which;

		public:

		void setParameter(vector < baseType > parameter)
		{
			EDGE::setParameter(parameter);
			if (parameter.size() == 0)					return ;  // not all parameter have been specified. Stopping.
			which = parameter[parameter.size() -1];
			parameter.pop_back();
		}

		component ( int c) :  which ( c ) {}
		component ( ) :  which ( 0 ) {}

		const edgeInfo getEdgeInfo() {
			edgeInfo ancestor = EDGE::getEdgeInfo();
			edgeInfo ei = {_component_,_weighted_ | ancestor.theEdgeKind, ancestor.theEdgeName + "_component" }; return ei;
		}

		baseType getTargetState()
		{
			return (  (dynNode*)  ( EDGE::getTarget() ) ) ->getState(which)   ;

		}
		edgeVirtual *construct() {
			return new component( *this );
		};





	};

	//! Edge mit Pulsekopplung und delay
	class pulsecoupleDelayEdge: public weightedEdgeVirtual
	{
		double threshold;
		int nextFiring;
		int timeDelay;
		public:
		pulsecoupleDelayEdge ( double th, double tD ) : threshold ( th ), timeDelay ( tD )  {};
		const edgeInfo getEdgeInfo() {edgeInfo ei = {_pulsecoupleDelayEdge_,_weighted_}; return ei;}
		baseType getTargetState()
		{
			if ( nextFiring == 0 )
			{
				if ( weightedEdgeVirtual::getTargetState() >= threshold )
					nextFiring = timeDelay;
				return 0;
			}
			else
			{
				if ( nextFiring == 1 )
				{
					nextFiring--;
					return this->getWeight();
				}
				else
				{
					nextFiring--;
					return 0;
				}
			}
		}
		edgeVirtual *construct() { return new pulsecoupleDelayEdge ( *this ); };


		/* void printStatistics()
			{
			cout << "(pulsecoupleDelayEdge,";
			weightedEdgeVirtual<baseType>::printStatistics();
			}*/

		// Überladung des Ausgabestreams
		//
		//

		ostream& printStatistics ( ostream &os, double edgeVerbosity) 
		{
			edgeInfo ei = getEdgeInfo();
			edge::printStatistics(os, edgeVerbosity, ei.theEdgeKind, ei.theEdgeName,  getWeight());
			return os;
		}
	};




	/*	template <typename baseType>
		class kuramotoEdge : public weightedEdgeVirtual<baseType>
		{
		private:
		public:
		kuramotoEdge ()  {};

		const edgeInfo getEdgeInfo() {edgeInfo ei = {_kuramotoEdge_,_weighted_}; return ei;}

		baseType getTargetState()
		{
		return weightedEdge<baseType>::weight * sin ( ( weightedEdge<baseType>::target->state - weightedEdge<baseType>::source->state ) );
		}
		void printStatistics()
		{
		cout << "(kuramotoEdge,";
		weightedEdge<baseType>::printStatistics();
		}
		edge<baseType> *construct() { return new  kuramotoEdge<baseType> ( *this ); };
		};
		*/

	//! Edge mit Delay
	class delayEdge : public weightedEdgeVirtual
	{
		vector <baseType> memory;
		int delay;
		int counter;

		public:

		const edgeInfo getEdgeInfo() {edgeInfo ei = {_delayEdge_,_weighted_}; return ei;}
		delayEdge ( int d ) : memory ( d+1 ), delay ( d ), counter ( 0 ) {};
		baseType getTargetState()
		{
			memory[counter] = weightedEdgeVirtual::getTargetState();
			counter++;
			if ( counter == delay +1 )
				counter = 0;
			return memory[counter];
		}
		edgeVirtual *construct() { return new delayEdge ( *this ); };

		// Überladung des Ausgabestreams
		ostream& printStatistics ( ostream &os, double edgeVerbosity)
		{
			// Ausgabe Header:
			//
			//
			//
			edgeInfo ei = getEdgeInfo();
			edge::printStatistics(os, edgeVerbosity, ei.theEdgeKind, ei.theEdgeName,  getWeight());

			if (edgeVerbosity>=2)
			{
				os << "delay = " << delay << "\t";
				os << "counter = " << counter << "\t";
				os << "size(memory) = " << memory.size() << "\t";
			}


			// Ausgabe Gewicht
			os << this->getWeight();

			return os;
		}
	};




	/*! \brief Definition einer weightedEdge mit Sigmoidaler Ausgabefunktion mit Ordnung 3 (by HD)
	 * 
	 *	Diese Edge holt den Status der Nachbarzelle ab und gibt diese sigmoidal an die Zielzelle aus. \n
	 *	LaTeX: \operatorname{sig}(t) = \frac{1}{1 + e^{-\beta t}} \n
	 *
	 *	Die Zellen koppeln dabei mit der Ordnung 3 in die Nachbarzelle ein.
	 */
	class stdEdgeOrd3 : public weightedPolyEdge
	{
		baseType	a, b, c;			//!< Gewichte ax +bx² + cx³

		public:
		//! Konstruktor mit beta = 4 Std, a = 1, b = c = 0.
		stdEdgeOrd3 ( ) {a = 1; b = 0; c = 0;};		

		/*! Konstruktor mit beta = b
		 * \param beta int: Gibt die Flankensteilheit an
		 */ 
		//stdEdgeOrd3 ( int b ) : beta ( b ) {};	
		//! Gibt die Kanteninfo zurück
		/*!
		  \return edgeInfo ei = {_stdEdge_,_weighted_
		  */
		const edgeInfo getEdgeInfo() {edgeInfo ei = {_stdEdgeOrd3_,_polynomial_}; return ei;}

		edgeVirtual *construct() { return new stdEdgeOrd3 ( *this ); };

		//! Setter für das Gewicht: nimmt Vector von Gewichten an.
		void setWeight(vector <baseType> newWeight)
		{
			if (newWeight.size() == 3)
			{
				a = newWeight[0];
				b = newWeight[1];
				c = newWeight[2];
			}
			else
				cerr << "Fehler - Gewichte sind nicht on der Ordnung 3" << endl;
		}			

		//! Getter für das Gewicht: gibt kein Gewicht zurück, da polynomial
		baseType getWeight() { return 0;}; 

		//! Überladung der Ausgabe einer Zelle: Sigmoidale Ausgabe
		/*!
		  \return 2 / (1+exp (-beta * targetState)) -1
		  */
		baseType getTargetState()
		{ 
			// alten Status abholen:
			baseType x = getTarget()->getState();

			//newState = ax + bx² + cx³
			baseType newState = a * x + b * x*x + c * x*x*x;
			/*	
				cout << "Gewicht abgeholt: " << x << endl; 
				cout << "a = " << a << endl;
				cout << "b = " << b << endl;
				cout << "c = " << c << endl;
				cout << "a * x = " << a*x << ", b*x*x = " << b*x*x << "c*x*x*x = " << c*x*x*x << endl;	
				*/	
			return (newState); 
		}

		//! Überladung des Ausgabestreams
		/*!
		  Gibt die Edge-Information aus:
		  \param &os ostream: gibt an, zu welchem Stream ausgegeben werden soll
		  \param edgeVerbosity double: gibt an, wie detailiert die Ausgabe seien soll.\n \n
		  edgeVerbosity >=1: Ausgabe aller EdgeInfos \n
		  edgeVerbosity >=2: Ausgabe aller Flanken-Parameter beta \n
		  */
		ostream& printStatistics ( ostream &os, double edgeVerbosity)
		{

			edgeInfo ei = getEdgeInfo();
			edge::printStatistics(os, edgeVerbosity, ei.theEdgeKind, ei.theEdgeName,  getWeight());




			if (edgeVerbosity>=2)
			{
				os << "Ordnung = 3" << endl;
			}

			// Ausgabe Gewichte
			os << a << "\t" << b << "\t" << c << endl;

			return os;
		}
	};




	/*! \brief Definition einer weightedEdge mit Sigmoidaler Ausgabefunktion mit Ordnung 3 (by HD)
	 * 
	 *	Diese Edge holt den Status der Nachbarzelle ab und gibt diese sigmoidal an die Zielzelle aus. \n
	 *	LaTeX: \operatorname{sig}(t) = \frac{1}{1 + e^{-\beta t}} \n
	 *
	 *	Die Zellen koppeln dabei mit der Ordnung 3 in die Nachbarzelle ein.
	 */
	class sigEdgeOrd3 : public weightedPolyEdge
		{
			baseType beta;				//!< Flankensteigung
			baseType	a, b, c;			//!< Gewichte ax +bx² + cx³

			public:
			//! Konstruktor mit beta = 4 Std, a = 1, b = c = 0.
			sigEdgeOrd3 ( ) {beta=4; a = 1; b = 0; c = 0;};		

			/*! Konstruktor mit beta = b
			 * \param beta int: Gibt die Flankensteilheit an
			 */ 
			sigEdgeOrd3 ( int b ) : beta ( b ) {};	
			//! Gibt die Kanteninfo zurück
			/*!
			  \return edgeInfo ei = {_sigEdge_,_weighted_
			  */
			const edgeInfo getEdgeInfo() {edgeInfo ei = {_sigEdgeOrd3_,_polynomial_}; return ei;}

			edgeVirtual *construct() { return new sigEdgeOrd3 ( *this ); };

			//! Setter für das Gewicht: nimmt Vector von Gewichten an.
			void setWeight(vector <baseType> newWeight)
			{
				if (newWeight.size() == 3)
				{
					a = newWeight[0];
					b = newWeight[1];
					c = newWeight[2];
				}
				else
					cerr << "Fehler - Gewichte sind nicht on der Ordnung 3" << endl;
			}			

			//! Getter für das Gewicht: gibt kein Gewicht zurück, da polynomial
			baseType getWeight() { return 0;}; 

			//! Überladung der Ausgabe einer Zelle: Sigmoidale Ausgabe
			/*!
			  \return 2 / (1+exp (-beta * targetState)) -1
			  */
			baseType getTargetState()
			{ 
				// alten Status abholen:
				baseType x = getTarget()->getState();
				//cout << "Gewicht abgeholt: " << x << endl; 
				x = 2.0 / ( 1+ exp ( -beta* x )) -1;
				//newState = ax + bx² + cx³
				baseType newState = a * x + b * x*x + c * x*x*x;

				return newState; 
			}

			//! Überladung des Ausgabestreams
			/*!
			  Gibt die Edge-Information aus:
			  \param &os ostream: gibt an, zu welchem Stream ausgegeben werden soll
			  \param edgeVerbosity double: gibt an, wie detailiert die Ausgabe seien soll.\n \n
			  edgeVerbosity >=1: Ausgabe aller EdgeInfos \n
			  edgeVerbosity >=2: Ausgabe aller Flanken-Parameter beta \n
			  */
			ostream& printStatistics ( ostream &os, double edgeVerbosity)
			{

				edgeInfo ei = getEdgeInfo();
				edge::printStatistics(os, edgeVerbosity, ei.theEdgeKind, ei.theEdgeName,  getWeight());



				// Ausgabe Kind, Name
				if (edgeVerbosity>=1)
				{
					edgeInfo ei = getEdgeInfo();

					os << "EdgeKind = " << ei.theEdgeKind << "\t";
					os << "EdgeName = " << ei.theEdgeName << "\t";
					if (edgeVerbosity>=2)
					{
						os << "beta = " << beta << "\t";
						os << "Ordnung = 3" << endl;
					}
				}	

				// Ausgabe Gewichte
				os << a << "\t" << b << "\t" << c << endl;

				return os;
			}
		};



		/*! \brief Definition einer weightedEdge mit Sigmoidaler Ausgabefunktion (by HD)
		 * 
		 *	Diese Edge holt den Status der Nachbarzelle ab und gibt diese sigmoidal an die Zielzelle aus. \n
		 *	LaTeX: /f$\operatorname{sig}(t) = \frac{1}{1 + e^{-\beta t}}$/f \n
		 */
		class sigEdge : public weightedEdgeVirtual
			{
				baseType beta;				//!< Flankensteigung

				public:
				//! Konstruktor mit beta = 4 Std
				sigEdge ( ) : beta ( 4 ) {};		

				/*! Konstruktor mit beta = b
				 * \param beta int: Gibt die Flankensteilheit an
				 */ 
				sigEdge ( int b ) : beta ( b ) {};	
				//! Gibt die Kanteninfo zurück
				/*!
				  \return edgeInfo ei = {_sigEdge_,_weighted_}
				  */
				const edgeInfo getEdgeInfo() {edgeInfo ei = {_sigEdge_,_weighted_}; return ei;}

				//! Überladung der Ausgabe einer Zelle: Sigmoidale Ausgabe
				/*!
				  \return 2 / (1+exp (-beta * targetState)) -1
				  */
				baseType getTargetState()
				{
					baseType x = getTarget()->getState();

					x = 2.0 / ( 1+ exp ( -beta* x )) -1;

					baseType a = this->getWeight();

					baseType newState = a*x;

					return (newState); 
				}

				edgeVirtual  *construct() { return new sigEdge ( *this ); };


				//! Überladung des Ausgabestreams
				/*!
				  Gibt die Edge-Information aus:
				  \param &os ostream: gibt an, zu welchem Stream ausgegeben werden soll
				  \param edgeVerbosity double: gibt an, wie detailiert die Ausgabe seien soll.\n \n
				  edgeVerbosity >=1: Ausgabe aller EdgeInfos \n
				  edgeVerbosity >=2: Ausgabe aller Flanken-Parameter beta \n
				  */
				ostream& printStatistics ( ostream &os, double edgeVerbosity)
				{
					// Ausgabe Header:
					edgeInfo ei = getEdgeInfo();
					edge::printStatistics(os, edgeVerbosity, ei.theEdgeKind, ei.theEdgeName,  getWeight());

					if (edgeVerbosity>=2)
					{
						os << "beta = " << beta << "\t";
					}	

					return os;
				}
			};
		/*! \brief Definition einer weightedEdge höherer Ordnung mit Sigmoidaler Ausgabefunktion (by HD)
		 * 
		 *	Diese Edge holt den Status der Nachbarzelle ab und gibt diese sigmoidal an die Zielzelle aus. \n
		 *	LaTeX: \operatorname{sig}(t) = \frac{1}{1 + e^{-\beta t}} \n
		 *
		 *	Dabei sind die Gewichte nicht linear sondern polynomial:\n
		 * 	output_i = sigfkt( a_i * state_i + b_i state_i² + c_i state_i³ ...)
		 */
		class sigEdgeParams : public weightedPolyEdge, public params< vector<baseType> >
			{
				private:
					//! Flankensteilheit
					baseType beta;

					//! Iterator über die Gewichte
					vector<baseType>::iterator it;

				public:	
					//! Konstruktor mit beta = 4.
					sigEdgeParams ( ) : params< vector<baseType> >(_sigEdgeParams_),  beta ( 4 ) {};

					/*! Konstruktor mit beta = 4
					 * \param node<baseType>* t Gibt die Zielnode an.
					 * \param baseType w	vector < double>: Gibt die Gewichte an.
					 */ 
					//			sigEdgeParams ( node* t, baseType w ) : weightedPolyEdge(t), beta ( 4 ) {}; 

					/*! Konstruktor mit beta = b
					 * \param beta int: Gibt die Flankensteilheit an
					 */ 
					sigEdgeParams ( int b ) : params< vector<baseType> >(_sigEdgeParams_), beta ( b ) {}; 

					// Überladung edge-Konstruktor:
					edgeVirtual *construct() { return new sigEdgeParams ( *this ); };

					//! Registriert den Parameter (Vector double), in den die Gewichte gespeichert werden.
					/*!
					  Std.: Erster Ordnung mit Gewicht 1.0
					  */
					static void registerStandardValues()
					{
						params< vector<baseType> >::registerStandard ( _sigEdgeParams_,"sigEdgeParams",0, vector<baseType> (1,1) );
					}

					//! Speichert die Gewichte (Vector double) ab.
					/*!
					  \param newWeight vector<double> Modifiziert die Gewichte der edge.Ordnung = vector<double>.size()
					  */
					void setWeight(vector <baseType> newWeight)
					{
						vector <vector <baseType> > n;
						n.push_back(newWeight);
						//if (params< vector<baseType> >::isStandard(_sigEdgeParams_))
						if (params< vector<baseType> >::isStandard())
							rerouteParams(n);
						//				else
						//					;
						//	setParams(0,newWeight);
					}

					//! Gibt die edgeInfo aus:
					/*!
					  \return edgeInfo ei = {_sigEdgeParams_,_polynomial_};
					  */
					const edgeInfo getEdgeInfo() 
					{
						edgeInfo ei = {_sigEdgeParams_,_polynomial_}; 
						return ei;
					}


					//! Gibt das Gewicht aus:
					/*!
					  \return 0, da das Gewicht polynomial und NICHT skalar.
					  */
					baseType getWeight() {return 0;}; //return params< vector<baseType> >::getParams(0)[0]; }

					//! Überladung der Ausgabefunktion
					/*!
					  output_i = sigfkt( a_i * state_i + b_i state_i² + c_i state_i³ ...) \n
					  Normiert auf [-1:1]
					  */
					baseType getTargetState()
					{ 
						baseType temp = getTarget()->getState();
						temp = 2.0 / ( 1+ exp ( -beta* temp )) -1;
						baseType x=1.0;
						baseType newState=0.0;

						// Bilde Summe über alle (Gewicht_i * State)^i
						for (it=params < vector <baseType> >::getParams(0).begin(); it!=params < vector <baseType> >::getParams(0).end(); it++)
						{
							// x = x^i
							x=x*temp;

							// newState = sum_i \alpha_i x^i
							newState += (*it) * x;
						}

						return (newState); 
					}

					//! Überladung des Ausgabestreams
					/*!
					  Gibt die Edge-Information aus:
					  \param &os ostream: gibt an, zu welchem Stream ausgegeben werden soll
					  \param edgeVerbosity double: gibt an, wie detailiert die Ausgabe seien soll.\n \n
					  edgeVerbosity >=1: Ausgabe aller EdgeInfos \n
					  edgeVerbosity >=2: Ausgabe aller Flanken-Parameter beta \n
					  */
					ostream& printStatistics ( ostream &os, double edgeVerbosity)
					{
						// Ausgabe Header:
						edgeInfo ei = getEdgeInfo();
						edge::printStatistics(os, edgeVerbosity, ei.theEdgeKind, ei.theEdgeName,  getWeight());

						// Ausgabe Kind, Name

						if (edgeVerbosity>=2)
						{
							os << "beta = " << beta << "\t";
							os << "Ordnung = " << params < vector<baseType> >::getParams(0).size() << "\t";
						}

						// Ausgabe Gewichte
						for (it=params < vector <baseType> >::getParams(0).begin(); it!=params < vector <baseType> >::getParams(0).end(); it++)
							os << (*it) << "\t";

						return os;
					}

					//			 ~sigEdgeParams() { cout << "Edge Destruktor called!" << endl; }
					//ostream& operator<< (ostream& os){ os << "Selbstausgabe sigEdgeParam" << endl; return os;};

		};






	}


#endif

