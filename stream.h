

#ifndef __inStream
#define __inStream 0


#include <stdio.h>
#include <iostream>
#include <fstream>
#include <sstream>

using namespace std;

// LETZTE ÄNDERUNG: cyclicStream (HD - 26.08.2009) readDouble: erneutes Einlesen ist überarbeitet

// Die Integers sind momentan noch schrott, funktioniert nur mit Kommas

namespace conedy
{


	const string fileNameSeperators = ";,:) \n";

	const string stringSeperators = "+-*/(){}[],;: <>=\n";

	const string stringSeperatorsWithoutBrackets = ",;:";

	const string blanks  ="; \n";

	const string execStreamFileNameBeg = "__temp";

// Leerzeichen und so



	//! Obsolete
	class cyclicStream : public ifstream
	{

		public:
			cyclicStream ( string fileName )
			{

				open ( fileName.c_str() );

				if ( !is_open() )
				{
					cerr << "Error opening file\n" ;
					exit ( 1 );
				}
			}
			
			double readDouble()
			{
				double res;
				ifstream::operator >> ( res );
						
				if (eof())
				{
#ifdef DEBUG
					cout << "Resetting FileStream!" << endl;
#endif					
					clear();
					seekg ( 0,ios_base::beg );
		
					//(*this ) >> res	// erneutes Einlesen geändert (HD - 26.08.2009)
					ifstream::operator >> ( res );
				}
				
			return res;
			}
			
			// neu hinzugefügt (HD - 26.08.2009)
			~cyclicStream()
			{
				close();
			}
	};




}



#endif
