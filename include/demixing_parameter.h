#ifndef DemixingParameter_H
#define DemixingParameter_H
#include "cell.h"

class DemixingParameter 
{
	public: 
	
	DemixingParameter();
	~DemixingParameter();
    void Routine();

    double total_mass; // all atom mass
    double global_density;

    double *** bin_mass;
    //int nmesh; // number of mesh points.
	//double dr; // delta r
	//double rcut; // radius cutoff
    //int count_geometry_number;    
    //int which;
    
    //void CoumpteDensityX(const Cell &cel, double *number_density);
    // void CoumpteDensityY(const Cell &cel, double *number_density);
    //void CoumpteDensityZ(const Cell &cel, double *number_density);

};
#endif