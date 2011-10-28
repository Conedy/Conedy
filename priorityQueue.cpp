#include "priorityQueue.h"



#include "eventHandler.h"


//#include "testPriorityQueue.h"




bool compare_eventTimes( const unsigned int  s1, const unsigned int s2 ) 
{
	return  (eventHandler::eventList[s1].time  - (int) eventHandler::eventList[s1].time) <
		(eventHandler::eventList[s2].time  - (int) eventHandler::eventList[s2].time);

}


calendarQueue::calendarQueue (unsigned int size, eventHandler& p) :  head (0), nBuckets (size),currentBucket (0), isEmpty(true), bucketOf(size) {

	priorities = &p;
	list < unsigned int > dummy;
	for (unsigned int i = 0; i < nBuckets; i++)
		buckets.push_back(dummy);


}



bool calendarQueue::operator() ( const unsigned int  s1, const unsigned int s2 ) const {
	return  (priorities->priority(s1)  - (int) priorities->priority(s1)) <
		(priorities->priority(s2)  - (int) priorities->priority(s2));
}

void calendarQueue::increaseKey ( unsigned int i)
{

//	cout << "increase:" << i;
//	cout << "-------------" << endl;
//debug();

	if (*marker == i)
	{
		//cout << "mist" << endl;
		marker = buckets[bucketOf[i]].erase (marker);
		cycleMarker();
		push (i);
	}
	else
	{

	list <unsigned int>:: iterator it;
	for (it = buckets[bucketOf[i]].begin(); it != buckets[bucketOf[i]].end(); it ++)

	{
		if (*it == i)
		{
			buckets[bucketOf[i]].erase (it);
			break;
		}

	}

	push (i);
	}

}



void calendarQueue::decreaseKey (unsigned int i)
{	

	if (*marker == i)
	{
	isEmpty = true;   // this is just a cheat, as we already know that the element will be the smallest one.
	}

	list <unsigned int>:: iterator it;
	for (it = buckets[bucketOf[i]].begin(); it != buckets[bucketOf[i]].end(); it ++)

	{
		if (*it == i)
		{
			buckets[bucketOf[i]].erase (it);
			break;
		}

	}

//	buckets[ bucketOf[i] ].erase (i);
	push (i);

//	buckets[bucketOf[i]].sort(*this);

}

void calendarQueue::update (unsigned int i)
{
	throw "weg";
	if (*marker == i)
	{
		//cout <<  "giving up";
	}

	list <unsigned int>:: iterator it;
	for (it = buckets[bucketOf[i]].begin(); it != buckets[bucketOf[i]].end(); it ++)

	{
		if (*it == i)
		{
			buckets[bucketOf[i]].erase (it);
			break;
		}

	}

//	buckets[ bucketOf[i] ].erase (i);
	push (i);

//	buckets[bucketOf[i]].sort(*this);
}


void calendarQueue::debug ()
{
	map <unsigned int, unsigned int>::iterator it;
//	for (it = bucketOf.begin(); it != bucketOf.end(); it++)
//		cout << (it)->first << " " << (it)-> second << endl;


	list <unsigned int>::iterator jt;


	for (unsigned int i = 0; i < nBuckets; i++)
	{
//			cout << "Bucket:"  << i << ":" << endl;
		for (jt = buckets[i]. begin(); jt != buckets[i].end(); jt++)
		{
			cout << *jt << "," << priorities->priority(*jt) << endl;
		}
	}


}






eventHandler * calendarQueue::priorities;



void calendarQueue::push (unsigned int i)
{ 	//debug()
	double priority = priorities->priority(i);
	unsigned int vBucket = priority * nBuckets;	
	unsigned int bucket = vBucket % nBuckets;	



	buckets [bucket].push_back(i);
	//debug();
	buckets [bucket].sort(compare_eventTimes);
	//debug();
	bucketOf [i] = bucket;
	

	newMarker = buckets[bucket].begin();
	while (*newMarker != i)
		newMarker ++;



	if (isEmpty)
	{
		firstElement = i;
		currentBucket = bucket;
		marker = newMarker;

		isEmpty = false;
		return;
	}

	else if  (priority < priorities->priority( *marker ) )
	{
		firstElement = i;
		marker = newMarker;
		currentBucket = bucket;
		return;

	}

}


void calendarQueue::cycleMarker()
{
	newMarker = marker;
	while (true)
	{
		if (newMarker == buckets[currentBucket].end())
		{
			currentBucket = currentBucket++;
			if (currentBucket == nBuckets)
			{
				currentBucket = 0;
				head ++;
			}
			newMarker = buckets[currentBucket].begin();
			continue;
		}
		if (priorities->priority(*newMarker)  > head + 1 )
		{
			newMarker++;
			continue;

		}
		break;
	}
	marker = newMarker;
}



unsigned int calendarQueue::top () { return *marker;}
unsigned int calendarQueue::pop ()
{
  

	//debug();

//	list <unsigned int >::iterator marker, newMarker;
//	marker = buckets[currentBucket].find(firstElement);
	unsigned int res = firstElement;

//	newMarker = marker++;


	newMarker = marker; 
	newMarker++;
//	bucketOf.erase (firstElement);

	buckets[currentBucket].erase (marker);

//	buckets[currentBucket].erase (firstElement);

	cycleMarker();

	firstElement = *newMarker;
	marker = newMarker;
	return res;					
}
void calendarQueue::nextYear ()
{	

}




