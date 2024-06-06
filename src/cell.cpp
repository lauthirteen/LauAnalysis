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

    mass_dict["In"] = 114.818;
    mass_dict["Sb"] = 121.760;

    mass_dict["Ca"] = 39.9625906;
    mass_dict["Cu"] = 62.9295989;
    mass_dict["W"] = 183.950928;
    mass_dict["V"] = 50.94;
    mass_dict["Ti"] = 47.88;
    
    // PTQ8-Y6
    mass_dict["P1"] = 19.000;
    mass_dict["P2"] = 25.028;
    mass_dict["P3"] = 24.020;
    mass_dict["P4"] = 16.000;
    mass_dict["P5"] = 37.038;
    mass_dict["P6"] = 26.020;
    mass_dict["P7"] = 32.060;
    mass_dict["P8"] = 14.010;
    mass_dict["P9"] = 26.020;
    mass_dict["P10"] = 27.044;
    mass_dict["P11"] = 29.060;
    mass_dict["P12"] = 28.052;
    mass_dict["P13"] = 43.086;
    mass_dict["P14"] = 26.036;
    mass_dict["P15"] = 24.020;
    mass_dict["P16"] = 27.028;
    mass_dict["P17"] = 26.020;
    mass_dict["P18"] = 16.000;
    mass_dict["P19"] = 27.044;
    mass_dict["P20"] = 28.052;
    mass_dict["P21"] = 29.060;
    mass_dict["P22"] = 19.000;
    mass_dict["P23"] = 25.028;
    mass_dict["P24"] = 32.060;
    // PTQ10-Y6
    mass_dict["T1"] =  19.000;
    mass_dict["T2"] =  25.028;
    mass_dict["T3"] =  24.020;
    mass_dict["T4"] =  16.000;
    mass_dict["T5"] =  37.038;
    mass_dict["T6"] =  26.020;
    mass_dict["T7"] =  32.060;
    mass_dict["T8"] =  14.010;
    mass_dict["T9"] =  26.020;
    mass_dict["T10"] = 27.044;
    mass_dict["T11"] = 29.060;
    mass_dict["T12"] = 28.052;
    mass_dict["T13"] = 43.086;
    mass_dict["T14"] = 19.000;
    mass_dict["T15"] = 25.028;
    mass_dict["T16"] = 24.020;
    mass_dict["T17"] = 27.028;
    mass_dict["T18"] = 26.020;
    mass_dict["T19"] = 16.000;
    mass_dict["T20"] = 27.044;
    mass_dict["T21"] = 28.052;
    mass_dict["T22"] = 29.060;
    mass_dict["T23"] = 26.036;
    mass_dict["T24"] = 32.060;
}


void Cell::clean()
{
	delete[] this->atom;
}

Cell::~Cell()
{
    //delete[] this->atom;
}
