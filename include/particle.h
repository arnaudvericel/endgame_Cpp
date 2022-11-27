#ifndef PARTICLE_H
#define PARTICLE_H

#include <iostream>
#include <sstream>
#include <cmath>
#include "utils.h"
#include "disc.h"

using namespace std;

class Particle {
private:
    // particle number
    int part_number;

    // state
    int iam;
    int iwas;
    bool accreted;

    // properties
    double velocity;
    double vdrift;
    double vviscous;
    double St;
    double size;
    double radius;
    double vrelonvfrag;
    double growthrate;
    double rho;

    // outfiles
    string filename;

    // method
    void set_filename();
    void init_outfile();
public:
    // number of particles, shared across all instances of Particle class
    static int particle_count;

    // constructors
    Particle();
    Particle(double, double, double);

    // destructor
    ~Particle() = default;

    // status access
    bool is_accreted() const;

    // getter
    string get_filename() const;

    // template column format method
    // used to print a variable inside a column text format no matter its type
    template<class T>
    void column_format(fstream& f, int width, int precision, T element) {
        f << left << setw(width) << setprecision(precision) << element << "\t";
    }

    // methods
    void init_units();
    void update_size(double, Disc&);
    void update_state(double, Disc&);
    void update_radius(double, Disc&);
    void write_in_file(double, Disc&);
};

#endif
