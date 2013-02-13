#ifndef command_h
#define command_h command_h



#include "baseType.h"
#include <map>
#include <boost/function.hpp>

#include "node.h"

#define _baseType_ 1
#define _network_ 2
#define _node_ 3
#define _int_ 4
#define _string_ 5
#define _bool_ 6


using namespace std;
using namespace conedy;

//typedef dynNode nodeBlueprint;
//typedef edgeVirtual edgeBlueprint;

void emptyFunction();

namespace conedy {


template <typename T> class MyNetwork;


// is called by conedyCondor instead of network functions




typedef MyNetwork<baseType> networkTemplate;

class dynNode;
typedef dynNode nodeBlueprint;

class edgeVirtual;
typedef edgeVirtual edgeBlueprint;


//! Alle Befehle erben von Command. Außerdem werden hier die Variablen gehandhabt.
class command
{
	protected:

		//! statische Zuordnung von Strings zum Type, der in einem Conedyskript deklariert wurde
		static map < string, int > varType;

		static map < string, baseType* > baseTypeVar;
		static map < string, bool* > boolVar;
		static map < string, int* > intVar;
		static map < string, networkTemplate * > networkVar;
		static map < string, nodeBlueprint ** > nodeVar;
		static map < string, edgeBlueprint ** > edgeVar;
		static map < string, string * > stringVar;
		static map < string, nodeDescriptor*> nodeDescriptorVar;

		static vector <string> inputFiles;


		static bool contextCheck (string s, int type)
		{ if ((varType.count(s) == 0 )|| (varType[s] != type)) return 0; else return 1;} // Überprüft, ob s als Variablenname vom Type type angemeldet wurde

	public:
		static void clear ();

		static int getType(string s) {return varType[s]; }

		static void addInputFile(string s) { inputFiles.push_back(s);};
		static  int addInputFileInt(string s) { inputFiles.push_back(s);  return 0;};


		//! delete all variables in the interpreter.
		static void finalize();

		template <typename T>
			static T * retrieve(string s) { throw "retrieve-Error"; }

		static void declare(string s, vector<baseType> *d)
		{
#ifdef DEBUG
			cout << "vector<doubles> are not supproted at the moment in the interpreter." << endl;
#endif
			//throw "vector<doubles> sind im interpreter atm not implemented!";
		}

		static void declare(string s, bool *d)
		{
			if (varType.count(s) != 0)
			{
				cout << "String:" << s << endl;
				cout << "VarType:" << varType[s] << endl;
				throw "declared twice.";
			}
			varType[s] = _bool_;
			boolVar[s] = d;
		}

		static void declare(string s, int *d)
		{
			if (varType.count(s) != 0)
			{
				cout << "String:" << s << endl;
				cout << "VarType:" << varType[s] << endl;
				throw "declared twice.";
			}
			varType[s] = _int_;
			intVar[s] = d;
		}

		static void declare(string s, baseType *d)
		{
			if (varType.count(s) != 0)
			{
				cout << "String:" << s << endl;
				cout << "VarType:" << varType[s] << endl;
				throw "declared twice.";
			}
			varType[s] = _baseType_;
			baseTypeVar[s] = d;
		}

		static void declare(string s, string *d)
		{
			if (varType.count(s) != 0)
			{
				cout << "String:" << s << endl;
				cout << "VarType:" << varType[s] << endl;
				throw "declared twice.";
			}
			varType[s] = _string_;
			stringVar[s] = d;
		}

		static void declare(string s, int type);	// Meldet s als Variablenname an ( so wie bei  "double d;")
		command() {}
		virtual ~command() {};
};


//! Basis-Klasse für alle Instructionen.
class instruction : public command
{
	public:
		virtual void execute() {};
};

//! Basis-Klasse für Ausdrücke im Parser-Baum vom Typ T
template <typename T>
class expression : public instruction
{
	public:
		//! Werte den  Ausdruck aus.
		virtual T evaluate() { return (T)0; }
		virtual void execute() { this->evaluate(); }
};



	template <>
inline baseType *  command ::retrieve<baseType> (string s)
{
	if (!contextCheck (s, _baseType_))
		throw (s +"ContextError!").c_str();
	else
		return baseTypeVar[s];

}

template <> inline bool *  command ::retrieve<bool> (string s)
{
	if (!contextCheck (s, _bool_))
		throw (s +"ContextError!").c_str();
	else
		return boolVar[s];

}

template <> inline int *  command ::retrieve<int> (string s)
{
	if (!contextCheck (s, _int_))
		throw (s +"ContextError!").c_str();
	else
		return intVar[s];

}

	template <>
inline string *  command ::retrieve<string> (string s)
{
	if (!contextCheck (s, _string_))
		throw (s +"ContextError!").c_str();
	else
		return stringVar[s];

}


	template <>
inline networkTemplate *  command::retrieve<networkTemplate> (string s)
{
	if (!contextCheck (s, _network_))
	{
		cout << "ContextError!" << endl;
		cout << "NetworkTemplate:" << s << endl;
		exit(1);
	}
	else
		return networkVar[s];

}

	template <>
inline nodeBlueprint**  command::retrieve<nodeBlueprint *> (string s)
{
	if (!contextCheck (s, _node_))
	{

		cout << "ContextError!" << endl;
		cout << "NodeTemplate:" << s << endl;
		exit(1);
	}
	else
		return nodeVar[s];

}

	template <>
inline edgeBlueprint**  command::retrieve<edgeBlueprint *> (string s)
{
	if (!contextCheck (s, _edge_))
	{

		cout << "ContextError!" << endl;
		cout << "EdgeTemplate:" << s << endl;
		exit(1);
	}
	else
		return edgeVar[s];

}






}
#endif
