



#ifndef containerNode_h
#define containerNode_h containerNode_h



#include "node.h"
#include "params.h"
#include <boost/function.hpp>
#include <gsl/gsl_errno.h>
#include <gsl/gsl_matrix.h>
#include <gsl/gsl_odeiv.h>
#include "dynNode.h"

#include <list>


// nodes	container number

// odeNode : 	1
// mapNode :	2
// gslOdeNode: 	3
// sdeNode : 	4


namespace conedy
{



	//! Container class, which puts nodes representing dynamical systems of the same kind (e.g. ODEs) into container. The second template is the container number. Nodes in the same container have consecutive memory for their state variables. Time evolution is handled by the first node in the container. 
	template <typename T, int N>
		class containerNode : public dynNode
	{
		protected:

			static T * dynamicVariablesOfAllDynNodes;
			static unsigned int usedIndices;
			static unsigned int sizeOfArray; 
			typedef  list<containerNode<T,N> *> containerNodeList;
			static containerNodeList nodeList;
			params<T> p;




			// Hilfsfunktionen für die GSL:


		public:
			containerNode (networkElementType n ) : dynNode ( n), p ( _containerNode_ )
		{

		};

			static void clear()
			{
				usedIndices = 0;
				nodeList.clear();
			}

			virtual bool timeEvolution ()   // only the first element of the container will be called for time evolution.
			{ 
				if ( (*nodeList.begin()) == this)
					return 1; 
				else
					return 0;

			}


			containerNode ( const containerNode & c ) : dynNode ( c ), p ( _containerNode_ )
		{
			free( this->tmp);
			//cout << "Copy-Konstruktor" << endl;

			if ( usedIndices == 0 )    // first node in the container. Reserve memory according two gslOdeNode_arraySize
			{
				dynamicVariablesOfAllDynNodes = ( T* ) calloc ( p.getParams ( 0 ),sizeof ( T ) );
				sizeOfArray = p.getParams(0);
			}


			while ( usedIndices + (&c)->dimension() > sizeOfArray )   // memory space is empty 
			{ 
				realign();   // try to fill in the wholes in the array
				if ( usedIndices + (&c)->dimension() > sizeOfArray )  // still not enough space in the array, so copy the array to a new location.
				{
					unsigned int newSize = (unsigned int) sizeOfArray * 1.5;

					T* newArray = ( T* ) calloc ( newSize ,sizeof ( T ) );
					sizeOfArray =  newSize;
					T* pointer = newArray;

					usedIndices = 0;



					typename containerNodeList::iterator it;


					for (it = nodeList.begin(); it != nodeList.end(); it++)
					{

						for (unsigned int i = 0; i < (*it)->dimension(); i++)
							pointer[i] = (*it)->tmp [i] ;


						(*it)->tmp = pointer;
						(*it)->startPosGslOdeNodeArray = usedIndices;
						pointer = pointer + (*it)->dimension();
						usedIndices = usedIndices + (*it)->dimension();
					}

					free (dynamicVariablesOfAllDynNodes);
					dynamicVariablesOfAllDynNodes = newArray;

				}


			}
				this->tmp =  &dynamicVariablesOfAllDynNodes[usedIndices];

				nodeList.push_back ( this );
				startPosGslOdeNodeArray = usedIndices;
				usedIndices += (&c)->dimension();


		}

			//! Lücken füllen und zusammenschieben
			static void realign ()   
			{

				typename containerNodeList::iterator it;

				T* pointer = dynamicVariablesOfAllDynNodes;
				unsigned int offset = 0;
				usedIndices = 0;
				for (it = nodeList.begin(); it != nodeList.end(); it++)
				{

					while (usedIndices + offset != (*it)->startPosGslOdeNodeArray)
						offset++;
					for (unsigned int i = 0; i < (*it)->dimension(); i++)
					{
						(*it)->tmp = pointer;
						pointer[i] = pointer[i + offset];
						usedIndices ++;
					}
					pointer = pointer + (*it)->dimension();
				}
			}

			//! 1. und einizger Intergrationsschritt:

			virtual ~containerNode()
			{
				typename containerNodeList::iterator it;
				for (it = nodeList.begin(); it != nodeList.end(); it++)
					if (*it == this)
					{
						nodeList.erase(it);
						break;
					}
			}



			unsigned int startPosGslOdeNodeArray;

			//! clean: wird vor der Integration aufgerufen und initialisiert diverse GSL-Parameter (Art der Stufenfunktion, Schrittweite usw.)
			virtual void clean ()
			{


			}

			//			virtual void operator() ( const T x[], T dydx[] )  = 0;

			//! Bereitstellung des ODE-Systems: Ableitungen werden in Array geschrieben

			bool amIFirst()	 { return ( (*nodeList.begin()) == this);  }



			virtual int requiredTimeSteps ()
			{
				if ( startPosGslOdeNodeArray == 0 )
					return 1;
				else
					return 0;
			};

			//! Kopieren der Temp-Zustände in den Zustand nach erfolgter Integration
			//		virtual void swap()
			//		{
			//			this->state = this->tmp[0];

			//		};

			//	virtual void clean(unsigned int timeSteps) {};

			//	virtual T getHiddenComponent(int component) { return tmp[component]; }


			//	virtual T getState();

			//	virtual streamIn(ifstream &in);
			//	virtual streamOut(ofstream &out);

			//			virtual node *construct() { return new node ( *this ); };

			static void registerStandardValues()
			{
				params<T>::registerStandard ( _containerNode_,"containerNode_arraySize", 0,4096 );
			}


	};





	template < class T, int N>
		T*containerNode<T, N>::dynamicVariablesOfAllDynNodes;

	template < class T, int N>
		unsigned int containerNode<T,N>::usedIndices;

	template < class T, int N>
		std::list<containerNode<T,N>*> containerNode<T,N>::nodeList;

	template < class T, int N>
		unsigned int containerNode<T,N>::sizeOfArray;

	//template < class T>
	//double containerNode<T>::time;





}







#endif
