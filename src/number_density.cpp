#include "../include/number_density.h"
#include "../include/global_functions.h"    // global functions
#include "../include/cell.h"
#include "../include/cellFile.h"

NumberDensity::NumberDensity(){}
NumberDensity::~NumberDensity(){}

void NumberDensity::Routine()
{
    cout << "calculate the number density of atom. Jianchuan Liu 20220609" << endl;
	// set 'delta r' in real space from input file.
	this->dr = INPUT.dr;
	assert(dr>0.0);
	// where a is the lattice constant of a cubic box.
	this->rcut = INPUT.rcut;
	assert(rcut>0.0);
	// number of radial mesh grids.
	this->nmesh = int(rcut / dr) +  1;
	ofs_running << " dr = " << dr << " Angstrom" << endl;
	ofs_running << " rcut = " << rcut << " Angstrom" << endl;
	ofs_running << " nmesh = " << nmesh << endl;

    double * number_density = new double[nmesh];
    for(int i=0; i<nmesh; ++i) number_density[i] = 0;
    this->count_geometry_number=0;
    // create the file
    stringstream ss1;
    ofstream ofs;
	ss1 << INPUT.direction << "_" << INPUT.atom_name1 << "_number_density.dat";
	ofs.open(ss1.str().c_str());

    CellFile cel;

    for(int igeo=1; igeo<=INPUT.end_frame; ++igeo)
    {
        // read pos
        CellFile::ReadGeometry( cel );
        cel.snapshot_time = igeo * INPUT.frame_dt;
        cout << "igeo=" << igeo << " time=" << cel.snapshot_time << endl;
        if (igeo < INPUT.begin_frame || (igeo - INPUT.begin_frame)  % INPUT.interval_frame != 0) 
        {
            //cout << "1111111111111111111111111" << endl;
            continue;
        }

        // x direction
        if (INPUT.direction == "x")
        {
            CoumpteDensityX(cel, number_density);
            count_geometry_number += 1;
        }
        // y direction
        if (INPUT.direction == "y")
        {
            CoumpteDensityY(cel, number_density);
            count_geometry_number += 1;
        }
        // z direction
        if (INPUT.direction == "z")
        {
            CoumpteDensityZ(cel, number_density);
            count_geometry_number += 1;
        }

    }
    // average
    double avg;
    for(int i=0; i<nmesh; ++i)
    {
        avg = number_density[i]/count_geometry_number;
        ofs << (i+0.5)*dr << " " << avg << endl;
    }
    //
    delete[] number_density;
}

void NumberDensity::CoumpteDensityX(const Cell &cel, double *number_density)
{
    for (int ia=0; ia<cel.atom_num; ++ia)
    {
        if (cel.atom[ia].name == INPUT.atom_name1)
        {
            which = int(cel.atom[ia].x / dr);
            number_density[which] += 1.00;
            //cout << which << endl;
        }
    }
}

void NumberDensity::CoumpteDensityY(const Cell &cel, double *number_density)
{
    for (int ia=0; ia<cel.atom_num; ++ia)
    {
        if (cel.atom[ia].name == INPUT.atom_name1)
        {
            which = int(cel.atom[ia].y / dr);
            number_density[which] += 1.00;
            //cout << which << endl;
        }
    }
}

void NumberDensity::CoumpteDensityZ(const Cell &cel, double *number_density)
{
    for (int ia=0; ia<cel.atom_num; ++ia)
    {
        if (cel.atom[ia].name == INPUT.atom_name1)
        {
            which = int(cel.atom[ia].z / dr);
            number_density[which] += 1.00;
            //cout << which << endl;
        }
    }
}