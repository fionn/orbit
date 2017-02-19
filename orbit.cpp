#include <cmath>
#include <iostream>
#include <string>
#include <fstream>
#include <sstream>

using namespace std;

class Planet
{
    public:
        double mass;
        double coord[2];
        double velocity[2];
};

class SolarSystem
{
    public:
        int n;
        Planet* p;

        SolarSystem(char *filename)
        {
            string line;
            ifstream file(filename);
            
            getline(file, line);
            stringstream(line) >> n;  // load number of planets
            p = new Planet[n];

            for(int i = 0; i < n; i++)
            {
                getline(file, line);
                stringstream(line) >> p[i].mass;
                getline(file, line);
                stringstream ss(line);
                ss >> p[i].coord[0];
                ss >> p[i].coord[1];
                ss >> p[i].velocity[0];
                ss >> p[i].velocity[1];
            }
        }

        SolarSystem(int nplanets)
        {
            n = nplanets;
            p = new Planet[nplanets];
        }
};

void update_coord(double h, SolarSystem s)
{
    for(int i = 0; i < s.n; i++)      // for all planets
        for(int a = 0; a < 2; a++)    // for both x and y coordinates
            s.p[i].coord[a] += h * s.p[i].velocity[a];
}

void update_velocity(double h, SolarSystem s, double g_newton)
{
    for(int i = 0; i < s.n; i++)      // for all planets
        for(int j = 0; j < s.n; j++)  // for all other planets
            if(j != i)
            {
                double r_ij[2], r_ij2 = 0;
                
                for(int a = 0; a < 2; a++)
                {
                    r_ij[a] = s.p[i].coord[a] - s.p[j].coord[a];
                    r_ij2 += r_ij[a] * r_ij[a];
                }

                double r_ij3 = pow(r_ij2, 1.5);

                for(int a = 0; a < 2; a++)
                    s.p[i].velocity[a] -= h * g_newton * s.p[j].mass * r_ij[a] / r_ij3;
            }
}

void update(double h, SolarSystem s, double g_newton)
{
    update_coord(0.5 * h, s);
    update_velocity(h, s, g_newton);
    update_coord(0.5 * h, s);
}

double energy(SolarSystem &s, double g_newton)
{
    double r_ij[s.n], r_ij2 = 0;
    double T = 0, V = 0;
    
    for(int i = 0; i < s.n; i++)
    {
        T += 0.5 * s.p[i].mass 
             * (s.p[i].velocity[0] * s.p[i].velocity[0] 
                + s.p[i].velocity[1] * s.p[i].velocity[1]);

        for(int j = i; j < s.n; j++)
            if(i != j) // I bet this could be better
            {
                for(int a = 0; a < s.n; a++)
                {
                    r_ij[a] = s.p[i].coord[a] - s.p[j].coord[a];
                    r_ij2 += r_ij[a] * r_ij[a];
                }

                double r_ij3 = pow(r_ij2, 0.5);
                V -= g_newton * s.p[i].mass * s.p[j].mass / r_ij3;
            }
    }

    return T + V;
}

double angularmomentum(SolarSystem &s)
{
    double L = 0, origin[2] = {0, 0}; 
    for(int i = 0; i < s.n; i++)
        L += s.p[i].mass * ((s.p[i].coord[0] - origin[0]) * s.p[i].velocity[1] 
             - (s.p[i].coord[1] - origin[1]) * s.p[i].velocity[0]);

    return L;
}

void gallileo(SolarSystem s, double origin[2])
{
    // This boosts us into the inertial frame of the sun
    cout << origin[0] << "\t" << origin[1] << flush;
    for(int i = 1; i < s.n; i++)
    {
        cout << "\t" << s.p[i].coord[0] - s.p[0].coord[0] + origin[0] << "\t"
                     << s.p[i].coord[1] - s.p[0].coord[1] + origin[1] << flush;
    }
    cout << endl;
}

int main(int argc, char *argv[])
{
    if(argc < 2)
    {
        cout << "Usage: " << argv[0] << " filename" << endl;
        return 0;
    }

    const double g_newton = 10.0;
    double h = 0.001, origin[2] = {0, 0};
    SolarSystem s(argv[1]);

    for(int a = 0; a < 100000; a++) 
    {
        update(h, s, g_newton);

        //cout << a << "\t" << energy(s, g_newton)
        //     << "\t" << angularmomentum(s) << endl;
    
        gallileo(s, origin);
    }

    return 0;
}

