


#include "nodeImplement.h"

#include "edge.h"

namespace conedy {


	 baseType edge::getTargetState() { return node::theNodes[targetNumber]->getState(); }




}
