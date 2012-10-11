#ifndef instruction_h
#define instruction_h instruction_h

#include <map>
#include <string>
#include <iostream>

#include "stream.h"
#include "fullNetwork.h"

#include "commandLineArguments.h"
#include "gslNoise.h"
#include "network.h"
#include "nodeImplement.h"


#include "command.h"
#include "globals.h"

#include <iomanip>
#include "expression.h"



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
				cout << "executing " << counter<<". loop iteration." << endl;
				start->execute();
				for (int i = 0; i < counter; i++)
				{
					inc->execute();
				}
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

#if CONDOR






#define INTNETWORKFUNK(funktionName, net)  new constantCommand <int> (0)
#define INTNETWORKFUNK1(funktionName, net, arg1)  new constantCommand <int> (0)
#define INTNETWORKFUNK2(funktionName, net, arg1, arg2)    new constantCommand <int> (0)
#define INTNETWORKFUNK3(funktionName, net, arg1, arg2, arg3)    new constantCommand <int> (0)
#define INTNETWORKFUNK4(funktionName, net, arg1, arg2, arg3, arg4)    new constantCommand <int> (0)
#define INTNETWORKFUNK5(funktionName, net, arg1, arg2, arg3, arg4, arg5)    new constantCommand <int> (0)

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

#define INTNETWORKFUNK(funktionName, net)  new bindExpression <int> (bind(&networkTemplate::funktionName, net))
#define INTNETWORKFUNK1(funktionName, net, arg1)  new bindExpression <int> (bind(&networkTemplate::funktionName, net, (arg1)   ))
#define INTNETWORKFUNK2(funktionName, net, arg1, arg2)  new bindExpression <int> (bind(&networkTemplate::funktionName, net, (arg1), (arg2)   ))
#define INTNETWORKFUNK3(funktionName, net, arg1, arg2, arg3)  new bindExpression <int> (bind(&networkTemplate::funktionName, net, (arg1), (arg2), (arg3)   ))
#define INTNETWORKFUNK4(funktionName, net, arg1, arg2, arg3, arg4)  new bindExpression <int> (bind(&networkTemplate::funktionName, net, (arg1), (arg2), (arg3), (arg4)   ))
#define INTNETWORKFUNK5(funktionName, net, arg1, arg2, arg3, arg4, arg5)  new bindExpression <int> (bind(&networkTemplate::funktionName, net, (arg1), (arg2), (arg3), (arg4), (arg5)   ))


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
			doublestring << setprecision(12) << val;
			if (doublestring.str().find('.') == string::npos)
				doublestring << ".0";
			ss   << doublestring.str();
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
		virtual const nodeInfo getNodeInfo() { nodeInfo n = {_randomBlueprintNode_,_dynNode_, "randomBlueprintNode" };     return n; };
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
