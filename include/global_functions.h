#ifndef GFUN_H
#define GFUN_H

#include <cstdlib>
#include <string>
#include <fstream>
#include <iostream>
#include <sstream>
#include <iomanip>

#include <complex>
#include <cassert>
#include <ctime>

#ifdef __MPI
#include <mpi.h>
#endif

using namespace std;

extern ofstream ofs_running;
extern int NPROC;
extern int RANK;


//==========================================================
// Constants 
//==========================================================
extern double PI;
extern double KB; // Boltzmann constant
extern double EPSILON0; // vacuum permitivity
extern double BOHR; // atomic unit of length

//==========================================================
// GLOBAL FUNCTION :
//==========================================================
template <class T>
static void READ_VALUE(ifstream &ifs, T &v)
{
    ifs >> v;
    ifs.ignore(350, '\n');
    return;
}

void TITLE(const string &class_name,const string &function_name);

void QUIT(const string &name);

template <class T>
inline void ZEROS(T a, const int &size)
{
	assert(size>0);
	for(int i=0; i<size; ++i) a[i]=0;
}

double shortest(const double &tmp_pos, const double &pos, const double &celldm);

#endif

