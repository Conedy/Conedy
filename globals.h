#ifndef globals_h
#define globals_h globals_h

#include <map>
#include <iostream>
#include <sstream>
#include <string>
#include "baseType.h"

#include "command.h"

#include "params.h"

using namespace std;

int typeInteger(int);
int typeInteger(double);
int typeInteger(string);
int typeInteger(bool);
int typeInteger(float);
int typeInteger(long double);


// Maps of Types to ints for identification and to strings for error texts.

//template <class T> int typeInteger(T);
// template <class T> int typeInteger(T) {return -1;};


class globals
{
	private:

		string static typeString(int type)
		{
			switch ( type )
			{
				case 0:
					return "int";
				case 1:
					return "double";
				case 2:
					return "string";
				case 3:
					return "bool";
				case 4:
					return "float";
				case 5:
					return "long double";
				default:
					stringstream fehler;
					fehler << "You are using a non-predefined type (" << type << "). To predefine this type, modify globals.h." << endl;
					throw fehler.str().c_str();
			}
		}

		static map <string, void*> value;
		static map <string, int> type;

	public:

		template <typename T> static void registerGlobal(string name, T v)
		{
			type[name] = typeInteger(v);
			value[name] = new T (v);
#ifndef PYTHON
			command::declare(name, (T*)value[name]);
#endif
		}

		template <typename T> static T getGlobal(string name)
		{
			T dummy; int typeInt = typeInteger(dummy);

			if (type.count(name) > 0)
			{
				if (type[name] == typeInt)
					return * ((T*) value[name]) ;

				stringstream fehler;
				fehler <<  "Type mismatch: You try to get " << name <<  " as " << typeString(typeInt) << ". However, " << name <<	" is of type " << typeString(type[name]) << endl;
				throw fehler.str().c_str();
			}
			else
			{
				cerr << name << endl;
				throw "unknown string in getGlobal.";
			}
		}

		template <typename T> static T* getPointerToGlobal(string name)
		{
			T dummy; int typeInt = typeInteger(dummy);

			if (type.count(name) > 0)
			{
				if (type[name] == typeInt)
					return ((T*) value[name]) ;

				stringstream fehler;
				fehler <<  "Type mismatch: You try to get " << name <<  " as " << typeString(typeInt) << ". However, " << name <<	" is of type " << typeString(type[name]) << endl;;
				throw fehler.str().c_str();
			}
			else throw "unknown string in getGlobal.";
		}

		template <typename T> static void setGlobal(string name, T d)
		{
			if (type.count(name) > 0)
			{
				if (type [name] == typeInteger(d))
					* ((T*)value[name]) = d;
				else
				{
					stringstream fehler;
					fehler << "Type mismatch: " << name << " is of type " << typeString(type[name]) << ". But you try to set it as a " << typeString(typeInteger(d)) << endl;;
					throw fehler.str().c_str();
				}
			}
			else
				params<T>::setStandard (name, d);
		}
};

#endif
