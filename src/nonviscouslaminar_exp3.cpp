#include <bits/stdc++.h>
using namespace std;

// setup
double rou0 = 1.225;
double t0 = 293.0;
double visc = 1.458e-6 * sqrt(t0 * t0 * t0) / (t0 + 110.4);
double width = 0.5;
double v0 = 20.0;
double re0 = rou0 * v0 * width / visc;
double blt = width * 5.2 / sqrt(re0);
double dpdx = -50;

// calculation grid
int nx = 50000;
double dx = width / double(nx);
int ny = 200;
double ymax = blt * 2.0;
double dy = ymax / double(ny);
vector<vector<double> > y(nx + 1);
vector<vector<double> > u(nx + 1);
vector<vector<double> > v(nx + 1);

void conditions(){
    cout << ">> Solve Bounddary Layer Equation for Flat Plate." << endl;
    cout << ">> Flow Conditions:" <<  endl;
    cout << "   Velocity (m/s) = " << v0 << endl;
    cout << "   Length (m) = " << width << endl;
    cout << "   Reynolds No. = " << re0 << endl; 
    cout << "   Boundary Layer Thickness (mm) = " << blt * 1000.0 << endl;
}

void computational_grid()
{
    for(int i = 0; i < nx + 1; i++)
    {
        for(int j = 0; j < ny; j++) y[i].push_back(dy * double(j - 1));
        for(int j = 0; j < ny; j++) u[i].push_back(0);
        for(int j = 0; j < ny; j++) v[i].push_back(0);
    }
}

void start_condition()
{
    for(int j = 0; j < ny; j++)
    {
        u[0][j] = v0;
        v[0][j] = 0.0;
    }
}

void calculate_next_uv(int i)
{
    vector<double> un(ny);
    vector<double> vn(ny);

    for(int j = 1; j < ny; j++)
    {
        u[i+1][j] = u[i][j]+ dx / u[i][j] * ((visc/rou0)*((u[i][j+1]-2*u[i][j]+u[i][j-1])/(dy*dy))\
        - v[i][j]*((u[i][j+1]-u[i][j-1])/(2*dy)) - dpdx / rou0) ;
    
        u[i][0] = 0.0;
        u[i][ny - 1] = v0;
        v[i][0] = 0.0;

        v[i+1][j] = v[i+1][j-1]-(((u[i+1][j-1]-u[i][j-1])/dx)+((u[i+1][j]-u[i][j])/dx))*dy/2;
        
    }
}

int main() {
    conditions();
    computational_grid();
    start_condition();
    for(int i = 0; i < nx; i++){
        fprintf(stderr, "\r[%3d / %5d]", i + 1, nx);
        calculate_next_uv(i);
    }
    cout << endl;
    cout << "finished!" << endl;
    ofstream writing_file;
    string filename_u = "../out/exp3/u.csv";
    writing_file.open(filename_u, ios::out);
    for(int i = 0; i < nx + 1; i++){
        for(int j = 0; j < ny + 1; j++){
            writing_file << " " << u[i][j];
        }
        writing_file << endl;
    }
    writing_file.close();

    string filename_v = "../out/exp3/v.csv";
    writing_file.open(filename_v, ios::out);
    for(int i = 0; i < nx + 1; i++){
        for(int j = 0; j < ny + 1; j++){
            writing_file << " " << v[i][j];
        }
        writing_file << endl;
    }
    writing_file.close();
    
    return 0;
}