

#ifndef __eventHandler
#define __eventHandler __eventHandler

#include <boost/bind.hpp>
#include <limits.h>
#include <boost/pending/relaxed_heap.hpp>
#include <boost/pending/fibonacci_heap.hpp>
#include <vector>
#include <limits>


#include <boost/function.hpp>

#define _fire_ 0
#define _exciteRandomly_ 1
#define _ioNode_ 2
#define _distributeExcitations_ 3

#ifndef EVENTCOUNT
#define EVENTCOUNT
#endif

#ifndef ONETIMEEVENTS
#define ONETIMEEVENTS
#endif

#include <stack>


#include "baseType.h" 

using namespace std;
using namespace boost;
//#include "dynNode.h"



//typedef fibonacci_heap priorityQueueTemplate;


//#define priorityQueueTemplate fibonacci_heap
#define priorityQueueTemplate relaxed_heap


//        class event



//        int get (eventIdentifier, event a )
//        {
//                return a.owner->getNumber()  ;
//        }

class neuronNumberProperty
{
};


int get(neuronNumberProperty, int ev);


class eventHandler;

//! In event wird ein Zeiger, auf die zurückzurufende Klasse gespeichert, zusammen mit der priorität (time).und einen Integer für die Art des Events, der mit an die callBack-funktion übergeben wird.
class event
{
	public:
		//! Priorität des Ereignisses
		baseType time;

		//! Integer, der die Art des Ereignisses spezifiziert.
		unsigned int signature;
		//! Zeiger auf die zurückzurufende Klasse
		eventHandler *owner;
	public:

		event()  {};
		virtual baseType action();  

};
//! Klasse, die eine Prioritätswarteschlange mit "Rückruf-Ereignisse" beinhaltet. Erben von eventHandler können die Funktion callBack überladen. Wird pop() aufgerufen, bekommt die Instanz, die die kleinste Priorität in der Warteschlange einen Rückruf.


class eventHandler
{

	//! Statische Liste mit events für jede Teilnehmende Klasse
	static vector<event > eventList;

	//! Statische Prioritätswarteschlange mit den Ereignisse., als Ordnung wird der Operator () verwendet, der die Ereignisse nach event::time ordnet.
	static priorityQueueTemplate< int,eventHandler > *eventQueue;

	//! obsolete
	static neuronNumberProperty nnp;

	//! Anzahl der Ereignisse in der Warteschlange
	static unsigned int eventsInQueue;

	static stack<unsigned int> freeEventNumbers;

	//! Position im Statischen vector eventList, an der die eigenen Ereignisse beginnen.

	public:

	int top() { return eventQueue->top(); };

	//! Die Priorität des events mit der Nummer eventNummer auf newTime setzen
	static void staticUpdateKey ( unsigned int eventNummer, baseType newTime );

	//! Hier wird gespeichert, bei welchem Index die events von der eigenen Instanz starten. Ist vor dem erstan Aufruf von registerCallback auf numeric_limits<unsigned int> gesetzt
	unsigned int myEventsStartAt;
	bool alreadyRegistered() { return (myEventsStartAt  != numeric_limits<unsigned int>::max()); }
#ifdef EVENTCOUNT
	//!  Vector, in dem die aufgetretenen Events gezählt werden.
	static vector<int> eventCount;
#endif


	//! Fügt eine Funktion ein, die jeweils direkt vor dem eigentlichen callback von event eventNumber aufgerufen wird.
	static void insertVisiter(function <void()> v, unsigned int eventNumber);

	//! Fügt eine Funktion ein, die vor jedem Event mit der Signature signature aufgerufen wird.
	static void insertVisiterAtSignature (function <void()> v, unsigned int signature);

	//! Ordnungsfunktion für die Ereignisse. Geordnet wird nach event::time
	bool operator() ( const unsigned int  s1, const unsigned int s2 ) const {
		return eventList[s1].time < eventList[s2].time;
	}

	//! gibt die Priorität (Integrationszeit) des obersten Elements zurück
	static baseType nextEvent() {
		return eventList[eventQueue->top() ].time;
	}

	//! ruft die call-back-funktion des obersten Elements auf und erhöht die Priorität der event-Instanz  um din Rückgabewert der call-back-funktion.
	static void pop();
	eventHandler ( );

	//! Nur Copykonstruierte Elemente erhöhen den internen Counter für die benötigte Anzahl Ereignisse
	eventHandler ( const eventHandler &b );


	//! Alle Events aus der Liste löschen
	static void clear()
	{
		eventList.clear();				
		delete eventQueue;
		eventQueue = NULL;

	}
			virtual ~eventHandler();


	//		bool amIFirst() { return (myEventsStartAt == 0); }





	//! 
	//
	//
	//

	void eventClean ();

#ifdef ONETIMEEVENTS
	void registerOneTimeCallBack (unsigned int eventSignature, baseType time);
#endif



	void unregisterCallBack (unsigned int eventSignature);
	void registerCallBack ( unsigned int eventSignature,  baseType time );





	void decreaseKey ( unsigned int eventSignature, baseType newTime );
	void increaseKey ( unsigned int eventSignature, baseType newTime );

	void updateKey ( unsigned int eventSignature, baseType newTime );
	baseType getKey ( unsigned int eventSignature );

	//! Erben von eventHandler müssen über diese Funktion mitteilen, wieviele unterschiedliche Arten von events benötigt werden.
	virtual unsigned int numberOfEvents() const { throw "numberOfEvents called (eventHandler)"; return 0;  }

	//! Wahrscheinliche Obere Schranke für einmalige Elemente, für die in der Prioritätswarteschlange Platz reserviert werden soll.
	virtual unsigned int numberOfOneTimeEvents() const { return 0;  }

	//! Diese Funktion wird von pop aufgerufen
	virtual baseType callBack ( unsigned int eventSignature ) { throw "eventHandlerMist!"; }



	};



		//! Objekt, das es ermöglicht eine zweite Funktion zwischzuschalten, die immer kurz vor dem eigentlichen callback aufgerufen wird. Die zweite Funktion wird mit einem Funktionszeiger-Objekt gespeichert.
		class visiter : public eventHandler {
			boost::function <void()> visit;
			eventHandler *target;
			public:
			visiter( function <void()> v, eventHandler *t) : visit(v), target(t) {}; 
			virtual baseType callBack ( unsigned int eventSignature ) { 
				visit();
				return target->callBack(eventSignature);
			};
			virtual unsigned int numberOfEvents() const { return target->numberOfEvents();  }

		};




//	  class callBackEvent: event
//	  {
//	  public:
//
//	  callBackEvent(double time) : event(time) {}
//	  virtual void action()
//	  {
//	  this->callBack(N);
//	  }
//
//	  };
//
//
//	  class exciteEvent<baseType>
//	  {
//	  dynNode *targetNode;
//	  baseType couplingStrength;
//	  public:
//	  exciteEvent(dynNode * t,double time, double c) : targetNode(t), event(time), couplingStrength(c) {}
//	  virtual void action()
//	  {
//	  targetNode->excite(couplingstrength);
//	  }
//
//	  };
//



#endif


