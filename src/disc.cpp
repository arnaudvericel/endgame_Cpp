#include "../include/disc.h"

using namespace constants;

/*************************************/
/************** PUBLIC ***************/
/*************************************/

Disc::Disc() {
    // disc related
    p     = 0;
    q     = 0;
    mdisc = 0;
    mstar = 0;
    racc  = 0;
    rin   = 0;
    rout  = 0;
    rzero = 0;
    Tzero = 0;
    mu    = 0;
    alpha = 0;
    phi   = 0;
    w     = 0;

    // at rzero
    cszero     = 0;
    rhogzero   = 0;
    sigmagzero = 0;

    // dust related
    epsilon = 0;
    rhoin   = 0;
    rhoout  = 0;
    smin    = 0;
    epsimax = 0;

    // physics options
    vfrag    = 0;
    vfragin  = 0;
    vfragout = 0;
    rsnow    = 0;
    rbump    = 0;
    Tsnow    = 0;
    abun     = 0;
    mratio   = 0;

    // control options
    igrow  = 0;
    ifrag  = 0;
    isnow  = 0;
    ibump  = 0;
    istate = 0;
    ibr    = 0;
}

/* GETTERS - FUNCTIONS */

double Disc::get_vk(double r) const { return get_omega_k(r)*r; }

double Disc::get_nu(double r) const { return alpha*get_cs(r)*get_h(r); }

double Disc::get_cs(double r) const { return cszero*pow((r/rzero),(-q/2.)); }

double Disc::get_sigmag(double r) const
{
    return sigmagzero*pow((r/rzero),(-p)) + 0.*phi*sigmagzero*exp(-pow((r-rbump),2)/(2*pow(w,2)));
}

double Disc::get_omega_k(double r) const { return sqrt(gg*mstar/pow(r,3)); }

double Disc::get_press(double r) const { return pow(get_cs(r),2) * get_rhog(r); }

double Disc::get_rhog(double r) const { return get_sigmag(r)/(sqrt(2*constants::pi)*get_h(r)); }

double Disc::get_h(double r) const { return get_cs(r)/get_omega_k(r); }

double Disc::get_hoverr(double r) const { return get_h(r)/r; }

double Disc::get_Temp(double r) const { return Tzero*pow(r/rzero,-q); }

double Disc::get_epsi(double r) const { return epsilon + ibump*(epsimax-epsilon)*exp(-pow((r-rbump),2)/(2*pow(w,2))); }

double Disc::get_vdrift(double St, double r) const
{
    double deriv = pow(get_hoverr(r),2) * get_vk(r) * ((get_press(r+constants::earthr) - get_press(r-constants::earthr))/(2*constants::earthr)) * r/get_press(r);
    double eps = 0;

     if (ibr == 1) { eps = get_epsi(r); }

     return St / (pow((1.+eps),2) + pow(St,2)) * deriv;
}
double Disc::get_vvisc(double St, double r) const {

    double K = 3./(r*get_rhog(r)*get_vk(r));
    double deriv = (get_rhog(r+constants::earthr)*get_nu(r+constants::earthr)*(r+constants::earthr)*get_vk(r+constants::earthr) - get_rhog(r-constants::earthr)*get_nu(r-constants::earthr)*(r-constants::earthr)*get_vk(r-constants::earthr)) / (2*constants::earthr);
    double eps = 0;

     if (ibr == 1) { eps = get_epsi(r); }

     return (1.+eps)/(pow((1+eps),2) + pow(St,2)) * K * deriv;
}

/* GETTERS - ATTRIBUTES */

double Disc::get_rzero() const { return rzero; }

double Disc::get_vfrag() const { return vfrag; }

double Disc::get_vfragin() const { return vfragin; }

double Disc::get_vfragout() const { return vfragout; }

double Disc::get_rsnow() const { return rsnow; }

double Disc::get_Tsnow() const { return Tsnow; }

double Disc::get_smin() const { return smin; }

double Disc::get_alpha() const { return alpha; }

double Disc::get_racc() const { return racc; }

int Disc::get_igrow() const { return igrow; }

int Disc::get_ifrag() const { return ifrag; }

int Disc::get_isnow() const { return isnow; }

int Disc::get_ibump() const { return ibump; }

int Disc::get_istate() const { return istate; }

int Disc::get_ibr() const { return ibr; }

/* METHODS */

void Disc::fill_disc_prop(ifstream& f) {

    // read disc properties from first part of instream f
    buffer_file(f,2);
    f >> p >> q >> mdisc >> mstar >> racc >> rin >> rout >> rzero >> Tzero >> mu >> alpha >> phi >> w;
    buffer_file(f,4);
    f >> epsilon >> rhoin >> rhoout >> smin >> epsimax;
    buffer_file(f,4);
    f >> vfrag >> vfragin >> vfragout >> rsnow >> rbump >> Tsnow >> abun >> mratio;
    buffer_file(f,4);
    f >> igrow >> ifrag >> isnow >> ibump >> istate >> ibr;
}

void Disc::init_units() {

    mdisc *= solarm;
    mstar *= solarm;
    rin   *= au;
    rout  *= au;
    rzero *= au;
    w     *= au;
    rsnow *= au;
    rbump *= au;

    if(!(abs(p-2.) < 1.e-5)) {
        sigmagzero = mdisc/(2*pi) / (pow(rzero,2)/(2-p)*(pow((rout/rzero),(2-p)) - pow((rin/rzero),(2-p))) + ibump*sqrt(pi/2)*w*(erf((rbump-rin)/(sqrt(2.)*w))-erf((rbump-rout)/(sqrt(2.)*w))));
    }
    else {
        sigmagzero = mdisc/(2*pi*pow(rzero,2)*log(rout/rin) + ibump*sqrt(pi/2)*w*(erf((rbump-rin)/(sqrt(2.)*w))-erf((rbump-rout)/(sqrt(2.)*w))));
    }
    cszero   = sqrt(kboltz*Tzero/(mu*mh));
    rhogzero = sigmagzero / (sqrt(2*pi)*cszero/get_omega_k(rzero));
}

void Disc::print_model() const {

    int width = 10;
    int preci = 2;

    cout << "--------------" << endl;
    cout << "The Physical properties of the disc at " << (int)(rzero/constants::au) << " AU" << endl;
    cout << left << setw(width) << "sigma_gas" << setw(2) << " = " << setprecision(preci) << scientific << sigmagzero << setw(width) << " kg/m2" << endl;
    cout << left << setw(width) << "cs" << setw(2) << " = " << setprecision(preci) << cszero << setw(width) << " m/s" << endl;
    cout << left << setw(width) << "rho_gas" << setw(2) << " = " << setprecision(preci) << rhogzero << setw(width) << " kg/m3" << endl;
    cout << left << setw(width) << "P_gas" << setw(2) << " = " << setprecision(preci) << get_press(rzero) << setw(width) << " Pa" << endl;
    cout << left << setw(width) << "H/R" << setw(2) << " = " << setprecision(preci) << get_hoverr(rzero) << endl;
    cout << "--------------" << endl;
}
