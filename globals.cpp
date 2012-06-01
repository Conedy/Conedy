#include "globals.h"

int typeInteger(int) { return 0;}
int typeInteger(double) { return 1;}
int typeInteger(string) { return 2;}
#ifndef PYTHON
	int typeInteger(bool) { return 3;}
#else
	int typeInteger(bool) { return 0;}
#endif
int typeInteger(float) { return 4;}
int typeInteger(long double) { return 5;}

map <string, void*> globals::value;
map <string, int> globals::type;
