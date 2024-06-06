#ifndef CELLFILE_H
#define CELLFILE_H
#include "cell.h"
#include "global_functions.h" 


class CellFile : public Cell 
{
public: 	
	CellFile();
	~CellFile();
    static bool ReadGeometry( Cell &cel );

private: 
    static bool ReadGeometry_LAMMPS( Cell &cel, ifstream &ifs );
    static bool ReadGeometry_CP2K( Cell &cel, ifstream &ifs );
    static bool ReadGeometry_ABACUS( Cell &cel, ifstream &ifs );
    static ifstream ifs;
    static bool file_open;
};
#endif