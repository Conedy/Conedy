#ifndef globals_h
#define globals_h globals_h

#include <map>
#include <iostream>
#include <string>
#include "baseType.h"

#include "command.h"

#include "params.h"


using namespace std;

// Maps of Types to ints for identification and to strings for error texts.

//template <class T> int typeInteger(T);
template <class T> int typeInteger(T) {return -1;};




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
					cout << "Type:"<< type << endl;
					throw "You are using a non-predefined type. To predefine this type, modify globals.h.";
			}
		}

		static map <string, void*> value;
		static map <string, int> type;

	public:

		template <typename T> static void registerGlobal(string name, T v)
		{
			type[name] = typeInteger<T>(v);
			value[name] = new T (v);
#ifndef PYTHON
			command::declare(name, (T*)value[name]);
#endif
		}

		template <typename T> static T getGlobal(string name)



		{

			T  dummy;
			if (type.count(name) > 0)
			{
				if (type[name] == typeInteger<T>(dummy))
					return * ((T*) value[name]) ;
				cerr <<  "Type mismatch: You try to get " << name	<<  " as " << typeString(typeInteger<T>(dummy)) << ". However, " << name <<	" is of type " << typeString(type[name]);
				throw "\n";
			}
			else
			{
				cerr << name << endl;
				throw "unknown string in getGlobal.";
			}
		}

		template <typename T> static T* getPointerToGlobal(string name)
		{
			T  dummy;
			if (type.count(name) > 0)
			{
				if (type[name] == typeInteger<T>(dummy))
					return ((T*) value[name]) ;
				cerr <<  "Type mismatch: You try to get " << name	<<  " as " << typeString(typeInteger<T>(dummy)) << ". However, " << name <<	" is of type " << typeString(type[name]);
				throw "\n";
			}
			else throw "unknown string in getGlobal.";
		}

		template <typename T> static void setGlobal(string name, T d)
		{
			if (type.count(name) > 0)
			{
				if (type [name] == typeInteger<T>(d))
					* ((T*)value[name]) = d;
				else
				{
					cerr << "Type mismatch: " << name << " is of type " << typeString(type[name]) << ". But you try to set it as a " << typeString(typeInteger<T>(d));
					throw "\n";
				}
			}
			else 
				params<T>::setStandard (name, d);
		}
};

template <> inline int typeInteger <>(int) { return 0;}
template <> inline int typeInteger <>(double) { return 1;}
template <> inline int typeInteger <>(string) { return 2;}
template <> inline int typeInteger <>(bool) { return 0;}
template <> inline int typeInteger <>(float) { return 4;}
template <> inline int typeInteger <>(long double) { return 5;}

#endif
