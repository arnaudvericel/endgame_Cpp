#include "../include/simulation.h"

/*************************************/
/************** PUBLIC ***************/
/*************************************/

Simulation::Simulation() {
    // timestep options
    current_time = 0.;
    maximum_time = 0.;
    delta_time   = 0.;
    n_dumps      = 0;

    // output related (TODO)
    dir_name = "";
    isort    = 0;
    end_only = 0;

    display_code_name();
}

void Simulation::read_particle_infile(string filename) {

    cout << "Reading file " << filename << "\n\t";

    int n_dust = 0;
    string tata;

    ifstream infile;
    infile.open(filename);

    if(infile.is_open()) {

        cout << filename << " is open.\n\t";

        infile >> tata >> n_dust;
        cout << n_dust << " dust particles to initialize...";

        buffer_file(infile,3);

        for (int i=0; i<n_dust; i++) {
            double size   = 0;
            double radius = 0;
            double rho    = 0;
            int toto      = 0;
            infile >> toto >> size >> radius >> rho;
            this->parts.push_back(Particle(size,radius,rho));
        }

        cout << "...done." << endl;

    } else {
        cout << "Error while opening " << filename << " (missing?)." << endl;
    }

    infile.close();
}

void Simulation::read_disc_infile(string filename) {

    string tata;
    int nsteps = 0;

    cout << "Reading file " << filename << "\n\t";

    ifstream infile;
    infile.open(filename);

    if(infile.is_open()) {

        // initi disc related quantities
        cout << filename << " is open.\n\t" << "Initializing disc parameters...";
        this->disc.fill_disc_prop(infile);

        // continue onto general simulation properties
        buffer_file(infile,4);
        infile >> nsteps >> maximum_time >> n_dumps;
        buffer_file(infile,4);
        infile >> dir_name >> isort >> end_only;

        delta_time = 1./nsteps;

        cout << "...done." << endl;

    } else {
        cout << "Error while opening " << filename << " (missing?)." << endl;
    }

    infile.close();
}

void Simulation::init_units() {
    // init disc units
    this->disc.init_units();

    // init parts units
    for(Particle& p: this->parts) {
        p.init_units();
    }

    double time_factor = 2*constants::pi/(disc.get_omega_k(disc.get_rzero()));
    delta_time *= time_factor;
    maximum_time *= time_factor;

    disc.print_model();
}

void Simulation::evolve() {

    bool writing_step = false;

    while (current_time < maximum_time) {
        current_time += delta_time;
        writing_step  = isWritingStep();

        /* integrate equations */
        for (Particle& p: this->parts) {
            if (!p.isAccreted()) {
                p.update_size(delta_time, this->disc);
                p.update_state(delta_time, this->disc);
                p.update_radius(delta_time, this->disc);
            }
            if (writing_step) { p.write_in_file(current_time, this->disc); }
        }
        display_loading_bar();
    }
}

void Simulation::print_summary() {

    int is_accreted = 0;

    for (Particle& p: this->parts) {
        if (p.isAccreted()) { is_accreted++; }
    }

    // TO EMBELISH
    cout << "\nPrinting summary after " << int(maximum_time/constants::years/1000) << " kyrs of simulation..." << endl;
    cout << left << setw(10) << "Accreted" << setw(3) << "|" << setw(10) << "Non-accreted" << endl;
    cout << left << setw(10) << is_accreted << setw(3) << "|" << setw(10) << Particle::particle_count - is_accreted << endl;
}

/*************************************/
/************** PRIVATE **************/
/*************************************/

void Simulation::display_code_name() {
    cout << "                                                                                                         " << endl;
    cout << "@@@@@@@@@@@% /@@@@     @@@@@ @@@@@@@@&,         @@@@@ @          @@@       @@@@@      @@@@@  @@@@@@@@@@@@" << endl;
    cout << "&@@      @%   @@@@%     @,   .@@     .@@@   @@@      @@        &&@@@       @@@@@     @@@@*    @@@      @"  << endl;
    cout << "&@@   @.      @#/@@@    @,   .@@      ,@@  @@@        @       .@  @@       @@*@@(   *@ @@*    @@@    "     << endl;
    cout << "&@@@@@@       @#  @@@   @,   .@@       @@* @@&                @@@@@@@      @@ @@@   @  @@*    @@@@@@@"     << endl;
    cout << "&@@   @   @   @#   @@@  @,   .@@      ,@@  @@@     @@@@@     @,    @@@     @@  @@@ @@  @@*    @@@  /@  @." << endl;
    cout << "&@@      @@   @#    @@@#@,   .@@      @@@  .@@/      @@#    @@     .@@&    @@   @@&@   @@*    @@@     .@"  << endl;
    cout << "@@@@@@@@@@@@ /@@@@    ,@@@,  @@@@@@@@@@@      @@@@@@@@*@#  @@@@&   &&@@@@* @@@@  &@@  @@@@@@ &@@@@@@@@@@@" << endl;
    cout << "                                                                                                         " << endl;
    cout << "By Arnaud Vericel (C++ version)." << endl;
    cout << "-------------------------------------------------------------------------------------------------------\n" << endl;
}

void Simulation::display_loading_bar() {

    double progress = current_time / maximum_time;
    int bar_width = 100;

    cout << "[";
    int pos = bar_width * progress;
    for (int i=0; i<bar_width; i++) {
        if (i<pos) { cout << "="; }
        else if (i==pos) { cout << ">"; }
        else { cout << " "; }
    }
    cout << "] " << int(progress * 100.0) << " %\r";
    cout.flush();

    if ((int)progress == 1) { cout << endl; }
}

bool Simulation::isWritingStep() {

    int step = (int) (current_time / delta_time);
    int nstep = (int)(maximum_time / delta_time);
    int writing_step = nstep / n_dumps;

    if (n_dumps >= nstep) { return true; }

    return (step%writing_step == 0) ;
}