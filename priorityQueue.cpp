#include "priorityQueue.h"



#include "eventHandler.h"


//#include "testPriorityQueue.h"




bool compare_eventTimes( const unsigned int  s1, const unsigned int s2 ) 
{
	return  (eventHandler::eventList[s1].time  - (int) eventHandler::eventList[s1].time) <
		(eventHandler::eventList[s2].time  - (int) eventHandler::eventList[s2].time);

}


calendarQueue::calendarQueue (unsigned int size, compareEventTimes& p) :  head (0), nBuckets (size),currentBucket (0), isEmpty(true), bucketOf(size) {

	priorities = p.theEventHandler;
	list < unsigned int > dummy;
	for (unsigned int i = 0; i < nBuckets; i++)
		buckets.push_back(dummy);

	infinityBucket.push_back (0);
	bucketOf[0] = nBuckets;
	marker = infinityBucket.begin();      
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
		marker = newMarker;
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
		marker = infinityBucket.begin();
//		isEmpty = true;   // this is just a cheat, as we already know that the element will be the smallest one.
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
					cout << "Bucket:"  << i << ":" << endl;
		for (jt = buckets[i]. begin(); jt != buckets[i].end(); jt++)
		{
			cout << *jt << "," << priorities->priority(*jt) << endl;
		}
	}


}






eventHandler * calendarQueue::priorities;




void calendarQueue::insertionSortBucket (unsigned int i)
{
	list <unsigned int> ::iterator it, iplus;
	list <unsigned int> ::reverse_iterator kt, kmt;

	it = buckets[i].begin();
	it++;
	for (; it != buckets[i].end(); it++)
	{
		iplus = it; iplus ++;
		for (kt = reverse_iterator< list<unsigned int>:: iterator>  (iplus);true; kt++)
		{
			kmt = kt;
			kmt++;
			if (kmt == buckets[i].rend())
					break;
			if (compare_eventTimes (*kt, *kmt))
			{
				unsigned int temp = *kt;
				*kt = *kmt;
				*kmt = temp;
			}
			else
				break;
		}
	}	
}

//	for (it = buckets[i].begin()


//	for ( unsigned int i = 0; i < 


void calendarQueue::push (unsigned int i)
{ 	//debug()
	double priority = priorities->priority(i);
	unsigned int vBucket = priority * nBuckets;	
	unsigned int bucket = vBucket % nBuckets;	



	buckets [bucket].push_back(i);
	//debug();
	//	buckets [bucket].sort(compare_eventTimes);
	bucketOf [i] = bucket;



	if (bucketOf[*marker] == bucket)          // sorting will destroy the marker to the next Event.
	{
		unsigned int oldMarker = *marker;
		insertionSortBucket (bucket);

		marker = buckets[bucket].begin();
		while (*marker != oldMarker) marker++;

	}		

	else
	{
		insertionSortBucket (bucket);
	}


//	marker = buckets[bucket].begin();
//	cycleMarker();


//	marker = newMarker;

//	newMarker = buckets[bucket].begin();
//	while (*newMarker != i)
//		newMarker ++;



	if  (priority < priorities->priority( *marker ) )
	{
		firstElement = i;

		newMarker = buckets[bucket].begin();
		while (*newMarker != i)
			newMarker ++;


		marker = newMarker;
		currentBucket = bucket;
		head =  (int)  priority;

		return;

	}
}


void calendarQueue::cycleMarker()
{

	bool alreadyBeenHere = false;
	newMarker = marker;
	while (true)
	{
		if (newMarker == buckets[currentBucket].end())
		{
			currentBucket++;
			if (currentBucket == nBuckets)
			{
				if (alreadyBeenHere == true)   // I havent found any event, assuming queue is empty
				{
					newMarker = infinityBucket.begin();
					break;
				}
				

				alreadyBeenHere = true;
				currentBucket = 0;

				head ++;
			}
			newMarker = buckets[currentBucket].begin();
			continue;
		}
		if (priorities->priority(*newMarker)  >= head + 1 )
		{
			newMarker++;
			continue;

		}
		break;
	}
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

	marker = buckets[currentBucket].erase (marker);

	//	buckets[currentBucket].erase (firstElement);

	cycleMarker();
	firstElement = *newMarker;
	marker = newMarker;
	return res;					
}




