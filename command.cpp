

#include "command.h"
#include<iostream>
#include<fstream>
#include <sstream>

//#include <unistd.h>


#define MAXTIMESTEPS 1000


//#include <direct> // for getcwd
#include <stdlib.h>  // for MAX_PATH
#include <iostream> // for cout and cin

// function to return the current working directory
// this is generally the application path


void emptyFunction() {}

string getCurrentPath()
{
	char CurrentPath[200];
	if ( !getcwd ( CurrentPath, 200 ) )
		throw "getcwd failed!";
	return CurrentPath;
}

using namespace std;

map < string, int > command::varType;
map < string, baseType* > command::baseTypeVar;
map < string, networkTemplate* >command::networkVar;
map < string, nodeBlueprint** >command::nodeVar;
map < string, edgeBlueprint** >command::edgeVar;

map < string, nodeDescriptor*> command::nodeDescriptorVar;

map < string, string* >command::stringVar;
vector < string > command::inputFiles;

stringstream vectorForInstruction::chefDagEnding;
vector<int> vectorForInstruction::iterations;
ofstream vectorForInstruction::condorSkript;
ofstream vectorForInstruction::chefDag;
stringstream vectorForInstruction::jobName;
unsigned int vectorForInstruction::loopCounter;
unsigned int vectorForInstruction::nestedness;
params<baseType>  *vectorForInstruction::p;



void instructionBlock::execute () 
{
				list <instruction *> :: iterator it;
				for (it = instructionList.begin(); it != instructionList.end(); it++)
					(*it)->execute();
}
		

edgeBlueprint* setEdgeParameter::evaluate() { (( edgeBlueprint *) (edge->evaluate() )) -> setParameter((parameter->evaluate()) ); return edge->evaluate();}

string vectorForInstruction::currentJobName()
{
	stringstream ss;
	ss << uniqueNumber::number << "_";


	for ( unsigned int i =1 ; i < loopCounter; i++ )
		ss << iterations[i]  << "_";
	ss << iterations[loopCounter];
	return ss.str();

}



void vectorForInstruction::writeCondorSkript()
{

      cout <<"Die Nummer:" << uniqueNumber::number << endl;
      cout << getCurrentPath();

      jobName.str ( "" );
      jobName << "__" << uniqueNumber::number << ".dag";
      jobName.str ( "" );
      jobName << "__" << uniqueNumber::number << ".condor";
      condorSkript.open ( jobName.str().c_str() );
      jobName.str("");


      condorSkript << "Universe     = vanilla\n";

      condorSkript << "Executable   =  " << getenv ( "HOME" ) << "/bin/conedy.$$(OpSys).$$(Arch).EXE\n";

      condorSkript << "Log    =" << commandLineArguments::arg[1] << ".log" << "\n\n";
		condorSkript << "stream_output = True \n"; 
      condorSkript << "Requirements =" ; 

bool first = true;

	if (linux64())
	{
		if (!first)
			condorSkript << " || \\\n";
		condorSkript << "(Arch == \"X86_64\" && OpSys == \"LINUX\")";
		first = false;
	}
	if (linux32())
	{
		if (!first)
			condorSkript << " || \\\n";
		condorSkript << "    (Arch == \"INTEL\" && OpSys == \"LINUX\")";
		first = false;
	}
	if (win51())
	{
		if (!first)
			condorSkript << " || \\\n";
		condorSkript << "    (Arch == \"INTEL\" && OpSys == \"WINNT51\")";
		first = false;
	}
	if (win60())
	{
		if (!first)
			condorSkript << " || \\\n";
		condorSkript << "    (Arch == \"INTEL\" && OpSys == \"WINNT60\")";
		first = false;
	}
	if (win61())
	{
		if (!first)
			condorSkript << " || \\\n";
		condorSkript << "    (Arch == \"INTEL\" && OpSys == \"WINNT61\")";
		first = false;
	}
	condorSkript << "\n\n";


      condorSkript << " TRANSFER_FILES  = ALWAYS\n";
//    out <<"notification = Complete\n";
//    out <<"notify_user=alex@goedel\n";
//    out << "next_job_start_delay = 100 \n";
      condorSkript << "should_transfer_files = YES \n";
//	   condorSkript << "on_exit_remove = (ExitBySignal == False) && (ExitCode == 0)\n";
      condorSkript << "WhenToTransferOutput = ON_EXIT\n\n";

      size_t found;
      found=commandLineArguments::arg[1].find_last_of("/\\");
      string fileName = commandLineArguments::arg[1].substr(found+1);


if (nestedness == 0)
		condorSkript << "transfer_input_files =" << fileName << "\n";
else
      condorSkript << "transfer_input_files     = $(transfer)\n";



		condorSkript << "\n";


      condorSkript << "Arguments =" << fileName;


      for ( unsigned int i =1 ; i <= nestedness; i++ )
         condorSkript << " $(arg" << i << ") ";


      condorSkript << "\n";
      condorSkript << "Error  =__" << fileName;
      for ( unsigned int i =1 ; i <= nestedness; i++ )
         condorSkript << "_$(arg" << i << ")";
      condorSkript <<  ".err\n";

      condorSkript << "Output =__" << fileName;
      for ( unsigned int i =1 ; i <= nestedness; i++ )
         condorSkript << "_$(arg" << i << ")";
      condorSkript << ".out\n";


      condorSkript  << "Queue \n";


      condorSkript.close();













}


void vectorForInstruction::submitToCondor()
{

#if CONDOR

	if ( loopCounter == 1 )
	{
		iterations.push_back ( 0 );


		cout <<"Die Nummer:" << uniqueNumber::number << endl;
		cout << getCurrentPath();

//		writeCondorSkript();


		jobName.str ( "" );
		jobName << "__" << uniqueNumber::number << ".dag";
		chefDag.open ( jobName.str().c_str() );
		jobName.str ( "" );
		jobName << "__" << uniqueNumber::number << ".condor";
		jobName.str("");



	}
	if ( loopCounter < nestedness )
	{

		iterations.push_back ( 0 );
		iterations[loopCounter] = 0;
		start->execute();
		while ( cond->evaluate() )
		{
			body->execute();
			iterations[loopCounter]++;
			inc->execute();
		}


	}
	if ( loopCounter == nestedness )
	{

		iterations.push_back ( 0 );

		iterations[loopCounter] = 0;
		start->execute();
		while ( cond->evaluate() )
		{
			body->execute();

			inc->execute();









			chefDag << "JOB J" << currentJobName() << " __" << uniqueNumber::number << ".condor" << "\n";
			chefDag << "VARS J" << currentJobName() << " ";
			for ( unsigned int i =1 ; i <= loopCounter; i++ )
				chefDag << " arg" << i << "=\"" <<  iterations[i] << "\" ";

			chefDag << "transfer=\""<< commandLineArguments::arg[1];
			for ( unsigned int i = 0; i < inputFiles.size(); i++ )
				chefDag << "," << inputFiles[i];	
			chefDag << "\"\n";

			if ( cond->evaluate() && isChained )
			{
				chefDagEnding << "PARENT J" << currentJobName() << " ";

				chefDagEnding<< "CHILD J" <<uniqueNumber::number << "_";
				for ( unsigned int i =1 ; i < loopCounter; i++ )
					chefDagEnding << iterations[i]  << "_";
				chefDagEnding << iterations[loopCounter] + 1 << "\n";


			}
			iterations[loopCounter]++;
			command::inputFiles.clear();

		}








	}
	if ( loopCounter == 1 )
	{



		/*	stringstream startSkriptFilename;
			startSkriptFilename << "__start" << uniqueNumber::number << ".sh";

			condorSkript.open(startSkriptFilename.str().c_str());
			out << "#!/usr/bin/bash" << endl;
			out << "EXE=`which " << commandLineArguments::arg[0] << "`" << endl;
			out << "cp " << commandLineArguments::arg[1] << " " << jobName.str() << ".ns" << endl;
			out << "ssh redwood2 mkdir ~/" << jobName.str() << "\n";
			out << "scp $EXE  " << jobName.str() << ".ns" << " " << jobName.str();

			for (unsigned int i = 0; i < inputFiles.size(); i++)
				out << " " << inputFiles[i];

			out << " redwood2:~/" << jobName.str() << "/\n";
			out << "ssh redwood2 cd ~/" << jobName.str() <<  " \\; condor_submit " << jobName.str() <<"\n";

			out << "while true; do\n";
			out << "	sleep 300;\n";
			out << "	if(condor_q -pool redwood2 -name redwood2|grep " << jobName.str() << "); then\n";
			out << "		echo \"Still Working!\"\n ";
			out << "		continue;\n";
			out << "	fi\n";
			out << "	break;\n";
			out << "done\n";
			out << "echo \"Finished!\"\n";
			out << "scp -r redwood2:~/" << jobName.str() << " " << getCurrentPath()<<"/output" << "\n";

		//	out << "ssh redwood2 rm -rf ~/" << jobName.str() << "\n";



		//	out << "rm conedy " << jobName.str() << " " << jobName.str() << ".ns " << "__start.sh\n";
			condorSkript.close();

			sleep(2);

		*/
//		condorSkript.close();
		chefDag << chefDagEnding.str();

		chefDag.close();
/*		jobName.str ( "" );
		jobName << "__" << uniqueNumber::number << ".dag";
		stringstream com;
		com << "/usr/condor/bin/condor_submit _dag" << jobName.str();
		FILE *lsofFile_p = popen ( com.str().c_str(), "r" );
		char buffer[1024];
		char *line_p = fgets ( buffer, sizeof ( buffer ), lsofFile_p );
		line_p = fgets ( buffer, sizeof ( buffer ), lsofFile_p );
		line_p = fgets ( buffer, sizeof ( buffer ), lsofFile_p );

		string thirdLine = line_p;
		string clusterNumber = thirdLine.substr ( thirdLine.find ( "cluster" ) + 8 , thirdLine.size() - 2 );

		pclose ( lsofFile_p );

		ofstream jobList;

		stringstream runningCondorJobsFileName;
		runningCondorJobsFileName << getenv ( "HOME" ) << "/runningCondorJobs";
		jobList.open ( runningCondorJobsFileName.str().c_str(),fstream::out | fstream::app );
		jobList << clusterNumber  << " " << getCurrentPath() << endl;

		jobList.close();

*/













//	stringstream command;
//	command << "condor_submit " << jobName.str();


//	if (system(command.str().c_str()))
//	{
//		throw "condor_submit failed!";
//	}





	}






//	system ("scp " << commandLineArguments::arg[0] << " " << commandLineArguments::arg[1] <<

#else
	throw "condor nicht mitkompiliert!";


#endif

}

