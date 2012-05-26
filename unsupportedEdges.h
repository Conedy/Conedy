
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


	/*! \brief Definition einer weightedEdge mit Sigmoidaler Ausgabefunktion mit Ordnung 3 (by HD)
	 *
	 *	Diese Edge holt den Status der Nachbarzelle ab und gibt diese sigmoidal an die Zielzelle aus. \n
	 *	LaTeX: \operatorname{sig}(t) = \frac{1}{1 + e^{-\beta t}} \n
	 *
	 *	Die Zellen koppeln dabei mit der Ordnung 3 in die Nachbarzelle ein.
	 */
/*	class stdEdgeOrd3 : public weightedPolyEdge
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
		ostream& printStatistics ( ostream &os, int edgeVerbosity)
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
			ostream& printStatistics ( ostream &os, int edgeVerbosity)
			{

				edgeInfo ei = getEdgeInfo();
				edge::printStatistics(os, edgeVerbosity, ei.theEdgeKind, ei.theEdgeName,  getWeight());



				// Ausgabe Kind, Name
				if (edgeVerbosity >= 1)
				{
					edgeInfo ei = getEdgeInfo();

					os << "EdgeKind = " << ei.theEdgeKind << "\t";
					os << "EdgeName = " << ei.theEdgeName << "\t";
					if (edgeVerbosity >= 2)
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
				ostream& printStatistics ( ostream &os, int edgeVerbosity)
				{
					// Ausgabe Header:
					edgeInfo ei = getEdgeInfo();
					edge::printStatistics(os, edgeVerbosity, ei.theEdgeKind, ei.theEdgeName,  getWeight());

					if (edgeVerbosity >= 2)
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
					ostream& printStatistics ( ostream &os, int edgeVerbosity)
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
