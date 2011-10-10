

#include "Parser.h"
#include <stdio.h>
#include "commandLineArguments.h"

#include "registerStandards.h"


#include "node.h"
#include "Scanner.h"
#include <fstream>
#include "fullNetwork.h"
#if OPENGL
#include "glNetwork.h"
#endif

//	Letzte Änderung:	23.07.2009	hdickten:	Fehlermeldung editiert

network *netCheat = 0;
void *pt2FunctionForGlutWrapper;

istream* Scanner::source;

int main ( int argc,char **argv )
{
	//	system("mkdir output");

	Parser theParser;

#if CONDOR
	uniqueNumber::initialize();
#else
	if (!system ("recompileConedy 2> /dev/null"))
	{
		cout << "Mission accomplished. You can restart your script now." << endl;
		exit (1);
	}	
#endif

	gslNoise::initialise();

	commandLineArguments::initialize(argc, argv);


	//	nodeTemplate *n;
	//	delete n;
	//	n->registerStandardValues();
	//	delete n;

	//	odeNode::registerStandardValues();

	registerStandards();

	vectorForInstruction::registerStandardValues();


	params<baseType>::initialise ( &command::declare );
	params<vector <baseType> >::initialise (&command::declare);
	params< string >::initialise (&command::declare);



//	params<baseType>::printAll();

	stringstream ss;  		       
	ss << getenv("HOME")<< "/.conedyrc";
	ifstream *in  = new ifstream (ss.str().c_str());

//	cout << ss.str();
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
		cerr << "Fehler:" << c << endl;
		exit ( 1 );
	}
	}
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
		cerr << "Fehler" << c << endl;
		exit ( 1 );
	}
	command::finalize();

	return 0;
};

