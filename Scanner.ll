/*
    Neurosim is a scientific tool which allows numerical integration of dynamical networks.

    Copyright (C) 2011 Alexander Rothkegel, Henning Dickten, Ferdinand Stolz, Justus Schwabedahl

    This file is part of conedy.

    Neurosim is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>
*/


%option noyywrap
%option yylineno

%{ 
#include "Parserbase.h" // Make sure the flexer can communicate with bison++ 
                      //using return values
%}

digit	[0-9]

ws	[ \t\n]+
ID       [A-Za-z][a-z0-9A-Z\_]*



%%
{ws}				{ /* no action */ }


{digit}+		{return (ParserBase::INT); }


		/* {digit}+"."{digit}*e     	 {return (ParserBase::DOUBLE); } */

[0-9]+"."[0-9]+([eE][-+]?[0-9]+)?  {return (ParserBase::DOUBLE); }








"#"[^\n]*\n	{}


"\""[^\"]*"\""	{return (ParserBase::STRING);}

:[^\:]*:	{return (ParserBase::SYSTEMCOMMAND);}


"&&"		{return(ParserBase::AND);}
"||"		{return(ParserBase::OR);}
"!"		{return(ParserBase::NOT);}
"<"		{return('<');}
">"		{return('>');}
"=="		{return(ParserBase::EQUAL);}

TRUE		{return(ParserBase::BOOLONE);}
FALSE		{return(ParserBase::BOOLZERO);}


"-"		{return('-');}
"+"		{return('+');}
"*"		{return('*');}
"/"		{return('/');}
"("		{return('(');}
")"		{return(')');}
"{"		{return('{');}
"}"		{return('}');}

print		{return(ParserBase::PRINT);}
loop		{return(ParserBase::LOOP);}
double	{return(ParserBase::DOUBLETOKEN);}
baseType	{return(ParserBase::DOUBLETOKEN);}
string		{return(ParserBase::STRINGTOKEN);}
while		{return(ParserBase::WHILE);}
for		{return(ParserBase::FOR);}
exit		{return(ParserBase::EXIT);}
vectorFor	{return(ParserBase::VECTORFOR);}
chainedFor 	{return(ParserBase::CHAINEDFOR); }
if		{return(ParserBase::IF);}
network	{return(ParserBase::NETWORKTOKEN); }
ode		{return(ParserBase::NODETOKEN); }
int	{return(ParserBase::INTTOKEN); }
readInitialCondition	{return(ParserBase::READINITIALCONDITION); }

%{		// Nodes 
%}
cnnNode			{return(ParserBase::CNNNODE); }
countEdges		{return(ParserBase::COUNTEDGES); }
couplingSumNode			{return(ParserBase::COUPLINGSUMNODE); }
gaussianNapK		{return(ParserBase::GAUSSIANNAPK);}
gaussianNapKKm	{return(ParserBase::GAUSSIANNAPKKM);}
integrateAndFire	{return(ParserBase::INTEGRATEANDFIRE); }
izhikevichMap		{return(ParserBase::IZHIKEVICHMAP);}
napK			{return(ParserBase::NAPK);}
napKKm		{return(ParserBase::NAPKKM);}
periodicNode		{return(ParserBase::PERIODICNODE); }
randomBlueprintNode {return(ParserBase::RANDOMBLUEPRINTNODE); }
randomWalkNeuron	{return(ParserBase::RANDOMWALKNEURON); }
setParams		{return(ParserBase::SETPARAMS); }
snapshot		{return(ParserBase::SNAPSHOT); }
static		{return(ParserBase::STATIC); }
stdKuramoto		{return(ParserBase::STDKURAMOTO); }
stdLorenz		{return(ParserBase::STDLORENZ); }
stdRoessler		{return(ParserBase::STDROESSLER); }
stdVanDerPol		{return(ParserBase::STDVANDERPOL); }
streamInLattice		{return(ParserBase::STREAMINLATTICE); }
%{	// addNewNode.py Nodes
%}



%{		// Netzwerk-Befehle
%}



getState				{return(ParserBase::GETSTATE); }


evolve				{return(ParserBase::EVOLVE); }
evolveAlong				{return(ParserBase::EVOLVEALONG); }
realignAtEvent 		{return(ParserBase::REALIGNATEVENT ); }
realignAtEventSignature {return(ParserBase::REALIGNATEVENTSIGNATURE);}
realignWhenDistant {return(ParserBase::REALIGNWHENDISTANT);}

comandLineDouble		{return(ParserBase::COMANDLINE); }
comandLineString		{return(ParserBase::COMANDLINESTRING); }
torusRandomlyNearestNeighbours	{return(ParserBase::TORUSRANDOMLYNEARESTNEIGHBOURS);}
connectCloseNodes		{return(ParserBase::CONNECTCLOSENODES);}

connectCloseNodesTorus		{return(ParserBase::CONNECTCLOSENODESTORUS);}

startingConditionSmallDisturbance	{return (ParserBase::STARTINGCONDITIONSMALLDISTURBANCE); }
randomTargetEdge				{return (ParserBase::RANDOMTARGETEDGE); }



noiseToStates		{ return (ParserBase::NOISETOSTATES); }

getParam		{ return (ParserBase::GETPARAM); }
snapshotAtEvent		{ return (ParserBase::SNAPSHOTATEVENT); }
size			{ return (ParserBase::SIZE); }
removeInput		{return(ParserBase::REMOVEINPUT); }
removeEdges		{return(ParserBase::REMOVEEDGES); }


clear		{return(ParserBase::CLEAR); }
addNode	{return(ParserBase::ADDVERTEX); }
printNodeStatistics	{return(ParserBase::PRINTNODESTATISTICS); }
addEdge		{return(ParserBase::ADDEDGE); }
randomNetwork		{return(ParserBase::RANDOMNETWORK); }
completeNetwork		{return(ParserBase::COMPLETENETWORK); }
observe		{return(ParserBase::OBSERVE); }
observeMean		{return(ParserBase::OBSERVEMEAN); }
observePhaseCoherence	{ return (ParserBase::OBSERVEPHASECOHERENCE); }
observePhaseCorrelation	{ return (ParserBase::OBSERVEPHASECORRELATION); }
observePhaseDistance 	{ return (ParserBase::OBSERVEPHASEDISTANCE); }


addRandomEdgesDegreeDistribution { return (ParserBase::ADDRANDOMEDGESDEGREEDISTRIBUTION); }


observeMeanPhase	{ return (ParserBase::OBSERVEMEANPHASE); }
observeTime		{return(ParserBase::OBSERVETIME); }
lattice		{return(ParserBase::LATTICE); }
torus			{return(ParserBase::TORUS); }
observeAll		{return(ParserBase::OBSERVEALL); }
observeComponents		{return(ParserBase::OBSERVECOMPONENTS); }


observeGl		{return(ParserBase::OBSERVEGL); }
observeGlut		{return(ParserBase::OBSERVEGLUT); }
observeEvent  {return(ParserBase::OBSERVEEVENT); }
observeEventTimes  {return(ParserBase::OBSERVEEVENTTIMES); }



useRandomPositioning    {return(ParserBase::USERANDOMPOSITIONING); }
useLatticePositioning   {return(ParserBase::USELATTICEPOSITIONING); }

rewireSource		{return(ParserBase::REWIRESOURCE); }
rewireTarget		{return(ParserBase::REWIRETARGET); }
rewire			{return(ParserBase::REWIRE); }
rewireSourcePerTimestep	{return(ParserBase::REWIRESOURCEPERTIMESTEP);}
addRandomEdges		{return(ParserBase::ADDRANDOMEDGES); }
cnnStd		{return(ParserBase::CNNSTD); }
cnnNeutral		{return(ParserBase::CNNNEUTRAL); }
readParams		{return(ParserBase::READPARAMS); }
setTime			{return(ParserBase::SETTIME); }
rewireUndirected	{return(ParserBase::REWIREUNDIRECTED); }
rewireTargetUndirected	{return(ParserBase::REWIRETARGETUNDIRECTED); }


"log"			{return(ParserBase::LOG); }
"exp"			{return(ParserBase::EXP); }



getRandomSeed		{return(ParserBase::GETRANDOMSEED); }
delayLink		{return(ParserBase::DELAYLINK); }
cycle			{return(ParserBase::CYCLE); }
line 			{return(ParserBase::LINE); }

cycleCluster		{return(ParserBase::CYCLECLUSTER); }
pulseCoupleEdge	{return(ParserBase::PULSECOUPLEEDGE); }
pulseCoupleDelayEdge	{return(ParserBase::PULSECOUPLEDELAYEDGE); }
	
edge	{return(ParserBase::EDGE); }
				  
component	{return(ParserBase::HIDDENCOMPONENT); }
unlink			{return(ParserBase::UNLINK); }
sigEdge		{return(ParserBase::SIGEDGE); }
sigEdgeOrd3		{return(ParserBase::SIGEDGEORD3); }
stdEdgeOrd3		{return(ParserBase::STDEDGEORD3); }
sigEdgeParams		{return(ParserBase::SIGEDGEPARAMS); }
staticWeightedEdge	{return(ParserBase::STATICWEIGHTEDEDGE);}
weightedEdge		{return(ParserBase::WEIGHTEDEDGE); }
streamOutNode		{return(ParserBase::STREAMOUTNODE); }
streamInNode		{return(ParserBase::STREAMINNODE); }

setRandomSeed		{return(ParserBase::SETRANDOMSEED); }



node					{return(ParserBase::NODE); }
pcoTrapez	{return(ParserBase::PCPOTRAPEZ); }



pulseCoupledExcitatoryNeuron	{return(ParserBase::INTEGRATEFIREQUEUE); }



gaussian		{return(ParserBase::GAUSSIAN); }
uniform		{return(ParserBase::UNIFORM); }
bimodal		{return(ParserBase::BIMODAL); }
poisson			{return(ParserBase::POISSON); }
powerLaw { return (ParserBase::POWERLAW); }

constant			{return(ParserBase::CONSTANT); }
randomizeStates	{return(ParserBase::RANDOMIZESTATES); }
randomizeParameter	{return(ParserBase::RANDOMIZEPARAMETER); }
randomizeWeights	{return(ParserBase::RANDOMIZEWEIGHTS); }
removeObserver		{return(ParserBase::REMOVEOBSERVER);}
addGlobalNoise		{return(ParserBase::ADDGLOBALNOISE);}
meanDegree		{return(ParserBase::MEANDEGREE); }
getTarget	{return(ParserBase::GETTARGET); }
degree		{return(ParserBase::DEGREE); }


outDegreeDistribution	{return(ParserBase::OUTDEGREEDISTRIBUTION);}
inDegreeDistribution	{return(ParserBase::INDEGREEDISTRIBUTION);}

isConnected	{return(ParserBase::ISCONNECTED); }
isDirected	{return(ParserBase::ISDIRECTED); }

meanWeight		{return(ParserBase::MEANWEIGHT); }
meanClustering		{return(ParserBase::MEANCLUSTERING); }
meanPathLength		{return(ParserBase::MEANPATHLENGTH); }
closenessCentrality	{return(ParserBase::CLOSENESSCENTRALITY); }
betweennessCentrality	{return(ParserBase::BETWEENNESSCENTRALITY); }
degreeCentrality	{return(ParserBase::DEGREECENTRALITY); }
saveAdjacencyList 	{return(ParserBase::SAVEADJACENCYLIST); }
saveGraphML	 	{return(ParserBase::SAVEGRAPHML); }
createFromAdjacencyList {return(ParserBase::CREATEFROMADJACENCYLIST); }
startingConditionOpenWaveEnding	{return (ParserBase::STARTINGCONDITIONOPENWAVEENDING); }
startingConditionOpenWaveMiddle	{return (ParserBase::STARTINGCONDITIONOPENWAVEMIDDLE); }
normalizeInWeightSum { return(ParserBase::NORMALIZEINWEIGHTSUM); }



select		{return (ParserBase::SELECT); }



newline			{return(ParserBase::NEWLINE); }
setState	{return(ParserBase::SETINITIALCONDITION); }


","		{return(','); }
";"		{return(';'); }
"."		{return('.'); }
"="		{return('='); }

{ID}        	{ 
			
			string s(yytext);  
			switch	(command::getType(s))
			{
				case _nodeDescriptor_:
					return (ParserBase::INTVAR);
				case _baseType_:
					return (ParserBase::DOUBLEVAR);
				case _string_:
					return (ParserBase::STRINGVAR);
				case _network_:
					return (ParserBase::NETWORKVAR);
				case _node_:
					return (ParserBase::NODEVAR);
				default:
//					val->sCmd = new constantCommand<string>(s);
					return (ParserBase::ID);
			}

		}


<<EOF>> { yyterminate();}
