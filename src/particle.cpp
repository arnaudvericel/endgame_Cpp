#include "../include/particle.h"

/*************************************/
/************** PUBLIC ***************/
/*************************************/

int Particle::particle_count = 0;

Particle::Particle() {
    // state
    iam      = 0;
    iwas     = 0;
    accreted = false;
    // properties
    size        = 0;
    radius      = 0;
    rho         = 0;
    velocity    = 0;
    vdrift      = 0;
    vviscous    = 0;
    St          = 0;
    vrelonvfrag = 0;
    growthrate  = 0;

    part_number = particle_count++;

    set_filename();
    init_outfile();

}

Particle::Particle(double s, double r, double rh): Particle() {
    this->size   = s;
    this->radius = r;
    this->rho    = rh;
}

bool Particle::isAccreted() { return accreted; }

string Particle::get_filename() { return file; }

void Particle::init_units() {
    this->radius *= constants::au;
    this->rho    *= 1000;
    // TODO: calculate rho in function of rho1 and rho2 when state changes are involved
}

void Particle::update_size(double dt, Disc& disc) {

    double ts = 0;
    double vrel = 0;

    ts = rho*size / (disc.get_rhog(radius) * disc.get_cs(radius));
    St = ts * disc.get_omega_k(radius);

    if (disc.get_igrow() == 1) {
        vrel = sqrt(pow(2,(3./2.))*disc.get_alpha()*constants::Ro) * disc.get_cs(radius) * sqrt(St)/(1+St);
        growthrate = disc.get_epsi(radius)*disc.get_rhog(radius)/rho*vrel;
        if (disc.get_ifrag() == 0) {
            vrelonvfrag = vrel;
        }
        else {
            switch(disc.get_isnow()) {
                case(0):
                    vrelonvfrag = vrel/disc.get_vfrag();
                    break;
                case(1):
                    if (radius<=disc.get_rsnow()) {
                        vrelonvfrag = vrel / disc.get_vfragin();
                        iam = 1;
                    }
                    else {
                        vrelonvfrag = vrel / disc.get_vfragout();
                        iam = 2;
                    }
                    break;
                case(2):
                    if (disc.get_Temp(radius) >= disc.get_Tsnow()) {
                        vrelonvfrag = vrel / disc.get_vfragin();
                        iam = 1;
                    }
                    else {
                        vrelonvfrag = vrel / disc.get_vfragout();
                        iam = 2;
                    }
                    break;
            }
        }

        if (vrelonvfrag < 1. || disc.get_ifrag() == 0) size += growthrate * dt;
        if (vrelonvfrag >= 1. && disc.get_ifrag() > 0) size -= growthrate * dt;
        if (size < disc.get_smin()) size = disc.get_smin();
    }
    else {
        vrelonvfrag = 0.;
        growthrate  = 0.;
    }
}

void Particle::update_state(double dt, Disc& disc) {}

void Particle::update_radius(double dt, Disc& disc) {

    vdrift   = disc.get_vdrift(St,radius);
    vviscous = disc.get_vvisc(St,radius);
    velocity = vdrift + vviscous;

    radius  += velocity*dt;

    if (radius <= disc.get_racc()) {
        accreted = true;
        radius = disc.get_racc();
    }
}

void Particle::write_in_file(double time, Disc& disc) {

    fstream out;
    out.open(file, ios::out | ios::app);
    // width - precision - value
    column_format(out, 10, 8, time/constants::years);
    column_format(out, 10, 8, radius/constants::au);
    column_format(out, 10, 8, velocity);
    column_format(out, 10, 8, vdrift);
    column_format(out, 10, 8, vviscous);
    column_format(out, 10, 8, size);
    column_format(out, 10, 8, growthrate);
    column_format(out, 10, 8, St);
    column_format(out, 10, 8, vrelonvfrag);
    column_format(out, 10, 8, rho);
    column_format(out, 10, 8, disc.get_rhog(radius));
    column_format(out, 10, 8, disc.get_epsi(radius));
    column_format(out, 10, 8, disc.get_press(radius));
    out << endl;
    out.close();
}

/*************************************/
/************** PRIVATE **************/
/*************************************/

void Particle::set_filename() {

    stringstream number_ss;
    number_ss << part_number;
    string zeros;

    if (part_number < 10) { zeros = "000"; }
    else if (part_number < 100) { zeros = "00"; }
    else { zeros = "0"; }

    file = "p_" + zeros + number_ss.str() + ".dat";
}

void Particle::init_outfile() {
    fstream out;
    out.open(file, ios::out);
    column_format(out, 10, 8, "time");
    column_format(out, 10, 8, "radius");
    column_format(out, 10, 8, "vdust");
    column_format(out, 10, 8, "vdrift");
    column_format(out, 10, 8, "vvisc");
    column_format(out, 10, 8, "size");
    column_format(out, 10, 8, "dsdt");
    column_format(out, 10, 8, "St");
    column_format(out, 10, 8, "vrelvfrag");
    column_format(out, 10, 8, "rhos");
    column_format(out, 10, 8, "rhog");
    column_format(out, 10, 8, "epsilon");
    column_format(out, 10, 8, "pressure");
    out << endl;
    out.close();
}
