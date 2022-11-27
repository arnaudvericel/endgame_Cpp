#include "../include/manager.h"

/*************************************/
/************** PUBLIC ***************/
/*************************************/

Manager::Manager(): run_directory("") {}

void Manager::set_dirname(string dirname) { run_directory = dirname; }

void Manager::sort_files(string dust_infile, string disc_infile, vector<string> particle_filenames) const
{
    bool sorting_is_okay = false;

    /* check if directory is present and create it if not */
    if (!directory_is_present(run_directory))
    {
        cout << "Creating directory " << run_directory << endl;
        create_output_dir(run_directory);
        sorting_is_okay = true;
    } else { /* if present, append _new to directory name */
        cout << "Directory " << run_directory << " already present, trying to create " << run_directory + "_new...";
        if (!directory_is_present(run_directory + "_new")) {
            cout << "...done." << endl;
            cout << "You've used your only joker. Files cannot automatically be moved to existing directories to avoid overwriting previous data." << endl;
            create_output_dir(run_directory + "_new");
            sorting_is_okay = true;
        }
        else { /* if both are present, abort sorting by fear of overwritting old data */
            cout << "...already present, automatic sorting aborted." << endl;
            sorting_is_okay = false;
        }
    }
    if (sorting_is_okay) {
        /* option files */
        copy_file(dust_infile);
        copy_file(disc_infile);

        /* particle files */
        for (string& p_file: particle_filenames) {
            move_file(p_file);
        }
    }
}

/*************************************/
/************** PRIVATE **************/
/*************************************/

bool Manager::directory_is_present(string dir_name) const {
    struct stat buffer;
    return stat(dir_name.c_str(), &buffer) == 0;
}

void Manager::create_output_dir(string dir_name) const {
    string command = "mkdir " + dir_name;
    system(command.c_str());
}

void Manager::move_file(string file) const {
    string command = "mv " + file + " " + run_directory;
    system(command.c_str());
}

void Manager::copy_file(string file) const {
    string command = "cp " + file + " " + run_directory;
    system(command.c_str());
}
