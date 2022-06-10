#include "../include/input.h"
#include "../include/global_functions.h"
#include <cstdlib>
#include <iostream>
#include <fstream>
#include <iomanip>
#include <stdio.h>
#include <string.h>

Input INPUT;

Input::Input() 
{
    traj_type = "LAMMPS";
    traj_path = "traj.lammpstrj";

}

Input::~Input() 
{
	
}

void Input::Init(const string &fn, const int &argc)
{
	time_t time_start = std::time(NULL);
	ofs_running << " ------------------------------------------------------------------------------------" << endl;
	ofs_running << "              WELCOME TO LauAnalysis " << ctime(&time_start) << endl;
	ofs_running << " THIS IS A PROGRAM FOR PERFORMING ANALYSIS FOR MOLECULAR DYNAMICS" << endl;
	ofs_running << " AUTHOR: Lau, LAST UPDATE: 2022-06" << endl;

	ofs_running << setiosflags(ios::right); // 右对齐输出
	ofs_running << setiosflags(ios::left);
	ofs_running << setiosflags(ios::left);

	ofs_running << " READING from INPUT file" << endl;


    this->Default();

    this->Read(fn);

    //this->Check();

    time_t  time_now = time(NULL);

	return;
}

void Input::Default(void)
{
    num_atom_type = 0;
    total_num_atom = 0;
    atom_type1 = "empty";
    atom_type2 = "empty";
    atom_type3 = "empty";
    atom_type4 = "empty";
    atom_type5 = "empty";
    atom_type6 = "empty";
    atom_type7 = "empty";
    atom_type8 = "empty";
    atom_type9 = "empty";
    atom_type10 = "empty";

    begin_frame = 0;
    end_frame = 0;
    interval_frame = 1;

    direction = "x"; // number density: x or y  or z
    rcut = 200.0; // A
    dr = 0.01; // A
    atom_name1 = "X"; // target operating atom
    atom_name2 = "X"; // target operating atom

    cell_dim_x = 0; // cell length A
    cell_dim_y = 0;
    cell_dim_z = 0;

    nHB_max = 8; // max HB number

    return;
}

void Input::Read(const string &fn) // read parameters
{
    ifstream ifs(fn.c_str(), ios::in);	// "in_datas/input_parameters"

    if (!ifs) 
	{
		cout << " Can't find the INPUT file." << endl;
		exit(0);
	}

    ifs.clear(); // 
    ifs.seekg(0); // 。

    char word[80];
    char word1[80];
    int ierr = 0;

    //ifs >> setiosflags(ios::uppercase);
    ifs.rdstate(); //
    
    while (ifs.good())  // read input file
    {
        ifs >> word1; // 
        strtolower(word1, word); // 
        //type of calculation 
        if (strcmp("calculation", word) == 0) read_value(ifs, calculation);
        // infomation of trajctory file
        else if (strcmp("traj_type", word) == 0) read_value(ifs, traj_type);
        else if (strcmp("traj_path", word) == 0) read_value(ifs, traj_path);
        else if (strcmp("num_atom_type", word) == 0) read_value(ifs, num_atom_type);
        else if (strcmp("total_num_atom", word) == 0) read_value(ifs, total_num_atom);
        // the max number of atom type is less than 10
        else if (strcmp("atom_type1", word) == 0) read_value(ifs, atom_type1);
        else if (strcmp("atom_type2", word) == 0) read_value(ifs, atom_type2);
        else if (strcmp("atom_type3", word) == 0) read_value(ifs, atom_type3);
        else if (strcmp("atom_type4", word) == 0) read_value(ifs, atom_type4);
        else if (strcmp("atom_type5", word) == 0) read_value(ifs, atom_type5);
        else if (strcmp("atom_type6", word) == 0) read_value(ifs, atom_type6);
        else if (strcmp("atom_type7", word) == 0) read_value(ifs, atom_type7);
        else if (strcmp("atom_type8", word) == 0) read_value(ifs, atom_type8);
        else if (strcmp("atom_type9", word) == 0) read_value(ifs, atom_type9);
        else if (strcmp("atom_type10", word) == 0) read_value(ifs, atom_type10);
        //
        else if (strcmp("frame_dt", word) == 0) read_value(ifs, frame_dt);
        else if (strcmp("begin_frame", word) == 0) read_value(ifs,begin_frame);
        else if (strcmp("end_frame", word) == 0) read_value(ifs, end_frame);
        else if (strcmp("interval_frame", word) == 0) read_value(ifs, interval_frame);
        //
        else if (strcmp("direction", word) == 0) read_value(ifs, direction);
        else if (strcmp("rcut", word) == 0) read_value(ifs, rcut);
        else if (strcmp("dr", word) == 0) read_value(ifs, dr);
        else if (strcmp("atom_name1", word) == 0) read_value(ifs, atom_name1);
        else if (strcmp("atom_name2", word) == 0) read_value(ifs, atom_name2);
        //
        else if (strcmp("cell_dim_x", word) == 0) read_value(ifs, cell_dim_x);
        else if (strcmp("cell_dim_y", word) == 0) read_value(ifs, cell_dim_y);
        else if (strcmp("cell_dim_z", word) == 0) read_value(ifs, cell_dim_z);
        //
        else if (strcmp("#", word) == 0)
        {
            ifs.ignore(150, '\n');
        }
        else
        {
            cout << " THE PARAMETER NAME '" << word
               << "' IS NOT USED!" << endl;
            ifs.ignore(150, '\n');
        }

        ifs.rdstate();
        if (ifs.eof() != 0)
        {
			break;
        }
        else if (ifs.bad() != 0)
        {
			cout << " Bad input parameters. " << endl;
			exit(0);
        }
        else if (ifs.fail() != 0)
        {
			cout << " word = " << word << endl;
			cout << " Fail to read parameters. " << endl; 
            ifs.clear();
			exit(0);
        }
        else if (ifs.good() == 0)
        {
			break;
        } // end read input file
    }


    return;
}// end read parameters


void Input::readbool(ifstream &ifs, bool &var)
{
    string str;
    ifs >> str;
    if (str == "true")
    {
        var = true;
    }
    else
    {
        var = false;
    }
    ifs.ignore(100, '\n');
    return;
}

void Input::strtolower(char *sa, char *sb)
{
    char c;
    int len = strlen(sa);
    for (int i = 0; i < len; i++)
    {
        c = sa[i];
        sb[i] = tolower(c); // 将给定字符转为小写
    }
    sb[len] = '\0';
}
