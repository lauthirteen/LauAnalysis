#include "../include/cellFile.h"
#include "../include/input.h"
#include "../include/global_functions.h" 


bool CellFile::ReadGeometry_CP2K( Cell &cel, ifstream &ifs )
{
    string useless;
    string atom_name;
    double x, y, z;
    // init cell length
    cel.cell_x = INPUT.cell_dim_x;
    cel.cell_y = INPUT.cell_dim_y;  
    cel.cell_z = INPUT.cell_dim_z;
    // read atom number
    READ_VALUE(ifs, cel.atom_num);
    READ_VALUE(ifs, useless);
    // read atom name and position
    delete[] cel.atom;
	cel.atom = new Atom[cel.atom_num];
    for(int ia=0; ia<cel.atom_num; ++ia)
    {
        ifs >> atom_name >> x >> y;
        READ_VALUE(ifs, z);
        cel.atom[ia].name = atom_name;
        for (auto atom_mass:cel.mass_dict)
        {
            if (atom_mass.first == cel.atom[ia].name) {cel.atom[ia].mass = atom_mass.second;}
        }
        cel.atom[ia].x = x;
        cel.atom[ia].y = y;
        cel.atom[ia].z = z;
    }
    return 0;
}
