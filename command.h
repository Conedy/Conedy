

//***Destruktoren für NEtwork
#ifndef command_h
#define command_h command_h

#include <map>
#include <string>
#include <iostream>

#include "stream.h"
#include "fullNetwork.h"

#include "commandLineArguments.h"
#include "gslNoise.h"

using namespace std;
using namespace conedy;

#define _baseType_ 1
#define _network_ 2
#define _node_ 3
#define _nodeDescriptor_ 4
#define _string_ 5


#include <boost/function.hpp>

#include "network.h"

//typedef dynNode nodeBlueprint;
//typedef edgeVirtual edgeBlueprint;



void emptyFunction();



typedef MyNetwork<baseType> networkTemplate;




//! Alle Befehle erben von Command. Außerdem werden hier die Variablen gehandhabt.
class command				
{
	protected:

		//! statische Zuordnung von Strings zum Type, der in einem Conedyskript deklariert wurde
		static map < string, int > varType;

		static map < string, baseType* > baseTypeVar;
		static map < string, networkTemplate * > networkVar;
		static map < string, nodeBlueprint ** > nodeVar;
		static map < string, edgeBlueprint ** > edgeVar;
		static map < string, string * > stringVar;
		static map < string, nodeDescriptor*> nodeDescriptorVar;

		static vector <string> inputFiles;



		static bool contextCheck (string s, int type) 
			{ if ((varType.count(s) == 0 )|| (varType[s] != type)) return 0; else return 1;} // Überprüft, ob s als Variablenname vom Type type angemeldet wurde
		
		public:

		static int getType(string s) {return varType[s]; }

		static void addInputFile(string s) { inputFiles.push_back(s);};

		static void finalize()
		{
			map <string,networkTemplate*>::iterator itnet, ienet;
			itnet = networkVar.begin();
			ienet = networkVar.end();
			for (;itnet != ienet; itnet++)
				delete itnet->second;

			map <string,edgeBlueprint**>::iterator itedge, ieedge;
			itedge = edgeVar.begin();
			ieedge = edgeVar.end();
			for (;itedge != ieedge; itedge++)
				delete itedge->second;

			map <string,nodeBlueprint**>::iterator itnode, ienode;
			itnode = nodeVar.begin();
			ienode = nodeVar.end();
			for (;itnode != ienode; itnode++)
				delete itnode->second;

/*			map <string,double*>::iterator itd, ied;
			itd = doubleVar.begin();
			ied = doubleVar.end();
			for (;itd != ied; itd++)
				delete itd->second;

			map <string,int*>::iterator iti, iei;
			iti = intVar.begin();
			iei = intVar.end();
			for (;iti != iei; iti++)
				delete iti->second;

*/

		}
			
		template <typename T>
			static T * retrieve(string s) { throw "retrieve-Error"; }

		static void declare(string s, vector<baseType> *d)
		{
#ifdef DEBUG
				cout << "vector<doubles> sind im interpreter atm not implemented!" << endl;
#endif
			//throw "vector<doubles> sind im interpreter atm not implemented!";
		}
		static void declare(string s, baseType *d)
		{

			if (varType.count(s) != 0)
			{
				cout << "String:" << s << endl;
				cout << "VarType:" << varType[s] << endl;
				throw "Doppelt declared.";
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
				throw "Doppelt declared.";
			}
			varType[s] = _string_;
			stringVar[s] = d;
		}		
		
		static void declare(string s, int type)	// Meldet s als Variablenname an ( so wie bei  "double d;")
		{ 
//			cout << "DECLARED" << endl;

#ifdef DEBUG
			cout << "declaring:" << s << " " << type << endl;
#endif

			if (varType.count(s) != 0)
			{
//				cout << "String:" << s << endl;
//				cout << "VarType:" << varType[s] << endl;
	//			throw "Doppelt declared.";	
			}
			varType [s] = type; 
			if (type == _network_) 
			{
				networkTemplate n;
				networkVar[s] = new networkTemplate(n);

			}
			if (type == _node_)
			{
				dynNode **n =new dynNode*();
				
//				node *nod = new node();
//				n = & nod;
				nodeVar[s] = n;
			}

			if (type == _edge_)
			{
				edgeBlueprint **n =new edgeBlueprint*();
				
//				edge *nod = new node();
//				n = & nod;
				edgeVar[s] = n;
			}



			if (type == _string_)
			{
				stringVar[s] = new string();
			}
			

			if (type == _baseType_) baseTypeVar[s] = new baseType(); 
			if (type == _nodeDescriptor_) nodeDescriptorVar[s] = new nodeDescriptor();
		};
	command() {}
	virtual ~command() {};
};
template <>
 inline baseType *  command ::retrieve<baseType> (string s)
{
	if (!contextCheck (s, _baseType_))
		throw (s +"ContextError!").c_str();
	else
		return baseTypeVar[s];

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




template <>
 inline nodeDescriptor*  command::retrieve<nodeDescriptor> (string s)
{
	if (!contextCheck (s, _nodeDescriptor_))
				{
					cout << "ContextError!" << endl;
					cout << "Long:" << "s" << endl;
					exit(1);
				}
				else
					return nodeDescriptorVar[s];

}

//! Basis-Klasse für alle Instructionen.
class instruction : public command
{
	public:
	virtual void execute() {};
};


//! Instruction, die einen shell-Befehl ausführt.
class systemInstruction : public instruction
{
	private:
		string theCommand;
	public:
		systemInstruction(string c) : theCommand(c) {};
		virtual void execute()
		{
			if (system(theCommand.c_str()))
			{	
				cout <<  "system Command Failed!" << endl;
//				throw theCommand.c_str();
			}
		}
};

//! Instruction, die eine Liste von Instruktionen speichert. Wird gebraucht, für das innere von Schleifen.
class instructionBlock : public instruction
{
	list <instruction*> instructionList;
	public:
		instructionBlock() {};
		void addInstruction (instruction *i) { instructionList.push_back(i); }
		virtual void execute () ;
}; 


//! Instruchtion, die einen Boost-Funktionszeiger speichert.
class bindInstruction : public instruction
{
	private:
		boost::function<void ()> _f;
	public:
		bindInstruction(boost::function<void ()> f) : _f(f) {}
		virtual void execute(){  (_f)();  }
		

;
};


//! Instruction, die eine Variable im Parser declariert.
class declareInstruction : public instruction
{
	private:
		string ident;
		int type;
	public:
		declareInstruction(string i, int t) : ident(i), type(t) {};
		void execute () { command::declare(ident, type); }
};


//! Basis-Klasse für Ausdrücke im Parser-Baum vom Typ T
template <typename T>
class expression : public command
{
	public:
		//! Werte den  Ausdruck aus.
		 virtual T evaluate() { return (T)0; }
};



//! Instruction mit einem Funktionszeiger.
template <typename T>
class bindExpression : public expression<T>
{
	public:
		boost::function<T ()> _f;
		bindExpression(boost::function<T ()> f) : _f(f) {};
		virtual T evaluate(){  return (_f)();  };
		T operator()() { return (_f)(); };
};


//! Ausdruck für einen Vector 
template <typename T>
class expressionVector : public command
{
	private:
		vector <expression <T>*> vec;
	
	public:
		void push_back(expression<T> *el) { vec.push_back(el); }
		vector <T> evaluate()
			{
				vector<T> resVec; 
				for (unsigned int i = 0; i < vec.size(); i++)
					resVec.push_back((T)vec[i]->evaluate());
				return resVec;
			}
};





class setNodeParameter : public expression<nodeBlueprint*>
{
	private:
		expressionVector<baseType> *parameter;
		expression<nodeBlueprint *> *node;
	public:
		setNodeParameter (expressionVector<baseType> * p, expression<nodeBlueprint*> *n) : parameter(p), node(n) {}
		virtual nodeBlueprint * evaluate() { ((dynNode*)  (node->evaluate() ))-> params<baseType>::rerouteParams((parameter->evaluate()));  return node->evaluate(); }
};


class setEdgeParameter : public expression<edgeBlueprint*>
{
	private:
		expressionVector<baseType> * parameter;
		expression<edgeBlueprint *>* edge;
	public:
		setEdgeParameter (expressionVector<baseType>* p, expression<edgeBlueprint *> *e) : parameter(p), edge(e) {}
		virtual edgeBlueprint* evaluate(); 

};



template <typename T>
class randomVector : public command
{
	private:
		vector <bindExpression <T>*> vec;
	
	public:
		void push_back(bindExpression<T> *el) { vec.push_back(el); }
		vector < function<T() > > evaluate()
			{
				vector<function <T()>  > resVec; 
				for (unsigned int i = 0; i < vec.size(); i++)
					resVec.push_back((baseType)vec[i]->_f);
				return resVec;
			}
};


//! TODO hier ist irgendwas faul. Der bison macht da eventuell unendlich lange Bäume, wenn int und double ineinander umwandelbar sind.
class convertToInt : public expression <nodeDescriptor>
{
	private:
		expression<double> *dExp;
	public:
		convertToInt(expression<double> *d) : dExp(d) {};
		nodeDescriptor evaluate() { return (nodeDescriptor)dExp->evaluate(); };
};


//! TODO hier ist irgendwas faul. Der bison macht da eventuell unendlich lange Bäume, wenn int und double ineinander umwandelbar sind.
class convertToBaseType : public expression <baseType>
{
	private:
		expression<nodeDescriptor> *dExp;
	public:
		convertToBaseType(expression<nodeDescriptor> *d) : dExp(d) {};
		baseType evaluate() { return (baseType)dExp->evaluate(); };
};





//! Instruction, die nix macht. Für Instructionen im Parse-Baum, die nur während des Parsens-was zu tun haben.
class emptyInstruction : public instruction
{
	public:
		emptyInstruction() {};
		void execute () {};
};

//! Einfache Schleife, bei der der Rumpf wiederholt wird, ohne Zählvariable
class loopInstruction : public instruction
{
	private:
		expression<nodeDescriptor> * count;
		instruction *ins;
	
	public:
		loopInstruction(expression<nodeDescriptor> * c, instruction *i) : count (c), ins(i) {};
		void execute() {
			for (unsigned int i = 0; i < (unsigned int) count ->evaluate(); i++)
				ins->execute();
		};
};



//! Instruction für eine while-Schleife
class whileInstruction : public instruction
{
	private:
		expression<bool> *cond;
		instruction *ins;
	public:
		whileInstruction(expression<bool> * c, instruction *i) : cond(c), ins(i) {};
		void execute()
		{
			while (cond->evaluate())
				ins->execute();
		}
};


//! If-Instruction.
class ifInstruction : public instruction
{
	private:
		expression<bool> *cond;
		instruction *ins;
	public:
		ifInstruction(expression<bool> * c, instruction *i) : cond(c), ins(i) {};
		void execute()
		{
			if (cond->evaluate())
				ins->execute();
		}
};


//!  Instructions-Klasse für Schleifen, mit Condor vectorisiert werden sollen. Funktioniert am besten, wenn die einzelnen Schleifendurchläufe unabhängig voneinander sind. neuroCondor erzeugt dann einen condor-dag, bei dem die Schleifendurchläufe einzeln als Jobs realisiert sind. Funktioniert auch mit 2 ineinander geschachtelten Schleifen. Bei 3 ist es nicht getestet und geht wahrscheinlich in die Hose. 
class vectorForInstruction : public instruction
{
	private:


		instruction *start;
		expression<bool> *cond;
		instruction *inc;
		instruction *body;
		bool isChained;

		static unsigned int loopCounter;
		static vector<int> iterations;
		static ofstream chefDag;
		static stringstream chefDagEnding;
		static ofstream condorSkript;
		static stringstream jobName;

		static params<baseType> *p;

		string currentJobName();


		void submitToCondor();
		
	public:
			

         static void registerStandardValues() {
            p->registerStandard ( _vectorForInstruction_,"vectorForInstruction_linux64",0,1.0);
            p->registerStandard ( _vectorForInstruction_,"vectorForInstruction_linux32",1,1.0);
            p->registerStandard ( _vectorForInstruction_,"vectorForInstruction_windows51",2,1.0);            		p->registerStandard ( _vectorForInstruction_,   "vectorForInstruction_windows60",3,1.0);
            p->registerStandard ( _vectorForInstruction_,"vectorForInstruction_windows61",4,1.0);
		
		p = new params<baseType> (_vectorForInstruction_);	

         }
		
		static	 bool linux64() { return p->getParams(0) > 0.0; };
		static	 bool linux32() { return p->getParams(1) > 0.0; };
		static	 bool win51() { return   p->getParams(2) > 0.0; };
		static	 bool win60() { return   p->getParams(3) > 0.0; };
		static	 bool win61() { return   p->getParams(4) > 0.0; };






		static void writeCondorSkript();

		static unsigned int nestedness;
		static void registerNewLoop() { nestedness++; }
		vectorForInstruction(instruction *s, expression<bool> * c, instruction *i, instruction *b, bool chained) : start(s), cond(c), inc(i), body(b), isChained(chained)  {};

		void execute()
		{


			if (commandLineArguments::arg.size() < 3 + loopCounter)
			{	
				loopCounter++;		
				submitToCondor();
				loopCounter--;
			}
			else
			{
				int counter = atoi(commandLineArguments::arg[2+loopCounter].c_str());
				loopCounter++;
				cout << "Ausführen des " << counter<<".ten Schleifendurchlauf. " << endl;
				start->execute();
				for (int i = 0; i < counter; i++)
				{
					inc->execute();
				}		
				body->execute();
			}
		}



};






//! Instruction für for-schleifen
class forInstruction : public instruction
{
	private:
		instruction *start;
		expression<bool> *cond;
		instruction *inc;
		instruction *body;
	public:
		forInstruction(instruction *s, expression<bool> * c, instruction *i, instruction *b) : start(s), cond(c), inc(i), body(b) {};
		void execute()
		{
			start->execute();
			while (cond->evaluate())
			{
				body->execute();
				inc->execute();
			}
		}
};





//! Instruction, die etwas auf die Konsole schreibt.
template <typename T>
class printInstruction : public instruction
{
	private:
		expression<T> *dExp;
	public:
		printInstruction(expression<T> *d) : dExp(d) {};
		void execute() { cout << dExp->evaluate(); }
};


#include <iomanip>

class printInstructionDouble : public instruction
{
	private:
		expression<baseType> *dExp;
	public:
		printInstructionDouble(expression<baseType> *d) : dExp(d) {};
		void execute() { cout  << setprecision (12) << dExp->evaluate(); }
};







//! Ausdruck, der den Wert einer Varieblen zurückgibt
template <typename T>
class varCommand : public expression<T>
{
	private:
		T *target;
	public:
		varCommand (string s) { 	target = command::retrieve<T> (s); }
		T evaluate() { return *target; };
		void assign(T newData) { *target = newData; }

};



//! Ausdruck, der einen Konstanten Wert zurückgibt. Wird verwendet für alle Zahlen, die in den Conedy-Skripten stehen
template <typename T>
class constantCommand : public expression<T>
{
	private:
		const T  value;
	public:
	constantCommand(T v) : value(v){};
	T evaluate() { return value; };
};






#define _E(type,pointer) (bind(&expression<type>::evaluate,(pointer)))

#if CONDOR






#define INTNETWORKFUNK(funktionName, net)  new constantCommand <nodeDescriptor> (0)
#define INTNETWORKFUNK1(funktionName, net, arg1)  new constantCommand <nodeDescriptor> (0)
#define INTNETWORKFUNK2(funktionName, net, arg1, arg2)    new constantCommand <nodeDescriptor> (0)
#define INTNETWORKFUNK3(funktionName, net, arg1, arg2, arg3)    new constantCommand <nodeDescriptor> (0)
#define INTNETWORKFUNK4(funktionName, net, arg1, arg2, arg3, arg4)    new constantCommand <nodeDescriptor> (0)
#define INTNETWORKFUNK5(funktionName, net, arg1, arg2, arg3, arg4, arg5)    new constantCommand <nodeDescriptor> (0)

#define BASETYPENETWORKFUNK(funktionName, net)  new constantCommand <baseType> (0)
#define BASETYPENETWORKFUNK1(funktionName, net, arg1)  new constantCommand <baseType> (0)
#define BASETYPENETWORKFUNK2(funktionName, net, arg1, arg2)    new constantCommand <baseType> (0)

#define BOOLNETWORKFUNK(funktionName, net)  new constantCommand <bool> (0)
#define BOOLNETWORKFUNK1(funktionName, net, arg1)  new constantCommand <bool> (0)
#define BOOLNETWORKFUNK2(funktionName, net, arg1, arg2)    new constantCommand <bool> (0)

#define NETWORKFUNK(funktionName, net)  new bindInstruction(bind(&emptyFunction))

#define NETWORKFUNK1(funktionName, net, arg1) new bindInstruction(bind(&emptyFunction)) 

#define NETWORKFUNK2(funktionName, net, arg1, arg2) new bindInstruction(bind(&emptyFunction)) 


#define NETWORKFUNK3(funktionName, net, arg1, arg2,arg3) new bindInstruction(bind(&emptyFunction)) 

#define NETWORKFUNK4(funktionName, net, arg1, arg2,arg3,arg4) new bindInstruction(bind(&emptyFunction)) 

#define NETWORKFUNK5(funktionName, net, arg1, arg2,arg3,arg4,arg5) new bindInstruction(bind(&emptyFunction)) 

#define NETWORKFUNK6(funktionName, net, arg1, arg2,arg3,arg4,arg5, arg6) new bindInstruction(bind(&emptyFunction)) 

#else


#define BOOLNETWORKFUNK(funktionName, net)  new bindExpression <bool> (bind(&networkTemplate::funktionName, net))
#define BOOLNETWORKFUNK1(funktionName, net, arg1)  new bindExpression <bool> (bind(&networkTemplate::funktionName, net, (arg1)   ))
#define BOOLNETWORKFUNK2(funktionName, net, arg1, arg2)  new bindExpression <bool> (bind(&networkTemplate::funktionName, net, (arg1), (arg2)   ))


#define BASETYPENETWORKFUNK(funktionName, net)  new bindExpression <baseType> (bind(&networkTemplate::funktionName, net))
#define BASETYPENETWORKFUNK1(funktionName, net, arg1)  new bindExpression <baseType> (bind(&networkTemplate::funktionName, net, (arg1)   ))
#define BASETYPENETWORKFUNK2(funktionName, net, arg1, arg2)  new bindExpression <baseType> (bind(&networkTemplate::funktionName, net, (arg1), (arg2)   ))

#define INTNETWORKFUNK(funktionName, net)  new bindExpression <nodeDescriptor> (bind(&networkTemplate::funktionName, net))
#define INTNETWORKFUNK1(funktionName, net, arg1)  new bindExpression <nodeDescriptor> (bind(&networkTemplate::funktionName, net, (arg1)   ))
#define INTNETWORKFUNK2(funktionName, net, arg1, arg2)  new bindExpression <nodeDescriptor> (bind(&networkTemplate::funktionName, net, (arg1), (arg2)   ))
#define INTNETWORKFUNK3(funktionName, net, arg1, arg2, arg3)  new bindExpression <nodeDescriptor> (bind(&networkTemplate::funktionName, net, (arg1), (arg2), (arg3)   ))
#define INTNETWORKFUNK4(funktionName, net, arg1, arg2, arg3, arg4)  new bindExpression <nodeDescriptor> (bind(&networkTemplate::funktionName, net, (arg1), (arg2), (arg3), (arg4)   ))
#define INTNETWORKFUNK5(funktionName, net, arg1, arg2, arg3, arg4, arg5)  new bindExpression <nodeDescriptor> (bind(&networkTemplate::funktionName, net, (arg1), (arg2), (arg3), (arg4), (arg5)   ))


#define NETWORKFUNK(funktionName, net)  new bindInstruction(bind(&networkTemplate::funktionName, net )) 

#define NETWORKFUNK1(funktionName, net, arg1) new bindInstruction(bind(&networkTemplate::funktionName, net, (arg1) ))

#define NETWORKFUNK2(funktionName, net, arg1, arg2) new bindInstruction(bind(&networkTemplate::funktionName, net, (arg1) , (arg2) ))


#define NETWORKFUNK3(funktionName, net, arg1, arg2,arg3) new bindInstruction(bind(&networkTemplate::funktionName, net, (arg1),(arg2),(arg3) ))

#define NETWORKFUNK4(funktionName, net, arg1, arg2,arg3,arg4) new bindInstruction(bind(&networkTemplate::funktionName, net, (arg1) , (arg2),(arg3),(arg4) ))

#define NETWORKFUNK5(funktionName, net, arg1, arg2,arg3,arg4,arg5) new bindInstruction(bind(&networkTemplate::funktionName, net, (arg1) , (arg2),(arg3),(arg4),(arg5) ))

#define NETWORKFUNK6(funktionName, net, arg1, arg2,arg3,arg4,arg5, arg6) new bindInstruction(bind(&networkTemplate::funktionName, net, (arg1) , (arg2),(arg3),(arg4),(arg5), (arg6) ))







#endif







//$$ = NETWORKFUNK (EVAL(int,$5), EVAL (double,$7))

#define DECLAREUNARY(x,name, type)  \
	template <typename L> \
	class  name ##Command ## type : public expression < type > \
	{\
		private:\
			expression< L > *left;\
		public:\
		name ## Command ## type (expression< L > *l) { left = l;}\
		type evaluate () { return (  x ( left->evaluate() ) ) ;  } \
		  \
	};




#define DECLAREBINARY(x, name, type) \
	template <typename L, typename R> \
	class  name ##Command ## type : public expression < type > \
	{\
		private:\
			expression< L > *left;\
			expression< R > *right;\
		public:\
		name ## Command ## type (expression< L > *l, expression< R > *r) { left = l; right = r ;}\
		type evaluate () { return ( left->evaluate()) x right->evaluate();  } \
		  \
	};


//			cout << "Iam calculating:" << left->evaluate() << #x << right->evaluate() << endl;
//		cout << "Result:" << ( ( left->evaluate()) x right->evaluate() )  ;


DECLAREBINARY(+, plus, nodeDescriptor)
DECLAREBINARY(-, minus, nodeDescriptor)
DECLAREBINARY(*,times, nodeDescriptor)
DECLAREBINARY(/,divide, nodeDescriptor)

DECLAREBINARY(+, plus, baseType)
DECLAREBINARY(-,minus, baseType)
DECLAREBINARY(*,times, baseType)
DECLAREBINARY(/,divide, baseType)

DECLAREBINARY(%,modolo, nodeDescriptor)



DECLAREBINARY( != , nequal, bool)
DECLAREBINARY( <, less, bool)
DECLAREBINARY( >, greater, bool)
DECLAREBINARY( >=, greaterEqual, bool)
DECLAREBINARY( <=, lessEqual, bool)
DECLAREBINARY( == , equal, bool)




DECLAREUNARY(log,log,baseType)
DECLAREUNARY(exp,exp,baseType)	
DECLAREUNARY(sin,sin,baseType)	



// Boolean


DECLAREBINARY(||, or, bool);
DECLAREBINARY(&&, and , bool);

	//! Ausdruck, der das Negat von Booleans zurückgibt
	class notCommand : public expression<bool> 
	{
		private:
			expression<bool> *left;
		public:
		notCommand (expression<bool> *l) : left(l) { };
		bool evaluate () { return !left->evaluate();  } 
	};





/*	class lessCommand : public expression<bool> 
	{
		private:
			expression<double> *left;
			expression<double> *right;
		public:
		lessCommand (expression<double> *l, expression<double> *r) { left = l; right = r ;}
		bool evaluate () { return left->evaluate() < right->evaluate(); } 
	};

class greaterCommand : public expression<bool> 
	{
		private:
			expression<double> *left;
			expression<double> *right;
		public:
		greaterCommand (expression<double> *l, expression<double> *r) { left = l; right = r ;}
		bool evaluate () { return left->evaluate() > right->evaluate(); } 
	};

class equalCommand : public expression<bool> 
	{
		private:
			expression<double> *left;
			expression<double> *right;
		public:
		equalCommand (expression<double> *l, expression<double> *r) { left = l; right = r ;}
		bool evaluate () { return left->evaluate() == right->evaluate(); } 
	};
*/

//! Zuweisungs-Anweisung a= 4.0;
template <typename T>
class assignInstruction : public instruction
{
	private:
		varCommand<T> *target;
		expression<T> *value;
	public:
		assignInstruction(varCommand<T> *var, expression<T> *dExp): target(var), value(dExp) {};
		void execute () { target->assign(value->evaluate());}
 };




//! Expression-Objekt, das zwei Strings concateniert.
template <typename X, typename Y>
class stringCat : public expression<string>
{
	private:
		expression <X> *left;
		expression <Y> *right;
	public:
	stringCat (expression <X> *l, expression <Y> *r): left(l), right(r) {};
	string evaluate()
	{
		stringstream ss;
		ss << left->evaluate();
		ss << right->evaluate();
		return ss.str();
	}
};



//! Expression-Objekt, das pwei Strings concateniort.
template <typename X>
class stringCat<X,double> : public expression<string>
{
	private:
		expression <X> *left;
		expression <double> *right;
	public:
	stringCat (expression <X> *l, expression <double> *r): left(l), right(r) {};
	string evaluate()
	{
		stringstream ss;
		stringstream doublestring;

		ss << left->evaluate();
		double val = right->evaluate();
		doublestring << val;
		if (doublestring.str().find('.') == string::npos)
			doublestring << ".0";
		ss << doublestring.str();
		return ss.str();
	}
	


};


	//! BlauPausen-node, der mit einer bestimmten Warhscheinlichkeit eine von zwei anderen nodes zurüchgibt.
	class randomBlueprintNode :  public nodeVirtualEdges <dynNode >
{
		private:
	//		node **blueprint1;
	//		node **blueprint2;
			expression<nodeBlueprint*> *blueprint1;
			expression<nodeBlueprint*> *blueprint2;

			double probability;
		public:
    virtual bool timeEvolution () {return 0;};
			randomBlueprintNode(expression<nodeBlueprint*> *b1, expression<nodeBlueprint*> *b2, double p) : blueprint1(b1), blueprint2(b2), probability(p) {}	
			virtual const nodeInfo getNodeInfo() { nodeInfo n = {_randomBlueprintNode_,_dynNode_};     return n; };
			void printStatistics() { cout << "randomBlueprintNode" << endl; }		
			virtual const unsigned int dimension () const { return 0; }
			virtual node * construct()
			{
				if (gslNoise::getUniform(0.0,1.0) < probability)
					return (blueprint1->evaluate())->construct();
				else	
					return (blueprint2->evaluate())->construct();

			}



	};



#endif
