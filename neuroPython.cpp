#include "registerStandards.h"

#include <stdio.h>
#include "commandLineArguments.h"

#include "node.h"
#include "neuroPython.h"

#include <fstream>
#if OPENGL
#include "glNetwork.h"
#endif


#include <boost/python.hpp>
#include <boost/python/module.hpp>
#include <boost/python/def.hpp>
#include <boost/python/suite/indexing/vector_indexing_suite.hpp>
#include <string>


#include "globals.h"

#include "docstrings.h"


//typedef double baseType;
//network<baseType> *netCheat = 0;




namespace { // Avoid cluttering the global namespace.
	using namespace conedy;


template <class N>
	 N* edgeFactory1 (double arg1)
	{
		N* res = new N();
		vector <baseType> allParams;
		allParams.push_back(arg1);
		res->setParameter(allParams);return res;
	}


template <class N>
	 N* edgeFactory2 (double arg1, double arg2)
	{
		N* res = new N();
		vector <baseType> allParams;
		allParams.push_back(arg1);
		allParams.push_back(arg2);
		res->setParameter(allParams);return res;
	}

template <class N>
	 N* edgeFactory3 (double arg1, double arg2, double arg3)
	{
		N* res = new N();
		vector <baseType> allParams;
		allParams.push_back(arg1);
		allParams.push_back(arg2);
		allParams.push_back(arg3);
		res->setParameter(allParams);return res;
	}

template <class N>
	 N* edgeFactory4 (double arg1, double arg2, double arg3, double arg4)
	{
		N* res = new N();
		vector <baseType> allParams;
		allParams.push_back(arg1);
		allParams.push_back(arg2);
		allParams.push_back(arg3);
		allParams.push_back(arg4);
		res->setParameter(allParams);return res;
	}

template <class N>
	 N* edgeFactory5 (double arg1, double arg2, double arg3, double arg4, double arg5)
	{
		N* res = new N();
		vector <baseType> allParams;
		allParams.push_back(arg1);
		allParams.push_back(arg2);
		allParams.push_back(arg3);
		allParams.push_back(arg4);
		allParams.push_back(arg5);
		res->setParameter(allParams);return res;
	}


template <class N>
	 N* edgeFactory6 (double arg1, double arg2, double arg3, double arg4, double arg5, double arg6)
	{
		N* res = new N();
		vector <baseType> allParams;
		allParams.push_back(arg1);
		allParams.push_back(arg2);
		allParams.push_back(arg3);
		allParams.push_back(arg4);
		allParams.push_back(arg5);
		allParams.push_back(arg6);
		res->setParameter(allParams);return res;
	}

template <class N>
	 N* edgeFactory7 (double arg1, double arg2, double arg3, double arg4, double arg5, double arg6, double arg7)
	{
		N* res = new N();
		vector <baseType> allParams;
		allParams.push_back(arg1);
		allParams.push_back(arg2);
		allParams.push_back(arg3);
		allParams.push_back(arg4);
		allParams.push_back(arg5);
		allParams.push_back(arg6);
		allParams.push_back(arg7);
		res->setParameter(allParams);return res;
	}

template <class N>
	 N* edgeFactory8 (double arg1, double arg2, double arg3, double arg4, double arg5, double arg6, double arg7, double arg8)
	{
		N* res = new N();
		vector <baseType> allParams;
		allParams.push_back(arg1);
		allParams.push_back(arg2);
		allParams.push_back(arg3);
		allParams.push_back(arg4);
		allParams.push_back(arg5);
		allParams.push_back(arg6);
		allParams.push_back(arg7);
		allParams.push_back(arg8);
		res->setParameter(allParams);return res;
	}


template <class N>
	 N* edgeFactory9 (double arg1, double arg2, double arg3, double arg4, double arg5, double arg6, double arg7, double arg8, double arg9)
	{
		N* res = new N();
		vector <baseType> allParams;
		allParams.push_back(arg1);
		allParams.push_back(arg2);
		allParams.push_back(arg3);
		allParams.push_back(arg4);
		allParams.push_back(arg5);
		allParams.push_back(arg6);
		allParams.push_back(arg7);
		allParams.push_back(arg8);
		allParams.push_back(arg9);
		res->setParameter(allParams);return res;
	}


template <class N>
	 N* nodeFactory1 (double arg1)
	{
		N* res = new N();
		vector <baseType> allParams;
		allParams.push_back(arg1);
		res->rerouteParams(allParams);return res;
	}


template <class N>
	 N* nodeFactory2 (double arg1, double arg2)
	{
		N* res = new N();
		vector <baseType> allParams;
		allParams.push_back(arg1);
		allParams.push_back(arg2);
		res->rerouteParams(allParams);return res;
	}

template <class N>
	 N* nodeFactory3 (double arg1, double arg2, double arg3)
	{
		N* res = new N();
		vector <baseType> allParams;
		allParams.push_back(arg1);
		allParams.push_back(arg2);
		allParams.push_back(arg3);
		res->rerouteParams(allParams);return res;
	}

template <class N>
	 N* nodeFactory4 (double arg1, double arg2, double arg3, double arg4)
	{
		N* res = new N();
		vector <baseType> allParams;
		allParams.push_back(arg1);
		allParams.push_back(arg2);
		allParams.push_back(arg3);
		allParams.push_back(arg4);
		res->rerouteParams(allParams);return res;
	}

template <class N>
	 N* nodeFactory5 (double arg1, double arg2, double arg3, double arg4, double arg5)
	{
		N* res = new N();
		vector <baseType> allParams;
		allParams.push_back(arg1);
		allParams.push_back(arg2);
		allParams.push_back(arg3);
		allParams.push_back(arg4);
		allParams.push_back(arg5);
		res->rerouteParams(allParams);return res;
	}


template <class N>
	 N* nodeFactory6 (double arg1, double arg2, double arg3, double arg4, double arg5, double arg6)
	{
		N* res = new N();
		vector <baseType> allParams;
		allParams.push_back(arg1);
		allParams.push_back(arg2);
		allParams.push_back(arg3);
		allParams.push_back(arg4);
		allParams.push_back(arg5);
		allParams.push_back(arg6);
		res->rerouteParams(allParams);return res;
	}

template <class N>
	 N* nodeFactory7 (double arg1, double arg2, double arg3, double arg4, double arg5, double arg6, double arg7)
	{
		N* res = new N();
		vector <baseType> allParams;
		allParams.push_back(arg1);
		allParams.push_back(arg2);
		allParams.push_back(arg3);
		allParams.push_back(arg4);
		allParams.push_back(arg5);
		allParams.push_back(arg6);
		allParams.push_back(arg7);
		res->rerouteParams(allParams);return res;
	}

template <class N>
	 N* nodeFactory8 (double arg1, double arg2, double arg3, double arg4, double arg5, double arg6, double arg7, double arg8)
	{
		N* res = new N();
		vector <baseType> allParams;
		allParams.push_back(arg1);
		allParams.push_back(arg2);
		allParams.push_back(arg3);
		allParams.push_back(arg4);
		allParams.push_back(arg5);
		allParams.push_back(arg6);
		allParams.push_back(arg7);
		allParams.push_back(arg8);
		res->rerouteParams(allParams);return res;
	}


template <class N>
	 N* nodeFactory9 (double arg1, double arg2, double arg3, double arg4, double arg5, double arg6, double arg7, double arg8, double arg9)
	{
		N* res = new N();
		vector <baseType> allParams;
		allParams.push_back(arg1);
		allParams.push_back(arg2);
		allParams.push_back(arg3);
		allParams.push_back(arg4);
		allParams.push_back(arg5);
		allParams.push_back(arg6);
		allParams.push_back(arg7);
		allParams.push_back(arg8);
		allParams.push_back(arg9);
		res->rerouteParams(allParams);return res;
	}








	void initializeConedy ()
	{
		gslNoise::initialise();
		//	commandLineArguments::initialize(argc, argv);

#if CONDOR
		uniqueNumber::initialize();
#endif

		registerStandards();


#if OPENGL
		GLNetwork::registerStandardValues();
#endif

		//	params<double>::initialise ( &command::declare );
		//	params<vector<double> >::initialise (&command::declare);


		//	cout << "Conedy erfolgreich initialisiert!" << endl;

	};


	MyNetwork<baseType> * networkFactory()
	{
		MyNetwork<baseType> n;
		return new MyNetwork<baseType>(n);
	}



	using namespace boost::python;

	int i;

	// Python requires an exported function called init<module-name> in every
	// extension module. This is where we build the module contents.


	//BOOST_PYTHON_MEMBER_FUNCTION_OVERLOADS(rewire_overloads, MyNetwork<baseType>::rewire, 1, 3)


	BOOST_PYTHON_MEMBER_FUNCTION_OVERLOADS (lattice_overloads, lattice, 2,5);
	//BOOST_PYTHON_MEMBER_FUNCTION_OVERLOADS (evolve_overloads, evolve, 2,3);
	BOOST_PYTHON_MEMBER_FUNCTION_OVERLOADS (rewire_overloads, rewire, 1,2);
	//BOOST_PYTHON_MEMBER_FUNCTION_OVERLOADS (addEdge_overloads, addEdge, 2,3);
	BOOST_PYTHON_MEMBER_FUNCTION_OVERLOADS (rewireUndirected_overloads, rewireUndirected, 1,2);
	BOOST_PYTHON_MEMBER_FUNCTION_OVERLOADS (randomNetwork_overloads, randomNetwork, 2,4);
	BOOST_PYTHON_MEMBER_FUNCTION_OVERLOADS (randomizeStates_overloads, randomizeStates, 2,4);
	BOOST_PYTHON_MEMBER_FUNCTION_OVERLOADS (observe_overloads, observe, 2,3);
	BOOST_PYTHON_MEMBER_FUNCTION_OVERLOADS (observeAll_overloads, observeAll, 1,2);
	BOOST_PYTHON_MEMBER_FUNCTION_OVERLOADS (completeNetwork_overloads, completeNetwork, 1,3);
	BOOST_PYTHON_MEMBER_FUNCTION_OVERLOADS (cycle_overloads, cycle, 2,4);
	BOOST_PYTHON_MEMBER_FUNCTION_OVERLOADS (createFromAdjacencyList_overloads, createFromAdjacencyList, 1,3);
	BOOST_PYTHON_MEMBER_FUNCTION_OVERLOADS (createFromAdjacencyMatrix_overloads, createFromAdjacencyMatrix, 1,3);
	BOOST_PYTHON_MEMBER_FUNCTION_OVERLOADS (observePhaseCoherence_overloads, observePhaseCoherence, 1,5);
	BOOST_PYTHON_MEMBER_FUNCTION_OVERLOADS (observeSum_overloads, observeSum, 1,2);
	BOOST_PYTHON_MEMBER_FUNCTION_OVERLOADS (setState_overloads, setInitialCondition, 2,13);
	BOOST_PYTHON_MEMBER_FUNCTION_OVERLOADS (getState_overloads, getState, 1,2);
	BOOST_PYTHON_MEMBER_FUNCTION_OVERLOADS (setStateTemplate_overloads, setState, 1,12);

	BOOST_PYTHON_MEMBER_FUNCTION_OVERLOADS (addRandomEdges_overloads, addRandomEdges, 1,2);

	void translator (const char *c)
	{ PyErr_SetString (PyExc_UserWarning, c); }




	BOOST_PYTHON_MODULE(conedy)
	{

		register_exception_translator<const char *>(translator);

#if RECOMPILE

		if (!system ("recompilePython-Conedy 2> /dev/null"))
		{
			cout << "Mission accomplished. You can restart your script now." << endl;
			exit (1);
		}

#endif



		initializeConedy();


		//	docstring_options doc_options(1,1,0);


		//	scope current;
		//	current.attr("aa") = &i;

		object o = object (i);

		//	scope().attr("aa") = &i;

		scope().attr("__doc__") =
			"What is Conedy"
			"================"
			"Conedy is a tool which allows you to integrate networks where each node is represented by some dynamical system. It is designed to allow for an change of the network structure or differential equation sperarately. ";



		boost::python::class_<std::vector<double> >("PyVec")
			.def(boost::python::vector_indexing_suite<std::vector<double> >());


		//	BOOST_PYTHON_MEMBER_FUNCTION_OVERLOADS (
		// Add regular functions to the module.


		def("set", &globals::setGlobal<baseType>);
		def("set", &globals::setGlobal<string>);
		def("set", &globals::setGlobal<bool>);
		def("set", &globals::setGlobal<int>);
		def("get", &globals::getGlobal<baseType>);
		def("get", &globals::getGlobal<string>);
		def("get", &globals::getGlobal<bool>);
		def("get", &globals::getGlobal<int>);
		def("setRandomSeed", &gslNoise::setSeed);

		class_<createNetwork>("createNetwork");
		class_<dynNetwork>("dynNetwork");

		class_<MyNetwork<baseType>, bases <createNetwork, dynNetwork> >("network")
			//	 class_<MyNetwork<baseType> >("directedNetwork")
			.def("__init__", make_constructor(networkFactory))
			.def("__del__", &MyNetwork<baseType>::clear, reinterpret_cast<const char *>(__network_clear))
			.def("lattice", &MyNetwork<baseType>::lattice, lattice_overloads(reinterpret_cast<const char *>(__createNetwork_lattice)))

			// dynNetwork commands
			//
			.def("evolve", &MyNetwork<baseType>::evolve, reinterpret_cast<const char *>(__dynNetwork_evolve))
			.def("snapshot", &MyNetwork<baseType>::snapshot, reinterpret_cast<const char *>(__dynNetwork_snapshot))
			.def("observe", &MyNetwork<baseType>::observe, observe_overloads (reinterpret_cast<const char *>(__dynNetwork_observe)))
			.def("observeAll", &MyNetwork<baseType>::observeAll, observeAll_overloads (reinterpret_cast<const char *>(__dynNetwork_observeAll)))
			.def("observeTime", &MyNetwork<baseType>::observeTime, reinterpret_cast<const char *>(__dynNetwork_observeTime))
			.def("observePhaseCoherence", &MyNetwork<baseType>::observePhaseCoherence, observePhaseCoherence_overloads( reinterpret_cast<const char *>(__dynNetwork_observePhaseCoherence)))
			.def("observeSum", &MyNetwork<baseType>::observeSum, observeSum_overloads( reinterpret_cast<const char *>(__dynNetwork_observeSum)))
			.def("printNodeStatistics", &MyNetwork<baseType>::printNodeStatistics, reinterpret_cast<const char *>(__statisticsNetwork_printNodeStatistics))
			.def("removeObserver", &MyNetwork<baseType>::removeObserver, reinterpret_cast<const char *>(__dynNetwork_removeObserver))

			////network commands
			.def("addNode", &MyNetwork<baseType>::addNode, reinterpret_cast<const char *>(__network_addNode))
			.def("addEdge", &MyNetwork<baseType>::addEdge, reinterpret_cast<const char *>(__network_addEdge))
			.def("clear", &MyNetwork<baseType>::clear, reinterpret_cast<const char *>(__network_clear))
			//		.def("addWeightedEdge", &MyNetwork<baseType>::addWeightedEdge, reinterpret_cast<const char *>(__network_addWeightedEdge))
			//
			////statisticsNetworkCommands
			//
			.def("betweennessCentrality", &MyNetwork<baseType>::betweennessCentrality, reinterpret_cast<const char *>(__statisticsNetwork_betweennessCentrality))
			.def("closenessCentrality", &MyNetwork<baseType>::closenessCentrality, reinterpret_cast<const char *>(__statisticsNetwork_closenessCentrality))
			.def("degreeCentrality", &MyNetwork<baseType>::degreeCentrality, reinterpret_cast<const char *>(__statisticsNetwork_degreeCentrality))
			.def("degree", &MyNetwork<baseType>::degree, reinterpret_cast<const char *>(__statisticsNetwork_degree))
			.def("size", &MyNetwork<baseType>::size, reinterpret_cast<const char *>(__statisticsNetwork_size))
			.def("meanDegree", &MyNetwork<baseType>::meanDegree, reinterpret_cast<const char *>(__statisticsNetwork_meanDegree))
			.def("meanWeight", &MyNetwork<baseType>::meanWeight, reinterpret_cast<const char *>(__statisticsNetwork_meanWeight))
			.def("meanClustering", &MyNetwork<baseType>::meanClustering, reinterpret_cast<const char *>(__statisticsNetwork_meanClustering))
			.def("readInitialCondition", &MyNetwork<baseType>::readInitialCondition, reinterpret_cast<const char *>(__createNetwork_readInitialCondition))
			.def("meanPathLength", &MyNetwork<baseType>::meanPathLength, reinterpret_cast<const char *>(__statisticsNetwork_meanPathLength))
			.def("isConnected", &MyNetwork<baseType>::isConnected, reinterpret_cast<const char *>(__statisticsNetwork_isConnected))
			.def("isLinked", &MyNetwork<baseType>::isLinked, reinterpret_cast<const char *>(__statisticsNetwork_isLinked))
			.def("isDirected", &MyNetwork<baseType>::isDirected, reinterpret_cast<const char *>(__statisticsNetwork_isDirected))
			.def("getState", &MyNetwork<baseType>::getState, getState_overloads(reinterpret_cast<const char *>(__statisticsNetwork_getState)))
			.def("getParam", &MyNetwork<baseType>::getParam, reinterpret_cast<const char *>(__statisticsNetwork_getParam))
			.def("setParam", &MyNetwork<baseType>::setParam, reinterpret_cast<const char *>(__dynNetwork_setParam))

			.def("removeEdge", &MyNetwork<baseType>::unlink, reinterpret_cast<const char *>(__createNetwork_removeEdge))
			// createNetwork commands
			.def("removeEdges", &MyNetwork<baseType>::removeEdges, reinterpret_cast<const char *>(__createNetwork_addRandomEdges))
			.def("removeRandomEdges", &MyNetwork<baseType>::removeRandomEdges, reinterpret_cast<const char *>(__createNetwork_removeRandomEdges))
			.def("addRandomEdges", &MyNetwork<baseType>::addRandomEdges, addRandomEdges_overloads (reinterpret_cast<const char *>(__createNetwork_addRandomEdges)))

			.def("torusNearestNeighbors", &MyNetwork<baseType>::torusNearestNeighbors,  reinterpret_cast<const char *>(__createNetwork_torusNearestNeighbors))
			//		.def("loadGraphML", &MyNetwork<baseType>::loadGraphML, reinterpret_cast<const char *>(__createNetwork_loadGraphXml))
			.def("saveGraphML", &MyNetwork<baseType>::saveGraphML, reinterpret_cast<const char *>(__createNetwork_saveGraphML))
			.def("saveAdjacencyList", &MyNetwork<baseType>::saveAdjacencyList, reinterpret_cast<const char *>(__createNetwork_saveAdjacencyList))
			.def("createFromAdjacencyList", &MyNetwork<baseType>::createFromAdjacencyList, createFromAdjacencyList_overloads( reinterpret_cast<const char *>(__createNetwork_createFromAdjacencyList)))
			.def("createFromAdjacencyMatrix", &MyNetwork<baseType>::createFromAdjacencyMatrix ,  createFromAdjacencyMatrix_overloads( reinterpret_cast< const char *> (__createNetwork_createFromAdjacencyMatrix)))
			.def("saveAdjacencyMatrix", &MyNetwork<baseType>::saveAdjacencyMatrix, reinterpret_cast<const char *>(__createNetwork_saveAdjacencyMatrix))
			.def("randomNetwork", &MyNetwork<baseType>::randomNetwork ,  randomNetwork_overloads( reinterpret_cast< const char *> (__createNetwork_randomNetwork)))
			.def("completeNetwork", &MyNetwork<baseType>::completeNetwork, completeNetwork_overloads( reinterpret_cast<const char *>(__createNetwork_completeNetwork)))
			.def("line", &MyNetwork<baseType>::line, reinterpret_cast<const char *>(__createNetwork_line))
			.def("cycle", &MyNetwork<baseType>::cycle, cycle_overloads( reinterpret_cast<const char *>(__createNetwork_cycle)))


			.def("torus", &MyNetwork<baseType>::torus, reinterpret_cast<const char *>(__createNetwork_torus))
			.def("setState", &MyNetwork<baseType>::setInitialCondition, setState_overloads (reinterpret_cast<const char *>(__createNetwork_setState)))
			.def("rewire", &MyNetwork<baseType>::rewire ,  rewire_overloads( reinterpret_cast< const char *> (__createNetwork_rewire)))
			.def("rewireUndirected", &MyNetwork<baseType>::rewireUndirected ,  rewireUndirected_overloads( reinterpret_cast< const char *> (__createNetwork_rewireUndirected)))
			.def("randomizeWeights", &MyNetwork<baseType>::randomizeWeights, reinterpret_cast<const char *>(__createNetwork_randomizeWeights))
			.def("randomizeStates", &MyNetwork<baseType>::randomizeStates ,  randomizeStates_overloads( reinterpret_cast< const char *> (__createNetwork_randomizeStates)))
			.def("randomizeParameter", &MyNetwork<baseType>::randomizeParameter, reinterpret_cast<const char *>(__createNetwork_randomizeParameter));








		// random objects

		//	 class ("random", boost::function<double ()>);
		//

		class_<boost::function<double ()> > ("random");

		def ("uniform", &gslNoise::functionUniform);
		def ("constant", &gslNoise::functionConstant);
		def ("gaussian", &gslNoise::functionGaussian);
		def ("bimodal", &gslNoise::functionBimodal);
		def ("powerLaw", &gslNoise::functionPowerLaw);



		class_<nodeBlueprint> ("nodeBlueprint")
			.def("setState", &dynNode::setState, setStateTemplate_overloads ( reinterpret_cast <const char *> (__dynNetwork_setState)))  ;






		// addNewNode.py Nodes begin
#include "generatedNeuroPython.cpp"
		// addNewNode.py Nodes end


		//	class_< edgeVirtual, bases <edgeBlueprint> > ("unweightedEdge");

		class_< nodeVirtualEdges < dynNode >, bases <nodeBlueprint> > ("node");



		class_<edgeBlueprint> ("edge");
		//	class_<edgeBlueprint> ("edge");

		//	class_< edgeVirtual, bases <edgeBlueprint > > ("edge");

		class_< weightedEdge < edgeVirtual >, bases <edgeBlueprint> > ("weightedEdge",   reinterpret_cast<const char *>(__edges_weightedEdge)       ). def (init<baseType>());

		class_< staticWeightedEdge < edgeVirtual >  , bases <edgeBlueprint> > ("staticWeightedEdge", reinterpret_cast<const char *>(__edges_staticWeightedEdge)   ).
			def (init <baseType> ());



		class_< component < edgeVirtual > , bases <edgeBlueprint> >("component", reinterpret_cast<const char *>(__edges_component))
					.def ("__init__", make_constructor (edgeFactory1 <component< edgeVirtual > > ));
		class_< component < weightedEdgeVirtual>, bases <edgeBlueprint>   > ("component_weightedEdge" ,reinterpret_cast<const char *>(__edges_weightedEdge))
					.def ("__init__", make_constructor (edgeFactory2 <component< weightedEdgeVirtual > > ));

		class_< component < staticWeightedEdgeVirtual>, bases <edgeBlueprint>  >("component_staticWeightedEdge" ,reinterpret_cast<const char *>(__edges_component_staticWeightedEdge))
					.def ("__init__", make_constructor (edgeFactory2 <component< staticWeightedEdgeVirtual > > ));



		class_< staticComponent < edgeVirtual > , bases <edgeBlueprint> >("staticComponent", reinterpret_cast<const char *>(__edges_component))
					.def ("__init__", make_constructor (edgeFactory1 <staticComponent < edgeVirtual > > ));

		class_< staticComponent < weightedEdgeVirtual>, bases <edgeBlueprint>   > ("staticComponent_weightedEdge" ,reinterpret_cast<const char *>(__edges_weightedEdge))
					.def ("__init__", make_constructor (edgeFactory2 <staticComponent < weightedEdgeVirtual> > ));
		class_< staticComponent < staticWeightedEdgeVirtual>, bases <edgeBlueprint>  >("staticComponent_staticWeightedEdge" ,reinterpret_cast<const char *>(__edges_component_staticWeightedEdge))
					.def ("__init__", make_constructor (edgeFactory2 <staticComponent < staticWeightedEdgeVirtual> > ));


		class_< randomTarget < edgeVirtual>, bases <edgeBlueprint>  > ("randomTarget",  reinterpret_cast<const char *>(__edges_randomTarget))
					.def ("__init__", make_constructor (edgeFactory2 < randomTarget < edgeVirtual>   > ));
		class_< randomTarget < weightedEdgeVirtual>, bases <edgeBlueprint>  > ("randomTarget_weightedEdge",  reinterpret_cast<const char *>(__edges_weightedEdge))
					.def ("__init__", make_constructor (edgeFactory3 < randomTarget < weightedEdgeVirtual>   > ));
		class_< randomTarget < staticWeightedEdgeVirtual>, bases <edgeBlueprint>  >("randomTarget_staticWeightedEdge", reinterpret_cast<const char *>(__edges_randomTarget_staticWeightedEdge))
					.def ("__init__", make_constructor (edgeFactory3 < randomTarget < staticWeightedEdgeVirtual>   > ));

		class_< stepEdge < edgeVirtual>, bases <edgeBlueprint>  > ("step" ,reinterpret_cast<const char *>(__edges_stepEdge))
					.def ("__init__", make_constructor (edgeFactory1 < stepEdge <edgeVirtual > > ));
		class_< stepEdge < weightedEdgeVirtual>, bases <edgeBlueprint>  > ("step_weightedEdge", reinterpret_cast<const char *>(__edges_weightedEdge))
					.def ("__init__", make_constructor (edgeFactory2 < stepEdge <weightedEdgeVirtual > > ));
		class_< stepEdge < staticWeightedEdgeVirtual>, bases <edgeBlueprint>  >("step_staticWeightedEdge", reinterpret_cast<const char *>(__edges_step_staticWeightedEdge))
					.def ("__init__", make_constructor (edgeFactory2 < stepEdge <staticWeightedEdgeVirtual > > ));





		//	class_< delayEdge

		//	class_< phaseOfPCPOVirtual, bases <edgeBlueprint> > ("phaseOfPCO");



		//    python::def("square", square);
	}
}
