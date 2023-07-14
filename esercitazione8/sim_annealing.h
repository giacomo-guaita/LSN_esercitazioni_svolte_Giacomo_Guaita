#pragma once

#include <vector>

#include "MetroIntegral.h"
#include "Integrand.h"
#include "psi2.h"


class sim_annealing{

    public:
    sim_annealing(Random*);
    void initialize(double T_i,double T_f, double progression,double mu_i,double sigma_i,int n_operatios_per_block,int n_int_blocks,int n_int_steps);
    void optimize(double& bestmu,double& bestsigma,std::vector<double>& integral, std::vector<double>& uncertainty);



    private:

    Random* m_Rand;

    bool init;
    int nopt,attempted,accepted;
    int nblocks,nsteps;
    double T, m_Tfin;
    double m_prog;
    double beta;
    double mustep,sigmastep;
    double oldintvalue,newintvalue;
    double newmu,newsigma,mu,sigma;
};

