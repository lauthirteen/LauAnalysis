#include "../include/cellFile.h"
#include "../include/input.h"
#include "../include/global_functions.h" 

ifstream CellFile::ifs;
bool CellFile::file_open=false;

CellFile::CellFile()
{
}

CellFile::~CellFile()
{
}

bool CellFile::ReadGeometry( Cell &cel )
{
  	if (INPUT.traj_type=="LAMMPS")
	{
        
        if (file_open == false)
        {
            stringstream ss;
            ss << INPUT.traj_path;
            cout << " ReadGeometry : " << ss.str() << endl;
            ifs.open(ss.str().c_str());
            file_open = true;
        }
		return ReadGeometry_LAMMPS(cel, ifs);
	}
  	if (INPUT.traj_type=="CP2K" or INPUT.traj_type=="XYZ")
	{
        
        if (file_open == false)
        {
            stringstream ss;
            ss << INPUT.traj_path;
            cout << " ReadGeometry : " << ss.str() << endl;
            ifs.open(ss.str().c_str());
            file_open = true;
        }
		return ReadGeometry_CP2K(cel, ifs);
	}
    return false;
}
