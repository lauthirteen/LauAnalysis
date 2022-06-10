#include "../include/global_functions.h"    // global functions
#include "../include/input.h"   // input prameters
#include "../include/atom.h"
#include "../include/cell.h"
#include "../include/cellFile.h"
#include "../include/conver2PDB.h"
#include "../include/number_density.h"
#include "../include/water.h"


// example：./LauAnalysis INPUT

int main(int argc, char **argv)
{

    #ifdef __MPI
        MPI_Init(&argc,&argv);
        MPI_Comm_size(MPI_COMM_WORLD, &NPROC);
        MPI_Comm_rank(MPI_COMM_WORLD, &RANK);
    #endif

	//cout << "after initialization of MPI" << endl;

	stringstream ss;
	ss << "running" << RANK << ".log";
	ofs_running.open(ss.str().c_str());

	// read in the parameters.
	// INPUT has been generated in input.cpp
    char ** input = argv;
    string input_file;
    
    bool find = false;
    ++input;
   
    input_file = *input;

	INPUT.Init(input_file, argc);

	//if(INPUT.calculation == "ext"){Extend ext; ext.Routine();}
	//else if(INPUT.calculation == "tune_stru"){Tune_Stru ts; ts.Routine();}
    if(INPUT.calculation == "2PBD")
    {
        conver2PDB ts; ts.Routine();
    }
    else if(INPUT.calculation == "NUMBER_DENSITY")
    {
        NumberDensity ts; ts.Routine();
    }
    else
    {
        ofs_running << " calculation=" << INPUT.calculation << endl;
        QUIT("No 'calculation' available");
    }

    ofs_running << " --------------- " << endl;
    ofs_running << "      Finish     " << endl;
    ofs_running << " --------------- " << endl;

    #ifdef __MPI
        MPI_Finalize();
    #endif

    time_t time_end = std::time(NULL);
    ofs_running << " HAVE A GREAT DAY! " << ctime(&time_end) << endl;

    return 0;

}
