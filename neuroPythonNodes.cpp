#include "neuroPythonNodes.h"


#include <boost/python.hpp>
#include <boost/python/module.hpp>
#include <boost/python/def.hpp>
#include <boost/python/suite/indexing/vector_indexing_suite.hpp>

#include "docstringsNodes.h"

void revealNodesToPython ()
{
#include "generatedNeuroPython.cpp"

}
