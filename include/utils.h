#ifndef UTILS_H
#define UTILS_H

#include <iostream>
#include <cmath>
#include <fstream>
#include <string>
using namespace std;

namespace constants {
    // Mathematical constants
    const double pi =  3.1415926536;

    // Physics constants
    const double gg       = 6.672041e-11;
    const double kboltz   = 1.38066e-23;
    const double avogadro = 6.0221408577e23;
    const double Ro       = 3.;
    const double mh       = 1.67e-27;

    // Mass, radius and distance conversions
    const double solarm = 1.9891e30;
    const double solarr = 6.959500e8;
    const double earthm = 5.979e24;
    const double earthr = 6.371315e6;
    const double au     = 1.496e11;
    const double km     = 1.e3;

    // Time
    const double seconds = 1.;
    const double minutes = 6.0e1;
    const double hours   = 3.6e3;
    const double days    = 8.64e4;
    const double years   = 3.1556926e7;
}

void buffer_file(ifstream&, int);

#endif
