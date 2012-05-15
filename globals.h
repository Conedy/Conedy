#include <map>
#include <iostream>

template <typename X, typename Y> bool isOfSameType <X,Y>()
{ return typeInteger<X>() == typeInteger<Y>(); }

// Maps of Types to ints for identification and to strings for error texts.

template <typename T> int typeInteger<T>() {return -1;};

template <> int typeInteger <int>() { return 0;}
template <> int typeInteger <double>() { return 1;}
template <> int typeInteger <string>() { return 2;}
template <> int typeInteger <bool>() { return 3;}

class globals
{
	private:

		string typeString(int type)
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
				default:
					throw "You are using a non-predefined type. To predefine this type, modify globals.h."
			}
		}

		static map <string, void*> value;
		static map <string, int> type;

	public:

		template <typename T> static registerGlobal<T>(string name, T v);
		{
				type[name] = typeInteger<T>();
				value[name] = new T (v);
		}

		template <typename T> static T retrieve <T> (string name);
		{
			if (context[name] == typeInteger<T>)
				return * ((T*) map[name]) ;
			string error = "Type mismatch: You try to retrieve " + name + " as " + typeString(typeInteger<T>()) + ". However, " + name " is of type " + typeString(type[name]);
			throw error;
		}

		template <typename T> static void set <T> (string name, T d);
		{
			if (type [name] == typeInteger<T>)
				*value[name] = d;
			else
			{
				string error = "Type mismatch: " + name + " is of type " + typeString(type[name]) + ". But you try to set it as a " + typeString(typeInteger<T>());
				throw error;
			}
		}
};
