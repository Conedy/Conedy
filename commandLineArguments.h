

#ifndef commanLineArguments_h
#define commanLineArguments_h commanLineArguments_h


#include <vector>
#include <string>

#include <fstream>

#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <sstream>

using namespace std;


//! Klasse, die die Kommandozeilen-Argumente, mit denen Conedy aufgerufen wurde speichert.
class commandLineArguments
{	
	public:
		static vector <string> arg;	

	public:
	static void initialize ( int argc,char **argv )
	{
		string dummy;
		for (int i = 0; i< argc; i++)
		{
			dummy = argv[i];
			arg.push_back(dummy);		
		}

		if (argc == 1)
			arg.push_back("noFilename");

	}
	static string getStringArg(unsigned int argNum)
	{
		if (argNum < arg.size())
			return arg[argNum];
		else
		{
			cerr << "FEHLER: Argumentennummer zu groß! [0:" << arg.size() << ")" << endl;
			return "";
		}
	}
	
	static double getDoubleArg(unsigned int argNum)
	{
		istringstream isstr;
		
		if (argNum < arg.size())
		{
			isstr.str(arg[argNum]);
			double temp;
			isstr >> temp;
			return temp;
		}
		else
		{
			cerr << "FEHLER: Argumentennummer zu groß! [0:" << arg.size() << ")" << endl;
			return 0.0;
		}
	}


};

//! Klasse, die für Neurocondor eine eindeutige Jobnummer generiert. Die Zahl ist im Homeverzeichnis in der Datei .conedy gespeichert.
class uniqueNumber
{
	public:
		static int number;
		
		static void initialize()
		{

#if CONDOR
			stringstream ss;
			ss << getenv("HOME")<< "/.conedy";			

			ifstream in(ss.str().c_str());
			if (!in.is_open())
			{
				number = 0;
			}
			else
			{
				in >> number;
				number++;
				in.close();
			}
			ofstream out(ss.str().c_str());
			out << number;
			out.close();
	
#endif	
	
	
		}	







};




#endif
