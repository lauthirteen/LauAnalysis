#include "../include/conver2PDB.h"
#include "../include/cell.h"
#include "../include/cellFile.h"


conver2PDB::conver2PDB(){}
conver2PDB::~conver2PDB(){}

void conver2PDB::Routine()
{
    cout << "convert geometry to PDB format file. Jianchuan Liu 20211013" << endl;

    int indexatom;
    double a; // lattice parameter
    double b; // lattice parameter
    double c; // lattice parameter
    double alpha; // cosine of the angle between axis b and c
    double beta; // cosine of the angle between axis a and c
    double gamma; // cosine of the angle between axis a and b
    // create the pdb file
    ofstream ofs("output.pdb");

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
        //
        ofs << "MODEL         " << igeo << endl;
        ofs << "REMARK   Converted from "<< INPUT.traj_path << " file" << endl;
        ofs << "REMARK   Snapshot time: "<< cel.snapshot_time << " ps" << endl;
        ofs << "REMARK   Atom number: "<< cel.atom_num  << endl;
        ofs.width(6);
        ofs << "CRYST1";
        ofs.width(9);
        ofs.setf(ios::fixed);
        ofs.setf(ios::showpoint);
        ofs.setf(ios::right);
        a = cel.cell_x;
        ofs << setprecision(3) << a;
        ofs.width(9);
        ofs.setf(ios::fixed);
        ofs.setf(ios::showpoint);
        ofs.setf(ios::right);
        b = cel.cell_y;
        ofs << setprecision(3) << b;
        ofs.width(9);
        ofs.setf(ios::fixed);
        ofs.setf(ios::showpoint);
        ofs.setf(ios::right);
        c = cel.cell_z;
        ofs << setprecision(3) << c;
        alpha = 90.0; // cosine of the angle between axis b and c
        beta = 90.0; // cosine of the angle between axis a and c
        gamma = 90.0; // cosine of the angle between axis a and b
        ofs.width(7);
        ofs.setf(ios::fixed);
        ofs.setf(ios::showpoint);
        ofs.setf(ios::right);
        ofs << setprecision(2) << alpha;
        ofs.width(7);
        ofs.setf(ios::fixed);
        ofs.setf(ios::showpoint);
        ofs.setf(ios::right);
        ofs << setprecision(2) << beta;
        ofs.width(7);
        ofs.setf(ios::fixed);
        ofs.setf(ios::showpoint);
        ofs.setf(ios::right);
        ofs << setprecision(2) << gamma << endl;
        indexatom = 1;
        for(int ia=0; ia<cel.atom_num; ++ia)
        {
            //cout << 1111 << endl;
            // wirte the postion of pdb file
            ofs.width(6); // 1-6
            ofs << "ATOM  ";
            //cout << 2222 << endl;           
            ofs.width(5);// 7-11
            ofs.setf(ios::right);
            ofs << indexatom;

            ofs.width(1); // 12
            ofs.setf(ios::left);
            ofs << " ";

            ofs.width(4); // 13-16
            ofs.setf(ios::left);
            ofs << cel.atom[ia].name;
            
            ofs.width(1); // 17
            ofs.setf(ios::left);
            ofs << " ";
            
            ofs.width(3); // 18-20
            ofs.setf(ios::left);
            ofs << "MOL";

            ofs.width(2);// 21-22
            ofs.setf(ios::right);
            ofs << "A";

            ofs.width(4);// 23-26
            ofs.setf(ios::right);
            ofs << "1";

            ofs.width(4);// 26-30
            ofs.setf(ios::right);
            ofs << " ";

            ofs.width(8);// 31-38
            ofs.setf(ios::fixed);
            ofs.setf(ios::showpoint);
            ofs.setf(ios::right);
            ofs << setprecision(3) << cel.atom[ia].x;

            ofs.width(8);// 39-46
            ofs.setf(ios::fixed);
            ofs.setf(ios::showpoint);
            ofs.setf(ios::right);
            ofs << setprecision(3) << cel.atom[ia].y;
            
            ofs.width(8);// 47-54
            ofs.setf(ios::fixed);
            ofs.setf(ios::showpoint);
            ofs.setf(ios::right);
            ofs << setprecision(3) << cel.atom[ia].z;
            ofs << endl;
            indexatom++;
            if(indexatom > 99999)
            {
                indexatom = 1;
            }
        }
        //
        ofs << "END" << endl;
        //cout << INPUT.end_frame << "  " << igeo << endl;
        //cout << "atom num: " << cel.atom_num << endl;
        //cout << cel.atom[542].x << " " << cel.atom[542].name << " " << cel.atom[542].mass <<  endl; 
    }
    cel.clean();
}
