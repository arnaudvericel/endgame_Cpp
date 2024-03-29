#ifndef PARTICLE_H
#define PARTICLE_H

#include <iostream>
#include <sstream>
#include <cmath>
#include <iomanip>

#include "utils.h"

class Disc;

using namespace std;

enum VolatilesState {
    Undefined = 0,
    Gas,
    Solid
};

class Particle {
private:
    // particle number
    int part_number;

    // state of the particle
    VolatilesState iam;
    VolatilesState iwas;
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

    // disc owner
    Disc* disc;

    // outfiles
    string filename;

    // methods
    void set_filename();
    void init_outfile();
    bool should_sublimate() const;
    bool should_condense() const;
    void sublimate();
    void condense();
    void update_size(const double);
    void update_state();
    void update_radius(const double);
    
public:
    // number of particles, shared across all instances of Particle class
    static int particle_count;

    // constructors
    Particle(Disc*);
    Particle(Disc*, double, double, double);

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
    void update(const double);
    void write_in_file(const double);
};

#endif
