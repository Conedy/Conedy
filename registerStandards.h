

#ifndef registerStandards_h
#define registerStandards registerStandards_h


#include "fullNetwork.h"
#include "command.h"
using namespace conedy;


void registerStandards()
{
	
	//	dynNode::registerStandardValues();
	//	gslOdeNode::registerStandardValues();
	//	odeNode::registerStandardValues();
	//	pcoDelay::registerStandardValues();
	//	sdeNode::registerStandardValues();
		stdOdeIntegrator::registerStandardValues();	
		stdSdeIntegrator::registerStandardValues();	
	
	pcoBase::registerStandardValues();
	cnnNode::registerStandardValues();
	containerNode<baseType, 0>::registerStandardValues();
	dynNetwork::registerStandardValues();
	createNetwork::registerStandardValues();
	escapeNoiseNeuron::registerStandardValues();
	gaussianFHN::registerStandardValues();
//	gaussianHH::registerStandardValues();
//	gaussianHR::registerStandardValues();
	gaussianNapK::registerStandardValues();
	gaussianNapKKm::registerStandardValues();
	gslOdeNode::registerStandardValues();
//	hindmarshRose::registerStandardValues();
//	hodgkinHuxley::registerStandardValues();
	integrateAndFire::registerStandardValues();
	izhikevichMap::registerStandardValues();
//	logisticMap::registerStandardValues();
//	membranePotentialOfIFQ::registerStandardValues();
	napK::registerStandardValues();
	napKKm::registerStandardValues();
	network::registerStandardValues();
//	neuronMap::registerStandardValues();
//	ornUhl::registerStandardValues();
	pcoDelay::registerStandardValues();
//	pcoIFNeuronDelay::registerStandardValues();	
	pcoTrapez::registerStandardValues();
//	pcoTriangel::registerStandardValues();
	periodicNode::registerStandardValues();
	pulseCoupledExcitatoryNeuron::registerStandardValues();
	randomWalkNeuron::registerStandardValues();
	sigEdgeParams::registerStandardValues();
	stdKuramoto::registerStandardValues();
	stdLorenz::registerStandardValues();
	stdRoessler::registerStandardValues();
	streamInNode::registerStandardValues();
	streamOutNode::registerStandardValues();
	sdeNode::registerStandardValues();
#if OPENGL
	GLNetwork<baseType>::registerStandardValues();
#endif
	#include "generatedRegisterStandards.h"

}


#endif
