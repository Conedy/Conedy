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


template <typename T>
struct typeInteger
{
//		enum { result = 666; }
};



template<> struct typeInteger<int> { enum { result = 0 }; };
template<> struct typeInteger<double> { enum { result = 1 }; };
template<> struct typeInteger<string> { enum { result = 2 }; };
#ifndef PYTHON
template<> struct typeInteger<bool> { enum { result = 3 }; };
#else
template<> struct typeInteger<bool> { enum { result = 0 }; };
#endif
template<> struct typeInteger<float> { enum { result = 4 }; };
template<> struct typeInteger<long double> { enum { result = 5 }; };





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
			type[name] = typeInteger<T>::result;
			value[name] = new T (v);
#ifndef PYTHON
			command::declare(name, (T*)value[name]);
#endif
		}

		template <typename T> static T getGlobal(string name)
		{
			int typeInt = typeInteger <T>::result;

			if (type.count(name) > 0)
			{
				if (type[name] == typeInt)
					return * ((T*) value[name]) ;

				stringstream fehler;
				fehler <<  "Type mismatch: You try to get " << name <<  " as " << typeString(typeInt) << ". However, " << name << " is of type " << typeString(type[name]) << endl;
				throw fehler.str().c_str();
			}
			else
			{
				stringstream fehler;
				fehler << "Unknown string in getGlobal: " << name << endl;
				throw fehler.str().c_str();
			}
		}

		template <typename T> static T* getPointerToGlobal(string name)
		{
			int typeInt = typeInteger <T>::result;

			if (type.count(name) > 0)
			{
				if (type[name] == typeInt)
					return ((T*) value[name]) ;

				stringstream fehler;
				fehler <<  "Type mismatch: You try to get " << name <<  " as " << typeString(typeInt) << ". However, " << name <<	" is of type " << typeString(type[name]) << endl;
				throw fehler.str().c_str();
			}
			else
			{
				stringstream fehler;
				fehler << "Unknown string in getPointerToGlobal: " << name << endl;
				throw fehler.str().c_str();
			}
		}

		template <typename T> static void setGlobal(string name, T d)
		{
			if (type.count(name) > 0)
			{
				if (type [name] == typeInteger <T>::result)
					* ((T*)value[name]) = d;
				else
				{
					stringstream fehler;
					fehler << "Type mismatch: " << name << " is of type " << typeString(type[name]) << ". But you try to set it as a " << typeString(typeInteger<T>::result) << endl;;
					throw fehler.str().c_str();
				}
			}
			else
				params<T>::setStandard (name, d);
		}
};

#endif
