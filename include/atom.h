#ifndef ATOM_H
#define ATOM_H
#include "global_functions.h"

class Atom
{
public: 
	Atom();
	~Atom();
public:
    int index;
    int type;
    string name;
    double mass;
    double x;
    double y;
    double z;
};

#endif
