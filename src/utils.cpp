#include "../include/utils.h"

void buffer_file(ifstream& f, int n_lines) {
    string tata;
    for (int i=0; i<n_lines; i++) {
        getline(f,tata);
    }
}
