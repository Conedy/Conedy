

#include "ioNode.h"


namespace conedy
{

	void	streamOutNode:: 			evolve(double time) 

	{  
//		x = this->couplingSum(); 
		( * ( out[localStreamNumber] ) ) << setprecision((int)precision()) << this->couplingSum(); 
		( * ( out[localStreamNumber] ) ) << ' ';

	};


	streamOutNodeBinary::~streamOutNodeBinary()
	{
		counter[localStreamNumber] = counter [localStreamNumber] - 1;
		if ( counter[localStreamNumber] == 0 )
		{
			//			cout << "Closing:" << stringOfStreamNumber[localStreamNumber] << endl;
			//		out[localStreamNumber]->reset();
			delete  out[localStreamNumber];
			out[localStreamNumber] = NULL;
			// Rumkopieren, um die Lücke zu schließen ?
			//			for (unsigned int i=localStreamNumber; i < out.size() - 1;i++)
			//				out[i] = out[i+1];
			//			out.resize(out.size() - 1);

			//		out [localStreamNumber] = NULL;
			//		counter.erase[localStreamNumber];
			//		smallestUnusedNumber--;
			streamNumber.erase ( stringOfStreamNumber[localStreamNumber] );
			stringOfStreamNumber.erase ( localStreamNumber );
		}
	}

	streamOutNodeBinary::streamOutNodeBinary ( string s, networkElementType n )   : dynNode ( n )
	{
		//		s = "output/"+ s;

		if ( streamNumber.count ( s ) == 0 )
		{

			ofstream * newOut = new ofstream( s.c_str(), ios::out | ios::binary  );
			if (!newOut->is_open())
				throw "cannot open file for writing. ";



			out.push_back ( newOut );
			streamNumber[s] = smallestUnusedNumber;
			stringOfStreamNumber[smallestUnusedNumber] = s;
			localStreamNumber = smallestUnusedNumber;
			counter[smallestUnusedNumber] = 1;
			smallestUnusedNumber++;

		}
		else
		{
			counter[smallestUnusedNumber] = counter[smallestUnusedNumber] + 1;
			localStreamNumber = streamNumber[s];

		}
	}




	std::vector<ostream*> streamOutNodeBinary::out;
	std::map<int, unsigned int> streamOutNodeBinary::counter;
	std::map<string, int> streamOutNodeBinary::streamNumber;
	int streamOutNodeBinary::smallestUnusedNumber;
	std::map<int,string> streamOutNodeBinary::stringOfStreamNumber;




	void streamOutNode::enter() {
		for (unsigned int i = 0; i < out.size(); i++)
			if (out[i] != NULL)
				*out [i] << std::endl;
	}

	streamOutNode::~streamOutNode()
	{
		counter[localStreamNumber] = counter [localStreamNumber] - 1;
		if ( counter[localStreamNumber] == 0 )
		{

			//			cout << "Closing:" << stringOfStreamNumber[localStreamNumber] << endl;
			//		out[localStreamNumber]->reset();
			delete  out[localStreamNumber];
			out[localStreamNumber] = NULL;
			// Rumkopieren, um die Lücke zu schließen ?
			//			for (unsigned int i=localStreamNumber; i < out.size() - 1;i++)
			//				out[i] = out[i+1];
			//			out.resize(out.size() - 1);

			//		out [localStreamNumber] = NULL;
			//		counter.erase[localStreamNumber];
			//		smallestUnusedNumber--;
			streamNumber.erase ( stringOfStreamNumber[localStreamNumber] );
			stringOfStreamNumber.erase ( localStreamNumber );
		}
	}

	streamOutNode::streamOutNode ( string s, networkElementType n )   : dynNode ( n )
	{
		//		s = "output/"+ s;

		if ( streamNumber.count ( s ) == 0 )
		{
			io::filtering_ostream *newOut = new io::filtering_ostream();

			if ( zipOutput() )
			{
				newOut->push ( gzip_compressor() );
				//				cout << "Schreibe Daten gepackt ..." << endl;
			}
			if ( appendOutput())
			{
				io::file_sink fs = file_sink( s.c_str(), ios_base::out | ios_base::app);
				if (!fs.is_open())
					throw "cannot open file for writing. ";
				newOut->push ( fs );
				//				cout << "Hänge Daten an " << s << " ..." << endl;
			}
			else
			{
				io::file_sink fs = file_sink( s.c_str(), ios_base::out);
//				io::file_sink fs = file_sink("stupid", ios_base::out);
			
				if (!fs.is_open())
					throw "cannot open file for writing. ";
				newOut->push (fs );


			}
			out.push_back ( newOut );
			streamNumber[s] = smallestUnusedNumber;
			stringOfStreamNumber[smallestUnusedNumber] = s;
			localStreamNumber = smallestUnusedNumber;
			counter[smallestUnusedNumber] = 1;
			smallestUnusedNumber++;

		}
		else
		{
			counter[smallestUnusedNumber] = counter[smallestUnusedNumber] + 1;
			localStreamNumber = streamNumber[s];

		}
	}




	std::vector<io::filtering_ostream*> streamOutNode::out;
	std::map<int, unsigned int> streamOutNode::counter;
	std::map<string, int> streamOutNode::streamNumber;
	int streamOutNode::smallestUnusedNumber;
	std::map<int,string> streamOutNode::stringOfStreamNumber;


	streamInNode::~streamInNode()
	{
		counter[localStreamNumber] = counter [localStreamNumber] - 1;
		if ( counter[localStreamNumber] == 0 )
		{
			//			cout << "Closing:" << stringOfStreamNumber[localStreamNumber] << endl;
			in[localStreamNumber]->reset();
			//	delete  out[localStreamNumber];
			//		out [localStreamNumber] = NULL;
			//		counter.erase[localStreamNumber];
			streamNumber.erase ( stringOfStreamNumber[localStreamNumber] );
			stringOfStreamNumber.erase ( localStreamNumber );
		}
	}



	streamInNode::streamInNode ( string s, networkElementType n )   : dynNode ( n, 1 )
	{
		//		s = "output/"+ s;

		if ( streamNumber.count ( s ) == 0 )
		{
			io::filtering_istream *newIn = new io::filtering_istream();

			if ( zipInput() )
			{			
				newIn->push ( gzip_decompressor() );
			}

			io::file_source fs = file_source(s.c_str());
			if (!fs.is_open())
				throw "cannot open file for reading. ";

			newIn->push ( file_source ( s.c_str() ) );




			in.push_back ( newIn );
			streamNumber[s] = smallestUnusedNumber;
			stringOfStreamNumber[smallestUnusedNumber] = s;
			localStreamNumber = smallestUnusedNumber;
			counter[smallestUnusedNumber] = 1;
			smallestUnusedNumber++;

		}
		else
		{
			counter[smallestUnusedNumber] = counter[smallestUnusedNumber] + 1;
			localStreamNumber = streamNumber[s];

		}





	}








	std::vector<io::filtering_istream*> streamInNode::in;


	std::map<int, unsigned int> streamInNode::counter;


	std::map<string, int> streamInNode::streamNumber;
	int streamInNode::smallestUnusedNumber;


	std::map<int,string> streamInNode::stringOfStreamNumber;








}

