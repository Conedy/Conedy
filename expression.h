#ifndef __expression
#define __expression


#include "command.h"
#include <boost/function.hpp>
#include "dynNode.h"

using namespace boost;


template <typename T>
class expression : public instruction
{
	public:
		//! Werte den  Ausdruck aus.
		virtual T evaluate() { return (T)0; }
		virtual void execute() { this->evaluate(); }
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



class convertToNodeDescriptor : public expression <nodeDescriptor>
{

	private:
		expression<int> *nExp;
	public:
		convertToNodeDescriptor(expression<int> *n) : nExp(n) {};
		nodeDescriptor evaluate() {
			if (nExp->evaluate() < 0)
				throw "Negative Node Number !";
			return (nodeDescriptor)nExp->evaluate();

		};

};


//! TODO hier ist irgendwas faul. Der bison macht da eventuell unendlich lange Bäume, wenn int und double ineinander umwandelbar sind.
class convertToInt : public expression <int>
{
	private:
		expression<baseType> *dExp;
	public:
		convertToInt(expression<baseType> *d) : dExp(d) {};
		int evaluate() { return (nodeDescriptor)dExp->evaluate(); };
};


//! TODO hier ist irgendwas faul. Der bison macht da eventuell unendlich lange Bäume, wenn int und double ineinander umwandelbar sind.
class convertIntegerToBaseType : public expression <baseType>
{
	private:
		expression<int> *dExp;
	public:
		convertIntegerToBaseType(expression<int> *d) : dExp(d) {};
		baseType evaluate() { return (baseType)dExp->evaluate(); };
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
		virtual nodeBlueprint * evaluate() { (  (node->evaluate() ))-> params<baseType>::rerouteParams((parameter->evaluate()));  return node->evaluate(); }
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









#endif 
