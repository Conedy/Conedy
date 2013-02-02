

#ifndef mapNode_h
#define mapNode_h mapNode_h

#include <math.h>
#include "containerNode.h"

#include "eventHandler.h"



namespace conedy
{





	//! Klasse, für das Integrieren von Maps
	class mapNode : public containerNode<baseType,2>
	{

		protected:
//		unsigned short Ngls;

			baseType * mapNodeTmp;

		public:
//		mapNode() {};


			//! reserviert Speicher für mapNodeTmp soviel speicher wie die größte Dimension von den Erben von mapNode.
			mapNode ( networkElementType n, unsigned int dim ) : // ngls: Anzahl der Gleichungen, NodeNumber,  h Schrittweite
					containerNode<baseType,2> ( n, dim )
			{
			}

			mapNode ( const mapNode &b ) : containerNode<baseType,2> ( b )
			{

				mapNodeTmp = ( baseType* ) calloc ( ( &b )->dimension(),sizeof ( baseType ) );

			}



			virtual ~mapNode() {}


//		virtual void randomizeState(randomNumber<baseType> &r) { for (int i = 0; i < Ngls; i++) x[i] = r(); }


			virtual void operator() ( baseType xprime [], baseType x[] ) {};
			virtual int requiredTimeSteps() { return 1; }
			//		virtual void swap() { this->state = this->x[0];}

			virtual void clean ()
			{

			};

			virtual void evolve ( baseType time )
			{
				list<containerNode<baseType,2>*>::iterator it;
//			dynNode::dt = time;


				for ( unsigned int i =0 ; i < ( unsigned int ) ( time+0.5 ) ; i++ )   // Wir wollen hier richtig runden und nicht immer nur ab.
				{
					for ( it = containerNode<baseType,2>::nodeList.begin(); it != containerNode<baseType,2>::nodeList.end(); it++ )
						((mapNode*)( *it ))->action1();


					for ( it = containerNode<baseType,2>::nodeList.begin(); it != containerNode<baseType,2>::nodeList.end(); it++ )
						((mapNode*)( *it ))->swap();

				}
			}



			virtual void action1()
			{
				( *this ) ( mapNodeTmp,this->x );
			}

			virtual void swap()
			{
				for ( unsigned int i = 0; i < this->dimension(); i++ )
					this->x[i] = mapNodeTmp [i];
			}

	};




}

#endif
