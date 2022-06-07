#include "../include/cell.h"

Cell::Cell()
{
    atom = new Atom[1];
    snapshot_index = 0;
    snapshot_time = snapshot_index * INPUT.frame_dt ; // ps
    cell_x = -1;
    cell_y = -1;
    cell_z = -1;
    volume = cell_x * cell_y * cell_z;
    atom_num = 0;

//==========================================================
// atom mass list 
//==========================================================
    mass_dict["H"] = 1.00782504;
    mass_dict["D"] = 2.01565008;
    mass_dict["He"] = 4.00260324;
    mass_dict["Li"] = 7.016003;
    mass_dict["Be"] = 9.0121822;
    mass_dict["B"] = 11.0093054;
    mass_dict["C"] = 12.0;
    mass_dict["N"] = 14.003074;
    mass_dict["O"] = 15.9949146;
    mass_dict["F"] = 18.9984032;
    mass_dict["Ne"] = 19.9924356;
    mass_dict["Na"] = 22.9897677;
    mass_dict["Mg"] = 23.9850423;
    mass_dict["Al"] = 26.9815386;
    mass_dict["Si"] = 27.9769271;
    mass_dict["P"] = 30.973762;
    mass_dict["S"] = 31.9720707;

    mass_dict["Ca"] = 39.9625906;
    mass_dict["Cu"] = 62.9295989;
    mass_dict["W"] = 183.950928;
}


void Cell::clean()
{
	delete[] this->atom;
}

Cell::~Cell()
{
    //delete[] this->atom;
}
