#ifndef instruction_h
#define instruction_h instruction_h

#include <map>
#include <string>
#include <iostream>

#include "stream.h"
//#include "fullNetwork.h"

#include "commandLineArguments.h"
#include "gslNoise.h"
//#include "network.h"
//#include "nodeImplement.h"


#include "globals.h"

#include <iomanip>
#include "expression.h"
#include <list>


//! Basis-Klasse für alle Instructionen.

//! Instruction, die einen shell-Befehl ausführt.
class systemInstruction : public instruction
{
	private:
		expression <string> *theCommand;
	public:
		systemInstruction(expression<string> *c) : theCommand(c) {};
		virtual void execute()
		{
			if (system(theCommand->evaluate().c_str()))
			{
				cout <<  "system Command Failed!" << endl;
								throw theCommand->evaluate().c_str();
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
		expression<int> * count;
		instruction *ins;

	public:
		loopInstruction(expression<int> * c, instruction *i) : count (c), ins(i) {};
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
class vectorForInstruction : public instruction, private globals
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
			registerGlobal<bool>("LINUX_x86_64", false);
			registerGlobal<bool>("LINUX_x86", false);
			registerGlobal<bool>("WINNT51_x86", false);
			registerGlobal<bool>("WINNT60_x86", false);
			registerGlobal<bool>("WINNT61_x86", false);
			registerGlobal<string>("universe", "vanilla");
			registerGlobal<bool>("niceUser",false);
			registerGlobal<baseType>("priority",0.0);

#ifdef ARCHITECTURE
#define linuxify(y) LINUX_ ## y
#define xlinuxify(y) linuxify(y)
#define stringify(a) #a
#define xstringify(a) stringify(a)
			setGlobal<bool>(xstringify(xlinuxify(ARCHITECTURE)), true);
#endif
			}



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
				cout << "executing " << counter<<". ";
				if (isChained) cout << "chained ";	
				cout << " loop iteration." << endl;
				start->execute();
				for (int i = 0; i < counter; i++)
				{
					inc->execute();
				}
				if (!cond->evaluate()) { cout << "Warning: Loop Condition is not fulfilled." << endl; }
				
				body->execute();
			}
		}
};


//! Instruction für for-Schleifen
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



class printInstructionDouble : public instruction
{
	private:
		expression<baseType> *dExp;
	public:
		printInstructionDouble(expression<baseType> *d) : dExp(d) {};
		void execute() { cout  << setprecision (12) << dExp->evaluate(); }
};










#define _E(type,pointer) (bind(&expression<type>::evaluate,(pointer)))




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


DECLAREBINARY(+, plus, int)
DECLAREBINARY(-, minus, int)
DECLAREBINARY(*, times, int)
DECLAREBINARY(/, divide, int)

DECLAREBINARY(+, plus, baseType)
DECLAREBINARY(-, minus, baseType)
DECLAREBINARY(*, times, baseType)
DECLAREBINARY(/, divide, baseType)

DECLAREBINARY(%, modolo, int)



DECLAREBINARY( != , nequal, bool)
DECLAREBINARY( <, less, bool)
DECLAREBINARY( >, greater, bool)
DECLAREBINARY( >=, greaterEqual, bool)
DECLAREBINARY( <=, lessEqual, bool)
DECLAREBINARY( == , equal, bool)




DECLAREUNARY(log,log,baseType)
DECLAREUNARY(exp,exp,baseType)
DECLAREUNARY(sin,sin,baseType)
DECLAREUNARY(sqrt,sqrt,baseType)



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
class stringCat<X,baseType> : public expression<string>
{
	private:
		expression <X> *left;
		expression <baseType> *right;
	public:
		stringCat (expression <X> *l, expression <baseType> *r): left(l), right(r) {};
		string evaluate()
		{
			stringstream ss;
			stringstream baseTypestring;

			ss << left->evaluate();
			baseType val = right->evaluate();
			baseTypestring << setprecision(12) << val;
			if (baseTypestring.str().find('.') == string::npos)
				baseTypestring << ".0";
			ss   << baseTypestring.str();
			return ss.str();
		}



};



#endif
