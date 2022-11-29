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
    double get_cs(double) const;
    double get_nu(double) const;
    double get_vk(double) const;
    double get_omega_k(double) const;
    double get_press(double) const;
    double get_rhog(double) const;
    double get_sigmag(double) const;
    double get_h(double) const;
    double get_hoverr(double) const;
    double get_Temp(double) const;
    double get_epsi(double) const;
    double get_vdrift(double, double) const;
    double get_vvisc(double, double) const;

    // getters - attributes
    double get_rzero() const;
    double get_vfrag() const;
    double get_vfragin() const;
    double get_vfragout() const;
    double get_rsnow() const;
    double get_Tsnow() const;
    double get_smin() const;
    double get_alpha() const;
    double get_racc() const;
    double get_rhoin() const;
    double get_rhoout() const;
    double get_mratio() const;
    //
    int get_igrow() const;
    int get_ifrag() const;
    int get_isnow() const;
    int get_ibump() const;
    int get_istate() const;
    int get_ibr() const;

    // methods
    void fill_disc_prop(ifstream&);
    void init_units();
    void print_model() const;
};

#endif
