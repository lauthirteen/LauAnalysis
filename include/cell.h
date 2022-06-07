#ifndef CELL_H
#define CELL_H

#include "atom.h"
#include "input.h"
#include <map>

class Cell
{
	public: 
	
	Cell();
	~Cell();

	public:
    Atom *atom; // atom class
    double cell_x;  // lattice vectors
    double cell_y;  // lattice vectors
    double cell_z;  // lattice vectors
    double volume; // volume of cell
    int atom_num;
    int snapshot_index;
	double snapshot_time;
    void clean();
    void get_mass();

    map <string, float> mass_dict;
    //void read_pos(ifstream &ifs);

};

#endif