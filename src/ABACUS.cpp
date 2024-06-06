#include "../include/cellFile.h"
#include "../include/input.h"
#include "../include/global_functions.h" 



bool CellFile::ReadGeometry_ABACUS( Cell &cel, ifstream &ifs )
{
    string useless;
    string atom_name;
    double x, y, z, LATTICE_CONSTANT;
    // init cell length
    //cel.cell_x = INPUT.cell_dim_x;
    //cel.cell_y = INPUT.cell_dim_y;  
    //cel.cell_z = INPUT.cell_dim_z;
    READ_VALUE(ifs, useless);
    ifs >> useless >> LATTICE_CONSTANT;
    READ_VALUE(ifs, useless);
    READ_VALUE(ifs, useless);
    double LATTICE_VECTORS_x, LATTICE_VECTORS_y, LATTICE_VECTORS_z;
    READ_VALUE(ifs, LATTICE_VECTORS_x);
    ifs >> useless >> LATTICE_VECTORS_y;
    READ_VALUE(ifs, useless);   
    ifs >> useless >> useless >> LATTICE_VECTORS_z;
    READ_VALUE(ifs, useless);   
    cel.cell_x = LATTICE_VECTORS_x * LATTICE_CONSTANT;
    cel.cell_y = LATTICE_VECTORS_y * LATTICE_CONSTANT; 
    cel.cell_z = LATTICE_VECTORS_z * LATTICE_CONSTANT;
    READ_VALUE(ifs, useless); 
    READ_VALUE(ifs, useless); 
    READ_VALUE(ifs, useless); 
    READ_VALUE(ifs, useless); 
    // read atom number
    //READ_VALUE(ifs, cel.atom_num);
    cel.atom_num = INPUT.total_num_atom;
    // read atom name and position
    delete[] cel.atom;
	cel.atom = new Atom[cel.atom_num];
    for(int ia=0; ia<cel.atom_num; ++ia)
    {
        ifs >> useless >> atom_name >> x >> y;
        READ_VALUE(ifs, z);
        //cout << useless << "  " << atom_name << endl;
        cel.atom[ia].name = atom_name;
        for (auto atom_mass:cel.mass_dict)
        {
            if (atom_mass.first == cel.atom[ia].name) {cel.atom[ia].mass = atom_mass.second;}
        }
        //cout << x << " " << y << " " << z << endl;
        cel.atom[ia].x = x;
        cel.atom[ia].y = y;
        cel.atom[ia].z = z;
    }
    //READ_VALUE(ifs, useless); 
    //READ_VALUE(ifs, useless); 
    return 0;
}
