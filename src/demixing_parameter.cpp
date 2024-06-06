#include "../include/demixing_parameter.h"
#include "../include/global_functions.h"    // global functions
#include "../include/cell.h"
#include "../include/cellFile.h"

DemixingParameter::DemixingParameter(){}
DemixingParameter::~DemixingParameter(){}

void DemixingParameter::Routine()
{
    cout << "calculate the demixing parameter. Jianchuan Liu 20221202" << endl;
    // create the file
    ofstream ofs("demixing_parameter.dat");
    ofs << "time (ps)    parameter   " << endl;
    CellFile cel;

    for(int igeo=1; igeo<=INPUT.end_frame; ++igeo)
    {
        // read pos
        CellFile::ReadGeometry( cel );
        cel.snapshot_time = igeo * INPUT.frame_dt;
        cout << "igeo=" << igeo << " time=" << cel.snapshot_time << endl;
        if (igeo < INPUT.begin_frame || (igeo - INPUT.begin_frame)  % INPUT.interval_frame != 0) 
        {
            //cout << "1111111111111111111111111" << endl;
            continue;
        }
        // create new bin_mass
        this-> bin_mass = new double **[INPUT.bin_num];
        for(int i=0; i<INPUT.bin_num; i++)
        {
            bin_mass[i] = new double * [INPUT.bin_num];
            for(int j=0; j<INPUT.bin_num; j++)
            {
                this -> bin_mass[i][j] = new double[INPUT.bin_num];
                for(int k=0; k<INPUT.bin_num; k++)
                {
                    bin_mass[i][j][k] = 0;
                }
            }
        } //
        //
        total_mass = 0;
        // read all atom coordinates
        double bin_length_x = cel.cell_x / INPUT.bin_num;
        double bin_length_y = cel.cell_y / INPUT.bin_num;
        double bin_length_z = cel.cell_z / INPUT.bin_num;
        for(int ia=0; ia<cel.atom_num; ++ia)
        {
            // add the mass
            total_mass += cel.atom[ia].mass;
            int bin_x = cel.atom[ia].x / bin_length_x;
            int bin_y = cel.atom[ia].y / bin_length_y;
            int bin_z = cel.atom[ia].z / bin_length_z;
            //int tmp = -1.2 / 1.0;
            //cout << "tmp: " << tmp << endl;
            //cout << "x: " << cel.atom[ia].x << " y: " << cel.atom[ia].y << " z: " << cel.atom[ia].z << endl;
            //cout << "x: " << bin_x << " y: " << bin_y << " z: " << bin_z << endl;
            if (bin_x >= INPUT.bin_num) {bin_x = INPUT.bin_num - 1;}
            if (bin_y >= INPUT.bin_num) {bin_y = INPUT.bin_num - 1;}
            if (bin_z >= INPUT.bin_num) {bin_z = INPUT.bin_num - 1;}
            if (bin_x < 0) {bin_x = 0;}
            if (bin_y < 0) {bin_y = 0;}
            if (bin_z < 0) {bin_z = 0;}
            bin_mass[bin_z][bin_y][bin_x] += cel.atom[ia].mass;
        } // end of atom

        // claculate the density
        global_density = total_mass / cel.volume;
        //cout << cel.volume << endl;
        //cout << total_mass << endl;
        //cout << global_density << endl;
        double demixing_parameter;
        double local_density = 0;

        for(int i=0; i<INPUT.bin_num; i++)
        {
            for(int j=0; j<INPUT.bin_num; j++)
            {
                for(int k=0; k<INPUT.bin_num; k++)
                {
                    local_density += abs((bin_mass[i][j][k] / (bin_length_x * bin_length_y * bin_length_z)) / global_density - 1);
                }
            }
        } //
        demixing_parameter = local_density / (INPUT.bin_num*INPUT.bin_num*INPUT.bin_num);
        ofs << cel.snapshot_time << " " << demixing_parameter << endl;

        // delete the bin_mass
        for(int i=0;i<INPUT.bin_num;i++)
        {
            for (int j=0;j<INPUT.bin_num;j++)
            {
                delete[] bin_mass[i][j];
            }    
        }
        
    } // end of frame
}
