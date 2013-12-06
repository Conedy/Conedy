

#include "Parser.h"
#include <stdio.h>
#include "commandLineArguments.h"

#include "registerStandards.h"


#include "node.h"
#include "Scanner.h"
#include <fstream>
//#include "fullNetwork.h"
#if OPENGL
#include "glNetwork.h"
#endif


network *netCheat = 0;
void *pt2FunctionForGlutWrapper;

istream* Scanner::source;

void printDefines () 
{

	cout <<"#";
#if CONDOR
	cout << "CONDOR " ;
#endif


	//#if DOUBLE
	//	cout << "DOUBLE ";
	//#endif


#if LDOUBLE
	cout << "LDOUBLE ";
#endif


#if CALENDARQUEUE
	cout << "CALENDARQUEUE ";
#endif


#if DEBUG
	cout << "DEBUG "; 
#endif
	cout << endl;

}


int main ( int argc,char **argv )
{

	Parser theParser;

#if CONDOR
	uniqueNumber::initialize();
#elif RECOMPILE
	if (!system ("recompileConedy 2> /dev/null "))
	{
		cout << "Mission accomplished. You can restart your script now." << endl;
		exit (1);
	}	
#endif

	gslNoise::initialise(); // initialize random numbers
	printDefines();         // print some CFLAGS present during compilation to standard out
	commandLineArguments::initialize(argc, argv);   // save command line arguments as static members of commandLineArguments for global access.

	registerStandards();		// register	standard values for all node parameters
	vectorForInstruction::registerStandardValues();

	// initialize all standard values for node parameters to the interpreter 
	params<baseType>::initialise ( &command::declare );  	
	params<vector <baseType> >::initialise (&command::declare);
	params< string >::initialise (&command::declare);


	// interpret .conedyrc in the user's home directory
	stringstream ss;  		       
	ss << getenv("HOME")<< "/.conedyrc";
	ifstream *in  = new ifstream (ss.str().c_str());
	if (in->is_open())
	{
		try
		{
			Scanner::source = in;

			Parser theParser;
			theParser.parse();
#if CONDOR
			vectorForInstruction::writeCondorSkript();
#endif
		}
		catch ( const char *c )
		{
			cerr << "Error:" << c << endl;
			exit ( 1 );
		}
	}


	// interpret either the data from a file or from standard in

	string fileName;
	Scanner::source = &cin;
	if ( argc >= 2)
	{
		fileName = argv[1];

		if (fileName != "stdin")
		{

			ifstream *is = new ifstream();
			is->open ( fileName.c_str() );
			if ( !is->is_open() )
			{
				cerr << "Error opening file";
				exit ( 1 );

			}

			Scanner::source = is;


		}
	}

	try
	{
		Parser theParser;
		theParser.parse();
#if CONDOR
		vectorForInstruction::writeCondorSkript();
#endif

	}
	catch ( const char *c )
	{
		cerr << "Error:" << c << endl;
		exit ( 1 );
	}
	command::finalize();

	return 0;
};

