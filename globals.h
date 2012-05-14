






#include <map>
#include <iostream>



template <typename X, typename Y> bool isEqual <X,Y>()
{ return typeInteger<X>() == typeInteger<Y>(); }


template <typename T> int typeInteger<T>();


template <> int typeInteger <int>() { return 0;}
template <> int typeInteger <double>() { return 1;}
template <> int typeInteger <string>() { return 2;}
//template <> int typeInteger <int>() { return 3;}


template <typename T> string typeString<T>();


template <> string typeString <int>() { return "int";}
template <> string typeString <double>() { return "double";}
template <> string typeString <string> (){ return "string";}
//template <> string typeString <int> () { return "int";}




class globals
{
	public:

		template <typename T> static registerGlobal<T>(string name, T v);
		{
				type[name] = typeInteger<T>();	
				value[name] = new T (v);
		}
		template <typename T>
	   static T	retrieve <T> (string name); 
		{ 
			if (context[name] == typeInteger<T>)
				return * ((T*) map[name]) ;   
			string error = "context error with global variable." ;
			error += name + " is not of type" ;
			error += " ";
			throw error + name; 	
		}	
		
		


		template <typename T>
		static void set <T> (string name, T d);	
		{
			if (context [name] == typeInteger<T>)
				*value[name] = d;
			
			else
			{


			}


		}


	private:
	


		static map <string, void*> value; 
		static map <string, int> type;





			
};


			
			registerGlobal<baseType>("odeStepSize", 0.001);








};

template <T> static registerl
{
	throw "no map available for type"=;
}


		template <> static registerGlobal<baseType> (string name , basetype standardValue)
{
	

}
