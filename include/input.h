#ifndef INPUT_H
#define INPUT_H

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

class Input
{
public:
    
	Input();
    ~Input();
    
	// read in the parameters, be called in main.cpp
	void Init(const string &fn, const int &argc);

	private:
    void Read(const string &fn);
    void Default(void);
    void Check(void);

	public:
	// >>> General <<<
	string calculation; // type of calculations.
    string traj_type; // type of trajctory file
    string traj_path; // the directory of trajctory file

    int num_atom_type; // The number of atom type in the trajctory file
    int total_num_atom; // The total atom numbers in the trajctory file

    // atom type id for element name
    string atom_type1;
    string atom_type2;
    string atom_type3;
    string atom_type4;
    string atom_type5;
    string atom_type6;
    string atom_type7;
    string atom_type8;
    string atom_type9;
    string atom_type10;

    float frame_dt; // The time between every two configurations (ps)
    int begin_frame;
    int end_frame;
    int interval_frame;


	template <class T>
    static void read_value(ifstream &ifs, T &var)
    {
        ifs >> var;
        ifs.ignore(150, '\n'); // 
        return;
    }

	void strtolower(char *sa, char *sb);
	void readbool(ifstream &ifs, bool &var);

};

extern Input INPUT;

#endif //INPUT
