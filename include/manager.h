#ifndef MANAGER_H
#define MANAGER_H

#include <iostream>
#include <cstdlib>
#include <string>
#include <vector>
#include <sys/stat.h>

using namespace std;

class Manager {
private:
    string run_directory;
    bool directory_is_present(string);
    void create_output_dir(string);
    void move_file(string);
    void copy_file(string);
public:
    // constructor
    Manager();

    // destructor
    ~Manager() = default;

    // setter
    void set_dirname(string);

    // method
    void sort_files(string, string, vector<string>);
};

#endif
