
#include "lyapunov.h"
#include <iomanip>

	meanVar realign::calculateDist(vector <baseType> &states)
	{

		network::nodeIterator vi;
		baseType mean= 0;
		baseType var = 0;

		baseType diff = 0;
		unsigned int i=0;
		for (vi = vl->begin(); vi != vl->end();vi++)
		{
			diff = states[i] - node::theNodes[*vi]->getState();
			if (diff > 0.5)
				diff = diff - 1.0;
			if (diff < -0.5)
				diff = diff + 1.0;

			var += diff * diff;
			mean += diff;
			i++;
		}
		meanVar res;
		res.var  = var / (vl->size() - 1) - mean * mean / vl->size() / vl->size();
		res.mean = mean / vl->size();
		return res;
	}
	//		void	realign::goForIt(  )
	//		{



	void realign::realignPeriodically()
	{


		vector <baseType> along(vl->size());
				baseType timeFirstRun;
			  in >> timeFirstRun;
		//		cout << "timeFirstRun: " << timeFirstRun << endl;
		//		cout << "time: " << dynNode::time << endl;

		for (unsigned int i = 0; i < vl->size(); i++ )
			in >>along[i];

		meanVar dist = calculateDist(along);
		if (counter==skip)
		{
			counter = 0;
			out << dynNode::time << " " << setprecision(20) << dist.mean << " " << sqrt(dist.var) << endl;
			cout << "vorher:" << setprecision(20) << dist.mean << " " << sqrt(dist.var) << endl;
			realignNow(along, eps, dist);
			meanVar newDist = calculateDist(along);
			cout << "nachher:" << setprecision(20) << newDist.mean << " " << sqrt(newDist.var) << endl;
		}
		else
		{
			counter++;
			out << "#" << setprecision(20) << dynNode::time <<  " " << dist.mean << " " << sqrt(dist.var) << endl;

		}

	}


	void realign::realignWhenDistant()
	{



		vector <baseType> along(vl->size());


			baseType timeFirstRun;
		  in >> timeFirstRun;
//			cout << "timeFirstRun: " << timeFirstRun << endl;
//			cout << "time: " << dynNode::time << endl;

		for (unsigned int i = 0; i < vl->size(); i++ )
			in >>along[i];

		meanVar  dist = calculateDist(along);

		if (sqrt(dist.var) > eps* skip)


		{
			out << dynNode::time << " " << setprecision(20) << dist.mean << " " << sqrt(dist.var) << endl;
			cout << "vorher:" << setprecision(20) << dist.mean << " " << sqrt(dist.var) << endl;
			realignNow(along, eps, dist);
			meanVar newDist = calculateDist(along);
			cout << "nachher:" << setprecision(20) << newDist.mean << " " << sqrt(newDist.var) << endl;
		}
		else if ( sqrt(dist.var) < eps / skip  )
		{
			out << dynNode::time << " " << setprecision(20) << dist.mean << " " << sqrt(dist.var) << endl;
			cout << "vorher:" << setprecision(20) << dist.mean << " " << sqrt(dist.var) << endl;
			realignNow(along, eps, dist);
			meanVar newDist = calculateDist(along);
			cout << "nachher:" << setprecision(20) << newDist.mean << " " << sqrt(newDist.var) << endl;
		}
		else
		{


			out << "#" << setprecision(20) <<  dynNode::time <<  " " << dist.mean << " " << sqrt(dist.var) << endl;





		}
	}
	// realign to eps
	void realign::realignNow(vector <baseType> &along, baseType eps, meanVar dist)
	{
		baseType factor = eps / sqrt(dist.var);

		network::nodeIterator vi;
		queue <baseType> states;
		unsigned int i = 0;

		for (vi = vl->begin(); vi != vl->end();vi++)
		{
			//				baseType stat = theNodes[*vi]->getState();
			baseType diff =  along[i] - node::theNodes[*vi]->getState() ;

			if (diff > 0.5)
				diff = diff - 1;
			else if (diff < -0.5)
				diff = diff + 1;


			diff = diff - dist.mean;
			diff = diff *  factor;



			if (diff > 0.5  || diff < -0.5)
				throw "Fehler Abstand zu gro� f�r den Raum (evolveAlong)";

			baseType n;
			if (diff > 0)
			{
				n = along[i] - diff;
				if (n < 0)
					n=n + 1;
			}
			else
			{
				n = along[i] - diff;
				if ( n > 1)
					n = n - 1;
			}

			states.push (n);
			i++;
		}
		boost::function<baseType () > r =  bind(&frontAndPop, &states);
		for (vi = vl->begin(); vi != vl->end();vi++)
		{
			((dynNode*)  node::theNodes[*vi]) ->	randomizeState( r) ;
		}

	}
