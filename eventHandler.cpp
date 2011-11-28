

#include "eventHandler.h"






void eventHandler::eventClean ()
{

	if (eventQueue != NULL)
		delete eventQueue;

		eventQueue = new priorityQueueTemplate ( eventsInQueue + 3 ,*this );
		for ( unsigned int i = 1; i < eventList.size(); i++ )
			eventQueue->push ( i );


#ifdef ONETIMEEVENTS
	event e;
	e.time = numeric_limits<baseType>::max();
	e.signature = 0;
	e.owner = NULL;

	for ( unsigned int i = eventList.size(); i < eventsInQueue; i++ )
	{
		eventList.push_back ( e );
		freeEventNumbers.push ( i );
	}


#endif


}

void eventHandler::unregisterCallBack (unsigned int eventSignature){
		
	if ( myEventsStartAt != numeric_limits<unsigned int>::max() )
		eventList[myEventsStartAt+eventSignature].time = numeric_limits<baseType>::max();	
}



eventHandler::~eventHandler()
{

	for ( unsigned int i = 0; i < this->numberOfEvents();i++ )
		eventList[myEventsStartAt+i].time = numeric_limits<baseType>::max();

}

void eventHandler::registerCallBack ( unsigned int eventSignature,  baseType time )
{
	if ( myEventsStartAt == numeric_limits<unsigned int>::max() )
	{

		event e;
		e.owner = this;
		myEventsStartAt = eventList.size();
		for ( unsigned int i = 0; i < this-> numberOfEvents();i++ )
		{
			if ( i == eventSignature )
				e.time = time;
			else
				e.time = numeric_limits<baseType>::max();
			e.signature = i;

			eventList.push_back ( e );
			//		eventQueue->push(eventList.size() - 1);

		}


	}
	else
	{
		
//		if (eventQueue != NULL)
//					updateKey (eventSignature, time);
//		else
			eventList[myEventsStartAt + eventSignature]. time = time;
	}

	//		if ( eventList.size() == eventsInQueue )
	//		{
}




void eventHandler::staticUpdateKey ( unsigned int eventNumber, baseType newTime )
{
	if ( eventList[ eventNumber].time > newTime )
	{

		eventList[eventNumber].time = newTime;
		eventQueue->update ( eventNumber );

	}
	else
	{
		eventQueue->pop();
		eventList[eventNumber].time = newTime;
		eventQueue->push ( eventNumber );


	}


}




void eventHandler::decreaseKey ( unsigned int eventSignature, baseType newTime )
{
	unsigned int eventNumber = myEventsStartAt + eventSignature;
	decreaseKeyStatic (eventNumber, newTime);
}


void eventHandler::decreaseKeyStatic ( unsigned int eventNumber, baseType newTime )
{

	eventList[eventNumber].time = newTime;
#ifdef CALENDARQUEUE
	eventQueue->decreaseKey (eventNumber);
#else
	eventQueue->update ( eventNumber );
#endif
}

void eventHandler::increaseKey ( unsigned int eventSignature, baseType newTime )
{
	unsigned int eventNumber = myEventsStartAt + eventSignature;
	increaseKeyStatic(eventNumber, newTime);
}

void eventHandler::increaseKeyStatic (unsigned int eventNumber, baseType newTime)
{
#ifdef CALENDARQUEUE


	eventList[eventNumber].time = newTime;

	eventQueue->increaseKey (eventNumber);
#else
	decreaseKeyStatic ( eventNumber, numeric_limits<baseType>::min() );
	eventQueue->pop();
	eventList[eventNumber].time = newTime;
	eventQueue->push ( eventNumber );
#endif
}

void eventHandler::updateKey ( unsigned int eventSignature, baseType newTime )
{

	if ( getKey ( eventSignature ) > newTime )
		decreaseKey ( eventSignature, newTime );
	else
		increaseKey ( eventSignature, newTime );
}

baseType eventHandler::getKey ( unsigned int eventSignature )
{
	return eventList[myEventsStartAt + eventSignature].time;


}



#ifdef ONETIMEEVENTS
void eventHandler::registerOneTimeCallBack ( unsigned int eventSignature, baseType time )
{

#ifdef DEBUG
	if (freeEventNumbers.empty())
		throw "event queue is full.";

#endif	
	unsigned int useThisNumber =	freeEventNumbers.top();
	freeEventNumbers.pop();
	eventList[useThisNumber].time = time;
	eventList[useThisNumber].signature = eventSignature;
	eventList[useThisNumber].owner = this;
	eventQueue->push ( useThisNumber);
//	staticUpdateKey ( useThisNumber, time )
}


#endif




eventHandler::eventHandler ( const eventHandler &b )
{


	eventsInQueue+= ( &b )->numberOfEvents();
	eventsInQueue+= ( &b )->numberOfOneTimeEvents();
	myEventsStartAt = b.myEventsStartAt;

}


eventHandler::eventHandler ( )
{
	if ( eventList.size() == 0 )
	{
		event dummy;                           // inserting event which never happens.
		dummy.time = numeric_limits<double>::max();
		eventList.push_back ( dummy );
	}
	myEventsStartAt = numeric_limits<unsigned int>::max();

}

void eventHandler::insertVisiter ( function <void() > v, unsigned int eventNumber )
{
	eventList[eventNumber].owner = new visiter ( v, eventList[eventNumber].owner );
}

void eventHandler::insertVisiterAtSignature( function <void()> v, unsigned int signature)
{
	for (unsigned int i=0; i < eventList.size();i++)
		if (eventList[i].signature == signature)
			insertVisiter (v, i);
}


void eventHandler::pop()
{

	unsigned int topElement = eventQueue->top();

#ifdef EVENTCOUNT
	eventCount[eventList[topElement].signature] += 1;	
#endif


	baseType returnValue =   eventList[topElement].action();



#ifdef ONETIMEEVENTS
	if ( returnValue == 0 )
	{
		eventQueue->pop();
		eventList[topElement].time = numeric_limits<baseType>::max();
		return;
	}
#endif


#ifdef CALENDARQUEUE 
 if (eventList[topElement].signature == _fire_)	
	{
		eventList[topElement].time = returnValue;
	  eventQueue->nextYear();	
		return;
	}
#endif


	increaseKeyStatic (topElement, returnValue); 
}




vector<event > eventHandler::eventList;

unsigned int eventHandler::eventsInQueue;

stack<unsigned int> eventHandler::freeEventNumbers;

priorityQueueTemplate *eventHandler::eventQueue = NULL;

neuronNumberProperty eventHandler::nnp;


vector <int> eventHandler::eventCount ( 100 );









baseType event::action()  { return owner->callBack ( signature );}

int get ( neuronNumberProperty, int ev )
{
	return ev;
}
