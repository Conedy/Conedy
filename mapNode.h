

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
			mapNode ( networkElementType n ) : // ngls: Anzahl der Gleichungen, NodeNumber,  h Schrittweite
					containerNode<baseType,2> ( n )
			{
			}

			mapNode ( const mapNode &b ) : containerNode<baseType,2> ( b )
			{

				mapNodeTmp = ( baseType* ) calloc ( ( &b )->dimension(),sizeof ( baseType ) );

			}



			virtual ~mapNode() {}


//		virtual void randomizeState(randomNumber<baseType> &r) { for (int i = 0; i < Ngls; i++) tmp[i] = r(); }


			virtual void operator() ( baseType xprime [], baseType x[] ) {};
			virtual int requiredTimeSteps() { return 1; }
			//		virtual void swap() { this->state = this->tmp[0];}

			virtual void clean ()
			{

			};

			virtual void evolve ( double time )
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
				( *this ) ( mapNodeTmp,this->tmp );
			}

			virtual void swap()
			{
				for ( unsigned int i = 0; i < this->dimension(); i++ )
					this->tmp[i] = mapNodeTmp [i];
			}

	};




//! Izhikevich-Map-Neuronen
	class izhikevichMap : public mapNode, public eventHandler

	{
		private:
			gslNoise noise;
		public:

			inline baseType a() { return ( params<baseType>::getParams ( 0 ) ); }
			inline baseType b() { return ( params<baseType>::getParams ( 1 ) ); }
			inline baseType c() { return ( params<baseType>::getParams ( 2 ) ); }
			inline baseType d() { return ( params<baseType>::getParams ( 3 ) ); }
			inline baseType I() { return ( params<baseType>::getParams ( 4 ) ); }
			inline baseType pendo() { return ( params<baseType>::getParams ( 5 ) ); }
			inline baseType pendoC() { return ( params<baseType>::getParams ( 6 ) ); }
			inline baseType timeDelay() { return ( params<baseType>::getParams ( 7 ) ); }

			static void registerStandardValues()
			{

				params<baseType>::registerStandard ( _izhikevichMap_,"izhikevichMap_a",0,0.02 );
				params<baseType>::registerStandard ( _izhikevichMap_,"izhikevichMap_b",1,0.2 );
				params<baseType>::registerStandard ( _izhikevichMap_,"izhikevichMap_c",2,-65 );
				params<baseType>::registerStandard ( _izhikevichMap_,"izhikevichMap_d",3,8 );
				params<baseType>::registerStandard ( _izhikevichMap_,"izhikevichMap_I",4,1 );
				params<baseType>::registerStandard ( _izhikevichMap_,"izhikevichMap_pendo",5,0.001 );
				params<baseType>::registerStandard ( _izhikevichMap_,"izhikevichMap_pendoC",6,10.0 );
				params<baseType>::registerStandard ( _izhikevichMap_,"izhikevichMap_timeDelay",7,1.0 );

			}

			virtual const unsigned int dimension() const { return 2;}

			virtual baseType callBack ( unsigned int eventSignature )
			{
				fire();

				return 0;

			}

			izhikevichMap() : mapNode ( _izhikevichMap_ )
			{		}

			virtual unsigned int numberOfEvents() const { return 0; }
			virtual unsigned int numberOfOneTimeEvents() const { return 10; }


			izhikevichMap ( const izhikevichMap  &b ) : mapNode ( b ), eventHandler ( b )
			{
				dynNode::tmp[0] =  -70.0;
				dynNode::tmp[1] =  -14.0;

			}



			virtual void operator() ( baseType xprime [], baseType x[] );


			virtual const nodeInfo getNodeInfo() { nodeInfo n = {_izhikevichMap_,_dynNode_};     return n; };



			virtual baseType getState()
			{
				if ( this->tmp[0] > 30.0 )
					return 1.0;
				else
					return 0.0;
			}


//		virtual void swap();

			virtual void clean ()
			{
//				registerCallBack ( _fire_, numeric_limits<baseType>::max() );
			};
	};





}






#endif
