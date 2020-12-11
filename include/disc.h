#ifndef DISC_H
#define DISC_H

#include "utils.h"
#include <fstream>
#include <string>
#include <iostream>
#include <iomanip>

using namespace std;

class Disc {
private:
    // disc related
    double p;
    double q;
    double mdisc;
    double mstar;
    double racc;
    double rin;
    double rout;
    double rzero;
    double Tzero;
    double mu;
    double alpha;
    double phi;
    double w;

    // at rzero
    double cszero;
    double rhogzero;
    double sigmagzero;

    // dust related
    double epsilon;
    double rhoin;
    double rhoout;
    double smin;
    double epsimax;

    // physics options
    double vfrag;
    double vfragin;
    double vfragout;
    double rsnow;
    double rbump;
    double Tsnow;
    double abun;
    double mratio;

    // control options
    int igrow;
    int ifrag;
    int isnow;
    int ibump;
    int istate;
    int ibr;
public:
    // constructor
    Disc();

    // destructor
    ~Disc() = default;

    // getters - functions
    double get_cs(double);
    double get_nu(double);
    double get_vk(double);
    double get_omega_k(double);
    double get_press(double);
    double get_rhog(double);
    double get_sigmag(double);
    double get_h(double);
    double get_hoverr(double);
    double get_Temp(double);
    double get_epsi(double);
    double get_vdrift(double, double);
    double get_vvisc(double, double);

    // getters - attributes
    double get_rzero();
    double get_vfrag();
    double get_vfragin();
    double get_vfragout();
    double get_rsnow();
    double get_Tsnow();
    double get_smin();
    double get_alpha();
    double get_racc();
    //
    int get_igrow();
    int get_ifrag();
    int get_isnow();
    int get_ibump();
    int get_istate();
    int get_ibr();

    // methods
    void fill_disc_prop(ifstream&);
    void init_units();
    void print_model();
};

#endif
