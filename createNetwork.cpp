

#include "createNetwork.h"

#include "specialNodes.h"
#include "pulseCoupledPhaseOscillator.h"
#include "nodeImplement.h"
#include "statisticsNetwork.h"
#include <cmath>

#include "ioNode.h"

namespace conedy {





			static bool cmp2d ( pair< int, int > a, pair< int, int > b )
			{

				return ( a.first * a.first + a.second * a.second ) < ( b.first * b.first + b.second * b.second );

			}

	void createNetwork::observeEventSignatureTimes( string fileName,nodeDescriptor eventNumber) {
		nodeBlueprint* nod = new nodeVirtualEdges<timeNode<baseType> >();
		nodeDescriptor timeNodeNumber = addNode ( nod );
		delete nod;

		nod = new  nodeVirtualEdges<streamOutNode>(fileName);
		nodeDescriptor streamOutNodeNumber = addNode(nod);
		streamOutNode *s = dynamic_cast<streamOutNode*>( nodeBlueprint::theNodes[streamOutNodeNumber]);

		eventHandler::insertVisiterAtSignature(bind(&streamOutNode::evolve,s, 0.0),eventNumber);
		delete nod;




		network::addEdge( streamOutNodeNumber, timeNodeNumber);





	}





	void createNetwork::observeEventTimesEquals( string fileName,nodeDescriptor eventNumber) {

		nodeBlueprint* nod = new nodeVirtualEdges<timeNode<baseType> >();
		nodeDescriptor timeNodeNumber = addNode ( nod );
		delete nod;

		nod = new  nodeVirtualEdges<streamOutNodeCountEquals>(fileName);
		nodeDescriptor streamOutNodeNumber = addNode(nod);
		streamOutNode *s = dynamic_cast<streamOutNode*>( nodeBlueprint::theNodes[streamOutNodeNumber]);

		eventHandler::insertVisiterAtSignature(bind(&streamOutNode::evolve,s, 0.0),eventNumber);
		delete nod;




		network::addEdge( streamOutNodeNumber, timeNodeNumber);


	}





	void createNetwork::observeEventTimes( string fileName,nodeDescriptor eventNumber) {
		nodeBlueprint* nod = new nodeVirtualEdges<timeNode<baseType> >();
		nodeDescriptor timeNodeNumber = addNode ( nod );
		delete nod;

		nod = new  nodeVirtualEdges<streamOutNode>(fileName);
		nodeDescriptor streamOutNodeNumber = addNode(nod);
		streamOutNode *s = dynamic_cast<streamOutNode*>( nodeBlueprint::theNodes[streamOutNodeNumber]);

		eventHandler::insertVisiter(bind(&streamOutNode::evolve,s, 0.0),eventNumber);
		delete nod;




		network::addEdge( streamOutNodeNumber, timeNodeNumber);





	}

	nodeDescriptor createNetwork::lattice ( int sizex,  int sizey, double c, nodeBlueprint *n, edgeBlueprint *l )
	{
		int i,j;
		int a, b;

		c=c*c;

		if (sizex == 0 || sizey == 0)
			return -1;



		unsigned int firstNodeNumber=	addNode ( n );


		//	bool passedCircle = false;

		for ( i = 1 ; i < sizex*sizey; i++ )
		{
			addNode ( n );
		}
		for ( i = 0; i < sizex; i++ )
			for ( j = 0; j < sizey; j++ )
				for ( a= 0 ; a < sizex ; a++ )
				{
					if ( ( a-i ) * ( a-i ) > c )
						continue;
					for ( b = 0  ; b < sizey ; b++ )
					{
						if ( ( a - i ) * ( a - i ) + ( b-j ) * ( b-j ) <= c && ( a - i ) * ( a - i ) + ( b-j ) * ( b-j ) > 0 )
						{

							network::addEdge (firstNodeNumber+ i + sizey * j ,firstNodeNumber+ a + sizey * b, l );

						}
					}

				}


		//	cout << "HIERRAUS" << endl;

		return firstNodeNumber;
	}



	nodeDescriptor createNetwork::torusNearestNeighbors ( int sizex, int sizey, double k, nodeBlueprint *n, edgeBlueprint *l )
	{


		vector< pair< int, int > > distVector;
		vector< pair< int, int > > toAddForAllNodes;
		vector< pair< int, int > > toSelectRandomlyFrom;


		vector< pair<int, int > >::iterator it;
		//		bool cmp (pair< int, int > a, pair< int, int > b);




		for ( unsigned int i = 1; i < 50; i++ )
			for ( unsigned int j = 0; j <= i; j++ )
				distVector.push_back ( make_pair<int,int> ( i,j ) );

		sort ( distVector.begin(), distVector.end(), &cmp2d );
		//		distVector.sort(&cmp);




		int i,j;


		it = distVector.begin();
		for ( ; it != distVector.end(); it++ )
		{
			if ( it->first == it->second )
			{
				if ( k < 4 )
				{
					toSelectRandomlyFrom.push_back ( make_pair<int,int> ( it->first, it->second ) );
					toSelectRandomlyFrom.push_back ( make_pair<int,int> ( -it->first, it->second ) );
					toSelectRandomlyFrom.push_back ( make_pair<int,int> ( it->first, -it->second ) );
					toSelectRandomlyFrom.push_back ( make_pair<int,int> ( -it->first, -it->second ) );
					break;


				}
				else
				{
					k = k - 4;
					toAddForAllNodes.push_back ( make_pair<int,int> ( it->first, it->second ) );
					toAddForAllNodes.push_back ( make_pair<int,int> ( -it->first, it->second ) );
					toAddForAllNodes.push_back ( make_pair<int,int> ( it->first, -it->second ) );
					toAddForAllNodes.push_back ( make_pair<int,int> ( -it->first, -it->second ) );
				}
			}
			else if ( it->second == 0 )
			{
				if ( k < 4 )
				{
					toSelectRandomlyFrom.push_back ( make_pair<int,int> ( it->first, 0 ) );
					toSelectRandomlyFrom.push_back ( make_pair<int,int> ( -it->first, 0 ) );
					toSelectRandomlyFrom.push_back ( make_pair<int,int> ( 0, it->first ) );
					toSelectRandomlyFrom.push_back ( make_pair<int,int> ( 0, -it->first ) );

					break;



				}
				else
				{
					k = k - 4;
					toAddForAllNodes.push_back ( make_pair<int,int> ( it->first, 0 ) );
					toAddForAllNodes.push_back ( make_pair<int,int> ( -it->first, 0 ) );
					toAddForAllNodes.push_back ( make_pair<int,int> ( 0, it->first ) );
					toAddForAllNodes.push_back ( make_pair<int,int> ( 0, -it->first ) );
				}
			}
			else
			{
				if ( k < 8 )
				{

					toSelectRandomlyFrom.push_back ( make_pair<int,int> ( it->first, it->second ) );
					toSelectRandomlyFrom.push_back ( make_pair<int,int> ( -it->first, it->second ) );
					toSelectRandomlyFrom.push_back ( make_pair<int,int> ( it->first, -it->second ) );
					toSelectRandomlyFrom.push_back ( make_pair<int,int> ( -it->first, -it->second ) );
					toSelectRandomlyFrom.push_back ( make_pair<int,int> ( it->second, it->first ) );
					toSelectRandomlyFrom.push_back ( make_pair<int,int> ( -it->second, it->first ) );
					toSelectRandomlyFrom.push_back ( make_pair<int,int> ( it->second, -it->first ) );
					toSelectRandomlyFrom.push_back ( make_pair<int,int> ( -it->second, -it->first ) );
					break;
				}
				else
				{
					k = k - 8;
					toAddForAllNodes.push_back ( make_pair<int,int> ( it->first, it->second ) );
					toAddForAllNodes.push_back ( make_pair<int,int> ( -it->first, it->second ) );
					toAddForAllNodes.push_back ( make_pair<int,int> ( it->first, -it->second ) );
					toAddForAllNodes.push_back ( make_pair<int,int> ( -it->first, -it->second ) );
					toAddForAllNodes.push_back ( make_pair<int,int> ( it->second, it->first ) );
					toAddForAllNodes.push_back ( make_pair<int,int> ( -it->second, it->first ) );
					toAddForAllNodes.push_back ( make_pair<int,int> ( it->second, -it->first ) );
					toAddForAllNodes.push_back ( make_pair<int,int> ( -it->second, -it->first ) );
				}
			}
		}


		nodeDescriptor smallest = addNode(n);

		for ( i = 1 ; i < sizex*sizey ; i++ )
		{
			addNode ( n );
		}
//		nodeDescriptor largest = addNode(n); unused, daher auskommentiert und die for-Schleife verlängert

		int targetX;
		int targetY;
		for ( i = 0; i < sizex; i++ )
			for ( j = 0; j < sizey; j++ )
			{
				for (it = toAddForAllNodes.begin(); it != toAddForAllNodes.end(); it++)
				{
					targetX = it->first + i;
					targetY = it->second + j;
					while (targetX < 0) targetX+= sizex;
					while (targetY < 0) targetY+= sizey;
					targetX = targetX % sizex;
					targetY = targetY % sizey;


					network::addEdge (smallest +  i + sizex * j , smallest + targetX + sizex*targetY, l );
				}
				int targetVector;

				for (unsigned int ij = 0; ij < k ; ij++)
				{
					do
					{
						targetVector = network::noise.getUniformInt( 0, toSelectRandomlyFrom.size() -1);
						targetX = toSelectRandomlyFrom[targetVector].first + i;
						targetY = toSelectRandomlyFrom[targetVector].second + j;
						while (targetX < 0) targetX+= sizex;
						while (targetY < 0) targetY+= sizey;
						targetX = targetX % sizex;
						targetY = targetY % sizey;
					} while ( network::isLinked(smallest + i+sizex*j,smallest + targetX + sizex*targetY));

					network::addEdge ( smallest + i + sizex * j , smallest + targetX + sizex*targetY, l );

				}

			}
		return smallest;

	}


	nodeDescriptor createNetwork::torus ( int sizex,  int sizey, double c, nodeBlueprint *n, edgeBlueprint *l )
	{
		int i,j;
		int a, b;

		int distx, disty;

		c = c * c;
		if (sizex == 0 || sizey ==0)
			return -1;


		unsigned int firstNodeNumber = addNode(n);

		for ( i = 1 ; i < sizex*sizey; i++ )
		{
			addNode ( n );
		}
		for ( i = 0; i < sizex; i++ )
			for ( j = 0; j < sizey; j++ )
				for ( a= 0 ; a < sizex ; a++ )
				{
					if ( abs ( a-i ) > abs ( abs ( a-i ) - sizex ) )
						distx = abs ( abs ( a-i )-sizex );

					else
						distx = abs ( a-i );
					if ( distx*distx > c )
						continue;
					for ( b = 0  ; b < sizey ; b++ )
					{
						if ( abs ( b-j ) > abs ( abs ( b-j ) - sizex ) )
							disty = abs ( abs ( b-j )-sizex );
						else
							disty = abs ( b-j );


						if ( distx * distx + disty * disty  <= c && distx*distx + disty*disty > 0 )
						{

							network::addEdge (firstNodeNumber + i + sizey * j ,firstNodeNumber + a + sizey * b, l );

						}
					}

				}






		//	cout << "HIERRAUS" << endl;
		return firstNodeNumber;


	}






nodeDescriptor createNetwork::beeWeb ( int x, int y, nodeBlueprint *n )
{
	int i, a_x,a_y,b_x,b_y;
	int dist_x, dist_y;

	if (x == 0 || y == 0)
		return -1;

	nodeDescriptor firstNodeNumber = addNode(n);
	for ( i = 1; i < x*y; i++ )
		addNode ( n );


	for ( b_x = 0; b_x < x;b_x++ )
		for ( b_y = 0; b_y < y;b_y++ )
		{
			for ( a_x = 0; a_x < x;a_x++ )
				for ( a_y = 0; a_y < y;a_y++ )
				{

					dist_x = ( a_x - b_x ) % ( x );
					dist_y = ( a_y - b_y ) % ( y );


					if ( sqrt ( (baseType) dist_x*dist_x+dist_y*dist_y+dist_x*dist_y ) <=1 )

						network::addEdge ( a_x * x + a_y, b_x*x + b_y );


				}

		}
	return firstNodeNumber;
}



void createNetwork::addRandomEdgesUndirected ( double meanOutDeg, edgeBlueprint *l )
{

	int source, target;




	baseType meanOut = ( ( statisticsNetwork* ) this )->meanOutDegree() ;

	int toDo = ( int ) ( ( meanOutDeg - meanOut ) * network::numberVertices() / 2 );



	if ( toDo > 0 )
	{
		for ( int i = 0; i < toDo; i++ )
		{
			do
			{
				source = network::randomNode();
				target = network::randomNode();
			}
			while ( source == target || network::isLinked ( source,target ) );
			network::addEdge ( source,target,l );
			network::addEdge ( target,source,l );
		}
	}

}


void createNetwork::removeRandomEdgesUndirected ( double prop, edgeBlueprint * l)
{

	network::edgeList allLinks;
	network::edgeList toChange;
	network::edgeIterator it;
	network::edgesMatching (allLinks, l->getEdgeInfo().theEdgeType);


	for (it = allLinks.begin(); it != allLinks.end();it++)
		if (getTarget(*it) > getSource(*it))
			toChange.push_back(*it);

	for ( it = toChange.begin(); it != toChange.end(); it++ )
	{

		if ( network::noise.getUniform() > prop )
			continue;

		nodeDescriptor  source;
		nodeDescriptor  target;

		source = it->first ;
		target = getTarget ( *it);

		network::unlink ( source, target );
		network::unlink ( target, source );

	}

	network::clean();

}



void createNetwork::removeRandomEdges ( double prop, edgeBlueprint * l)
{


	network::edgeList toChange;
	network::edgeIterator it;
	network::edgesMatching (toChange, l->getEdgeInfo().theEdgeType);



	for ( it = toChange.begin(); it != toChange.end(); it++ )
	{

		if ( network::noise.getUniform() > prop )
			continue;

		nodeDescriptor  source;
		nodeDescriptor  target;

		source = it->first ;
		target = getTarget ( *it);

		network::unlink ( source, target );

	}

	network::clean();

}



void createNetwork::addRandomEdges ( double meanOutDeg, edgeBlueprint *l )
{

	int source, target;




	baseType meanOut = ( ( statisticsNetwork* ) this )->meanOutDegree() ;

	int toDo = ( int ) ( ( meanOutDeg - meanOut ) * network::numberVertices() );



	if ( toDo > 0 )
	{
		for ( int i = 0; i < toDo; i++ )
		{
			do
			{
				source = network::randomNode();
				target = network::randomNode();
			}
			while ( source == target || network::isLinked ( source,target ) );
			network::addEdge ( source,target,l );
		}
	}

}





	template < typename RANDOM>
void createNetwork::randomOutDegreeDistribution ( int number, RANDOM &r, nodeBlueprint *n )
{
	int i, j;
	int deg;
	int rnd;
	network::clear();
	for ( i = 0; i < number; i++ )
		addNode ( n );
	uniformInt randomNode ( 0,number-1 );
	for ( i = 0; i < number; i++ )
	{
		deg = ( int ) r();
		if ( deg > number - 1 )
			deg = number - 1;


		for ( j = 0; j < deg; j++ )
		{
			do { rnd = randomNode(); }
			while ( ( rnd == i ) || network::isLinked ( i,rnd ) );
			network::addEdge ( i,rnd );
		}
	}
}



	template < typename RANDOM>
void createNetwork::randomInDegreeDistribution ( int number, RANDOM &r, nodeBlueprint *n )
{
	int i, j;
	int deg;
	int rnd;
	network::clear();
	for ( i = 0; i < number; i++ )
		addNode ( n );
	uniformInt randomNode ( 0,number-1 );
	for ( i = 0; i < number; i++ )
	{
		deg = ( int ) r();
		if ( deg > number - 1 )
			deg = number - 1;


		for ( j = 0; j < deg; j++ )
		{
			do { rnd = randomNode(); }
			while ( ( rnd == i ) || network::isLinked ( i,rnd ) );
			network::addEdge ( rnd,i );
		}
	}
}







void createNetwork::addRandomEdgesDegreeDistributionUndirected ( function <double () > r , edgeBlueprint *l)
{
	nodeList vl;
	verticesMatching (vl,_dynNode_);
	nodeIterator it;
	vector <nodeDescriptor> nodeStubs;


	unsigned int numberLinks;
	double randomNumber;

	for 	(it = vl.begin(); it != vl.end(); it++)
	{
		randomNumber = r();
		if (randomNumber >= 0)
			numberLinks = randomNumber;
		else
			numberLinks = 0;
		for (unsigned int i = 0; i < numberLinks ; i++)
			nodeStubs.push_back(*it);
	}

	// shuffle the stub-list with Fisher-Yates

	unsigned int j;
	nodeDescriptor swap;
	for (unsigned int i = nodeStubs.size()-1; i > 1 ; i = i - 1)
	{
		j = gslNoise::getUniformInt (0, i);
		swap = nodeStubs [j];
		nodeStubs [j] = nodeStubs[i];
		nodeStubs [i] = swap;
	}
	for (unsigned int i = 0 ; i < nodeStubs.size() / 2; i++ )
	{
		addEdge ( nodeStubs[2 * i], nodeStubs [ 2 * i + 1], l);
		addEdge ( nodeStubs[2 * i + 1], nodeStubs [ 2 * i], l);
	}

}


void createNetwork::addRandomEdgesDegreeDistribution ( function <double () > r , edgeBlueprint *l)
{
	nodeList vl;
	verticesMatching (vl,_dynNode_);
	nodeIterator it;
	vector <nodeDescriptor> nodeStubs;


	unsigned int numberLinks;

	for 	(it = vl.begin(); it != vl.end(); it++)
	{
		numberLinks = r();
		for (unsigned int i = 0; i < numberLinks ; i++)
			nodeStubs.push_back(*it);
	}

	// shuffle the stub-list with Fisher-Yates

	unsigned int j;
	nodeDescriptor swap;
	for (unsigned int i = nodeStubs.size()-1; i > 1 ; i = i - 1)
	{
		j = gslNoise::getUniformInt (0, i);
		swap = nodeStubs [j];
		nodeStubs [j] = nodeStubs[i];
		nodeStubs [i] = swap;
	}
	for (unsigned int i = 0 ; i < nodeStubs.size() / 2; i++ )
		addEdge ( nodeStubs[2 * i], nodeStubs [ 2 * i + 1], l);

}



void createNetwork::addEnterNode ( string s )
{

	//		nodeBlueprint *n = new enterNode<baseType> ( s );
	//		addNode ( n );
	//		delete n;
}



void createNetwork::observeEvent (string s, nodeDescriptor signature)
{
	nodeBlueprint* nod = new nodeVirtualEdges <eventCountNode >(signature);
	nodeDescriptor newNodeNumber = addNode ( nod );

	delete nod;
	nod = new nodeVirtualEdges <streamOutNode > ( s );
	nodeDescriptor outNodeNumber = addNode ( nod );
	addEdge ( outNodeNumber, newNodeNumber);
	inOutNodeList.push_back ( dynamic_cast<dynNode*> ( node::theNodes[outNodeNumber] ));
	delete nod;
}

void createNetwork::observeTime ( string s )
{
	nodeBlueprint* nod = new nodeVirtualEdges<timeNode<baseType> >();
	nodeDescriptor timeNodeNumber = addNode ( nod );
	delete nod;

	observeWithoutCheck (timeNodeNumber, s, stdEdge);

}




nodeDescriptor createNetwork::streamInLattice ( int sizex, int sizey,string s )
{
	nodeBlueprint *n = new nodeVirtualEdges<streamInNode >( s );
	nodeDescriptor ret = lattice ( sizex,sizey,1,n, stdEdge );
	delete n;
	return ret;
}



void createNetwork::observeComponents (nodeDescriptor n, string fileName)
{
	unsigned int dimension =   ((dynNode*) node::theNodes[n])-> dimension();


		component<edgeVirtual> * l;

	for (unsigned int i = 0; i < dimension; i++) {
		l = new component <edgeVirtual> (i);
		observe (n, fileName, l);
		delete l;
	}




}





nodeDescriptor createNetwork::createFromAdjacencyList(string fileName, nodeBlueprint * n, edgeBlueprint *l)
{
	ifstream in (fileName.c_str());
	if (!in.is_open())
		throw (fileName + " nicht gefunden!").c_str();
	unsigned int size;
	in >> size;

	unsigned int smallest = addNode(n);

	for (unsigned int i = 1; i < size; i++)
		addNode(n);

	int source, target;
	baseType weight;

	while (in.peek() != -1)
	{
		in >> source;
		in >> target;
		in >> weight;
		if (in.eof())
			break;


//		if (weight == 0.0)
//			continue;

		if (weight != 1.0)
			((edgeVirtual*)l)->setWeight(weight);

		network::addEdge(source +smallest, target +smallest, l);




	}
	return smallest;
}












nodeDescriptor createNetwork::completeNetwork ( int number, nodeBlueprint *n, edgeBlueprint *l )
{
	int i, j;
//network::clear();
	if (number == 0)
		return -1;


	nodeDescriptor firstNodeNumber = addNode(n);
	for ( i = 1; i < number; i++ )
	{
		addNode ( n );

		//<baseType>::addNode < nodeBlueprint< baseType > > ();
		for ( j = 0; j < i; j++ )
		{
			network::addEdge (firstNodeNumber +  i, firstNodeNumber + j,l );
			network::addEdge (firstNodeNumber +  j, firstNodeNumber + i,l );
		}
	}
	return firstNodeNumber;
}

void createNetwork::addGlobalNoise ( boost::function <double() > r, nodeKind theNodeKind )
{
	//	nodeBlueprint * n = new nodeVirtualEdges <randomNode<baseType> >( r );
	//	nodeDescriptor newNodeNumber = addNode ( n );
	//	network::addEdges ( theNodeKind,newNodeNumber );


	//		addSuperAttractiveNode(n,theNodeKind);


}

void createNetwork::normalizeOutputs (baseType r)
{
	nodeIterator it;
	nodeList dynNodes;
	verticesMatching(dynNodes, _dynNode_);


	unsigned int degree;

	for (it = dynNodes.begin(); it != dynNodes.end(); it++)
	{
		degree =		nodeBlueprint::theNodes[*it]->degree();
		for (unsigned int i = 0 ; i < nodeBlueprint::theNodes[*it]->degree(); i ++)
		{
			nodeBlueprint::theNodes[*it]->setWeight (i, r / degree);
		}
	}

}


void createNetwork::normalizeInputs (baseType r)
{
	nodeIterator it;
	nodeList dynNodes;
	verticesMatching(dynNodes, _dynNode_);
	for (it = dynNodes.begin(); it != dynNodes.end(); it++)
		nodeBlueprint::theNodes[*it]->normalizeInWeightSum(r);

	network::clean();
}

nodeDescriptor createNetwork::cycle ( int number, int a,nodeBlueprint *n, edgeBlueprint *l )
{

	int i, j;

	if (number == 0)
		return - 1;
	else if (number == 1)
	{
		return	addNode(n);
	}

	unsigned int smallest = addNode(n);
	for ( i = 1 ; i < number ; i++ )
		addNode ( n );

	for ( j = 0; j < number; j++ )
		for ( i = 1; i <= a ; i++ )
		{
			//           cout << "VON:"<< j<< "NACH:" << ((number + j - i) % number)<< endl;
			network::addEdge ( smallest + j, smallest + ( ( number + j - i ) % number) ,l );
			network::addEdge ( smallest + j, smallest + ( ( number + j + i ) % number) ,l );
		}
	return smallest;
}



//void createNetwork::cycle ( int number, int a,nodeBlueprint *n )
//{
//	cycle (number, a, n, stdEdge);
//}



nodeDescriptor createNetwork::line ( unsigned int number, unsigned int a,nodeBlueprint *n, edgeBlueprint *l )
{

	unsigned int i, j;
	nodeDescriptor smallest = addNode(n);

	for ( i = 1 ; i < number - 1; i++ )
		addNode ( n );

	nodeDescriptor largest = addNode(n);

	for ( j = smallest; j <= largest; j++ )
		for ( i = 1; i <= a ; i++ )
		{
			//           cout << "VON:"<< j<< "NACH:" << ((number + j - i) % number)<< endl;
			if  (j + i <=  largest)
				network::addEdge ( j,  j + i  ,l );
			if (j >= smallest + i)
				network::addEdge ( j,   j  - i    ,l );
		}
	return smallest;
}









nodeDescriptor createNetwork::cycleCluster (int number1, nodeBlueprint *n1, int number2, nodeBlueprint *n2, int a)
{

	network::clear();

	int number = number1 + number2;
	int i1, i2, i, j;
	nodeDescriptor smallest = addNode(n1);
	for ( i1 = 1 ; i1 < number1; i1++ )
		addNode ( n1 );
	for ( i2 = 0 ; i2 < number2; i2++ )
		addNode ( n2 );

	for ( j = 0; j < number; j++ )
	{
		for ( i = 1; i <= a ; i++ )
		{
			network::addEdge ( j, ( ( number + ( j ) - i ) % number ) , stdEdge );
			network::addEdge ( j, ( ( number + ( j ) + i ) % number ) , stdEdge );
		}
	}
	return smallest;
}


void createNetwork::rewireSourcePerTimestep ( double prop,function <baseType ()> r, nodeKind theNodeKind )
{
	/*	nodeBlueprint *n = new nodeVirtualEdges <distributeRandomelyNode<baseType> > ( network::numberVertices(),r );
		nodeDescriptor newNodeNumber = addNode ( n );
		network::addEdges ( theNodeKind,newNodeNumber );

	//		addSuperAttractiveNode(n,theNodeKind);


	network::edgeList toChange;
	network::edgeIterator it;

	unsigned int i;
	network::edgesBetween ( toChange,theNodeKind,theNodeKind );



	for ( it = toChange.begin(); it != toChange.end(); it++ )
	{
	if ( network::noise.getUniform() > prop )
	continue;
	i = it->first;
	throw "createNetwork::rewireSourcePerTimeStep need repairing!";
	//			it->second ->weight = 1;
	//			network::theNodes[network::numberVertices()-1]->link ( it->second->target, it->second );
	//			network::theNodes[i]->unlink (it->second->target );
	}
*/
}





void createNetwork::rewireTarget ( double prop, nodeKind theNodeKind )
{
	network::edgeList toChange;
	network::edgeIterator it;
	network::edgesBetween ( toChange,theNodeKind,theNodeKind );

	nodeList vl;
	network::verticesMatching(vl, theNodeKind);
	getRandomNode r (vl);

	for ( it = toChange.begin() ; it != toChange.end(); it++ )
		if (( network::noise.getUniform() <= prop ) )
			nodeBlueprint::theNodes[it->first]->getEdge(it->second)->targetNumber = r();
}




void createNetwork::rewireWeights ( double prop ,boost::function<double () > r,nodeKind theNodeKind )
{
	network::edgeList toChange;
	network::edgeIterator it;
	//		unsigned int i;

	network::edgesBetween ( toChange, theNodeKind, theNodeKind );

	nodeList vl;
	network::verticesMatching(vl, theNodeKind);
	getRandomNode rn (vl);

	for ( it = toChange.begin(); it != toChange.end(); it++ )
	{
		if ( network::noise.getUniform() > prop )
			continue;

		nodeDescriptor  newSource;
		nodeDescriptor  newTarget;

		nodeDescriptor oldSource = it->first ;
		nodeDescriptor oldTarget = getTarget(*it);

		do
		{
			newSource = rn();
			newTarget = rn();
		}
		while ( newSource == newTarget || nodeBlueprint::theNodes[newSource]->isLinked ( nodeBlueprint::theNodes[newTarget] ) );   // keine Selbst- und Doppelverbindungen

			//			if ((network::theNodes[newSource] == (*it)->source) && (network::theNodes[newTarget] == (*it)->target))
			//				continue;

		((edgeVirtual*)  getEdge(*it))->setWeight( r() );

		network::addEdge ( newSource,newTarget, (edgeBlueprint *) node::theNodes[it->first]-> getEdge(it->second));

		network::unlink( oldSource, oldTarget);
	}


	network::clean();
}



void createNetwork::rewire ( double prop, nodeBlueprint *n )
{

	network::edgeList toChange;
	network::edgeIterator it;

	network::edgesBetween ( toChange, n,n);

	nodeList vl;
	network::verticesMatching(vl, n);
	getRandomNode r (vl);



	for ( it = toChange.begin(); it != toChange.end(); it++ )
	{

		//		network::printAdjacencyList();
		if ( network::noise.getUniform() > prop )
			continue;

		nodeDescriptor newSource, oldSource;
		nodeDescriptor newTarget, oldTarget;

		oldSource = it->first ;
		oldTarget = getTarget ( *it);


		do
		{
			newSource = r();
			newTarget = r();

		}
		while ( newSource == newTarget || nodeBlueprint::theNodes[newSource]->isLinked ( nodeBlueprint::theNodes[newTarget] ) );   // keine Selbst- und Doppelverbindungen

		if ( ( newSource == oldSource ) && ( newTarget == oldTarget ) )
			continue;


		network::addEdge ( newSource,newTarget, (edgeBlueprint *)getEdge(*it));
		network::unlink ( oldSource, oldTarget );

	}

	network::clean();

}









void createNetwork::replaceEdges ( double prop, edgeBlueprint * l, nodeBlueprint *n )
{

	network::edgeList toChange;
	network::edgeIterator it;

	network::edgesBetween ( toChange, n,n);

	nodeList vl;
	network::verticesMatching(vl, n);
	getRandomNode r (vl);


	for ( it = toChange.begin(); it != toChange.end(); it++ )
	{
		//		network::printAdjacencyList();
		if ( network::noise.getUniform() > prop )
			continue;

		nodeDescriptor newSource, oldSource;
		nodeDescriptor newTarget, oldTarget;

		oldSource = it->first ;
		oldTarget = getTarget(*it);


		do
		{
			newSource = r();
			newTarget = r();

		}
		while ( newSource == newTarget || nodeBlueprint::theNodes[newSource]->isLinked ( nodeBlueprint::theNodes[newTarget] ) );   // keine Selbst- und Doppelverbindungen

		if ( ( newSource == oldSource ) && ( newTarget == oldTarget ) )
			continue;


		network::addEdge ( newSource,newTarget, l );
		nodeBlueprint::theNodes[oldSource]->unlink ( oldTarget );

	}
	clean();

}




void createNetwork::rewireUndirected ( double prop, nodeKind theNodeKind ) // rewire für ungerichtete Netzwerke die danach immer noch ungerichtetet sein sollen

{
	network::edgeList allLinks, toChange;
	network::edgeIterator it;

	network::edgesBetween ( allLinks, theNodeKind, theNodeKind );

	nodeList vl;
	network::verticesMatching(vl, theNodeKind);
	getRandomNode r (vl);


	for (it = allLinks.begin(); it != allLinks.end();it++)
		if (getTarget(*it) > getSource(*it))
			toChange.push_back(*it);


	for ( it = toChange.begin(); it != toChange.end(); it++ )
	{
		if ( network::noise.getUniform() > prop )
			continue;

		nodeDescriptor newSource, oldSource;
		nodeDescriptor newTarget, oldTarget;

		oldSource = it->first ;
		oldTarget = getTarget (*it);

		do
		{
			newSource = r();
			newTarget = r();
		}

		while( newSource == newTarget || nodeBlueprint::theNodes[newSource]->isLinked (nodeBlueprint::theNodes[newTarget]) ); //keine selfloops und Doppelverbindungen

		if ( ( newSource == oldSource ) && ( newTarget == oldTarget ) )
			continue;

		network::addEdge ( newSource, newTarget, (edgeBlueprint *)getEdge(*it));
		network::addEdge ( newTarget, newSource, (edgeBlueprint *)getEdge(*it));
		network::unlink ( oldSource, oldTarget );
		network::unlink ( oldTarget, oldSource );

	}
	clean();

}


void createNetwork::rewireTargetUndirected ( double prop, nodeKind theNodeKind ) // rewireTarget für ungerichtete Netzwerke um danach wieder ein ungerichtetes Netzwerk zu erhalten

{
	network::edgeList allLinks, toChange;
	network::edgeIterator it;
	network::edgesBetween ( allLinks, theNodeKind, theNodeKind );

	nodeDescriptor Source, oldTarget, newTarget;

	nodeList vl;
	network::verticesMatching(vl, theNodeKind);
	getRandomNode r (vl);


	for ( it = allLinks.begin(); it != allLinks.end(); it++)
		if ( getTarget (*it) > getSource (*it)  )
			toChange.push_back(*it);

	for (it = toChange.begin() ; it != toChange.end(); it++ )
	{
		if (( network::noise.getUniform() <= prop ) )
		{

			Source = it->first;
			oldTarget = getTarget (*it);

			do
			{
			newTarget = r();
			}

			while ( Source == newTarget || nodeBlueprint::theNodes[Source]->isLinked ( nodeBlueprint::theNodes[newTarget] )  ) ; //keine Selfloops oder Doppelverbindungnen

			nodeBlueprint::theNodes[it->first]->getEdge(it->second)->targetNumber = newTarget ;

			network::addEdge ( newTarget, Source, (edgeBlueprint *)getEdge(*it) );
			network::unlink ( oldTarget, Source );

		}
	}
	clean();

}


void createNetwork::rewireSource ( double prop, nodeKind theNodeKind )
{
	network::edgeList toChange;
	network::edgeIterator it;
	unsigned int i;

	network::edgesBetween ( toChange,theNodeKind,theNodeKind );

	nodeList vl;
	network::verticesMatching(vl, theNodeKind);
	getRandomNode r (vl);

	for ( it = toChange.begin(); it != toChange.end(); it++ )
	{
		if ( network::noise.getUniform() > prop )
			continue;

		i = ( *it ).first;
		unsigned int a;
		while ( ( a = r() ) == i || network::isLinked ( a, getTarget(*it)) )  {};
		link ( a,getTarget( *it) );
		unlink ( i, getTarget(( *it)) );
	}

	clean();

}


nodeDescriptor createNetwork::randomNetwork ( int size, double promille, nodeBlueprint *n, edgeBlueprint *l )
{
	int i, j;


	if (size == 0)
		return -1;

	nodeDescriptor smallest= addNode(n);
	for ( i = 1; i < size; i++ )
	{
		addNode ( n );

		for ( j = 0; j < i; j++ )
		{
			if ( network::noise.getUniform() <= promille )
				network::addEdge ( smallest + i,smallest + j,l );
			if ( network::noise.getUniform() <= promille )
				network::addEdge ( smallest + j,smallest + i,l );

		}
	}
	return smallest;
}


nodeDescriptor createNetwork::randomUndirectedNetwork ( int size, double promille, nodeBlueprint *n, edgeBlueprint *l )
{
	int i, j;


	if (size == 0)
		return -1;

	nodeDescriptor smallest= addNode(n);
	for ( i = 1; i < size; i++ )
	{
		addNode ( n );

		for ( j = 0; j < i; j++ )
		{
			if ( network::noise.getUniform() <= promille )
			{
				network::addEdge ( smallest + i,smallest + j,l );
				network::addEdge ( smallest + j,smallest + i,l );
			}
		}
	}
	return smallest;
}

//baseType limit();

nodeDescriptor createNetwork::scaleFreeNetwork ( int size, int c, nodeBlueprint *n, edgeBlueprint *l )
{
	if (size == 0)
		return -1;
	if (size <= c)
		return -1;
	
	int degrees[size];
	nodeDescriptor smallest= completeNetwork ( c, n, l );

	for ( int i = 0; i<c; i++)
		degrees[i]=c-1;
	for ( int i = c; i<size;i++)
		degrees[i]=0;
	
	for ( int i = 0; i<size-c; i++)
	{
		addNode ( n );
		int used[c-1];
		for(int k=0; k<c-1; k++)
			used[k]=-1;
		for(int k=0; k<c; k++)
		{
			int j;
			bool isUsed;
			do
			{
				if(c*(c+2*i-1)+k<1)
				{
					j=0;
				}
				else
				{
					int r=network::noise.getUniformInt(1, c*(c+2*i-1)+k );
					int sum=0;
					for( j=0; j<c+i; j++)
					{
						sum+=degrees[j];
						if(r<=sum)
						{
							break;
						}
					}
					isUsed=false;
					for( int l=0; l<k; l++)
						if(used[l]==j)
						{
							isUsed=true;
						}
				}
			}
			while(isUsed);
			network::addEdge (smallest+c+i, smallest+j, l);
			network::addEdge (smallest+j, smallest+c+i, l);
			degrees[j]+=1;	
			used[k]=j;
		}
		for(int k=0; k<c-1; k++)
			used[k]=-1;
		degrees[c+i]=c;
	}
	return smallest;
}

//baseType limit() { return 0; };



nodeDescriptor createNetwork::createFromMatrix ( vector <vector<baseType> > weights, nodeBlueprint *n )
{
	network::clear();

	nodeDescriptor smallest = addNode(n);
	for ( unsigned int l = 1; l < weights.size(); l++ )
	{
		addNode ( n );
	}


	for ( unsigned int i = 0; i < weights.size(); i++ )
		for ( unsigned int j = 0; j < weights.size(); j++ )
			if ( std::abs ( weights[i][j] ) != (baseType) 0 )
				network::link ( i,j,weights[i][j] );

	return smallest;

}





nodeDescriptor createNetwork::createFromAdjacencyMatrix (string fileName, nodeBlueprint * n, edgeBlueprint *e)
{
	ifstream in(fileName.c_str());

	string line;


	if (!getline (in, line, '\n'))
		throw "error createFromAdjacencyMatrix. File does not even contain one line ?";

	stringstream ss(line);
	double d;

	unsigned int size = 0;
	while ( ss >> d)
		size ++;

	unsigned int firstNodeNumber = addNode(n);

	for ( unsigned int i = 1; i < size; i++ )
		addNode (n);

	in.seekg(0, fstream::beg);


	for ( unsigned int i = firstNodeNumber; i < firstNodeNumber+size; i++ )
		for ( unsigned int j = firstNodeNumber; j < firstNodeNumber+size; j++ )
		{
			in >> d;
			if (d ==0)
				continue;
			if (d != 1.0)
				e->setWeight(d);
			addEdge ( i,j,e);
		}
	return firstNodeNumber;
}



//! wie oben mit links vom Typ l
void createNetwork::observeSum ( string s, edgeBlueprint *l )
{


	nodeBlueprint *nod = new nodeVirtualEdges <streamOutNode> ( s );
	int newNodeNumber = addNode ( nod );

//	unsigned int nodeNumbers = numberVertices(_dynNode_);
//	l->setWeight(1.0/nodeNumbers);
	network::addEdges ( newNodeNumber,_dynNode_,l );

	inOutNodeList.push_back ( dynamic_cast<dynNode*> (nodeBlueprint::theNodes[newNodeNumber] ));
//	addEnterNode ( s );
	delete nod;
}


//! wie oben allerdings wird die Phasenkohärenz r der States s_i weggeschrieben: r = 1/N \sum\limits_i exp( 2 * PI * s_i). Phasen gehen von 0 bis 1 !!! TODO: vielleicht von streamOutNode erben ??

//void createNetwork::observePhaseCoherence ( string s )
//{
//	nodeBlueprint *nod = new nodeVirtualEdges < calculateMeanPhaseCoherence > ();
//	nodeDescriptor newNodeNumber = addNode ( nod );
//	network::addEdges ( newNodeNumber,_dynNode_ );
//	delete nod;
//	observe(newNodeNumber,s);
//}


void createNetwork::observeAll ( string s, edgeBlueprint *l )
{
	network::nodeList vl;
	network::verticesMatching ( vl,_dynNode_ );
	network::nodeIterator it;

	for ( it = vl.begin(); it != vl.end(); it++ )
		observe( *it,s, l);

}


//void createNetwork::observeAll ( string s, edgeBlueprint *l , nodeBlueprint *n , nodeDescriptor lower , nodeDescriptor upper)
//{
//
//
//	nodeBlueprint *nod = new nodeVirtualEdges < calculateMeanPhaseCoherence > ();
//	nodeDescriptor newNodeNumber = addNode ( nod );
//	nodeList vl;
//
//	if (n == stdNode)
//		verticesMatching(vl, _dynNode_);
//	else
//		verticesMatching(vl, n);
//
//	nodeIterator vi;
//	for (vi=vl.begin();vi != vl.end();vi++)
//	{
//		if ((node::theNodes[*vi]->getNumber() >=lower) && (node::theNodes[*vi]->getNumber() <= upper))
//		observe( *vi,s, l);
//	}
//
//
//}
//




void createNetwork::observePhaseCoherence ( string s, edgeBlueprint *l, nodeBlueprint *n, nodeDescriptor lower, nodeDescriptor upper)
{

	nodeBlueprint *nod = new nodeVirtualEdges < calculateMeanPhaseCoherence > ();
	nodeDescriptor newNodeNumber = addNode ( nod );
	nodeList vl;

	if (n == stdNode)
		verticesMatching(vl, _dynNode_);
	else
		verticesMatching(vl, n);

	nodeIterator vi;
	for (vi=vl.begin();vi != vl.end();vi++)
	{
		if ((node::theNodes[*vi]->getNumber() >=lower) && (node::theNodes[*vi]->getNumber() <= upper))
			network::addEdge(newNodeNumber, *vi);
	}

	delete nod;
	nod = new nodeVirtualEdges <streamOutNode > ( s );
	nodeDescriptor outNodeNumber = addNode ( nod );
	addEdge ( outNodeNumber, newNodeNumber);
	inOutNodeList.push_back ( dynamic_cast<dynNode*> ( node::theNodes[outNodeNumber] ));
	delete nod;
}

void createNetwork::observePhaseDistance ( string s, nodeBlueprint *n)
{
	network::edgeList *vl = new edgeList();
	edgesBetween(*vl, n->getNodeInfo().theNodeType, n->getNodeInfo().theNodeType);
	nodeBlueprint *nod = new nodeVirtualEdges <phaseDistance <baseType> >();
	 ( (nodeVirtualEdges< phaseDistance <baseType > > *) nod)->setList (vl);

	long newNodeNumber = addNode (nod);
	observe(newNodeNumber,s);

}

void createNetwork::observeHist ( string fileName,    nodeBlueprint *n)
{
	nodeBlueprint *nod = new  nodeVirtualEdges<streamOutNodeHist>(fileName);
		nodeDescriptor streamOutNodeNumber = addNode(nod);
		network::addEdges ( streamOutNodeNumber, n->getNodeInfo().theNodeType);

	inOutNodeList.push_back ( dynamic_cast<dynNode*> ( nodeBlueprint::theNodes[streamOutNodeNumber] ));



	}





void createNetwork::observePhaseCorrelation ( string s, nodeBlueprint *n)
{
	network::edgeList *vl = new edgeList();
	edgesBetween(*vl, n->getNodeInfo().theNodeType, n->getNodeInfo().theNodeType);
	nodeBlueprint *nod = new nodeVirtualEdges <phaseCorrelation <baseType> >();
	 ( (nodeVirtualEdges< phaseCorrelation <baseType > > *) nod)->setList (vl);

	long newNodeNumber = addNode (nod);
	observe(newNodeNumber,s);

}
//void createNetwork::observePhaseCoherence ( string s, nodeBlueprint *n,  edgeBlueprint *l )
//{
//	//	if (n->getNodeInfo().theNodeType == _pcoIFNeuron_ && l->getEdgeInfo().theEdgeType == _phaseOfPCPO_)
//	//		nod = new nodeTemplateEdges  <phaseOfPCPO < edge >,  pcoIFNeuron,   calculateMeanPhaseCoherence  >;
//	//	else
//
//
//	nodeBlueprint *nod = new nodeVirtualEdges < calculateMeanPhaseCoherence > ();
//	nodeDescriptor newNodeNumber = addNode ( nod );
//	network::addEdges ( newNodeNumber,n -> getNodeInfo().theNodeType,l );
//	delete nod;
//
//
//
//}
//

//! wie oben. Phasen werden von Edges vom Typ l übergeben.
//void createNetwork::observePhaseCoherence ( string s, edge *l )
//{
//
//	nodeBlueprint *nod = new nodeVirtualEdges < calculateMeanPhaseCoherence > ();
//	nodeDescriptor newNodeNumber = addNode ( nod );
//	network::addEdges ( newNodeNumber,_dynNode_,l );
//	delete nod;
//
//	observe(newNodeNumber,s);
//}
//

void createNetwork::observeMeanPhase ( string s )
{
	nodeBlueprint *nod = new nodeVirtualEdges <calculateMeanPhase> ();
	nodeDescriptor newNodeNumber = addNode ( nod );
	network::addEdges ( newNodeNumber,_dynNode_ );
	delete nod;
	observe(newNodeNumber,s);
}

//! wie oben. Phasen werden von Edges vom Typ l übergeben.
void createNetwork::observeMeanPhase ( string s, edgeBlueprint *l )
{
	nodeBlueprint *nod = new nodeVirtualEdges <calculateMeanPhase> ();
	nodeDescriptor newNodeNumber = addNode ( nod );
	network::addEdges ( newNodeNumber,_dynNode_,l );
	delete nod;

	observe(newNodeNumber,s);
}



//! schreibt die Simulationszeit dynNode::time in die Datei s.


void createNetwork::observeEventCounter ( string s, unsigned int signature)
{
	nodeBlueprint* nod = new nodeVirtualEdges <eventCountNode>  (signature);
	nodeDescriptor newNodeNumber = addNode ( nod );
	observe ( newNodeNumber, s );

}



//! observiert den Knoten number mit einer stdEdge und schreibt in die Datei s.
//void createNetwork::observe ( string s, nodeDescriptor number )
//{
//	nodeBlueprint *nod = new nodeVirtualEdges <streamOutNode> ( s );
//	nodeDescriptor newNodeNumber = addNode ( nod );
//	addEdge ( newNodeNumber, number );
//	inOutNodeList.push_back ( (dynamic_cast<dynNode*> (nodeBlueprint::theNodes[newNodeNumber] )));
//
//	delete nod;
//}
//


void createNetwork::observe ( nodeDescriptor number, string s, edgeBlueprint * l )
{
	if (node::theNodes.size()  <= number  || node::theNodes[number] == NULL)
		throw "node which should be observed does not exist.";
	if	((node::theNodes[number]->getNodeInfo().theNodeKind & _dynNode_ )== 0)
		throw "node to be observed is no dynNode.";
	observeWithoutCheck (number, s, l);
}


void createNetwork::observeWithoutCheck (nodeDescriptor number, string s, edgeBlueprint *l)
{
	nodeBlueprint *nod;

	if (getGlobal<bool>("outputBinary"))
		nod = new nodeVirtualEdges <streamOutNodeBinary > ( s );
	else
		nod = new nodeVirtualEdges <streamOutNode > ( s );
	nodeDescriptor newNodeNumber = addNode ( nod );

	addEdge ( newNodeNumber, number,l );
	inOutNodeList.push_back ( dynamic_cast<dynNode*> ( nodeBlueprint::theNodes[newNodeNumber] ));
	delete nod;

}











}
