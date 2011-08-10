


// Copyright Ralf W. Grosse-Kunstleve 2002-2004. Distributed under the Boost
// Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

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



#include "docstrings.h"


//typedef double baseType;
//network<baseType> *netCheat = 0;




namespace { // Avoid cluttering the global namespace.
	using namespace conedy;

	void initializeNeurosim ()
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


		//	cout << "Neurosim erfolgreich initialisiert!" << endl;

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
	BOOST_PYTHON_MEMBER_FUNCTION_OVERLOADS (observeMean_overloads, observeMean, 1,2);
	BOOST_PYTHON_MEMBER_FUNCTION_OVERLOADS (setState_overloads, setInitialCondition, 2,13);

	BOOST_PYTHON_MEMBER_FUNCTION_OVERLOADS (addRandomEdges_overloads, addRandomEdges, 1,2);

	void translator (const char *c)
	{ PyErr_SetString (PyExc_UserWarning, c); }




	BOOST_PYTHON_MODULE(conedy)
	{

		register_exception_translator<const char *>(translator);



		if (!system ("recompilePython-Conedy  2> /dev/null"))
		{
			cout << "Mission accomplished. You can restart your script now." << endl;
			exit (1);
		}	





		initializeNeurosim();


		//	docstring_options doc_options(1,1,0);


		//	scope current;
		//	current.attr("aa") = &i;

		object o = object (i);

		//	scope().attr("aa") = &i;

		scope().attr("__doc__") = 
			"What is Neurosim"
			"================"
			"Neurosim is a tool which allows you to integrate networks where each node is represented by some dynamical system. It is designed to allow for an change of the network structure or differential equation sperarately. ";



		boost::python::class_<std::vector<double> >("PyVec")
			.def(boost::python::vector_indexing_suite<std::vector<double> >());


		//	BOOST_PYTHON_MEMBER_FUNCTION_OVERLOADS (
		// Add regular functions to the module.


		def("set", &params<baseType>::setStandard);
		def("setString", &params<string>::setStandard);
		def("setRandomSeed", &gslNoise::setSeed);

		class_<createNetwork>("createNetwork");
		class_<dynNetwork>("dynNetwork");

		class_<MyNetwork<baseType>, bases <createNetwork, dynNetwork> >("network")
			//	 class_<MyNetwork<baseType> >("directedNetwork")
			.def("__init__", make_constructor(networkFactory))
			.def("lattice", &MyNetwork<baseType>::lattice, lattice_overloads(reinterpret_cast<const char *>(__createNetwork_lattice)))

			// dynNetwork commands
			//
			.def("evolve", &MyNetwork<baseType>::evolve, reinterpret_cast<const char *>(__dynNetwork_evolve))
			.def("snapshot", &MyNetwork<baseType>::snapshot, reinterpret_cast<const char *>(__dynNetwork_snapshot))
			.def("observe", &MyNetwork<baseType>::observe, observe_overloads (reinterpret_cast<const char *>(__dynNetwork_observe)))
			.def("observeAll", &MyNetwork<baseType>::observeAll, observeAll_overloads (reinterpret_cast<const char *>(__dynNetwork_observeAll)))
			.def("observeTime", &MyNetwork<baseType>::observeTime, reinterpret_cast<const char *>(__dynNetwork_observeTime))
			.def("observePhaseCoherence", &MyNetwork<baseType>::observePhaseCoherence, observePhaseCoherence_overloads( reinterpret_cast<const char *>(__dynNetwork_observePhaseCoherence)))
			.def("observeMean", &MyNetwork<baseType>::observeMean, observeMean_overloads( reinterpret_cast<const char *>(__dynNetwork_observeMean)))
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
			.def("size", &MyNetwork<baseType>::size, reinterpret_cast<const char *>(__statisticsNetwork_size))
			.def("meanDegree", &MyNetwork<baseType>::meanDegree, reinterpret_cast<const char *>(__statisticsNetwork_meanDegree))
			.def("meanWeight", &MyNetwork<baseType>::meanWeight, reinterpret_cast<const char *>(__statisticsNetwork_meanWeight))
			.def("meanClustering", &MyNetwork<baseType>::meanClustering, reinterpret_cast<const char *>(__statisticsNetwork_meanClustering))
			.def("meanPathLength", &MyNetwork<baseType>::meanPathLength, reinterpret_cast<const char *>(__statisticsNetwork_meanPathLength))
			.def("isConnected", &MyNetwork<baseType>::isConnected, reinterpret_cast<const char *>(__statisticsNetwork_isConnected))
			.def("isLinked", &MyNetwork<baseType>::isLinked, reinterpret_cast<const char *>(__statisticsNetwork_isLinked))
			.def("isDirected", &MyNetwork<baseType>::isDirected, reinterpret_cast<const char *>(__statisticsNetwork_isDirected))
			.def("getParam", &MyNetwork<baseType>::getParam, reinterpret_cast<const char *>(__statisticsNetwork_getParam))
			.def("setParam", &MyNetwork<baseType>::setParam, reinterpret_cast<const char *>(__dynNetwork_setParam))

			// createNetwork commands
			.def("addRandomEdges", &MyNetwork<baseType>::addRandomEdges, addRandomEdges_overloads (reinterpret_cast<const char *>(__createNetwork_addRandomEdges)))

			.def("torusNearestNeighbors", &MyNetwork<baseType>::torusRandomlyNearestNeighbours,  reinterpret_cast<const char *>(__createNetwork_torusNearestNeighbors))
			//		.def("loadGraphML", &MyNetwork<baseType>::loadGraphML, reinterpret_cast<const char *>(__createNetwork_loadGraphXml))
			.def("saveGraphML", &MyNetwork<baseType>::saveGraphML, reinterpret_cast<const char *>(__statisticsNetwork_saveGraphML))
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



		class_<nodeBlueprint> ("nodeBlueprint");




#define component_staticWeightedEdge     component < staticWeightedEdge >


		// addNewNode.py Nodes begin
class_< nodeTemplateEdges< staticWeightedEdge< edge >  , pcoIFNeuron , pcoIFNeuron >, bases<nodeBlueprint> > ("pcoIFNeuron",  reinterpret_cast<const char *>(__addedNodes_pcoBase_pcoIFNeuron) ); // added by addNewNodes.py 
class_< nodeTemplateEdges< staticWeightedEdge< edge >  , pcoIFNeuronDelay , pcoIFNeuronDelay >, bases<nodeBlueprint> > ("pcoIFNeuronDelay",  reinterpret_cast<const char *>(__addedNodes_pcoDelay_pcoIFNeuronDelay) ); // added by addNewNodes.py 
class_< nodeTemplateEdges< staticWeightedEdge< edge >  , pcoMirolloDelayStatic , pcoMirolloDelayStatic >, bases<nodeBlueprint> > ("pcoMirolloDelayStatic",  reinterpret_cast<const char *>(__addedNodes_pcoDelay_pcoMirolloDelayStatic) ); // added by addNewNodes.py 
class_< nodeTemplateEdges< staticWeightedEdge< edge >  , pcoMirolloDelayStatic , pcoMirolloRoot >, bases<nodeBlueprint> > ("pcoMirolloRoot",  reinterpret_cast<const char *>(__addedNodes_pcoDelay_pcoMirolloRoot) ); // added by addNewNodes.py 
class_< nodeTemplateEdges< staticWeightedEdge< edge >  , pcoNonleakyStatic , pcoNonleakyStatic >, bases<nodeBlueprint> > ("pcoNonleakyStatic",  reinterpret_cast<const char *>(__addedNodes_pcoBase_pcoNonleakyStatic) ); // added by addNewNodes.py 
class_< nodeTemplateEdges< staticWeightedEdge<component< edge> >  , roesslerStatic , roesslerStatic >, bases<nodeBlueprint> > ("roesslerStatic",  reinterpret_cast<const char *>(__addedNodes_stdOdeIntegrator_roesslerStatic) ); // added by addNewNodes.py 
class_< nodeTemplateEdges< weightedEdge< edge >  , exponentialStatic , exponentialStatic >, bases<nodeBlueprint> > ("exponentialStatic",  reinterpret_cast<const char *>(__addedNodes_stdOdeIntegrator_exponentialStatic) ); // added by addNewNodes.py 
class_< nodeVirtualEdges<exponentialGsl> , bases<nodeBlueprint> > ("exponentialGsl",  reinterpret_cast<const char *>(__addedNodes_gslOdeIntegrator_exponentialGsl) ); // added by addNewNodes.py 
class_< nodeVirtualEdges<exponentialOde> , bases<nodeBlueprint> > ("exponentialOde",  reinterpret_cast<const char *>(__addedNodes_stdOdeIntegrator_exponentialOde) ); // added by addNewNodes.py 
class_< nodeVirtualEdges<exponentialSde> , bases<nodeBlueprint> > ("exponentialSde",  reinterpret_cast<const char *>(__addedNodes_stdSdeIntegrator_exponentialSde) ); // added by addNewNodes.py 
class_< nodeVirtualEdges<fitzHughNagumo> , bases<nodeBlueprint> > ("fitzHughNagumo",  reinterpret_cast<const char *>(__addedNodes_stdOdeIntegrator_fitzHughNagumo) ); // added by addNewNodes.py 
class_< nodeVirtualEdges<gaussianFitzHughNagumo> , bases<nodeBlueprint> > ("gaussianFitzHughNagumo",  reinterpret_cast<const char *>(__addedNodes_stdSdeIntegrator_gaussianFitzHughNagumo) ); // added by addNewNodes.py 
class_< nodeVirtualEdges<gaussianHindmarshRose> , bases<nodeBlueprint> > ("gaussianHindmarshRose",  reinterpret_cast<const char *>(__addedNodes_stdSdeIntegrator_gaussianHindmarshRose) ); // added by addNewNodes.py 
class_< nodeVirtualEdges<gaussianHodgkinHuxley> , bases<nodeBlueprint> > ("gaussianHodgkinHuxley",  reinterpret_cast<const char *>(__addedNodes_stdSdeIntegrator_gaussianHodgkinHuxley) ); // added by addNewNodes.py 
class_< nodeVirtualEdges<gaussianKuramoto> , bases<nodeBlueprint> > ("gaussianKuramoto",  reinterpret_cast<const char *>(__addedNodes_stdSdeIntegrator_gaussianKuramoto) ); // added by addNewNodes.py 
class_< nodeVirtualEdges<gaussianLorenz> , bases<nodeBlueprint> > ("gaussianLorenz",  reinterpret_cast<const char *>(__addedNodes_stdSdeIntegrator_gaussianLorenz) ); // added by addNewNodes.py 
class_< nodeVirtualEdges<gaussianRoessler> , bases<nodeBlueprint> > ("gaussianRoessler",  reinterpret_cast<const char *>(__addedNodes_stdSdeIntegrator_gaussianRoessler) ); // added by addNewNodes.py 
class_< nodeVirtualEdges<hindmarshRose> , bases<nodeBlueprint> > ("hindmarshRose",  reinterpret_cast<const char *>(__addedNodes_stdOdeIntegrator_hindmarshRose) ); // added by addNewNodes.py 
class_< nodeVirtualEdges<hodgkinHuxley> , bases<nodeBlueprint> > ("hodgkinHuxley",  reinterpret_cast<const char *>(__addedNodes_stdOdeIntegrator_hodgkinHuxley) ); // added by addNewNodes.py 
class_< nodeVirtualEdges<kuramoto> , bases<nodeBlueprint> > ("kuramoto",  reinterpret_cast<const char *>(__addedNodes_stdOdeIntegrator_kuramoto) ); // added by addNewNodes.py 
class_< nodeVirtualEdges<logisticMap> , bases<nodeBlueprint> > ("logisticMap",  reinterpret_cast<const char *>(__addedNodes_mapNode_logisticMap) ); // added by addNewNodes.py 
class_< nodeVirtualEdges<lorenz> , bases<nodeBlueprint> > ("lorenz",  reinterpret_cast<const char *>(__addedNodes_stdOdeIntegrator_lorenz) ); // added by addNewNodes.py 
class_< nodeVirtualEdges<neuronMap> , bases<nodeBlueprint> > ("neuronMap",  reinterpret_cast<const char *>(__addedNodes_mapNode_neuronMap) ); // added by addNewNodes.py 
class_< nodeVirtualEdges<ornUhl> , bases<nodeBlueprint> > ("ornUhl",  reinterpret_cast<const char *>(__addedNodes_stdSdeIntegrator_ornUhl) ); // added by addNewNodes.py 
class_< nodeVirtualEdges<pcoIntegrateFire> , bases<nodeBlueprint> > ("pcoIntegrateFire",  reinterpret_cast<const char *>(__addedNodes_pcoBase_pcoIntegrateFire) ); // added by addNewNodes.py 
class_< nodeVirtualEdges<pcoIntegrateFireDelay> , bases<nodeBlueprint> > ("pcoIntegrateFireDelay",  reinterpret_cast<const char *>(__addedNodes_pcoDelay_pcoIntegrateFireDelay) ); // added by addNewNodes.py 
class_< nodeVirtualEdges<pcoMirollo> , bases<nodeBlueprint> > ("pcoMirollo",  reinterpret_cast<const char *>(__addedNodes_pcoBase_pcoMirollo) ); // added by addNewNodes.py 
class_< nodeVirtualEdges<pcoMirolloDelay> , bases<nodeBlueprint> > ("pcoMirolloDelay",  reinterpret_cast<const char *>(__addedNodes_pcoDelay_pcoMirolloDelay) ); // added by addNewNodes.py 
class_< nodeVirtualEdges<pcoNonleaky> , bases<nodeBlueprint> > ("pcoNonleaky",  reinterpret_cast<const char *>(__addedNodes_pcoBase_pcoNonleaky) ); // added by addNewNodes.py 
class_< nodeVirtualEdges<pcoNonleakyDelay> , bases<nodeBlueprint> > ("pcoNonleakyDelay",  reinterpret_cast<const char *>(__addedNodes_pcoDelay_pcoNonleakyDelay) ); // added by addNewNodes.py 
class_< nodeVirtualEdges<pcoTriangel> , bases<nodeBlueprint> > ("pcoTriangel",  reinterpret_cast<const char *>(__addedNodes_pcoBase_pcoTriangel) ); // added by addNewNodes.py 
class_< nodeVirtualEdges<pdeMirolloBackward> , bases<nodeBlueprint> > ("pdeMirolloBackward",  reinterpret_cast<const char *>(__addedNodes_gslOdeIntegrator_pdeMirolloBackward) ); // added by addNewNodes.py 
class_< nodeVirtualEdges<pdeMirolloCentered> , bases<nodeBlueprint> > ("pdeMirolloCentered",  reinterpret_cast<const char *>(__addedNodes_gslOdeIntegrator_pdeMirolloCentered) ); // added by addNewNodes.py 
class_< nodeVirtualEdges<pdeMirolloForward> , bases<nodeBlueprint> > ("pdeMirolloForward",  reinterpret_cast<const char *>(__addedNodes_gslOdeIntegrator_pdeMirolloForward) ); // added by addNewNodes.py 
class_< nodeVirtualEdges<percFitzHughNagumo> , bases<nodeBlueprint> > ("percFitzHughNagumo",  reinterpret_cast<const char *>(__addedNodes_stdSdeIntegrator_percFitzHughNagumo) ); // added by addNewNodes.py 
class_< nodeVirtualEdges<roessler> , bases<nodeBlueprint> > ("roessler",  reinterpret_cast<const char *>(__addedNodes_gslOdeIntegrator_roessler) ); // added by addNewNodes.py 
class_< nodeVirtualEdges<vanDerPol> , bases<nodeBlueprint> > ("vanDerPol",  reinterpret_cast<const char *>(__addedNodes_stdOdeIntegrator_vanDerPol) ); // added by addNewNodes.py 
		// addNewNode.py Nodes end


		//	class_< edgeVirtual, bases <edgeBlueprint> > ("unweightedEdge");

		class_< nodeVirtualEdges < dynNode >, bases <nodeBlueprint> > ("node");

		class_< nodeVirtualEdges<stdRoessler> , bases<nodeBlueprint> > ("stdRoessler");
		class_< nodeVirtualEdges<stdLorenz> , bases<nodeBlueprint> > ("stdLorenz");


		class_<edgeBlueprint> ("edge");
		//	class_<edgeBlueprint> ("edge");

		//	class_< edgeVirtual, bases <edgeBlueprint > > ("edge");

		class_< weightedEdge < edgeVirtual >, bases <edgeBlueprint> > ("weightedEdge",   reinterpret_cast<const char *>(__edges_weightedEdge)       ). def (init<baseType>());

		class_< staticWeightedEdge < edgeVirtual >  , bases <edgeBlueprint> > ("staticWeightedEdge", reinterpret_cast<const char *>(__edges_staticWeightedEdge)   );


		class_< component < edgeVirtual > , bases <edgeBlueprint> >("component", reinterpret_cast<const char *>(__edges_component) , init <int>() );
		class_< component < weightedEdgeVirtual>, bases <edgeBlueprint>   > ("component_weightedEdge" ,reinterpret_cast<const char *>(__edges_weightedEdge) , init <int>());
		class_< component < staticWeightedEdgeVirtual>, bases <edgeBlueprint>  >("component_staticWeightedEdge" ,reinterpret_cast<const char *>(__edges_component_staticWeightedEdge) , init <int>());

		class_< randomTarget < edgeVirtual>, bases <edgeBlueprint>  > ("randomTarget",  reinterpret_cast<const char *>(__edges_randomTarget) ,   init <double,double>() ) ;
		class_< randomTarget < weightedEdgeVirtual>, bases <edgeBlueprint>  > ("randomTarget_weightedEdge",  reinterpret_cast<const char *>(__edges_weightedEdge), init <double,double>() );
		class_< randomTarget < staticWeightedEdgeVirtual>, bases <edgeBlueprint>  >("randomTarget_staticWeightedEdge", reinterpret_cast<const char *>(__edges_randomTarget_staticWeightedEdge) , init <double,double>());

		class_< pulseCouple < edgeVirtual>, bases <edgeBlueprint>  > ("pulseCouple" ,reinterpret_cast<const char *>(__edges_pulseCouple) , init <double>());
		class_< pulseCouple < weightedEdgeVirtual>, bases <edgeBlueprint>  > ("pulseCouple_weightedEdge", reinterpret_cast<const char *>(__edges_weightedEdge) , init <double>());
		class_< pulseCouple < staticWeightedEdgeVirtual>, bases <edgeBlueprint>  >("pulseCouple_staticWeightedEdge", reinterpret_cast<const char *>(__edges_pulseCouple_staticWeightedEdge) , init <double>());





		//	class_< delayEdge

		//	class_< phaseOfPCPOVirtual, bases <edgeBlueprint> > ("phaseOfPCO");



		//    python::def("square", square);
	}
}
