

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


//! Klasse, die die Kommandozeilen-Argumente, mit denen Neurosim aufgerufen wurde speichert.
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
			/*std::stringstream ssCommand;
			
			string homePath;
			homePath = getenv("HOME");
			
			ssCommand << "scp redwood2:/home/condor/.conedy " << homePath << "/.conedy";
			if (system(ssCommand.str().c_str()))
			{
				cout << "scp redwood2 to home failed! (for unique number.)" << endl;
				exit (1);
			}
	
			ssCommand.clear();
			*/
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
	
	
	
			/*if (system("scp $HOME/.conedy redwood2:/home/condor/.conedy"))
			{
				cout << "scp home to redwood2 failed! (for unique number.)" << endl;
				exit (1);
			}
			
	
			if (system("ssh redwood2 chmod 666 /home/condor/.conedy"))
			{
				cout << "ssh redwood2:chmod failed! (for unique number)";
				exit(1);
			}
			*/
	
		}	







};




#endif
