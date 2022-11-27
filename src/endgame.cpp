#include "../include/simulation.h"

using namespace std;

int main(int argc, char *argv[]) {

    if (argc != 3)
    {
        cout << "Usage : ./endgame <disc_infile> <dust_infile>" << endl;
        return 0;
    }

    string disc_filename = argv[argc-2];
    string dust_filename = argv[argc-1];

    Simulation sim;

    sim.read_disc_infile(disc_filename);
    sim.read_particle_infile(dust_filename);

    sim.init_all();

    sim.evolve();

    sim.print_summary();

  return 0;
}
