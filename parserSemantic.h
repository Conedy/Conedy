

#ifndef __parserSemantic
#define __parserSemantic

#include "instruction.h"
#include "fullNetworkWithNodes.h"
//#include "networkGenerators.h"
//#include "networkCharacteristics.h"


class randomBlueprintNode :  public nodeVirtualEdges <dynNode >
{
	private:
		//		node **blueprint1;
		//		node **blueprint2;
		expression<nodeBlueprint*> *blueprint1;
		expression<nodeBlueprint*> *blueprint2;

		double probability;
	public:
		virtual bool timeEvolution () {return 0;};
		randomBlueprintNode(expression<nodeBlueprint*> *b1, expression<nodeBlueprint*> *b2, double p) : blueprint1(b1), blueprint2(b2), probability(p) {}
		virtual const nodeInfo getNodeInfo() { nodeInfo n = {_randomBlueprintNode_,_dynNode_, "randomBlueprintNode" };     return n; };
		virtual const unsigned int dimension () const { return 0; }
		virtual node * construct()
		{
			if (gslNoise::getUniform(0.0,1.0) < probability)
				return (blueprint1->evaluate())->construct();
			else
				return (blueprint2->evaluate())->construct();

		}
};







#if CONDOR

#define INTNETWORKFUNK(funktionName, net)  new constantCommand <int> (0)
#define INTNETWORKFUNK1(funktionName, net, arg1)  new constantCommand <int> (0)
#define INTNETWORKFUNK2(funktionName, net, arg1, arg2)    new constantCommand <int> (0)
#define INTNETWORKFUNK3(funktionName, net, arg1, arg2, arg3)    new constantCommand <int> (0)
#define INTNETWORKFUNK4(funktionName, net, arg1, arg2, arg3, arg4)    new constantCommand <int> (0)
#define INTNETWORKFUNK5(funktionName, net, arg1, arg2, arg3, arg4, arg5)    new constantCommand <int> (0)

#define BASETYPENETWORKFUNK(funktionName, net)  new constantCommand <baseType> (0)
#define BASETYPENETWORKFUNK1(funktionName, net, arg1)  new constantCommand <baseType> (0)
#define BASETYPENETWORKFUNK2(funktionName, net, arg1, arg2)    new constantCommand <baseType> (0)

#define BOOLNETWORKFUNK(funktionName, net)  new constantCommand <bool> (0)
#define BOOLNETWORKFUNK1(funktionName, net, arg1)  new constantCommand <bool> (0)
#define BOOLNETWORKFUNK2(funktionName, net, arg1, arg2)    new constantCommand <bool> (0)

#define NETWORKFUNK(funktionName, net)  new bindInstruction(bind(&emptyFunction))

#define NETWORKFUNK1(funktionName, net, arg1) new bindInstruction(bind(&emptyFunction))

#define NETWORKFUNK2(funktionName, net, arg1, arg2) new bindInstruction(bind(&emptyFunction))


#define NETWORKFUNK3(funktionName, net, arg1, arg2,arg3) new bindInstruction(bind(&emptyFunction))

#define NETWORKFUNK4(funktionName, net, arg1, arg2,arg3,arg4) new bindInstruction(bind(&emptyFunction))

#define NETWORKFUNK5(funktionName, net, arg1, arg2,arg3,arg4,arg5) new bindInstruction(bind(&emptyFunction))

#define NETWORKFUNK6(funktionName, net, arg1, arg2,arg3,arg4,arg5, arg6) new bindInstruction(bind(&emptyFunction))

#else


#define BOOLNETWORKFUNK(funktionName, net)  new bindExpression <bool> (bind(&networkTemplate::funktionName, net))
#define BOOLNETWORKFUNK1(funktionName, net, arg1)  new bindExpression <bool> (bind(&networkTemplate::funktionName, net, (arg1)   ))
#define BOOLNETWORKFUNK2(funktionName, net, arg1, arg2)  new bindExpression <bool> (bind(&networkTemplate::funktionName, net, (arg1), (arg2)   ))


#define BASETYPENETWORKFUNK(funktionName, net)  new bindExpression <baseType> (bind(&networkTemplate::funktionName, net))
#define BASETYPENETWORKFUNK1(funktionName, net, arg1)  new bindExpression <baseType> (bind(&networkTemplate::funktionName, net, (arg1)   ))
#define BASETYPENETWORKFUNK2(funktionName, net, arg1, arg2)  new bindExpression <baseType> (bind(&networkTemplate::funktionName, net, (arg1), (arg2)   ))

#define INTNETWORKFUNK(funktionName, net)  new bindExpression <int> (bind(&networkTemplate::funktionName, net))
#define INTNETWORKFUNK1(funktionName, net, arg1)  new bindExpression <int> (bind(&networkTemplate::funktionName, net, (arg1)   ))
#define INTNETWORKFUNK2(funktionName, net, arg1, arg2)  new bindExpression <int> (bind(&networkTemplate::funktionName, net, (arg1), (arg2)   ))
#define INTNETWORKFUNK3(funktionName, net, arg1, arg2, arg3)  new bindExpression <int> (bind(&networkTemplate::funktionName, net, (arg1), (arg2), (arg3)   ))
#define INTNETWORKFUNK4(funktionName, net, arg1, arg2, arg3, arg4)  new bindExpression <int> (bind(&networkTemplate::funktionName, net, (arg1), (arg2), (arg3), (arg4)   ))
#define INTNETWORKFUNK5(funktionName, net, arg1, arg2, arg3, arg4, arg5)  new bindExpression <int> (bind(&networkTemplate::funktionName, net, (arg1), (arg2), (arg3), (arg4), (arg5)   ))


#define NETWORKFUNK(funktionName, net)  new bindInstruction(bind(&networkTemplate::funktionName, net ))

#define NETWORKFUNK1(funktionName, net, arg1) new bindInstruction(bind(&networkTemplate::funktionName, net, (arg1) ))

#define NETWORKFUNK2(funktionName, net, arg1, arg2) new bindInstruction(bind(&networkTemplate::funktionName, net, (arg1) , (arg2) ))


#define NETWORKFUNK3(funktionName, net, arg1, arg2,arg3) new bindInstruction(bind(&networkTemplate::funktionName, net, (arg1),(arg2),(arg3) ))

#define NETWORKFUNK4(funktionName, net, arg1, arg2,arg3,arg4) new bindInstruction(bind(&networkTemplate::funktionName, net, (arg1) , (arg2),(arg3),(arg4) ))

#define NETWORKFUNK5(funktionName, net, arg1, arg2,arg3,arg4,arg5) new bindInstruction(bind(&networkTemplate::funktionName, net, (arg1) , (arg2),(arg3),(arg4),(arg5) ))

#define NETWORKFUNK6(funktionName, net, arg1, arg2,arg3,arg4,arg5, arg6) new bindInstruction(bind(&networkTemplate::funktionName, net, (arg1) , (arg2),(arg3),(arg4),(arg5), (arg6) ))







#endif







#endif
