#ifndef SIMULATION_H
#define SIMULATION_H

#include "particle.h"
#include "manager.h"
#include "utils.h"
#include "disc.h"
#include <vector>
#include <string>
#include <fstream>
#include <iostream>

#ifdef THANOS
#include "thanos.h"
#endif

/* Simulation class is a wrapper of the other classes */
class Simulation {
private:
    // infiles related
    string dust_infile;
    string disc_infile;

    // timestep options
    double current_time;
    double maximum_time;
    double delta_time;
    int n_dumps;

    // output related (TODO)
    string dir_name;
    int isort;
    int end_only;

    // Higher level objects
    vector<Particle> parts; // vector of Particles
    Disc disc; // disc object
    Manager michel;
#ifdef THANOS
    Thanos thanos; // if Thanos if invoked
#endif

    // useful methods used by the public methods of this class
    void display_code_name();
    void display_loading_bar();
    bool isWritingStep();
    bool count_is_balanced(int);
    vector<string> get_part_filenames();
public:
    /* constructor */
    Simulation(); // print code name here

    /* destructor */
    ~Simulation() = default;

    /* methods */
    void read_particle_infile(string); // fill Particles vector
    void read_disc_infile(string); // fill Disc properties
    void init_all(); // init in SI units
    void evolve(); // time iteration and file output writing
    void print_summary(); // end of simulation summary
};

#endif
