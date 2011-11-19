

#ifndef nodeImplement_h
#define nodeImplement_h nodeImplement_h



#include "dynNode.h"
#include "edge.h"


namespace conedy {

	template <typename T>
		void eraseZero (vector <T> & vec)
		{
			unsigned int read = 0;
			unsigned int write = 0;
			for (read =0; read < vec.size();read ++)
			{
				if (vec[read] == 0)
					continue;
				vec[write] = vec[read];
				write++;
			}
			vec.resize(write);

		}


	template <typename T>
		void eraseAll (vector <T> & vec, T what)
		{
			unsigned int read = 0;
			unsigned int write = 0;
			for (read =0; read < vec.size();read ++)
			{
				if (vec[read] == what)
					continue;
				vec[write] = vec[read];
				write++;
			}
		}




	//!	Implementierung der vin node mit virtuellen Funktionen. Brauch mehr Speicherals nodeTemplateEdges, dafür können unterschiedliche Edge-Typen gespeichert werden.
	template <typename DYNNODE>
		class nodeVirtualEdges : public  DYNNODE
	{
		public:
	
#ifdef PRECALCULATEWEIGHTSUM
			baseType preCalculatedWeightSum;
#endif


			typedef node  targetNodeType;
			typedef edgeVirtual edgeType; 
			typedef typename DYNNODE::edgeDescriptor edgeDescriptor;


			// Konstruktoren
			//! Dieser Konstruktor ist nur zum Konstruieren der  Blaupausen gedacht. Echte Knoten im Netzwerk werden von Blaupausenknoten über construct erzeugt. 
			virtual ~nodeVirtualEdges();

			//    			nodeVirtualEdges ( networkElementType n) : DYNNODE ( n ) {}
			nodeVirtualEdges () : DYNNODE ( ) {}
			nodeVirtualEdges (string s) : DYNNODE (s) {}
			nodeVirtualEdges (unsigned int i) : DYNNODE (i) {}


			virtual void clean () {


#ifdef PRECALCULATEWEIGHTSUM



	float res = 0;
	edgeIterator ei;
	for ( ei =outEdges.begin(); ei != outEdges.end(); ei++ )
		res = res +  (*ei)->getWeight();

	preCalculatedWeightSum = res;
		


#endif


				unsigned int read = 0;
				unsigned int write = 0;
				for (read =0; read < outEdges.size();read ++)
				{
					if (outEdges[read]->targetNumber == (nodeDescriptor) -1)
					{
						delete outEdges[read];
						continue;
					}
					outEdges[write] = outEdges[read];
					write++;
				}
				outEdges.resize(write);

				DYNNODE::clean();



			}


			virtual void printEdgeStatistics ( ostream &os, double edgeVirtualVerbosity=1.0);
			virtual edgeInfo getEdgeInfo (edgeDescriptor eD) {return outEdges[eD]->getEdgeInfo(); }
			virtual void setWeight (edgeDescriptor theEdge, baseType w) { outEdges[theEdge]->setWeight(w); }
			virtual node* getTarget(edgeDescriptor theEdge) { return outEdges[theEdge]->getTarget(); }
			virtual baseType getWeight (edgeDescriptor theEdge) { return outEdges[theEdge]->getWeight(); }
			virtual baseType getTargetState (edgeDescriptor theEdge) { return outEdges[theEdge]->getTargetState(); }
			virtual edge * getEdge (edgeDescriptor eD){ return outEdges[eD]; }	

			// Verbindungen hinzufügen, entfernen
			virtual bool unlink (nodeDescriptor targetNumber);

			virtual void removeEdge	(edgeDescriptor e)
			{
					outEdges[e]->targetNumber = -1;
			}

			virtual void removeEdges() { outEdges.clear(); }

			virtual void link (nodeDescriptor targetNumber, baseType weight);
			virtual void link (nodeDescriptor targetNumber, edge *l);
			virtual bool isLinked ( node *target );
			virtual baseType linkStrength ( node *target );
			virtual void normalizeInWeightSum(baseType d);
			//		virtual void printStatistics(); 


			virtual node *construct()
			{
				return  new nodeVirtualEdges<DYNNODE>( *this );	
			};


			// Statistikkram
			//		virtual void printStatistics();
			virtual unsigned int degree() { return outEdges.size();}
			virtual float clustering ();
			virtual float weightSum();
			virtual float inWeightSum();
			//			virtual nodeDescriptor getNumber(); // { return ( nodeDescriptor ) number; };

		protected:

			//! so wie couplingSum. Allerdings werden die Zustände zirkulär addiert.
			baseType getMeanPhaseCoherence() ;
			baseType couplingSum();
			void fire (
					);
		private:
			//! Variable, die von der Klasse offeriert wird, zum Beispiel zum Einkoppeln in andere Nodes 
			//		baseType state;


			//! Private Variable, in denen die Edges gespeichert werden
			vector <edgeVirtual* > outEdges;    // Liste der ausgehenden Kanten
			typedef  vector <edgeVirtual*  >::iterator edgeIterator;

	};




	template <typename DYNNODE>
		void nodeVirtualEdges<DYNNODE>::printEdgeStatistics(ostream &os, double edgeVirtualVerbosity)
		{
			if (edgeVirtualVerbosity > 0.9)
				os << "virtual edges:"; 
			

			for (unsigned int i = 0; i < outEdges.size(); i++)
				outEdges[i]->printStatistics(os, edgeVirtualVerbosity );
			os<< endl;
		}


	template <typename DYNNODE>
		nodeVirtualEdges<DYNNODE>::~nodeVirtualEdges()
		{
			// Edges löschen
			for (edgeIterator it = outEdges.begin(); it!=outEdges.end(); it++ )
			{
				delete ( *it );
			}

			//zeiger auf edges löschen
			//		outEdges.rlear();
		}


	template <typename DYNNODE>
		bool nodeVirtualEdges<DYNNODE>::unlink ( nodeDescriptor target )
		{
			bool res = false;
			edgeIterator s;

			for ( s=outEdges.begin(); s != outEdges.end(); s++ )
			{
				if ((*s)->targetNumber  == target )
				{
					res = true;
					//				outEdges.remove(s);
					//				delete *s;
					//				outEdges.erase ( s );
					(*s)->targetNumber = (nodeDescriptor)-1;
					break;
				}
			}
			return res;
		}



	template <typename DYNNODE>
		baseType nodeVirtualEdges<DYNNODE>::couplingSum()
		{
			baseType re = 0;

			edgeIterator it, end;
			it =  outEdges.begin();
			end = outEdges.end();
			for ( ;it!=end; it++ )
				re = re + (*it)->getWeight() *  (*it)->getTargetState();
			return re;
		}



	//		a = new weightedEdgeVirtual ( targetNumber, w );
	//		outEdges.push_back ( a );

	//	}



	template <typename DYNNODE>
void nodeVirtualEdges<DYNNODE>::link (nodeDescriptor targetNumber,  edge *l )
{
	edge *newEdge = ((edgeVirtual*)l)  ->construct();
	newEdge->targetNumber= targetNumber;
	outEdges.push_back ( (edgeVirtual*)newEdge );
}


	template <typename DYNNODE>
void nodeVirtualEdges<DYNNODE>::link (nodeDescriptor targetNumber,  baseType weight)
{
	weightedEdgeVirtual	*newEdge = new weightedEdgeVirtual(targetNumber,weight);
	outEdges.push_back ( newEdge );
}


	template <typename DYNNODE>
bool nodeVirtualEdges<DYNNODE>::isLinked ( node *target )
{
	bool res = false;
	edgeIterator s;
	for ( s=outEdges.begin(); s != outEdges.end(); s++ )
	{
		if ((*s )->targetNumber == target->getNumber() )
		{
			res = true;
			break;
		}
	}
	return res;
}


	template <typename DYNNODE>
void nodeVirtualEdges<DYNNODE>::fire ()
{
	edgeIterator it, end;
	it =  outEdges.begin();
	end = outEdges.end();
	for ( ;it!=end; it++ )
		((dynNode*)(*it)->getTarget() )->excite ( (*it) ->getWeight() );
}



template <typename DYNNODE>
float nodeVirtualEdges<DYNNODE>::inWeightSum() {
	float res = 0;
	vector<node *>::iterator it;
	for (it = DYNNODE::theNodes.begin(); it != DYNNODE::theNodes.end(); it++)
	{	
		res+= linkStrength(*it); 

	}
	return res;
}




#ifdef PRECALCULATEWEIGHTSUM
template <typename DYNNODE>
float nodeVirtualEdges<DYNNODE>::weightSum() {
	return preCalculatedWeightSum;
}
#else	
	template <typename DYNNODE>
float nodeVirtualEdges<DYNNODE>::weightSum()
{
	float res = 0;
	edgeIterator ei;
	for ( ei =outEdges.begin(); ei != outEdges.end(); ei++ )
		res = res +  (*ei)->getWeight();
	return res;
}

#endif

	template <typename DYNNODE>
baseType nodeVirtualEdges<DYNNODE>::getMeanPhaseCoherence()
{
	complex<baseType> re ( ( baseType ) 0, ( baseType ) 0 );
	//	complex<double> dummy;
	edgeIterator i;
	for ( i = outEdges.begin(); i != outEdges.end(); i++ )
	{
		complex<baseType> dummy ( (baseType)0.0, (baseType) ( *i )->getTargetState() );
		re = re + exp ( dummy );

	}
	return abs ( re );
}





	template <typename DYNNODE>
void nodeVirtualEdges<DYNNODE>::normalizeInWeightSum(baseType d) 
{

	nodeDescriptor i;
	baseType a;
	vector<nodeDescriptor> presynaptics;

	for (i = 0; i < node::theNodes.size(); i++)
		if ((a = node::theNodes[i]->linkStrength(this))) {

			//					inWeightSum += a;
			presynaptics.push_back (i);
		}
	for ( i = 0; i < presynaptics.size();i++)
	{
		node::theNodes[presynaptics[i]]->unlink(DYNNODE::getNumber());
		node::theNodes[presynaptics[i]]-> link (DYNNODE::getNumber(),  d / presynaptics.size());

	}


}





	template <typename DYNNODE>
baseType nodeVirtualEdges<DYNNODE>::linkStrength ( node *target )
{
	baseType res = 0;
	edgeIterator s;
	for ( s=outEdges.begin(); s != outEdges.end(); s++ )
	{
		if (  (*s)->targetNumber  == target->getNumber() )
		{
			res = ( *s )->getWeight();
			break;
		}
	}
	return res;
}

	template <typename DYNNODE>
float nodeVirtualEdges<DYNNODE>::clustering ()
{
	baseType linkedFriends = 0;
	edgeIterator s,t;
	for ( s=outEdges.begin();s != outEdges.end();s++ )
		for ( t= outEdges.begin(); t!= outEdges.end();t++ )
		{
			linkedFriends = linkedFriends + (( * s )->getTarget()->linkStrength ( ( *t )->getTarget() ) ) ;
		}
	if ( outEdges.size() > 1 )
		return ( float ) linkedFriends / ( outEdges.size() * ( outEdges.size() -1 ) );
	else
		return 0;
}


















//! Implementierung von node mit Edges ohne virtuelle Funktionen (brauch weniger Speicherpladz und ist theoretisch schneller.
template <typename EDGE, typename TARGETNODETYPE, typename DYNNODE>
class nodeTemplateEdges : public DYNNODE
{
	public:

#ifdef PRECALCULATEWEIGHTSUM
	baseType preCalculatedWeightSum;
#endif


		typedef TARGETNODETYPE  targetNodeType;
		typedef EDGE edgeType; 
		static EDGE standardEdge;
		typedef typename DYNNODE::edgeDescriptor edgeDescriptor;

		//! Statischer Vector mit Zeigern zu allen Knoten, die mit construct erzeugt wurden. 
		static vector<nodeTemplateEdges* > theNodes;



		//! Variable, die von der Klasse offeriert wird, zum Beispiel zum Einkoppeln in andere Nodes 
		baseType state;

	

			virtual void removeEdge	(edgeDescriptor e)
			{
					outEdges[e].targetNumber = -1;
			}

		virtual void clean () {
#ifdef PRECALCULATEWEIGHTSUM

	float res = 0;

	edgeIterator ei;
	for ( ei =outEdges.begin(); ei != outEdges.end(); ei++ )
		res = res +  ei->getWeight();



	preCalculatedWeightSum = res;

#endif


			unsigned int read = 0;
			unsigned int write = 0;
			for (read =0; read < outEdges.size();read ++)
			{
				if (outEdges[read].targetNumber == (nodeDescriptor) -1)
					continue;
				outEdges[write] = outEdges[read];
				write++;
			}
			outEdges.resize(write);

			DYNNODE::clean();


		}


		//   			nodeTemplateEdges ( networkElementType n) : DYNNODE( n ) {}


		// Konstruktoren
		//! Dieser Konstruktor ist nur zum Konstruieren der  Blaupausen gedacht. Echte Knoten im Netzwerk werden von Blaupausenknoten über construct erzeugt. 
		nodeTemplateEdges () :state ( 0 ) {};

		//		list< edgeDescriptor >

		//! Private Variable, in denen die Edgess gespeichert werden
		vector <EDGE > outEdges;    // Liste der ausgehenden Kanten

		virtual edgeInfo getEdgeInfo (edgeDescriptor eD) {return outEdges[eD].getEdgeInfo(); }
		virtual void setWeight (edgeDescriptor theEdge, baseType w) { outEdges[theEdge].setWeight(w); }
		virtual node* getTarget(edgeDescriptor theEdge) { return   outEdges[theEdge].getTarget(); }
		virtual baseType getWeight (edgeDescriptor theEdge) { return outEdges[theEdge].getWeight(); }
		virtual baseType getTargetState (edgeDescriptor theEdge) { return outEdges[theEdge].getTargetState(); }
		virtual edge * getEdge (edgeDescriptor eD){ return &outEdges[eD]; }

		virtual node *construct()
		{
			return  new nodeTemplateEdges< EDGE, TARGETNODETYPE, DYNNODE>( *this );	
		};

		// Verbindungen hinzufügen, entfernen
		virtual bool unlink (nodeDescriptor targetNumber);

		virtual void removeEdges () { outEdges.clear(); }

		virtual void link (nodeDescriptor targetNumber, baseType weight);
		virtual void link (nodeDescriptor targetNumber, edge *l);
		virtual bool isLinked ( node *target );
		virtual baseType linkStrength ( node *target );
		virtual void normalizeInWeightSum(baseType d);

		virtual void printEdgeStatistics ( ostream &os, double edgeVirtualVerbosity=1.0);

		// Statistikkram
		//		virtual void printStatistics();
		virtual unsigned int degree() { return outEdges.size();}
		virtual float clustering ();
		virtual float weightSum();
		virtual float inWeightSum();
		//			virtual nodeDescriptor getNumber(); // { return ( nodeDescriptor ) number; };

	protected:
		//! so wie couplingSum. Allerdings werden die Zustände zirkulär addier
		baseType getMeanPhaseCoherence();
		baseType couplingSum () ;
		void fire ();


	private:
		//! die Nummer vom Knoten.  theNodes[number] = this!
		int number;   


		typedef typename vector<EDGE>::iterator edgeIterator;
		static EDGE privateBluePrint;


};


template <typename EDGE, typename TARGETNODETYPE, typename DYNNODE>
EDGE nodeTemplateEdges<EDGE, TARGETNODETYPE, DYNNODE>::standardEdge;



	template <typename EDGE, typename TARGETNODETYPE, typename DYNNODE>
void nodeTemplateEdges<EDGE,TARGETNODETYPE, DYNNODE>::printEdgeStatistics(ostream &os, double edgeVirtualVerbosity)
{
	os<< "static edges: ";


	for (unsigned int i = 0; i < outEdges.size(); i++)
		outEdges[i].printStatistics(os, edgeVirtualVerbosity );


	os << endl;


}


	template <typename EDGE, typename TARGETNODETYPE, typename DYNNODE>
void nodeTemplateEdges<EDGE,TARGETNODETYPE, DYNNODE>::fire ()
{
	edgeIterator it, end;
	it =  outEdges.begin();
	end = outEdges.end();
	for ( ;it!=end; it++ )
		((targetNodeType*) it->getTarget())->excite ( it ->getWeight() );
}


	template <typename EDGE, typename TARGETNODETYPE, typename DYNNODE>
baseType nodeTemplateEdges<EDGE,TARGETNODETYPE, DYNNODE>::getMeanPhaseCoherence()
{
	complex<baseType> re ( ( baseType ) 0, ( baseType ) 0 );
	//	complex<double> dummy;
	edgeIterator i;
	for ( i = outEdges.begin(); i != outEdges.end(); i++ )
	{
		complex<baseType> dummy ( (baseType)0.0, (baseType) i->getTargetState() );
		re = re + exp ( dummy );

	}
	return abs ( re );
}


template <typename EDGE, typename TARGETNODETYPE, typename DYNNODE>
float nodeTemplateEdges<EDGE,TARGETNODETYPE, DYNNODE>::inWeightSum ()
{
	float res = 0;
	vector<node *>::iterator it;
	for (it = DYNNODE::theNodes.begin(); it != DYNNODE::theNodes.end(); it++)
	{	
		res+= linkStrength(*it); 

	}
	return res;

}


#ifdef PRECALCULATEWEIGHTSUM
template <typename EDGE, typename TARGETNODETYPE, typename DYNNODE>
float nodeTemplateEdges<EDGE,TARGETNODETYPE, DYNNODE>::weightSum ()
{
	return preCalculatedWeightSum;
}
#else	
template <typename EDGE, typename TARGETNODETYPE, typename DYNNODE>
float nodeTemplateEdges<EDGE,TARGETNODETYPE, DYNNODE>::weightSum ()
{
	float res = 0;
	edgeIterator ei;
	for ( ei =outEdges.begin(); ei != outEdges.end(); ei++ )
		res = res +  ei->getWeight();
	return res;
}
#endif





template <typename EDGE, typename TARGETNODETYPE, typename DYNNODE>
void nodeTemplateEdges<EDGE,TARGETNODETYPE, DYNNODE>::normalizeInWeightSum(baseType d)  {

	nodeDescriptor i;
	baseType a;
	vector<nodeDescriptor> presynaptics;

	for (i = 0; i < node::theNodes.size(); i++)
		if ((a = node::theNodes[i]->linkStrength(this))) {

			//					inWeightSum += a;
			presynaptics.push_back (i);
		}

	for ( i = 0; i < presynaptics.size();i++)
	{
		node::theNodes[presynaptics[i]]->unlink(DYNNODE::getNumber());
		node::theNodes[presynaptics[i]]-> link (DYNNODE::getNumber(),  d / presynaptics.size());
	}



};





	template <typename EDGE, typename TARGETNODETYPE, typename DYNNODE>
baseType nodeTemplateEdges<EDGE,TARGETNODETYPE, DYNNODE>::linkStrength ( node *target )
{
	baseType res = 0;
	edgeIterator s;
	for ( s=outEdges.begin(); s != outEdges.end(); s++ )
	{
		if ( s->targetNumber == target->getNumber() )
		{
			res =  s ->getWeight();
			break;
		}
	}
	return res;
}


	template <typename EDGE, typename TARGETNODETYPE, typename DYNNODE>
float nodeTemplateEdges<EDGE,TARGETNODETYPE, DYNNODE>::clustering ()
{
	baseType linkedFriends = 0;
	edgeIterator s,t;
	for ( s=outEdges.begin();s != outEdges.end();s++ )
		for ( t= outEdges.begin(); t!= outEdges.end();t++ )
			linkedFriends = linkedFriends +  s->getTarget()->linkStrength ( t->getTarget() )  ;
	if ( outEdges.size() > 1 )
		return ( float ) linkedFriends / ( outEdges.size() * ( outEdges.size() -1 ) );
	else
		return 0;
}









	template <typename EDGE, typename TARGETNODETYPE, typename DYNNODE>
baseType nodeTemplateEdges<EDGE,TARGETNODETYPE, DYNNODE>::couplingSum()
{
	baseType re = 0;

	edgeIterator it, end;
	it =  outEdges.begin();
	end = outEdges.end();
	for ( ;it!=end; it++ )
		re = re +  it->getWeight()* it->getTargetState();
	return re;
}



	template <typename EDGE, typename TARGETNODETYPE, typename DYNNODE>
void nodeTemplateEdges<EDGE,TARGETNODETYPE, DYNNODE>::link (nodeDescriptor targetNumber,  edge *l )
{
	//			cout << "warnung, nodeTemplateEdge";


	link(targetNumber, l->getWeight());
}

	template <typename EDGE, typename TARGETNODETYPE, typename DYNNODE>
void nodeTemplateEdges<EDGE,TARGETNODETYPE, DYNNODE>::link (nodeDescriptor targetNumber, baseType w )
{
	outEdges.push_back ( standardEdge );

	outEdges[outEdges.size() -1].targetNumber = targetNumber;
	outEdges[outEdges.size() -1].setWeight (w);
}


	template <typename EDGE, typename TARGETNODETYPE, typename DYNNODE>
bool nodeTemplateEdges<EDGE,TARGETNODETYPE, DYNNODE>::unlink ( nodeDescriptor target )
{
	bool res = false;
	edgeIterator s;

	//		outEdges.remove(target);
	for ( s=outEdges.begin(); s != outEdges.end(); s++ )
	{
		if (  s->targetNumber == target )
		{
			res = true;
			//				outEdges.remove(s);
			//				delete *s;
			//		outEdges.erase ( s );

			s->targetNumber = (nodeDescriptor) -1;

			break;
		}
	}
	return res;
}

	template <typename EDGE, typename TARGETNODETYPE, typename DYNNODE>
bool nodeTemplateEdges<EDGE,TARGETNODETYPE, DYNNODE>::isLinked ( node *target )
{
	bool res = false;
	edgeIterator s;
	for ( s=outEdges.begin(); s != outEdges.end(); s++ )
	{
		if ( s->targetNumber == target->getNumber() )
		{
			res = true;
			break;
		}
	}
	return res;
}


/*	template <typename EDGE, typename TARGETNODETYPE, typename DYNNODE>
	baseType nodeTemplateEdges<EDGE,TARGETNODETYPE, DYNNODE>::ninkStrength ( node *target )
	{
	baseType res = 0;
	edgeIterator s;
	for ( s=outEdges.begin(); s != outEdges.end(); s++ )
	{
	if ( s->getTarget()== target )
	{
	res =  s->getWeight();
	break;
	}
	}
	return res;
	}

*/






}




#endif
