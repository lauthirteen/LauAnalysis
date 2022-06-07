#include "../include/global_functions.h"
#include <cstdlib>


ofstream ofs_running;
int NPROC=1;
int RANK=0;

// CONSTANTS
double PI=3.1415926535897932384626;
double KB=1.38064852*1.0e-23; // Botzmann constant. unit: m^2 * kg * s^-2 * K^-1
double EPSILON0=8.854187817*1.0e-12; // Vacuum permittivity. F * m^-1, 1 F= 1C/1V
double BOHR=0.52917721092; // 1 Bohr = 0.529 Angstrom


bool SCAN_BEGIN(ifstream &ifs, const string &TargetName, const bool restart)
{
    string SearchName;
    bool find = false;
    if (restart)
    {
        ifs.clear();
        ifs.seekg(0);
    }
    ifs.rdstate();
    while (ifs.good())
    {
        ifs >> SearchName;
		//cout << " " << SearchName << endl;
        if ( SearchName == TargetName)
        {
            find = true;
            break;
        }
    }
    if (!find)
    {
     //   cout <<" In SCAN_BEGIN, can't find: "<<TargetName<<" block."<<endl;
    }
    return find;
}



void TITLE(const string &class_name,const string &function_name)
{
	//return;
    //cout<<" ==> "<<class_name<<"::"<<function_name<<endl;
    return;
}

void QUIT(const string &reason)
{
	cout << " ------------------------------------------ " << endl;
	cout << " Quit because : " << reason << endl;
	exit(0);
}


double shortest(const double &tmp_pos, const double &pos, const double &celldm)
{
	double vec1 = tmp_pos-pos;
	double vec2 = tmp_pos-pos+celldm;
	double vec3 = tmp_pos-pos-celldm;

	double dis1 = abs(vec1);
	double dis2 = abs(vec2);
	double dis3 = abs(vec3);

	if(dis1<=dis2 and dis1<=dis3) return vec1; 
	if(dis2<=dis1 and dis2<=dis3) return vec2; 
	if(dis3<=dis1 and dis3<=dis2) return vec3;
        else
	{
	    return 0;
	}	
} 

