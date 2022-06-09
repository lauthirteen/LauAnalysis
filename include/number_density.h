#ifndef NUMBERD_ENSITY_H
#define NUMBERD_ENSITY_H
#include "cell.h"

class NumberDensity 
{
	public: 
	
	NumberDensity();
	~NumberDensity();
    int nmesh; // number of mesh points.
	double dr; // delta r
	double rcut; // radius cutoff
    int count_geometry_number;    
    int which;
    void Routine();
    void CoumpteDensityX(const Cell &cel, double *number_density);
    void CoumpteDensityY(const Cell &cel, double *number_density);
    void CoumpteDensityZ(const Cell &cel, double *number_density);

};
#endif
