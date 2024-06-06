#include "../include/cellFile.h"
#include "../include/input.h"
#include "../include/global_functions.h" 


bool CellFile::ReadGeometry_LAMMPS( Cell &cel, ifstream &ifs )
{
    string useless;
    int index, type;
    double x, y, z;
    double xlo, xhi, ylo, yhi, zlo, zhi;
    // (1) read atom numbers
	getline(ifs, useless); 
	getline(ifs, useless);
    getline(ifs, useless);
    READ_VALUE(ifs, cel.atom_num);
    READ_VALUE(ifs, useless);
   
    // (2) read in cell x y z
    ifs >> xlo;
    READ_VALUE(ifs, xhi);
    cel.cell_x = xhi - xlo;
    ifs >> ylo;
    READ_VALUE(ifs, yhi);
    cel.cell_y = yhi - ylo;
    ifs >> zlo;
    READ_VALUE(ifs, zhi);
    cel.cell_z = zhi - zlo;
    cel.volume = cel.cell_x * cel.cell_y * cel.cell_z;
    // (3) read id and coord
    delete[] cel.atom;
	cel.atom = new Atom[cel.atom_num];
    READ_VALUE(ifs, useless);
    for(int ia=0; ia<cel.atom_num; ++ia)
	{
        ifs >> index >> type >> x >> y;
        READ_VALUE(ifs, z);
        //cout << "idx=" << index << " type=" << type << " x=" << x << " y=" << y << " z=" << z << endl;
        cel.atom[ia].index = index;
        cel.atom[ia].type = type;
        if (type == 1) {cel.atom[ia].name = INPUT.atom_type1;}
        if (type == 2) {cel.atom[ia].name = INPUT.atom_type2;}
        if (type == 3) {cel.atom[ia].name = INPUT.atom_type3;}
        if (type == 4) {cel.atom[ia].name = INPUT.atom_type4;}
        if (type == 5) {cel.atom[ia].name = INPUT.atom_type5;}
        if (type == 6) {cel.atom[ia].name = INPUT.atom_type6;}
        if (type == 7) {cel.atom[ia].name = INPUT.atom_type7;}
        if (type == 8) {cel.atom[ia].name = INPUT.atom_type8;}
        if (type == 9) {cel.atom[ia].name = INPUT.atom_type9;}
        if (type == 10) {cel.atom[ia].name = INPUT.atom_type10;}
        if (type == 11) {cel.atom[ia].name = INPUT.atom_type11;}
        if (type == 12) {cel.atom[ia].name = INPUT.atom_type12;}
        if (type == 13) {cel.atom[ia].name = INPUT.atom_type13;}
        if (type == 14) {cel.atom[ia].name = INPUT.atom_type14;}
        if (type == 15) {cel.atom[ia].name = INPUT.atom_type15;}
        if (type == 16) {cel.atom[ia].name = INPUT.atom_type16;}
        if (type == 17) {cel.atom[ia].name = INPUT.atom_type17;}
        if (type == 18) {cel.atom[ia].name = INPUT.atom_type18;}
        if (type == 19) {cel.atom[ia].name = INPUT.atom_type19;}
        if (type == 20) {cel.atom[ia].name = INPUT.atom_type20;}
        if (type == 21) {cel.atom[ia].name = INPUT.atom_type21;}
        if (type == 22) {cel.atom[ia].name = INPUT.atom_type22;}
        if (type == 23) {cel.atom[ia].name = INPUT.atom_type23;}
        if (type == 24) {cel.atom[ia].name = INPUT.atom_type24;}
        if (type == 25) {cel.atom[ia].name = INPUT.atom_type25;}

        //cout << cel.atom[ia].name << endl;
        for (auto atom_mass:cel.mass_dict)
        {
            //cout << atom_mass.first << ":" << atom_mass.second << endl;
            if (atom_mass.first == cel.atom[ia].name) {cel.atom[ia].mass = atom_mass.second;}
        }
        cel.atom[ia].x = x - xlo;
        cel.atom[ia].y = y - ylo;
        cel.atom[ia].z = z - zlo;
        
    }
    return 0;
}
