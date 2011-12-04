#! /usr/bin/env python
# -*- coding: utf-8 -*-

import conedy as co


N = co.network()

nodeblueprint = co.gaussianRoessler()
co.set ("gaussianRoessler_a" , 0.165)
co.set ("gaussianRoessler_b" , 0.2)
co.set ("gaussianRoessler_c" , 10.0)
co.set ("gaussianRoessler_sigmaNoise" , 0.1)


N.cycle(100, 4, nodeblueprint,  co.weightedEdge(0.1))
N.rewire (0.1)

print "clustering coefficient:" + str (N.meanClustering())
print "mean path length:" + str (N.meanPathLength())

if( N.isConnected() ):
	N.betweennessCentrality("N.betweenness")
	N.closenessCentrality("N.closeness")

N.randomizeParameter( "gaussianRoessler_omega", co.uniform(0.8,1.2) ) 
N.randomizeStates(nodeblueprint, co.uniform (-0.1,0.1), co.uniform (-0.1,0.1), co.uniform (-0.1, 0.1))                           

N.evolve(0.0, 100.0)

N.observeTime( "output_Roessler" )
N.observeAll( "output_Roessler" , co.component(2))
co.set ("samplingTime" , 0.01)

N.evolve( 100.0, 200.0 )

