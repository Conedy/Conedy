

#ifndef params_h
#define params_h params_h

#include <map>
#include "networkConstants.h"


#include <vector>
//#include "node.h"
#include <boost/function.hpp>
using namespace boost;

namespace conedy
{
	using namespace std;

	/*!
		\Brief Klasse zur zentralen Verwaltung von Parametern

		Die Klasse Params dient der zentralen Verwaltung von Parametern:
		Durch die Methode "registerStandard" werden zunächst alle Standartparameter aller Nodes / Edges gespeichert. Diese dienen als Blaupause für weitere Nodes/Edges.

		Wird eine "unnormale" Node/Edge instanziert, so wird zusätzlicher Speicherplatz für Parameter mittels "rerouteParams" alloziiert->



*/


	template <typename T>
		class params
		{
			protected:
				//! Ablage für alle Parameter. Eine Node/Edge belegt eine Reihe (row) Speicherplatz
				static vector<vector<T*> > param;

				//! Anzahl der Standartparameter (Wird beim Start von Neurosim hochgezählt)
				static unsigned int numberOfStandardParameterSheets;

				//! Zähler für Anzahl der Nodes, die eine bestimmte Reihen benutzen
				static vector <unsigned int> usageCounter;

				//! Anzahl der bisher belegten Reihen
				static unsigned int Nparams;

				//! Zuordnung von "nodetype" zu Reihennummer mit Standardparametern
				static map<networkElementType, int> standardParam;  

				//! Zuordnung von string zu (standardadresse, parameternummer)
				static map <string, pair<int, int> > adress;    

				static map <pair<int,int>, string > name;



			public:
				//! Der Parametersheet  der lokalen Instanz
				unsigned int row;

				//! Gibt alle Parameter auf die Konsole aus.
				void printStatistics() 
				{	
					cout << "parameter:" << endl;
					if (isStandard())
						cout << "	standard parameter" << endl;
//					cout << "	row: " << row << endl;
					for (unsigned int i = 0; i < param[row].size(); i++)
						cout << "	" << name[make_pair(row, i)] << ": \t " << *param[row][i] << " " << endl;


					//			cout << "UsageCounter:" << usageCounter[row] << endl;

				}
				static T getStandardParameter(networkElementType n, unsigned int number)
				{
					return * param[standardParam[n]][number];
				}

				// ###### KONSTRUKTOREN ######
				//! Copyconstructor: wird aufgerufen, wenn Parameter mehrfach benutzt werden (Nodes/Edges kopiert werden)
				params ( const params<T> &b )
				{
					row = b.row;
					if (!isStandard())
						usageCounter.at(row)++;



				}
				//! Leerer Konstruktor
				//TODO: BRAUCHT MAN DIE??? lässt man den nicht lieber weg, damit alles funktioniert?
				//		params() {
				//				row = 0;

				//};

				params(const unsigned int N) {  vector <T> newVec(N); param.push_back(newVec); row = Nparams; Nparams++; }//usageCounter.push_back(1);};

				//! Copy-Konstructor, der für das erstellte Objekt, Standard-Parameter verwendet (Ist das sinnvoll?) TODO
				params(networkElementType theNodeType) 
				{ 

					if (standardParam.count(theNodeType) == 0)
					{
						vector <T*> newVec; param.push_back(newVec);
						usageCounter.push_back(0);



						standardParam[theNodeType] = Nparams;
						//usageCounter[Nparams] = 1;

						Nparams++;
						numberOfStandardParameterSheets++;

					}

					row = standardParam[theNodeType];
					// 		        usageCounter.push_back(1);
					//cout << theNodeType << " " << row << endl;
				}


				//! Destruktor: Verringert den usageCounter um 1. Wenn usageCounter==1 wird der Parameter gelöscht.
				virtual ~params() 
				{
#ifdef DEBUG
					cout << "Destruktor aufgerufen: usageCounter at row " << row << " = " << usageCounter.at(row) << endl;
#endif

					if (usageCounter.at(row) == 1)
					{
						if (!isStandard())
						{
							for (unsigned int i = 0; i < param[row].size(); i++)
								delete param[row][i];

#ifdef DEBUG
							cout << "Paramter Reihe " << row << " gelöscht!\n" << endl;
#endif

						}

						usageCounter.at(row)=0;
					}
					else if (usageCounter.at(row)>1)
						usageCounter.at(row)--;
				};


				//	virtual void registerStandardValues() { throw "ERROROROR";};

				//! Funktion zum Test, ob ein Parameter Std oder individuell ist.
				bool isStandard() { return row < numberOfStandardParameterSheets;}

				vector<T*> getParameters()	{ return param[row]; }


				/*!
					Funktion zum Abfragen der NodeType

					\param string s
					\return networkElementType
					*/
				static networkElementType getNodeTypeFromString(string s)
				{

					if (adress.count(s) == 0)
						throw "String does not correspond to node parameter!";
					int standardAdress = adress[s].first;
					map<networkElementType, int>::iterator ia,ie;
					ia = standardParam.begin();
					ie = standardParam.end();
					for (; ia != ie; ia++)
					{
						if (ia->second == standardAdress)
							return  ia->first;
					}
					throw "String does not correspond to node parameter!";
					return _undefinedNodeType_;
				}

				/*!
					Funktion zum Randomisieren der Parameter für ??????
				//TODO: Alex: bitte ändern!

				\param string s	String für ...
				\param networkElementType n	Art des Netzwerkelementes
				\param function<double ()> r	???
				*/
				void randomizeParameter(string s, networkElementType n, function<double ()> r)   // require: Nodetype ist richtig ! 
				{
					unsigned int place = (unsigned int )adress[s].second;
					if (isStandard())
					{
						vector <T*> newVec(param[row].size());
						param.push_back(newVec); 
						//				param[Nparams].resize( param[row].size());

						for (unsigned int i = 0; i < param[row].size(); i++)
						{
							if (i != place)
								param[Nparams][i] = new T(*(param[row][i]));
							else
								param[Nparams][i] = new T(r());
						}

						row = Nparams;
						Nparams++;
						usageCounter.push_back(1);

					}
					else
					{
						//		delete param[row][place];
						*(param[row][place]) = r();
					}
				}

				static void randomizeParameter( string parameterString, function<double ()> r)
				{
					randomizeParameter(parameterString, getNodeTypeFromString(parameterString), r);
				}

				//static void initialise( void  (*callback) (string,double *))
				static void initialise( void  (*callback) (string,T *))
				{ 
					map <string, pair<int, int> >::iterator it;
					for (it = adress.begin(); it != adress.end(); it++)
					{
						(*callback)(it->first, param[it->second.first][it->second.second]);
					}
				}

				//! Funktion zum Erstellen individueller Parameter aus einer Blaupause heraus. Neuer Speicherplatz wird hier zur Verfügung gestellt.
				//
				
				
				void rerouteParams (vector <T>  argList)           // am Besten nur einmal aufrufen solange die Parameter noch an der Standardstelle stehen
				{
					if (argList.size() != param[row].size())
					{
						throw "Fehler. falsche Argumenten Anzahl für Node";

					}
					else
					{
						if (usageCounter.at(row)>1)
							usageCounter.at(row)--;
						vector <T*> newVec; param.push_back(newVec); row = Nparams;
						usageCounter.push_back(1);
						Nparams++;
						param[row].resize( argList.size());
						for (unsigned int i = 0; i < argList.size(); i++)
							param[row][i] = new T(argList[i]);

					}
				}	
				//! Definiert die Parameter vom Momentanen sheet um.
				void setSheet (unsigned int theRow, vector <T> argList)
					{
          if (argList.size() != param[theRow].size())
						          {
												            throw "Fehler. falsche Argumenten Anzahl für Node";

																		          }
					          else
											          {
																	            for (unsigned int i = 0; i < argList.size(); i++)
																								              *param[theRow][i] = argList[i];
																							          }





					}


				//! Setzt alle Parameter, im lokalen sheet

				bool compareSheets (unsigned int sheet1, unsigned int sheet2)
				{
					if (param [sheet1].size() != param [sheet2].size())
						return 0;
				
					for (unsigned int i = 0 ; i < param[sheet1].size() ; i++)
					{
						if (param[sheet1][i] != param [sheet2][i])
							return 0;
					}
					return 1;

				}


				void setSheet( vector <T> argList)
				{
					if (argList.size() != param[row].size())
					{
						throw "Fehler. falsche Argumenten Anzahl für Node";

					}
					else
					{
						for (unsigned int i = 0; i < argList.size(); i++)
							*param[row][i] = argList[i];
					}




				}




				//! einfacher Zugriff auf die Parameter
				T operator[] (const unsigned int n) { return param[row][n]; };
				void setParams(const unsigned short i, T value) { *param[row][i]=value; }
				//		void setParams(inStream& in) { for (unsigned short i = 0; i < param[row].size(); i++) in >> param[row][i]; }
	
				//! obsolete ?
				T getParams(const unsigned short which)  const { return *param[row][which]; };

				void setParam(string parameterName, T value)
				{
					if (isStandard())
					{
							vector <T> newParams;
							unsigned int toChange = adress[parameterName].second;
							for (unsigned int i = 0; i < param[row].size(); i++)
							{
								if (toChange == i)
									newParams.push_back(value);
								else
									newParams.push_back(*param[row][i]);
							}
					rerouteParams(newParams);
				}






					else 
						*param[row][adress[parameterName].second] = value;
				}


				T& getParam(string name) const { return *param[row][adress[name].second]; }
				//		virtual valarray<T>* getParams() { return &param; }


				

				//! Setzt Standardparameter fest für den nodeType theNodeType. Mitübergeben wird der Name des Parameters (Im Parser), ein Standarwert und eine laufende Nummer
				static void registerStandard(networkElementType theNodeType, string s, unsigned int paramNumber, T value) 
				{ 






					if (standardParam.count(theNodeType) == 0)
					{
						vector <T*> newVec; param.push_back(newVec);
						usageCounter.push_back(0);



						standardParam[theNodeType] = Nparams;
						//usageCounter[Nparams] = 1;

						Nparams++;
						numberOfStandardParameterSheets++;
					}

					if (paramNumber +1 > param[standardParam[theNodeType]].size())
						param[standardParam[theNodeType]].resize(paramNumber+1,0);

					adress[s] = make_pair(standardParam[theNodeType], paramNumber);
					name[ make_pair(standardParam[theNodeType], paramNumber)] = s;
					param[standardParam[theNodeType]][paramNumber] = new T (value);




				}

				static void setStandard(string name, T d) 
				{
					if (adress.count (name) != 0 )
				  		*param[adress[name].first][adress[name].second] = d;
					else 
						throw "setting with unknown string!";
				}
				//		static void copyStandardSheet(networkElementType 

				//! obsolete
				static void printAll() { 
					
					map<string, pair<int,int> >::iterator it;
					for (it = adress.begin(); it != adress.end();it++)
						cout << it->first << " " << *param[it->second.first][it->second.second] << endl; 	

				};



};



template <typename T>
vector<vector<T*> >  params<T>::param;

template <typename T>
unsigned int params<T>::Nparams;


template <typename T>
unsigned int params<T>::numberOfStandardParameterSheets = 0;

template <typename T>
map<networkElementType, int> params<T>::standardParam;

template <typename T>
map <string, pair<int, int> > params<T>::adress;


template <typename T>
map <pair<int, int>,string > params<T>::name;


template <typename T>
vector <unsigned int> params<T>::usageCounter;

}


#endif





