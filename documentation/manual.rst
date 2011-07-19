manual
======



networks
--------




Neurosim depends on his own network class in order to apply the different available integration schemes. 



For the creation and manipulation of the networks, elementary functions are supplied, which can be combined in an arbitrary sequence. To create an empty network as a starting point, conedy accepts the following syntax::
   >>> import conedy as co
   >>> net = co.network()

In addition, it is possible to import networks from networkx and to create them from files containing graphML, whitespace-seperated txt-files matrices or adjacency lists. 


blueprints
----------

Most of the functions which manipulate networks accept node and edge blueprints as arguments. These are simple python classes, which specify node type and parameters of the specific a node. All nodes and edges which are then added to a networks are copies of the blueprints. Let's see a simple example, which adds a single node to the network. We first create the blueprint for a node with the dynamics of the standard logistic map (defined by x' = r x ( 1 - 1)
::   
   >>> nodeblueprint = co.logisticMap()
   >>> net.addNode(nodeblueprint)

and add a copy of this blueprint to the network::
   >>> net.clear()


#   >>> #net.addNode(nodeblueprint)

The blueprint can then savely be deleted by python without any influence on the network. In similar way blueprints for edges can be created. Functions in conedy which create at the same time nodes and edges will usually accept two blueprints as optional parameters. The following example will add a directed random network of 100 logistic maps, where two nodes are connected with a propability of 0.1 by a weighted edge::

   >>> edgeblueprint = ns.weightedEdge()
   >>> net.randomNetwork(100, 0.1, nodeblueprint, edgeblueprint)


When created in the described way, conedy will use the standard value for the parameter r of the map, which is 3.58 (see `logisticMap<reference/nodes/LogisticMap>)`. In case you want a different parameter, conedy offers to distinct possibilities: You can assign a different value to the blueprint, telling conedy to not use the standard parameter:
::
   >>> nodeblueprint = ns.logisticMap(3.4)
   >>> net.addNode(nodablueprint)

Alternatively, you can assign a different value to the standard parameter for the duration of your script::

   >>> set("logisticMap_r", 3.4)

Note that in this way all nodes in the network, which use the standard parameter will be affected even if the standard parameter is changed after node creation, as they all share the same memory for the parameter. 

memory usage
------------

Let's consider a more complicated node like the fitzHughNagumo neuron `Fitzhughnagumo<reference/nodes/Fitzhughnagumo>)`, which has 4 parameter in our notation. We want to build a network of 1000 neurons, from which 500 use the standard parameters and another 500 use a different parameter set::

   >>> standardFitzhughnagumo = ns.fitzhughnagumo ()
   >>> differentFitzhughnagumo = ns.fitzhughnagumo (0.15, 0.015, 0.01, 0.0)
   >>>
   >>> for i in range (0,499):
   >>>   net.addNode(standardFitzhughnagumo)
   >>> for i in range (0,499):
   >>>   net.addNode(differentFitzhughnagumo)

Neurosim will save for this network for every node just the number of the parameter set used instead of the actual parameters. This saves memory in this configuration as only one integer is needed for every node compared to 4 double for all parameter. For configurations with differing parameter for every node (i.e. randomly chosen) however, this may lead to an increased memory usage. For edges, which for large networks usually are responsible for most of the memory consumption, the following classes are available which handle coupling weights in different ways::

 - edge                    all coupling strengths are set to 1
 - weightedEdges           edge with an arbitrary couping strength
 - staticWeightedEdge      all edges of this kind share the same coupling strength

virtual vs static edges
-----------------------


In many situations it is not neccesarry that a node of a certain kind has edges of different kind. As this is in conedy implemented by virtual functions, the needed v-table will consume memory.  In addition whenever a node during numerical integration requires the state of a connected node, virtual function calls have to be made, which are -- depending on the circumstances -- may be unneccessaryily slow. Neurosim offers the possibility to create so called static nodes for which both the kind of outgoing edges of an node and the node type of the target nodes is specified at compile time.  For these nodes, no virtual function calls have to be made during integration. For cases with many unweighted edgse, the memory consumption of static nodes on 64 bit machines (compared to virtual nodes) is reduced by a factor of 4!. This is because in virtual nodes in addition to the target node number (4 byte) and the v-table (8 byte) most compiler will leave another 4 bytes unused due to alignment. The following table shows memry usage of edgse in conedy for 64 bit.

edgetype            static          virtual functions
=====               ========        =================
edge                    4                 16
staticWeightedEdge      4                 16
weightedEdge            16                24




observing
---------

After having created the network, you will want to tell conedy which features of the network should be observed during integration. Usually, you will call the evolve-function, which evolves the dynamical state of all nodes in the network. In perdiodic intervals, a snapshot of all observed features is performed. The duration between snapshots can be controlled by setting the global variable "dynNetwork_ioNodeDt"::

   ns.set("dynNetwork_ioNodeDt", 0.01)

Additionally, you can issue a snapshot manually::
   
   ns.snapshot()

This can be usefull, if you want to observe your dynamical system at non-liner intervalls. Neurosim keeps lists for every file you wish to write to. Whenever conedy writes data to files, it creates a new line in all these files and creates a whitespace-seperated line with all elements of this list. Observable features are expressed by edges to nodes. You can use standard unweighted edges, which get the same data from the node as a coupled node would. Or more complicated nodes, which calculate same observable of the node first. E.g. if you want to observe the first three dynamical varible of node number 0, you would use a component-edge, and use the following syntax. For example if you want conedy to create a file named "node0", which contains the first dynamical variables of node 0, you would use component-edges::


   net.observe(0,"node0", ns.component(0))
   net.observe(0,"node0", ns.component(1))
   net.observe(0,"node0", ns.component(2))

These columns of the created files are ordered in the way, the corresponding observe commands where called. The created files remain open until, a call of removeObserver or clear to the network. Therefore, you can without problem evolve, change some parameter and evolve further in time. The following global variables, allow to specify further how the data is written:

 - streamOutNode_compress     if this is set to 1.0, the outputed files will automatically be compressed with bzip2.
 - streamOutNode_append       if set to 1, data is appended to files instead of creating files new.
 - streamOutNode_precision    sets the number of counting digits for written floats.



adding new nodes
----------------

If the dynamics you want to investigate is not available in conedy, you may want to a new node.  A short file containing the desired differential equation and standard parameters has to be created and put into a directory which is specified in the config.h file. Neurosim needs to be recompiled afterwards, which will be automatically issued on the next import to python whenever a file in this directory is modified or added. The syntax of the needed file will in the following be eplained following the example of a roessler oscillator.


::
   [roessler]

Specify in square brackets the name of the node you wish to add. Be sure to avoid name collision with previos nodes. Also be sure that the name of the node is a valid python token, for example, it should not begin with a number.

::
   dimension = 3

Specify the number of dynamical variables of the node (e.g. the number of differential equations)

::
   paramreter = 4

Specify the number of needed parameters for the node.


::
   parametername1 = omega
   standardvalue1 = 0.89
   parametername2 = a
   standardvalue2 = 0.165
   parametername3 = b
   standardvalue3 = 0.2
   parametername4 = c
   standardvalue4 = 10.0

Chose for every parameter a name and a standard value.

::
   integrator = stdOdeIntegrator
   dynamics=
      dxdt[0]= -omega() * x[1] - x[2]+ getCouplingSum() - weightSum()*x[0];
      dxdt[1]= x[0] + a() * x[1];
      dxdt[2]=b() + x[2] *( x[0] - c() );

Choose an integrator, which handles the dynamics of the node. The form of the following dynamics entry depends on this as it describes e.g. a map or a differential equation, depending on the context. The following functions are accesible for all integrators:

getCouplingSum()
 - the sum of all states of all coupled nodes

weightSum()
 - the sum of all connection weights on incomming edges

note
----
diffusive coupling between nodes  can easily be expressed with these two functions:: 

        dxdt[0] = ....         +    getCouplingSum() - weightSum * x[0]

Neurosim offers the following integration schemes:

mapNode
-------

Iteration of a dynamical map. The dynamics field should define { xprime[i]  | i < dimension} in dependence of { x[i] | i < dimension }

Example::
   xprime[0] = r() * x[0] * (-x[0] + 1)

stdOdeIntegrator                   
----------------

simple integration by runge-kutta of 4th order. The dynamics field should define { dxdt[i]  | i < dimension} in dependence of { x[i] | i < dimension }

Example::
   dxdt[0]= -omega() * x[1] - x[2]+ getCouplingSum() - weightSum()*x[0];
   dxdt[1]= x[0] + a() * x[1];
   dxdt[2]=b() + x[2] *( x[0] - c() );

gslOdeIntegrator
----------------

Neurosim is linked against the gnu scientific library www.gnu.org/software/gsl/ and thus allows you to use their algorithms for numerical integration of ordinary differential equations. At the moment only those algorithm are supported, which make no use of the jacobian. To dynamics field has to defined as for stdOdeIntegrator. At run-time a specific stepping function can be choosen by setting "gslOdeNode_stepType" to one of the following values:

-- gsl_odeiv_step_rk2;
-- gsl_odeiv_step_rk4;
-- gsl_odeiv_step_rkf45;  
-- gsl_odeiv_step_rkck;   
-- gsl_odeiv_step_rk8pd;
-- gsl_odeiv_step_rk2imp;
-- gsl_odeiv_step_gear1;
-- gsl_odeiv_step_gear2; 

Example::
    ns.set("gslOdeNode_stepType","gsl_odeiv_step_rkf45")

See the documentation of the gsl for specific information.

stdSdeIntegrator
----------------

Justus fragen, was er da gemacht hat.


pulseCoupledOscillator
----------------------
Integration of an oscillator with a cyclic phase $\phi \in [0,1]$. Whenever at time $t_f$ the phase reaches 1, the phase of all adjacent oscillators will be changed according to the phase response curve:
        $\phi (t_f^+ ) = \phi(t_f) + Delta(\phi(t_f))$
        
The dynamcs field should define define the phase response delta in dependence of phi.
Example (Mirollo strogatz)::








