#ifdef THANOS // only compile this part if thanos has been requested by user
#ifndef THANOS_H
#define THANOS_H

#include <iostream>
#include <vector>
#include "unistd.h"
#include <fstream>
#include <cstdlib>

using namespace std;

class Thanos {
private:
    // object
    string filename;
    vector<string> punchlines;

    // private method used by constructor
    void read_quotesfile();
public:
    // constructor
    Thanos();

    // destructor
    ~Thanos() = default;

    // methods
    void print_artwork();
    void talks_to_gamora();
    void init_punchline();
    void regular_ending();
    void balanced_ending();
};

#endif
#endif
