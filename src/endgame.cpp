#include <thread>

#include "../include/simulation.h"

using namespace std;

void print_nb_threads()
{
    const auto processor_count = thread::hardware_concurrency();

    cout << "--" << endl;
    if (processor_count > 0)
    {
        cout << "Running on " << processor_count << " threads" << endl;
    }
    else
    {
        cout << "Unable to find the number of threads" << endl;
    }
    cout << "--" << endl;
}

int main(int argc, char *argv[]) {

    print_nb_threads();

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

    sim.finish();

    return 0;
}
