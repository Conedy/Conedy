

%scanner Scanner.h

%lines
%baseclass-preinclude "command.h"

%union {
//  command *cmd;
  expression<baseType> *doubleExpression;
  expression<bool> *booleanExpression;
  expression<nodeDescriptor> *integerExpression;
  expression<string> *stringExpression;
  expression<nodeBlueprint*> *nodCmd;
  networkTemplate* netCmd;
  expression<edgeBlueprint*> *lCmd;
  instruction *cmd;
  vector <function <baseType() > > *randomVec;
  expressionVector <baseType> *vec;
}


//koasdfshdgfj
%left <booleanExpression> OR
%left <booleanExpression> AND
%left <doubleExpression> '+' '-'
%left <doubleExpression> '*' '/'
%left <doubleExpression> UMINUS
%left <doubleExpression> LOG
%left <doubleExpression> EXP
%left <doubleExpression> SIN
%left <booleanExpression> NOT
%left '(' ')'
%left <booleanExpression> EQUAL NEQUAL GREATEREQUAL LESSEQUAL
%left '.'
%token <booleanExpression> BOOLONE BOOLZERO
%token <doubleExpression> DOUBLE DOUBLEVAR
%token <stringExpression> STRINGVAR
%token <nodCmd> NODEVAR
%type <integerExpression> nodeDescriptor statisticsNetworkCommandInt
%token <integerExpression> GETRANDOMSEED COMANDLINE INT INTVAR
%token <stringExpression> ID SYSTEMCOMMAND WHILE STRING COMANDLINESTRING
%token PRINT EXIT LOOP  IF FOR   VECTORFOR CHAINEDFOR NETWORKTOKEN STRINGTOKEN NODETOKEN INTTOKEN DOUBLETOKEN
// Netzwerk-Befehle
%token USERANDOMPOSITIONING REMOVEEDGES SNAPSHOTATEVENT USELATTICEPOSITIONING LATTICE READPARAMS NORMALIZEINWEIGHTSUM OBSERVEALL OBSERVEGL OBSERVEGLUT REWIRETARGET ADDRANDOMEDGES ADDRANDOMEDGESDEGREEDISTRIBUTION REWIRESOURCE REWIRESOURCEPERTIMESTEP DELAYLINK COMPONENT CYCLE LINE CLEAR SNAPSHOT ADDNODE  PRINTNODESTATISTICS ADDEDGE RANDOMNETWORK OBSERVE OBSERVECOMPONENTS OBSERVEMEANPHASE OBSERVEPHASEDISTANCE OBSERVEPHASECORRELATION OBSERVEPHASECOHERENCE OBSERVEMEAN OBSERVETIME OBSERVEEVENT OBSERVEEVENTTIMES ADDGLOBALNOISE NOISETOSTATES RANDOMIZESTATES RANDOMIZEPARAMETER MEANDEGREE RANDOMIZEWEIGHTS TORUS CONNECTCLOSENODESTORUS CONNECTCLOSENODES TORUSNEARESTNEIGHBORS READINITIALCONDITION COMPLETENETWORK MEANWEIGHT REWIRE SAVEADJACENCYLIST SAVEGRAPHML SIZE MEANCLUSTERING NEWLINE UNLINK CNNSTD CNNNEUTRAL GETPARAM EVOLVE EVOLVEALONG REALIGNWHENDISTANT REALIGNATEVENT REALIGNATEVENTSIGNATURE ISLINKED GETTARGET DEGREE REWIREUNDIRECTED REWIRETARGETUNDIRECTED BETWEENNESSCENTRALITY MEANPATHLENGTH DEGREECENTRALITY CLOSENESSCENTRALITY SELECT COUNTEDGES GETSTATE ISCONNECTED ISDIRECTED SETPARAM
// Nodes
%token NODE IZHIKEVICHMAP REMOVEOBSERVER REMOVEINPUT STARTINGCONDITIONOPENWAVEENDING STARTINGCONDITIONSMALLDISTURBANCE STARTINGCONDITIONOPENWAVEMIDDLE STREAMINNODE STREAMINLATTICE SETINITIALCONDITION CREATEFROMADJACENCYLIST SETPARAMS 
%token INTEGRATEFIREQUEUE SETRANDOMSEED  CNNNODE RANDOMBLUEPRINTNODE STREAMOUTNODE COUPLINGSUMNODE SETTIME
// addNewNode.py token
%include generatedAddNewNodeTokens.yy
// Edges
%token COMPONENT_WEIGHTEDEDGE COMPONENT_STATICWEIGHTEDEDGE 
%token STATICCOMPONENT STATICCOMPONENT_WEIGHTEDEDGE STATICCOMPONENT_STATICWEIGHTEDEDGE 
%token RANDOMTARGET RANDOMTARGET_WEIGHTEDEDGE RANDOMTARGET_STATICWEIGHTEDEDGE 
%token STEPEDGE STEPEDGE_WEIGHTEDEDGE STEPEDGE_STATICWEIGHTEDEDGE 

PULSECOUPLEEDGE STATICWEIGHTEDEDGE RANDOMTARGETEDGE SIGEDGE STDEDGEORD3 SIGEDGEORD3 SIGEDGEPARAMS PULSECOUPLEDELAYEDGE WEIGHTEDEDGE EDGE
// Random
%token GAUSSIAN BIMODAL EXPONENTIAL POWERLAW UNIFORM FROMFILE ADDINPUTFILE  CONSTANT POISSON  INDEGREEDISTRIBUTION OUTDEGREEDISTRIBUTION
// Arithmetic
%token  ASSIGNPLUS ASSIGNMINUS ASSIGNDIVIDE ASSIGNTIMES PLUSPLUS MINUSMINUS ASSIGNMODOLO
%token <netCmd> NETWORKVAR
%type <cmd> loop print instruction declare assign networkCommand bluePrintCommand commands commandBlock while createNetworkCommand for if vectorFor system spatialNetworkCommand

%type <stringExpression> identifier
%type <stringExpression> string

%type <doubleExpression> baseType statisticsNetworkCommandBaseType
%type <booleanExpression> bool
%type <booleanExpression> statisticsNetworkCommandBool
%type <nodCmd> node createNode
%type <netCmd> NETWORK
%type <lCmd> link createLink
%type <vec> argList
%type <randomVec> randomList
%type <doubleExpression> random
%start program


%%

// asdfsjhg

program: commands  { $1->execute();};

commands:   commands instruction ';' {  ((instructionBlock*)$1)->addInstruction($2); $$ = $1; }
		| instruction ';' { $$ = new instructionBlock();  ((instructionBlock*)$$)->addInstruction($1); };
 //		| error  { $$ = new instructionBlock();  cout    << "jjj" << endl; };


instruction		: system
		|  print
	| loop
| while
| declare
| assign
| networkCommand
| commandBlock
| createNetworkCommand
| spatialNetworkCommand
| bluePrintCommand
| statisticsNetworkCommandInt
| for
	| EXIT { $$ = new bindInstruction(bind(exit, 1)); }
| if
	| vectorFor ;





//		| error ';' { $$ = new emptyInstruction(); } ;

commandBlock	: '{' commands '}' { $$ = $2;};




assign		: baseType '=' baseType { $$ = new assignInstruction<baseType> ((varCommand<baseType>*)$1, $3); }
		| nodeDescriptor '=' nodeDescriptor { $$ = new assignInstruction<nodeDescriptor> ((varCommand<nodeDescriptor>*)$1,$3); }
		| string '=' string { $$ = new assignInstruction<string> ((varCommand<string>*)$1,$3); }
		| SETRANDOMSEED '(' nodeDescriptor ')'  { $$ = new bindInstruction( bind(&gslNoise::setSeed,_E(nodeDescriptor,$3))); }
		|   ADDINPUTFILE '(' string ')' { $$ = new bindInstruction(bind(&command::addInputFile, _E(string,$3))); }
		|  nodeDescriptor ASSIGNPLUS nodeDescriptor { varCommand<nodeDescriptor> *var = (varCommand<nodeDescriptor>*)$1;
				$$ = new assignInstruction<nodeDescriptor> ( var,  new plusCommandnodeDescriptor<nodeDescriptor, nodeDescriptor> ($3,  (var)) )  ; }
		|  nodeDescriptor ASSIGNMINUS nodeDescriptor { varCommand<nodeDescriptor> *var =  (varCommand<nodeDescriptor>*)$1;
				$$ = new assignInstruction<nodeDescriptor> ( var,  new minusCommandnodeDescriptor<nodeDescriptor, nodeDescriptor> ($3,  (var))); }
		|  nodeDescriptor ASSIGNDIVIDE nodeDescriptor { varCommand<nodeDescriptor> *var = (varCommand<nodeDescriptor>*)$1;
				$$ = new assignInstruction<nodeDescriptor> ( var,  new divideCommandnodeDescriptor<nodeDescriptor, nodeDescriptor> ($3,  (var))); }
		|  nodeDescriptor ASSIGNMODOLO nodeDescriptor { varCommand<nodeDescriptor> *var = (varCommand<nodeDescriptor>*)$1;
				$$ = new assignInstruction<nodeDescriptor> ( var,  new modoloCommandnodeDescriptor<nodeDescriptor, nodeDescriptor> ($3,  (var))); }
		|  nodeDescriptor ASSIGNTIMES nodeDescriptor { varCommand<nodeDescriptor> *var = (varCommand<nodeDescriptor>*)$1;
				$$ = new assignInstruction<nodeDescriptor> ( var,  new timesCommandnodeDescriptor<nodeDescriptor, nodeDescriptor> ($3,  (var))); }
		|  nodeDescriptor PLUSPLUS { varCommand<nodeDescriptor> *var = (varCommand<nodeDescriptor>*)$1;	
				$$ = new assignInstruction<nodeDescriptor> ( var,  new plusCommandnodeDescriptor<nodeDescriptor, nodeDescriptor> (new constantCommand<nodeDescriptor>(1),  (var))); }
		|  baseType PLUSPLUS { varCommand<baseType> *var = (varCommand<baseType>*)$1;	
				$$ = new assignInstruction<baseType> ( var,  new plusCommandbaseType<baseType, baseType> (new constantCommand<baseType>(1),  (var))); }
		|  nodeDescriptor MINUSMINUS { varCommand<nodeDescriptor> *var = (varCommand<nodeDescriptor>*)$1;	
				$$ = new assignInstruction<nodeDescriptor> ( var,  new minusCommandnodeDescriptor<nodeDescriptor, nodeDescriptor> (new constantCommand<nodeDescriptor>(1),  (var))); }
		|  baseType MINUSMINUS { varCommand<baseType> *var = (varCommand<baseType>*)$1;	
				$$ = new assignInstruction<baseType> ( var,  new minusCommandbaseType<baseType, baseType> (new constantCommand<baseType>(1),  (var))); };


declare		:

//	DOUBLETOKEN ID '=' baseType
//		{ command::declare($2->evaluate(),_baseType_); $$ = new assignInstruction<baseType> ((varCommand<baseType>*)$2, $4); }
//		|
DOUBLETOKEN ID { command::declare($2->evaluate(),_baseType_); $$ = new emptyInstruction(); }
		| NODETOKEN ID { command::declare($2->evaluate(), _node_); $$ = new emptyInstruction(); }
		| INTTOKEN ID { command::declare($2->evaluate(), _nodeDescriptor_); $$ = new emptyInstruction (); }
		| NETWORKTOKEN ID { command::declare($2->evaluate(), _network_); $$ = new emptyInstruction(); }
		| STRINGTOKEN ID { command::declare($2->evaluate(), _string_); $$ = new emptyInstruction(); }
		| INTTOKEN identifier '=' nodeDescriptor { command::declare($2->evaluate(),_nodeDescriptor_); $$ = new assignInstruction<nodeDescriptor> (new varCommand<nodeDescriptor> ($2->evaluate()), $4); }
		| DOUBLETOKEN identifier '=' baseType    { command::declare($2->evaluate(),_baseType_);       $$ = new assignInstruction<baseType>       (new varCommand<baseType>($2->evaluate()), $4); };

identifier : ID { $$ = $1; };





system	: SYSTEMCOMMAND	{ string s(d_scanner->YYText() + 1, strlen(d_scanner->YYText()) - 2);
	$$ = new systemInstruction(s); };



networkCommand	:  NETWORK '.' CLEAR '(' ')' { $$ = NETWORKFUNK(clear,$1); }
//		| NETWORK '.' SIMULATE '(' nodeDescriptor ')' { $$ = NETWORKFUNK2(simulate,$1,_E(nodeDescriptor,$5),_dynNode_); }
		| NETWORK '.' SNAPSHOT '(' ')' { $$ = NETWORKFUNK(snapshot,$1); }
//		| NETWORK '.' SNAPSHOT '(' error ')' { $$ = new emptyInstruction(); cout << "snapshot nimmt keine Argumente"; }
		| NETWORK '.' ADDNODE  '(' createNode ')' { $$ = NETWORKFUNK1(addNode,$1,_E(nodeBlueprint*,$5)); }
		| NETWORK '.' PRINTNODESTATISTICS '(' ')'{ $$ = NETWORKFUNK(printNodeStatistics,$1); }
		| NETWORK '.' ADDEDGE '(' nodeDescriptor ',' nodeDescriptor ',' baseType ')' { $$ = NETWORKFUNK3(addWeightedEdge,$1,_E(nodeDescriptor,$5),_E(nodeDescriptor,$7),_E(baseType,$9)); }
		| NETWORK '.' UNLINK '(' nodeDescriptor ',' nodeDescriptor ')' { $$= NETWORKFUNK2(unlink,$1,_E(nodeDescriptor,$5),_E(nodeDescriptor,$7)); }
		| NETWORK '.' SETTIME '(' baseType ')' { $$= NETWORKFUNK1(setTime,$1,_E(baseType,$5)); }

		| NETWORK '.' SELECT '(' string  ')'
	{ $$ = NETWORKFUNK1(select, $1, _E(string, $5)); }
		| NETWORK '.' ADDEDGE '(' nodeDescriptor ',' nodeDescriptor ',' createLink ')'
 { $$ = new bindInstruction(
		bind(&networkTemplate::addEdge,$1,
		bind(&expression<nodeDescriptor>::evaluate, $5),
		bind(&expression<nodeDescriptor>::evaluate, $7),
		bind(&expression<edgeBlueprint* >::evaluate, $9)));
}
		| NETWORK '.' EVOLVE	'(' baseType ',' baseType ')' { $$ = NETWORKFUNK2(evolve,$1,_E(baseType,$5), _E(baseType,$7)); }
		| NETWORK '.' EVOLVE	'(' baseType ')' { $$ = NETWORKFUNK1(evolveFor,$1,_E(baseType,$5)); }
		| NETWORK '.' EVOLVEALONG	'(' createNode ',' baseType ',' string ',' string ')'
{
#if CONDOR
$$ = new bindInstruction(bind(&command::addInputFile, _E(string,$9)));
#else
$$ = NETWORKFUNK4(evolveAlong,$1, $5->evaluate()->getNodeInfo().theNodeType, _E(baseType,$7), _E(string, $9 ),_E(string, $11 )  );
#endif
}
		| NETWORK '.' REALIGNATEVENT  '(' string ',' string ','  createNode ',' baseType ',' nodeDescriptor ',' nodeDescriptor ')'
{
#if CONDOR
//$$ = new bindInstruction(bind(&command::addInputFile, _E(string,$5)));
$$ = new emptyInstruction();
#else
$$ = NETWORKFUNK6(realignAtEvent,$1,  _E(string, $5 ),_E(string, $7 ) , $9->evaluate()->getNodeInfo().theNodeType, _E(baseType, $11), _E(nodeDescriptor,$13), _E(nodeDescriptor,$15 ));
#endif
}


		| NETWORK '.' REALIGNWHENDISTANT  '(' string ',' string ','  createNode ',' baseType ',' nodeDescriptor ',' nodeDescriptor ')'
{
#if CONDOR
//$$ = new bindInstruction(bind(&command::addInputFile, _E(string,$5)));
$$ = new emptyInstruction();
#else
$$ = NETWORKFUNK6(realignWhenDistant,$1,  _E(string, $5 ),_E(string, $7 ) , $9->evaluate()->getNodeInfo().theNodeType, _E(baseType, $11), _E(nodeDescriptor,$13), _E(nodeDescriptor,$15 ));
#endif
}



		| NETWORK '.' REALIGNATEVENTSIGNATURE  '(' string ',' string ','  createNode ',' baseType ',' nodeDescriptor ',' nodeDescriptor ')'
{
#if CONDOR
$$ = new emptyInstruction();
//$$ = new bindInstruction(bind(&command::addInputFile, _E(string,$5)));
#else
$$ = NETWORKFUNK6(realignAtEventSignature,$1,  _E(string, $5 ),_E(string, $7 ) , $9->evaluate()->getNodeInfo().theNodeType, _E(baseType, $11), _E(nodeDescriptor,$13), _E(nodeDescriptor,$15 ));
#endif
}
		| NETWORK '.' INDEGREEDISTRIBUTION '(' string ')' { $$ = NETWORKFUNK1(inDegreeDistributionToFile,$1,_E(string,$5));}
		| NETWORK '.' OUTDEGREEDISTRIBUTION '(' string ')' { $$ = NETWORKFUNK1(outDegreeDistributionToFile,$1,_E(string,$5)); }
		| NETWORK '.' NOISETOSTATES '(' createNode ',' random ')'
  { function<baseType ()> r = bind(&expression<baseType>::evaluate,$7);
	$$ = new bindInstruction(
		bind(&networkTemplate::noiseToStates,$1, r, $5->evaluate()->getNodeInfo().theNodeType)); }
		| NETWORK '.' RANDOMIZESTATES '(' createNode ',' randomList ')'
  {

//	function<baseType()> r =bind(&expression<baseType>::evaluate,*$7);
//	vector <function<double() > > vec;
//	vec.push_back(r);

$$ = NETWORKFUNK2(randomizeStatesVec, $1,  _E(nodeBlueprint*, $5),*$7 ); }
//function<baseType ()> r = bind(&expression<baseType>::evaluate,$7);
//	$$ = new bindInstruction(
//		bind(&networkTemplate::randomizeStates,$1, r, $5->evaluate()->getNodeInfo().theNodeType)); }

	| NETWORK '.' RANDOMIZEPARAMETER '(' string ',' random ')'
 { function<baseType ()> r = bind(&expression<baseType>::evaluate,$7);
    $$ = new bindInstruction(
		bind(&networkTemplate::randomizeParameter,$1,
	bind(&expression<string>::evaluate, $5), r)); }
		| NETWORK '.' ADDGLOBALNOISE '(' random ')'
  { function <baseType ()> r = bind(&expression<baseType>::evaluate, $5);

$$ = new bindInstruction( bind(&networkTemplate::addGlobalNoise, $1, r)); }



		| NETWORK '.' RANDOMIZEWEIGHTS '(' random ')'
  { function<baseType ()> r = bind(&expression<baseType>::evaluate,$5);
    $$ = new bindInstruction( bind(&networkTemplate::randomizeWeights, $1, r));}
		| NETWORK '.' READINITIALCONDITION '(' createNode ',' string ')'
 {
#if CONDOR
$$ = new bindInstruction(bind(&command::addInputFile, _E(string,$7)));
#else
$$ =	NETWORKFUNK2(readInitialCondition, $1,  _E(string,$7),  _E(nodeBlueprint *,$5) );
//new bindInstruction(bind(&networkTemplate::readInitialCondition, $1, _E(string,$7),$5->evaluate()->getNodeInfo().theNodeType));
#endif
}
		| NETWORK '.' READPARAMS '(' string ',' string ')'
		{
#if CONDOR
$$ = new bindInstruction(bind(&command::addInputFile, _E(string,$7)));
#else
$$ =NETWORKFUNK2(readParameter, $1, _E(string,$5),_E(string,$7));
#endif
}



		| NETWORK '.' STARTINGCONDITIONOPENWAVEENDING '(' ')' { $$ = NETWORKFUNK(startingConditionOpenWaveEnding,$1); }
		| NETWORK '.' STARTINGCONDITIONOPENWAVEMIDDLE '(' ')' { $$ = NETWORKFUNK(startingConditionOpenWaveEndingMiddle,$1); }
		| NETWORK '.' STARTINGCONDITIONSMALLDISTURBANCE '(' baseType ',' random ')'
  { function<baseType ()> r = bind(&expression<baseType>::evaluate,$7);
    $$ = NETWORKFUNK2(smallDisturbance,$1,_E(baseType,$5), r); }

		| NETWORK '.' STARTINGCONDITIONSMALLDISTURBANCE '(' baseType ',' nodeDescriptor ',' nodeDescriptor ',' random ')'
  { function<baseType ()> r = bind(&expression<baseType>::evaluate,$11);
    $$ = NETWORKFUNK4(smallDisturbance,$1,_E(baseType,$5), _E(nodeDescriptor,$7), _E(nodeDescriptor,$9), r); }

		| NETWORK '.' SETINITIALCONDITION '(' nodeDescriptor ',' argList ')'
//  {	$$ = NETWORKFUNK2(setInitialCondition, $1, _E(int, $5),  bind(&expressionVector<baseType>::evaluate, $7)); };
{$$ = NETWORKFUNK2(setInitialConditionVec, $1, _E(nodeDescriptor, $5), bind(&expressionVector<baseType>::evaluate, $7)); };
//{$$ = new bindInstruction(bind(&networkTemplate::setInitialCondition, $1, _E(nodeDescriptor, $5), bind(&expressionVector<baseType>::evaluate, $7))); };

string :	STRING       {  std::string s(d_scanner->YYText()+1, strlen(d_scanner->YYText()) - 2); $$ =  new constantCommand<string>(s);}
	| string '+' nodeDescriptor	{ $$ = new stringCat<string,nodeDescriptor>($1,$3); }
	| string '+' string	{ $$ = new stringCat<string,string>($1,$3); }
	| string '+' baseType	{ $$ = new stringCat<string,baseType>($1,$3);}
     	| STRINGVAR {$$ = new varCommand<string>(d_scanner->YYText()); }
	| string '+' bool { $$ = new stringCat <string, bool > ( $1, $3);}
	| NEWLINE { $$ = new constantCommand<string>("\n"); }
	// Ohne Seg-Schutz
	//| COMANDLINESTRING '(' nodeDescriptor ')' { $$ = new constantCommand<string>( commandLineArguments::arg[ $3->evaluate() + 1].c_str()   ); }
	| COMANDLINESTRING '(' nodeDescriptor ')' { $$ = new constantCommand<string>( commandLineArguments::getStringArg( $3->evaluate() + 1)); };




spatialNetworkCommand : NETWORK '.' USERANDOMPOSITIONING '(' ')'
		 { $$ = NETWORKFUNK(useRandomPositioning, $1); }
	| NETWORK '.' USELATTICEPOSITIONING '(' nodeDescriptor ',' nodeDescriptor ')'   // REDUCE CONFLICT XXX
		 { $$ = NETWORKFUNK2(useLatticePositioning, $1,  _E(nodeDescriptor, $5),_E(nodeDescriptor,$7)  );};


bluePrintCommand : createNode '=' createNode { $$ = new assignInstruction<nodeBlueprint*> ((varCommand<nodeBlueprint*>*)$1 ,$3);}
	| createNode '.' SETPARAMS '(' argList ')' { $$ = new bindInstruction( bind( &params<baseType>::setSheet , bind (&expression<nodeBlueprint*>::evaluate, $1), bind(&expressionVector<baseType>::evaluate, $5))); };


createNetworkCommand : NETWORK '.' RANDOMNETWORK  '(' nodeDescriptor ',' baseType ','createNode ',' createLink ')' { $$ = NETWORKFUNK4(randomNetwork,$1,_E(nodeDescriptor,$5),_E(baseType,$7),_E(nodeBlueprint*,$9),_E(edgeBlueprint*,$11));}
	| NETWORK '.' RANDOMNETWORK  '(' nodeDescriptor ',' baseType ','createNode ')' { $$ = NETWORKFUNK4(randomNetwork,$1,_E(nodeDescriptor,$5),_E(baseType,$7),_E(nodeBlueprint*,$9),network::stdEdge );}
	| NETWORK '.' OBSERVE '(' nodeDescriptor ',' string ')'	{ $$ = NETWORKFUNK3(observe, $1,      _E(nodeDescriptor, $5), _E(string, $7)  ,network::stdEdge); }
	| NETWORK '.' OBSERVEMEAN '(' string ')' 	{ $$ =NETWORKFUNK2(observeSum,$1,_E(string,$5), network::stdEdge ); }
	| NETWORK '.' OBSERVEPHASECOHERENCE '(' string ')' { $$ = NETWORKFUNK5(observePhaseCoherence,$1, _E(string,$5), network::stdEdge, network::stdNode, 0, numeric_limits<nodeDescriptor>::max()); }
	| NETWORK '.' OBSERVEPHASECOHERENCE  '(' string ',' createLink ')' { $$ = NETWORKFUNK5(observePhaseCoherence,$1, _E(string,$5), _E(edgeBlueprint*, $7), network::stdNode, 0, numeric_limits<nodeDescriptor>::max() ); }
	| NETWORK '.' OBSERVEPHASECOHERENCE '(' string ',' node ')' { $$ = NETWORKFUNK5(observePhaseCoherence,$1, _E(string,$5), network::stdEdge,  _E(nodeBlueprint*, $7), 0, numeric_limits<nodeDescriptor>::max() ); }
	| NETWORK '.' OBSERVEPHASECOHERENCE  '(' string ',' createLink ',' node ')'
			{ $$ = NETWORKFUNK5(observePhaseCoherence,$1, _E(string,$5) ,_E(edgeBlueprint*, $7), _E(nodeBlueprint*, $9) , 0 , numeric_limits<nodeDescriptor>::max()); }
	| NETWORK '.' OBSERVEPHASECORRELATION  '(' string ',' node  ')'
  	{ $$ = NETWORKFUNK2( observePhaseCorrelation, $1, _E(string, $5 ), _E(nodeBlueprint*, $7)); }
	| NETWORK '.' OBSERVEPHASEDISTANCE  '(' string ',' node  ')'
  	{ $$ = NETWORKFUNK2( observePhaseDistance, $1, _E(string, $5 ), _E(nodeBlueprint*, $7)); }
	| NETWORK '.' OBSERVEPHASECOHERENCE '(' string ',' createLink ',' nodeDescriptor ',' nodeDescriptor ')'  
			{ $$ = NETWORKFUNK5(observePhaseCoherence,$1,  _E(string,$5) ,_E(edgeBlueprint*, $7), network::stdNode, _E(nodeDescriptor,$9), _E(nodeDescriptor,$11)    ); }
	| NETWORK '.' OBSERVEMEANPHASE '(' string ')' { $$ = NETWORKFUNK1(observeSumPhase,$1, _E(string,$5) ); }
	| NETWORK '.' OBSERVEMEANPHASE '(' string ',' createLink ')' { $$ = NETWORKFUNK2(observeSumPhase,$1, _E(string,$5), _E(edgeBlueprint*, $7) ); }
	| NETWORK '.' OBSERVETIME '(' string ')' 	{ $$ = NETWORKFUNK1(observeTime,$1, _E(string,$5)); }
	| NETWORK '.' OBSERVEEVENT '(' string ',' nodeDescriptor ')' 	{ $$ = NETWORKFUNK2(observeEvent,$1, _E(string,$5), _E(nodeDescriptor, $7)); }
	| NETWORK '.' SNAPSHOTATEVENT '(' nodeDescriptor ')' 	{ $$ = NETWORKFUNK1(snapshotAtEvent,$1, _E(nodeDescriptor, $5)); }
	| NETWORK '.' SNAPSHOTATEVENT '(' nodeDescriptor ',' nodeDescriptor ')' 	{ $$ = NETWORKFUNK2(snapshotAtEventOfNode,$1, _E(nodeDescriptor, $5), _E(nodeDescriptor,$7)); }

	| NETWORK '.' OBSERVEEVENTTIMES '(' string ',' nodeDescriptor  ')' 	{ $$ = NETWORKFUNK2(observeEventTimes,$1, _E(string,$5), _E(nodeDescriptor, $7)); }
	| NETWORK '.' OBSERVEALL '(' string ')' 	{ $$ = NETWORKFUNK2(observeAll, $1, _E(string,$5), network::stdEdge); }
	| NETWORK '.' OBSERVECOMPONENTS '(' nodeDescriptor ',' string ')' 	{ $$ = NETWORKFUNK2(observeComponents, $1, _E(nodeDescriptor, $5),_E(string,$7)); }
	| NETWORK '.' OBSERVE '(' nodeDescriptor ',' string ',' createLink ')' {$$ = NETWORKFUNK3(observe,$1,_E(nodeDescriptor,$5),_E(string,$7),_E(edgeBlueprint*,$9)); }
	| NETWORK '.' OBSERVEMEAN '(' string ',' createLink ')' { $$ = NETWORKFUNK2(observeSum,$1, _E(string,$5),_E(edgeBlueprint*,$7)); }
	| NETWORK '.' OBSERVEALL '(' string ',' createLink ')'  { $$ = NETWORKFUNK2(observeAll,$1,_E(string,$5), _E(edgeBlueprint*, $7));}
	| NETWORK '.' REMOVEOBSERVER '(' ')' { $$ = NETWORKFUNK(removeObserver,$1); }
	| NETWORK '.' REMOVEINPUT   '(' ')' { $$ = NETWORKFUNK1(remove,$1,_inNode_| _dynNode_ ); }
	| NETWORK '.' REMOVEEDGES '(' createLink ')' { $$ = NETWORKFUNK1 (removeEdges, $1, _E(edgeBlueprint*, $5)); }




	| NETWORK '.' CONNECTCLOSENODES '(' createNode ',' createNode ',' baseType ',' createLink ')'
  { $$ = NETWORKFUNK4(connectCloseNodes, $1, _E(nodeBlueprint *, $5), _E(nodeBlueprint *, $7), _E(baseType, $9), _E(edgeBlueprint*,$11)); }
	| NETWORK '.' CONNECTCLOSENODESTORUS '(' createNode ',' createNode ',' baseType ',' createLink ')'
  { $$ = NETWORKFUNK4(connectCloseNodesTorus, $1, _E(nodeBlueprint *, $5), _E(nodeBlueprint *, $7), _E(baseType, $9), _E(edgeBlueprint*,$11)); }


	| NETWORK '.' SETPARAM '(' nodeDescriptor ',' string ',' baseType ')' { $$ = NETWORKFUNK3(setParam, $1, _E(nodeDescriptor,$5), _E(string, $7), _E(baseType,$9));}

// at the moment not supported

	| NETWORK '.' CNNSTD '<' createNode ',' createLink '>' '(' nodeDescriptor ',' nodeDescriptor ',' string ')'
	{ $$ = NETWORKFUNK5(cnnStd,$1,_E(nodeDescriptor,$10), _E(nodeDescriptor,$12), _E(string,$14), _E(nodeBlueprint*,$5), _E(edgeBlueprint*, $7)); }
	| NETWORK '.' CNNSTD '<' createNode '>' '(' nodeDescriptor ',' nodeDescriptor ',' string ')'
	{ $$ = NETWORKFUNK5(cnnStd,$1,_E(nodeDescriptor,$8), _E(nodeDescriptor,$10), _E(string,$12), _E(nodeBlueprint*,$5), new weightedEdgeVirtual); }
	| NETWORK '.' CNNNEUTRAL '<' createNode ',' createLink '>' '(' nodeDescriptor ',' nodeDescriptor ',' string ')'
	{ $$ = NETWORKFUNK5(cnnNeutral,$1,_E(nodeDescriptor,$10), _E(nodeDescriptor,$12), _E(string,$14), _E(nodeBlueprint*,$5), _E(edgeBlueprint*, $7)); }
	| NETWORK '.' CNNNEUTRAL '<' createNode '>' '(' nodeDescriptor ',' nodeDescriptor ',' string ')'
	{ $$ = NETWORKFUNK5(cnnNeutral,$1,_E(nodeDescriptor,$8), _E(nodeDescriptor,$10), _E(string,$12), _E(nodeBlueprint*,$5), new weightedEdgeVirtual); }
	| NETWORK '.' STREAMINLATTICE '(' nodeDescriptor ',' nodeDescriptor ',' string ')' { $$ =NETWORKFUNK3(streamInLattice,$1,_E(nodeDescriptor,$5),_E(nodeDescriptor,$7),_E(string,$9)); }

// at the moment not supported ^



	| NETWORK '.' OBSERVEGLUT '('  baseType ',' string ')'
{
#if OPENGL
 $$ = NETWORKFUNK2(startNeverStopGlut,$1,_E(string,$7),_E(baseType,$5));
#else
	throw "OpenGl nicht mitKompiliert!";
#endif
}
	| NETWORK '.' OBSERVEGL '('  baseType ',' baseType ')'
  {
#if OPENGL
 $$ = NETWORKFUNK3(startNeverStopOld,$1,_E(baseType,$5),_E(baseType,$7),networkTemplate::stdEdge);
#else
	throw "OpenGl nicht mitKompiliert!";
#endif
}
	| NETWORK '.' OBSERVEGL '('  baseType ',' baseType ',' createLink ')'
  {
#if OPENGL
 $$ = NETWORKFUNK3(startNeverStopOld,$1,_E(baseType,$7),_E(baseType,$5),_E(edgeBlueprint*,$9));
#else
	throw "OpenGl nicht mitKompiliert!";
#endif

}
	| NETWORK '.' OBSERVEGL '(' baseType ',' createLink ')'
	{
#if OPENGL
 $$ = NETWORKFUNK2(startNeverStopOld,$1,_E(baseType,$5),_E(edgeBlueprint*,$7));
#else
	throw "OpenGl nicht mitKompiliert!";
#endif
}
	| NETWORK '.' OBSERVEGL '(' baseType ')'
	{
#if OPENGL
 $$ = NETWORKFUNK2(startNeverStopOld,$1,_E(baseType,$5), networkTemplate::stdEdge);
#else
	throw "OpenGl nicht mitKompiliert!";
#endif
}
	| NETWORK '.' OBSERVEGLUT '(' baseType ',' string ',' createLink ')'
{
#if OPENGL
 $$ = NETWORKFUNK3(startNeverStopGlut,$1,_E(string,$7),_E(baseType,$5),_E(edgeBlueprint*,$9));
#else
	throw "OpenGl nicht mitKompiliert!";
#endif
}




	| NETWORK '.' REWIRESOURCE '(' baseType ')' { $$ = NETWORKFUNK2(rewireSource,$1,_E(baseType,$5), _dynNode_); }
	| NETWORK '.' REWIRETARGET '(' baseType ')' { $$ = NETWORKFUNK2(rewireTarget,$1,_E(baseType,$5),_dynNode_); }
	| NETWORK '.' REWIRE '(' baseType ')' { $$ = NETWORKFUNK2(rewire,$1,_E(baseType,$5), network::stdNode); }
	| NETWORK '.' NORMALIZEINWEIGHTSUM '(' baseType ')' { $$ = NETWORKFUNK1(normalizeInputs,$1,_E(baseType,$5)); }
	| NETWORK '.' REWIRE '(' baseType  ',' createLink ')' { $$ = NETWORKFUNK3(replaceEdges,$1,_E(baseType,$5), _E(edgeBlueprint*,$7),network::stdNode); }
	| NETWORK '.' REWIREUNDIRECTED '(' baseType ')' { $$ = NETWORKFUNK2(rewireUndirected,$1,_E(baseType,$5),_dynNode_); }
	| NETWORK '.' REWIRETARGETUNDIRECTED '(' baseType ')' { $$ = NETWORKFUNK2(rewireTargetUndirected,$1,_E(baseType,$5),_dynNode_); }



| NETWORK '.' REWIRESOURCEPERTIMESTEP '(' baseType ',' baseType ')'
 { function<baseType ()> r = bind(&expression<baseType>::evaluate,$7);
    $$ = new bindInstruction( bind(&networkTemplate::rewireSourcePerTimestep, $1 ,
		bind(&expression<baseType>::evaluate, $5)     , r,_dynNode_)); }
	| NETWORK '.' REWIRE '(' baseType ',' random ')'
  { function<baseType ()> r = bind(&expression<baseType>::evaluate,$7);
$$ = new bindInstruction(bind(&networkTemplate::rewireWeights ,$1, bind(&expression<baseType>::evaluate, $5),r,_dynNode_)); }
	| NETWORK '.' ADDRANDOMEDGES '(' baseType ',' createLink ')'
 { $$ = NETWORKFUNK2(addRandomEdges,$1,_E(baseType,$5), _E(edgeBlueprint*,$7)); }
	| NETWORK '.' ADDRANDOMEDGESDEGREEDISTRIBUTION '(' random ',' createLink ')'
 {  function<baseType ()> r = bind(&expression<baseType>::evaluate,$5);


$$ = NETWORKFUNK2(addRandomEdgesDegreeDistribution,$1,r, _E(edgeBlueprint*,$7)); }
	| NETWORK '.' CYCLE '(' nodeDescriptor ',' nodeDescriptor ',' createNode ')'{ $$ = NETWORKFUNK4(cycle,$1,_E(nodeDescriptor,$5),_E(nodeDescriptor,$7),_E(nodeBlueprint*,$9), network::stdEdge); }
	| NETWORK '.' CYCLE '(' nodeDescriptor ',' nodeDescriptor ',' createNode ',' createLink ')' { $$ = NETWORKFUNK4(cycle,$1,_E(nodeDescriptor,$5),_E(nodeDescriptor,$7),_E(nodeBlueprint*,$9), _E(edgeBlueprint*,$11)); }
	| NETWORK '.' LINE '(' nodeDescriptor ',' nodeDescriptor ',' createNode ',' createLink ')' { $$ = NETWORKFUNK4(line,$1,_E(nodeDescriptor,$5),_E(nodeDescriptor,$7),_E(nodeBlueprint*,$9), _E(edgeBlueprint*,$11)); }
//	| NETWORK '.' CYCLECLUSTER '<' createNode ',' nodeDescriptor '>' '<' createNode ',' nodeDescriptor '>' '(' nodeDescriptor ')' { $$ = NETWORKFUNK5(cycleCluster,$1, _E(nodeDescriptor,$7),_E(nodeBlueprint*,$5), _E(nodeDescriptor,$12),_E(nodeBlueprint*,$10), _E(nodeDescriptor,$15)); }
	| NETWORK '.' BETWEENNESSCENTRALITY '(' string  ')' { $$ = NETWORKFUNK1(betweennessCentrality,$1,_E(string,$5)); }
	| NETWORK '.' CLOSENESSCENTRALITY '(' string ')' { $$ = NETWORKFUNK1(closenessCentrality,$1, _E(string,$5)); }
	| NETWORK '.' DEGREECENTRALITY '(' string ')' { $$ = NETWORKFUNK1(degreeCentrality, $1, _E(string,$5)); }
	| NETWORK '.' SAVEADJACENCYLIST '(' string ')' { $$ = NETWORKFUNK1(saveAdjacencyList,$1,_E(string,$5)); }
	| NETWORK '.' SAVEGRAPHML '(' string ')' { $$ = NETWORKFUNK1(saveGraphML,$1,_E(string,$5)); }
	| NETWORK '.' CREATEFROMADJACENCYLIST '(' string ',' createNode ',' createLink ')' {
#if CONDOR
$$ = new bindInstruction(bind(&command::addInputFile, _E(string,$5)));

#else
$$ = NETWORKFUNK3(createFromAdjacencyList,$1,_E(string,$5),_E(nodeBlueprint*,$7),_E(edgeBlueprint*,$9));

#endif

};

print          	: PRINT baseType { $$ = new printInstructionDouble ($2);}
		| PRINT bool { $$ = new printInstruction<bool> ($2); }
		| PRINT nodeDescriptor { $$ = new printInstruction<nodeDescriptor> ($2); }
		| PRINT string { $$ = new printInstruction<string> ($2); }
		| PRINT NEWLINE { $$ = new printInstruction<string>(new constantCommand<string>("\n")); };


loop		: LOOP '(' nodeDescriptor ')' instruction {  $$ = new loopInstruction ($3,$5); };

while		: WHILE '(' bool ')' instruction { $$ = new whileInstruction ($3,$5); };
for		: FOR '(' instruction ';' bool ';' instruction ')' instruction { $$ = new forInstruction ($3,$5,$7,$9); };
vectorFor	: VECTORFOR '(' instruction ';' bool ';' instruction ')' instruction {
//#ifdef CONDOR
 	vectorForInstruction::registerNewLoop(); $$ = new vectorForInstruction ($3,$5,$7,$9, false); 
//#else
//	cout << "#Warning. This Executable of Conedy was not compiled for generating condor-scripts. \n Calculating at home." << endl; $$ = new forInstruction ($3,$5,$7,$9); 
//endif
}
		| CHAINEDFOR '(' instruction ';' bool ';' instruction ')' instruction {
 vectorForInstruction::registerNewLoop(); $$ = new vectorForInstruction ($3,$5,$7,$9, true); };

if		: IF '(' bool ')' instruction { $$ = new ifInstruction ($3,$5);
};




//: ID {  $$ = new varCommand<nodeBlueprint*> (*$1); }
//: node '(' argList ')' {  ( (dynNode*)($1->evaluate()  ) ) ->params<baseType>::rerouteParams(($3->evaluate())); }


node	: NODE { nodeBlueprint *n = new nodeVirtualEdges<dynNode>(); $$ = new constantCommand<nodeBlueprint*>(n);}
		| CNNNODE { nodeBlueprint *n = new nodeVirtualEdges<cnnNode>(); $$ = new constantCommand<nodeBlueprint*>(n); }
		| COUPLINGSUMNODE { nodeBlueprint *n = new nodeVirtualEdges<couplingSumNode>(); $$ = new constantCommand<nodeBlueprint*>(n);}
//		| ESCAPENOISENEURON { nodeBlueprint *n = new escapeNoiseNeuronStatic(); $$ = new constantCommand<nodeBlueprint*>(n);}
//		| GAUSSIANNAPK { nodeBlueprint *n = new nodeVirtualEdges<gaussianNapK>();$$ = new constantCommand<nodeBlueprint*>(n); }
//		| GAUSSIANNAPKKM { nodeBlueprint *n = new nodeVirtualEdges<gaussianNapKKm>();$$ = new constantCommand<nodeBlueprint*>(n); }
//		| INTEGRATEANDFIRE { nodeBlueprint *n = new nodeVirtualEdges<integrateAndFire>(); $$ = new constantCommand<nodeBlueprint*>(n); }
		| INTEGRATEFIREQUEUE { nodeBlueprint *n = new nodeVirtualEdges<pulseCoupledExcitatoryNeuron>(); $$ = new constantCommand<nodeBlueprint*>(n);}
		| IZHIKEVICHMAP { nodeBlueprint *n = new nodeVirtualEdges<izhikevichMap>(); $$ = new constantCommand<nodeBlueprint*>(n);}
//		| NAPK { nodeBlueprint *n = new nodeVirtualEdges<napK>();$$ = new constantCommand<nodeBlueprint*>(n); }
//		| NAPKKM { nodeBlueprint *n = new nodeVirtualEdges<napKKm>();$$ = new constantCommand<nodeBlueprint*>(n); }
// addNewNode.py Nodes
%include generatedAddNewNode.yy
//		| PERIODICNODE { nodeBlueprint *n = new nodeVirtualEdges<periodicNode>(); $$ = new constantCommand<nodeBlueprint*>(n); }
//		| RANDOMWALKNEURON { nodeBlueprint *n = new nodeVirtualEdges<randomWalkNeuron>(); $$ = new constantCommand<nodeBlueprint*>(n); }
		| RANDOMBLUEPRINTNODE '(' createNode ',' createNode ',' baseType ')' { nodeBlueprint *n = new randomBlueprintNode ( $3, $5, $7->evaluate()); $$ = new constantCommand<nodeBlueprint*>(n); }
		| STREAMOUTNODE '(' string ')'	{ nodeBlueprint *n = new nodeVirtualEdges<streamOutNode> ($3->evaluate()); $$ = new constantCommand<nodeBlueprint*>(n);}
		| STREAMINNODE '(' string ')'	{ nodeBlueprint *n = new nodeVirtualEdges<streamInNode> ($3->evaluate()); $$ = new constantCommand<nodeBlueprint*>(n);};
//		| RANDOMNODE { nodeBlueprint * n = new randomNode<baseType>(); $$ = new constantCommand<nodeBlueprint*>(n);}



createNode	: node
		| NODEVAR { $$ = new varCommand<nodeBlueprint *>(d_scanner->YYText()); }
		| node '(' ')'
      | node '(' argList ')' { $$ = new setNodeParameter ( $3, $1); };


createLink : link
	  | link '(' ')'
	  | link '(' argList ')' { $$ = new setEdgeParameter ( $3, $1); };



link	:  DELAYLINK '(' nodeDescriptor ')' {edgeBlueprint *l = new delayEdge($3->evaluate()); $$ = new constantCommand<edgeBlueprint*>(l); }
		| STDEDGEORD3 { edgeBlueprint *l = new stdEdgeOrd3(); $$ = new constantCommand<edgeBlueprint*>(l); }

		| SIGEDGE'(' nodeDescriptor ')' {edgeBlueprint *l = new sigEdge($3->evaluate()); $$ = new constantCommand<edgeBlueprint*>(l); }
		| SIGEDGE {edgeBlueprint *l = new sigEdge(); $$ = new constantCommand<edgeBlueprint*>(l); }

		| SIGEDGEORD3'(' nodeDescriptor ')' {edgeBlueprint *l = new sigEdgeOrd3($3->evaluate()); $$ = new constantCommand<edgeBlueprint*>(l); }
		| SIGEDGEORD3 {edgeBlueprint *l = new sigEdgeOrd3(); $$ = new constantCommand<edgeBlueprint*>(l); }

		| SIGEDGEPARAMS'(' nodeDescriptor ')' {edgeBlueprint *l = new sigEdgeParams($3->evaluate()); $$ = new constantCommand<edgeBlueprint*>(l); }
		| SIGEDGEPARAMS {edgeBlueprint *l = new sigEdgeParams(); $$ = new constantCommand<edgeBlueprint*>(l); }

//		| MEMBRANEPOTENTIALOFIFQ { edgeBlueprint *l = new membranePotentialOfIFQ(); $$ = new constantCommand<edgeBlueprint*>(l); }
//		| PHASEOFIFQ { edgeBlueprint *l = new phaseOfIFQ<baseType>(); $$ = new constantCommand<edgeBlueprint*>(l); }
//		| PHASEOFPCPO { edgeBlueprint *l = new phaseOfPCPOVirtual(); $$ = new constantCommand<edgeBlueprint*>(l); }
	//	| PHASEOFPCPOOPT { edgeBlueprint *l = new phaseOfPCPO<baseType>(); $$ = new constantCommand<edgeBlueprint*>(l); }
//		| RANDOMTARGETEDGE '(' nodeDescriptor ',' nodeDescriptor ')' {edgeBlueprint *l = new randomTarget < edgeVirtual> ($3->evaluate(), $5->evaluate()); $$ = new constantCommand<edgeBlueprint*>(l);  }
//		| RANDOMTARGETEDGE {edgeBlueprint *l = new weightedEdgeVirtual(); $$ = new constantCommand<edgeBlueprint*>(l); }
		| PULSECOUPLEEDGE'(' baseType ')' {edgeBlueprint *l = new stepEdge< edgeVirtual>   ($3->evaluate()); $$ = new constantCommand<edgeBlueprint*>(l); }
		| PULSECOUPLEDELAYEDGE'(' baseType ',' baseType ')' {edgeBlueprint *l = new pulsecoupleDelayEdge($3->evaluate(), $5->evaluate()); $$ = new constantCommand<edgeBlueprint*>(l); }


		| WEIGHTEDEDGE  { edgeBlueprint *l = new weightedEdgeVirtual(); $$ = new constantCommand<edgeBlueprint*>(l); }
		| EDGE { edgeBlueprint *l = new edgeVirtual(); $$ = new constantCommand<edgeBlueprint*>(l); }
		| STATICWEIGHTEDEDGE { edgeBlueprint *l = new staticWeightedEdgeVirtual();$$ = new constantCommand<edgeBlueprint*>(l);  }

//		| TESTEDGE '(' baseType ')'  { edgeBlueprint *l = new testEdge<baseType>($3->evaluate()); $$ = new constantCommand<edgeBlueprint*>(l); }
		| COMPONENT { $$ = new constantCommand<edgeBlueprint*>(new component<edgeVirtual>); }
		| COMPONENT_WEIGHTEDEDGE { $$ = new constantCommand<edgeBlueprint*>(new component<weightedEdgeVirtual>); }
		| COMPONENT_STATICWEIGHTEDEDGE { $$ = new constantCommand<edgeBlueprint*>(new component<staticWeightedEdgeVirtual>); }

		| STATICCOMPONENT { $$ = new constantCommand<edgeBlueprint*>(new staticComponent<edgeVirtual>); }
		| STATICCOMPONENT_WEIGHTEDEDGE { $$ = new constantCommand<edgeBlueprint*>(new staticComponent<weightedEdgeVirtual>); }
		| STATICCOMPONENT_STATICWEIGHTEDEDGE { $$ = new constantCommand<edgeBlueprint*>(new staticComponent<staticWeightedEdgeVirtual>); }


		| RANDOMTARGET { $$ = new constantCommand<edgeBlueprint*>(new randomTarget<edgeVirtual>); }
		| RANDOMTARGET_WEIGHTEDEDGE { $$ = new constantCommand<edgeBlueprint*>(new randomTarget<weightedEdgeVirtual>); }
		| RANDOMTARGET_STATICWEIGHTEDEDGE { $$ = new constantCommand<edgeBlueprint*>(new randomTarget<staticWeightedEdgeVirtual>); }

		| STEPEDGE { $$ = new constantCommand<edgeBlueprint*>(new stepEdge<edgeVirtual>); }
		| STEPEDGE_WEIGHTEDEDGE { $$ = new constantCommand<edgeBlueprint*>(new stepEdge<weightedEdgeVirtual>); }
		| STEPEDGE_STATICWEIGHTEDEDGE { $$ = new constantCommand<edgeBlueprint*>(new stepEdge<staticWeightedEdgeVirtual>); };



//		| KURAMOTOEDGE	 { edgeBlueprint *l = new kuramotoEdge<baseType>(); $$ = new constantCommand<edgeBlueprint*>(l);}



//boost::function<baseType(baseType)> r = baseTypeSin();
//boost::function<baseType(baseType)>(&sin);


random		: GAUSSIAN '(' baseType ',' baseType ')'
  { $$ = new bindExpression<baseType>(bind(&gslNoise::getGaussian ,bind(&expression<baseType>::evaluate, $3), bind(&expression<baseType>::evaluate, $5)));}
	| POWERLAW '(' baseType ',' baseType ')'
	{ $$ = new bindExpression<baseType>(bind(&gslNoise::getPowerLaw,bind(&expression<baseType>::evaluate, $3), bind(&expression<baseType>::evaluate, $5)));}
	| EXPONENTIAL '(' baseType ')'
	{ $$ = new bindExpression<baseType>(bind(&gslNoise::getExponential,bind(&expression<baseType>::evaluate, $3)));}
		| UNIFORM '(' baseType ',' baseType ')'
  { $$ = new bindExpression<baseType>(bind(&gslNoise::getUniform,bind(&expression<baseType>::evaluate, $3), bind(&expression<baseType>::evaluate, $5)));}
   		| BIMODAL '(' baseType ',' baseType ',' baseType ')'
  { $$ = new bindExpression<baseType>(bind(&gslNoise::getBimodal,		bind(&expression<baseType>::evaluate, $3),		bind(&expression<baseType>::evaluate, $5),		bind(&expression<baseType>::evaluate, $7))); }
		| POISSON '(' baseType ')'
  { $$ = new bindExpression<baseType>(bind(gslNoise::getPoisson, bind(&expression<baseType>::evaluate, $3))); }
		| POISSON '(' baseType ',' baseType ')'
 { $$ = new bindExpression<baseType>(bind(gslNoise::getPoisson, bind(&expression<baseType>::evaluate, $3), _E(baseType,$5))); }
		| CONSTANT '(' baseType ')'
 { $$ = new bindExpression<baseType>(bind(&gslNoise::getGaussian, _E(baseType, $3), 0)); }
		| FROMFILE '(' string ')'
	 {
		cyclicStream *cs = new cyclicStream ( $3->evaluate());
	$$ = new bindExpression <baseType>(bind (&cyclicStream::readDouble, cs));
};





//		| BIMODAL '(' baseType ',' baseType ',' baseType ')' { $$ = new bimodal<baseType>($3->evaluate(), $5->evaluate(), $7->evaluate());}

//		| BIMODAL '(' baseType ',' baseType ',' baseType ')' { $$ = new bimodal<baseType>($3->evaluate(), $5->evaluate(), $7->evaluate());}

 // Typ der Zufallszahlen aus einer Datei liest.
 //$$ = new gaussian<baseType>($3->evaluate(), $5->evaluate()); }


argList		: argList ',' baseType  { $1->push_back($3); }
		| argList ',' nodeDescriptor { $1->push_back(new convertToBaseType($3)); }
		| baseType { $$ = new expressionVector<baseType> (); $$->push_back($1); }
		| nodeDescriptor { $$ = new expressionVector<baseType> (); $$->push_back(new convertToBaseType($1)); };


randomList	: randomList ',' random { $1->push_back(((bindExpression<baseType> *)$3) -> _f); }
		| random { $$ = new vector < function <double () > >(); $$ -> push_back(((bindExpression<baseType> *)$1)->_f ); };


nodeDescriptor		: INT { $$ = new constantCommand<nodeDescriptor>(atoi(d_scanner->YYText())); }
      		| INTVAR { $$ = new varCommand<nodeDescriptor>(d_scanner->YYText()); }
		| nodeDescriptor '+' nodeDescriptor { $$ = new plusCommandnodeDescriptor<nodeDescriptor,nodeDescriptor>($1,$3); }
		| nodeDescriptor '*' nodeDescriptor { $$ = new timesCommandnodeDescriptor<nodeDescriptor,nodeDescriptor>($1,$3); }
		| nodeDescriptor '/' nodeDescriptor { $$ = new divideCommandnodeDescriptor<nodeDescriptor,nodeDescriptor>($1,$3); }
		| nodeDescriptor '%' nodeDescriptor { $$ = new modoloCommandnodeDescriptor<nodeDescriptor,nodeDescriptor>($1,$3); }
		| '(' INTTOKEN ')' baseType { $$ = new convertToInt($4); }
		| '-'nodeDescriptor { $$ = new timesCommandnodeDescriptor<nodeDescriptor,nodeDescriptor>(new constantCommand<nodeDescriptor>(-1),$2); } %prec UMINUS
		| GETRANDOMSEED '(' ')' { $$ = new bindExpression<nodeDescriptor> (bind(&gslNoise::getSeed)); }
		| statisticsNetworkCommandInt;




baseType		: DOUBLE { $$ = new constantCommand<baseType>(atof(d_scanner->YYText())); }
     		| DOUBLEVAR {$$ = new varCommand<baseType>(d_scanner->YYText()); }
		| '(' baseType ')' { $$ = $2;}
		| baseType '+' baseType {$$ = new plusCommandbaseType<baseType,baseType>($1,$3);}
	   | baseType '-' baseType {$$ = new minusCommandbaseType<baseType,baseType>($1,$3);}
		| baseType '*' baseType {$$ = new timesCommandbaseType<baseType,baseType>($1,$3);}
		| baseType '/' baseType {$$ = new divideCommandbaseType<baseType,baseType>($1,$3);}

		| baseType '+' nodeDescriptor  {$$ = new plusCommandbaseType<baseType,nodeDescriptor>($1,$3);}
		| baseType '-' nodeDescriptor  {$$ = new minusCommandbaseType<baseType,nodeDescriptor>($1,$3);}
		| baseType '*' nodeDescriptor  {$$ = new timesCommandbaseType<baseType,nodeDescriptor>($1,$3);}
		| baseType '/' nodeDescriptor  {$$ = new divideCommandbaseType<baseType,nodeDescriptor>($1,$3);}

		| nodeDescriptor '-' baseType  {$$ = new minusCommandbaseType<nodeDescriptor,baseType>($1,$3);}
		| nodeDescriptor '+' baseType  {$$ = new plusCommandbaseType<nodeDescriptor,baseType>($1,$3);}
		| nodeDescriptor '*' baseType  {$$ = new timesCommandbaseType<nodeDescriptor,baseType>($1,$3);}
		| nodeDescriptor '/' baseType  {$$ = new divideCommandbaseType<nodeDescriptor,baseType>($1,$3);}
		| LOG '(' baseType ')' 	{ $$ = new logCommandbaseType<baseType> ($3);}
		| EXP '(' baseType ')' 	{ $$ = new expCommandbaseType<baseType> ($3);}
		| SIN '(' baseType ')' 	{ $$ = new sinCommandbaseType<baseType> ($3);}
//		| nodeDescriptor { $$ = new convertToBaseType($1); }
		| '-' baseType { $$ = new timesCommandbaseType<baseType,baseType>(new constantCommand<baseType>(-1),$2); } %prec UMINUS
		| statisticsNetworkCommandBaseType
		// veraltet ohne Seg-Schutz:
//		| COMANDLINE '(' nodeDescriptor ')' { $$ = new constantCommand<baseType>((atof( commandLineArguments::arg[ $3->evaluate() + 1].c_str())   )); }
		| COMANDLINE '(' nodeDescriptor ')' { $$ = new constantCommand<baseType>( commandLineArguments::getDoubleArg( $3->evaluate() + 1)); }
      |	random   ;


NETWORK		: NETWORKVAR { $$ = command::retrieve<networkTemplate>(d_scanner->YYText()); };


statisticsNetworkCommandBaseType:  NETWORK '.' MEANDEGREE '(' ')' { $$ = BASETYPENETWORKFUNK(meanDegree, $1); }
		| NETWORK '.' MEANWEIGHT '(' ')' { $$= BASETYPENETWORKFUNK(meanWeight, $1);}
		| NETWORK '.' MEANPATHLENGTH '(' ')' { $$= BASETYPENETWORKFUNK(meanPathLength, $1); }
		| NETWORK '.' MEANCLUSTERING '(' ')' { $$= BASETYPENETWORKFUNK(meanClustering, $1); }
		| NETWORK '.' GETPARAM '(' nodeDescriptor ',' string ')' { $$= BASETYPENETWORKFUNK2 (getParam, $1, _E(nodeDescriptor, $5), _E(string, $7)); }
		| NETWORK '.' GETSTATE '(' nodeDescriptor ')' { $$= BASETYPENETWORKFUNK2 (getState, $1, _E(nodeDescriptor, $5),0 ); }
		| NETWORK '.' GETSTATE '(' nodeDescriptor ',' nodeDescriptor  ')' { $$= BASETYPENETWORKFUNK2 (getState, $1, _E(nodeDescriptor, $5),_E(nodeDescriptor, $7) ); };


statisticsNetworkCommandInt: NETWORK '.' DEGREE '(' nodeDescriptor ')'  {  $$ = INTNETWORKFUNK1( degree, $1, _E(nodeDescriptor, $5)); }
		| NETWORK '.' GETTARGET '(' nodeDescriptor ',' nodeDescriptor ')' {  $$ = INTNETWORKFUNK2 (getTarget, $1, _E(nodeDescriptor, $5), _E(nodeDescriptor, $7)); }
		| NETWORK '.' COUNTEDGES '(' createLink ')' { $$ = INTNETWORKFUNK1 ( countEdges , $1, _E(edgeBlueprint*, $5)); }
		| NETWORK '.' ADDNODE '(' createNode ')' { $$ = INTNETWORKFUNK1(addNode,$1,_E(nodeBlueprint*,$5)); }

		| NETWORK '.' COMPLETENETWORK   '(' nodeDescriptor ',' createNode ',' createLink ')' { $$ = INTNETWORKFUNK3(completeNetwork,$1,_E(nodeDescriptor,$5),_E(nodeBlueprint*,$7),_E(edgeBlueprint*,$9)); }
		| NETWORK '.' COMPLETENETWORK   '(' nodeDescriptor ')' { $$ = INTNETWORKFUNK3(completeNetwork,$1,_E(nodeDescriptor,$5), network::stdNode, network::stdEdge ); }
		| NETWORK '.' LATTICE '(' nodeDescriptor ',' nodeDescriptor ',' baseType ',' createNode ')'
  { $$ = INTNETWORKFUNK5(lattice,$1,_E(nodeDescriptor,$5),_E(nodeDescriptor,$7),_E(baseType,$9), _E(nodeBlueprint*,$11),networkTemplate::stdEdge); }
		| NETWORK '.' LATTICE '(' nodeDescriptor ',' nodeDescriptor ',' baseType ','createNode ',' createLink ')'
  { $$ = INTNETWORKFUNK5(lattice,$1,_E(nodeDescriptor,$5), _E(nodeDescriptor,$7), _E(baseType,$9), _E(nodeBlueprint*,$11), _E(edgeBlueprint*,$13)); }
		| NETWORK '.' TORUS '(' nodeDescriptor ',' nodeDescriptor ',' baseType ',' createNode ',' createLink ')'
  { $$ = INTNETWORKFUNK5(torus,$1,_E(nodeDescriptor,$5), _E(nodeDescriptor,$7), _E(baseType,$9), _E(nodeBlueprint*,$11), _E(edgeBlueprint*, $13)); }
		| NETWORK '.' TORUSNEARESTNEIGHBORS '(' nodeDescriptor ',' nodeDescriptor ',' baseType ',' createNode ',' createLink ')'
{ $$ = INTNETWORKFUNK5(torusNearestNeighbors,$1,_E(nodeDescriptor,$5), _E(nodeDescriptor,$7), _E(baseType,$9), _E(nodeBlueprint*,$11), _E(edgeBlueprint*, $13));  }



		| NETWORK '.' SIZE '(' ')' {  $$= INTNETWORKFUNK(size, $1); };


statisticsNetworkCommandBool: NETWORK '.' ISCONNECTED '(' ')' { $$ = BOOLNETWORKFUNK(isConnected, $1);}
		| NETWORK '.' ISDIRECTED '(' ')' { $$ = BOOLNETWORKFUNK(isDirected, $1);}
		| NETWORK '.' ISLINKED '(' nodeDescriptor ',' nodeDescriptor ')' {  $$ = BOOLNETWORKFUNK2 (isLinked, $1, _E(nodeDescriptor, $5), _E(nodeDescriptor, $7)); };




bool	: '(' bool ')' { $$ = $2; }
		| nodeDescriptor EQUAL nodeDescriptor {$$ = new equalCommandbool<nodeDescriptor,nodeDescriptor>($1,$3); }
		| baseType EQUAL baseType {$$ = new equalCommandbool<baseType,baseType>($1,$3); }
		| nodeDescriptor NEQUAL nodeDescriptor {$$ = new nequalCommandbool<nodeDescriptor,nodeDescriptor>($1,$3); }
		| baseType NEQUAL baseType {$$ = new nequalCommandbool<baseType,baseType>($1,$3); }
		| baseType NEQUAL nodeDescriptor  {$$ = new nequalCommandbool<baseType,nodeDescriptor>($1,$3); }
		| baseType NEQUAL baseType  {$$ = new nequalCommandbool<baseType,baseType>($1,$3); }


		| baseType '<' baseType {$$ = new lessCommandbool<baseType,baseType>($1,$3); }
		| nodeDescriptor '<' nodeDescriptor {$$ = new lessCommandbool<nodeDescriptor,nodeDescriptor>($1,$3); }
		| nodeDescriptor '<' baseType {$$ = new lessCommandbool<nodeDescriptor,baseType>($1,$3); }
		| baseType '<' nodeDescriptor {$$ = new lessCommandbool<baseType,nodeDescriptor>($1,$3); }

		| nodeDescriptor '>' nodeDescriptor {$$ = new greaterCommandbool<nodeDescriptor,nodeDescriptor>($1,$3); }
		| nodeDescriptor '>' baseType {$$ = new greaterCommandbool<nodeDescriptor,baseType>($1,$3); }
		| baseType '>' nodeDescriptor {$$ = new greaterCommandbool<baseType,nodeDescriptor>($1,$3); }
		| baseType '>' baseType {$$ = new greaterCommandbool<baseType,baseType>($1,$3); }

		| nodeDescriptor GREATEREQUAL nodeDescriptor {$$ = new greaterEqualCommandbool<nodeDescriptor,nodeDescriptor>($1,$3); }
		| nodeDescriptor GREATEREQUAL baseType {$$ = new greaterEqualCommandbool<nodeDescriptor,baseType>($1,$3); }
		| baseType GREATEREQUAL nodeDescriptor {$$ = new greaterEqualCommandbool<baseType,nodeDescriptor>($1,$3); }
		| baseType GREATEREQUAL baseType {$$ = new greaterEqualCommandbool<baseType,baseType>($1,$3); }

		| nodeDescriptor LESSEQUAL nodeDescriptor {$$ = new lessEqualCommandbool<nodeDescriptor,nodeDescriptor>($1,$3); }
		| nodeDescriptor LESSEQUAL baseType {$$ = new lessEqualCommandbool<nodeDescriptor,baseType>($1,$3); }
		| baseType LESSEQUAL nodeDescriptor {$$ = new lessEqualCommandbool<baseType,nodeDescriptor>($1,$3); }
		| baseType LESSEQUAL baseType {$$ = new lessEqualCommandbool<baseType,baseType>($1,$3); }

		| bool AND bool {$$ = new andCommandbool<bool,bool>($1,$3); }
		| bool OR bool { $$ = new orCommandbool<bool,bool>($1,$3); }
		| bool EQUAL bool  { $$ = new equalCommandbool<bool, bool > ( $1, $3	); }
		| NOT bool { $$ = new notCommand($2); }
		| BOOLONE { $$ = new constantCommand<bool>(1); }
		| BOOLZERO { $$ = new constantCommand<bool>(0); }
		| statisticsNetworkCommandBool;
