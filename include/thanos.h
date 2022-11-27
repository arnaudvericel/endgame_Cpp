#ifdef THANOS // only compile this part if thanos has been requested by the user
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

    void print_artwork() const;

    // monologue methods
    void talks_to_gamora() const;
    void init_punchline() const;
    void regular_ending() const;
    void balanced_ending() const;
};

#endif
#endif
