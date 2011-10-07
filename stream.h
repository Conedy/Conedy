

#ifndef stream_h
#define stream_h stream_h 


#include <stdio.h>
#include <iostream>
#include <fstream>
#include <sstream>



using namespace std;



namespace conedy
{




	//! Obsolete
	class cyclicStream : public ifstream
	{

		public:
			cyclicStream ( string fileName )
			{

				open ( fileName.c_str() );

				if ( !is_open() )
				{
					throw "Error opening file\n" ;
				}
			}

			double readDouble()
			{
				double res;
				ifstream::operator >> ( res );

				if (eof())
				{
					clear();
					seekg ( 0,ios_base::beg );

					ifstream::operator >> ( res );
				}

				return res;
			}

			~cyclicStream()
			{
				close();
			}
	};




}



#endif
