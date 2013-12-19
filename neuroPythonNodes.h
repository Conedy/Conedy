
#ifndef __neuroPythonNodes_h
#define __neuroPythonNodes_h __neuroPythonNodes_h
#include "fullNetworkWithNodes.h"
#include "docstringsNodes.h"

#include <boost/python.hpp>

using namespace boost::python;

void revealNodesToPython ();


template <class N>
	 N* nodeFactory1 (double arg1)
	{
		N* res = new N();
		vector <baseType> allParams;
		allParams.push_back(arg1);
		res->rerouteParams(allParams);return res;
	}


template <class N>
	 N* nodeFactory2 (double arg1, double arg2)
	{
		N* res = new N();
		vector <baseType> allParams;
		allParams.push_back(arg1);
		allParams.push_back(arg2);
		res->rerouteParams(allParams);return res;
	}

template <class N>
	 N* nodeFactory3 (double arg1, double arg2, double arg3)
	{
		N* res = new N();
		vector <baseType> allParams;
		allParams.push_back(arg1);
		allParams.push_back(arg2);
		allParams.push_back(arg3);
		res->rerouteParams(allParams);return res;
	}

template <class N>
	 N* nodeFactory4 (double arg1, double arg2, double arg3, double arg4)
	{
		N* res = new N();
		vector <baseType> allParams;
		allParams.push_back(arg1);
		allParams.push_back(arg2);
		allParams.push_back(arg3);
		allParams.push_back(arg4);
		res->rerouteParams(allParams);return res;
	}

template <class N>
	 N* nodeFactory5 (double arg1, double arg2, double arg3, double arg4, double arg5)
	{
		N* res = new N();
		vector <baseType> allParams;
		allParams.push_back(arg1);
		allParams.push_back(arg2);
		allParams.push_back(arg3);
		allParams.push_back(arg4);
		allParams.push_back(arg5);
		res->rerouteParams(allParams);return res;
	}


template <class N>
	 N* nodeFactory6 (double arg1, double arg2, double arg3, double arg4, double arg5, double arg6)
	{
		N* res = new N();
		vector <baseType> allParams;
		allParams.push_back(arg1);
		allParams.push_back(arg2);
		allParams.push_back(arg3);
		allParams.push_back(arg4);
		allParams.push_back(arg5);
		allParams.push_back(arg6);
		res->rerouteParams(allParams);return res;
	}

template <class N>
	 N* nodeFactory7 (double arg1, double arg2, double arg3, double arg4, double arg5, double arg6, double arg7)
	{
		N* res = new N();
		vector <baseType> allParams;
		allParams.push_back(arg1);
		allParams.push_back(arg2);
		allParams.push_back(arg3);
		allParams.push_back(arg4);
		allParams.push_back(arg5);
		allParams.push_back(arg6);
		allParams.push_back(arg7);
		res->rerouteParams(allParams);return res;
	}

template <class N>
	 N* nodeFactory8 (double arg1, double arg2, double arg3, double arg4, double arg5, double arg6, double arg7, double arg8)
	{
		N* res = new N();
		vector <baseType> allParams;
		allParams.push_back(arg1);
		allParams.push_back(arg2);
		allParams.push_back(arg3);
		allParams.push_back(arg4);
		allParams.push_back(arg5);
		allParams.push_back(arg6);
		allParams.push_back(arg7);
		allParams.push_back(arg8);
		res->rerouteParams(allParams);return res;
	}


template <class N>
	 N* nodeFactory9 (double arg1, double arg2, double arg3, double arg4, double arg5, double arg6, double arg7, double arg8, double arg9)
	{
		N* res = new N();
		vector <baseType> allParams;
		allParams.push_back(arg1);
		allParams.push_back(arg2);
		allParams.push_back(arg3);
		allParams.push_back(arg4);
		allParams.push_back(arg5);
		allParams.push_back(arg6);
		allParams.push_back(arg7);
		allParams.push_back(arg8);
		allParams.push_back(arg9);
		res->rerouteParams(allParams);return res;
	}



#endif
