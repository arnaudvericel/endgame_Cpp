#include "../include/simulation.h"

using namespace std;

int main() {

    string disc_filename = "disc.in";
    string dust_filename = "dust.in";

    Simulation sim;

    sim.read_disc_infile(disc_filename);
    sim.read_particle_infile(dust_filename);

    sim.init_units();

    sim.evolve();

    sim.print_summary(); // TO EMBELISH

  return 0;
}
