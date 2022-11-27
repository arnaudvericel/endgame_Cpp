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
    bool directory_is_present(string) const;
    void create_output_dir(string) const;
    void move_file(string) const;
    void copy_file(string) const;
public:
    // constructor
    Manager();

    // destructor
    ~Manager() = default;

    // setter
    void set_dirname(string);

    // method
    void sort_files(string, string, const vector<string>&) const;
};

#endif
