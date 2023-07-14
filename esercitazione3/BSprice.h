#pragma once

#include "random.h"


class BSprice{

    public:

    BSprice(Random& rnd );
    ~BSprice(){;}


    double Brown(double t_i,double T_f, double X_i);
    double Brown(double t_i,double T_f, double mu, double sigma, double X_i);

    double GeoBrown(double t_i,double T_f,  double mu, double sigma, double X_i);
    double GeoBrown_steps(double t_i,double T_f,  double mu, double sigma, double X_i,int nsteps);

    double Call(double t,double T,double S_0,double K,double r,double mu,double sigma);
    double Put(double t,double T,double S_0,double K,double r,double mu,double sigma);
    double Call(double t,double T,double S_0,double K,double r,double mu,double sigma,int N_rolls);
    double Put(double t,double T,double S_0,double K,double r,double mu,double sigma,int N_rolls);

    double Call_steps(double t,double T,double S_0,double K,double r,double mu,double sigma,int nsteps);
    double Put_steps(double t,double T,double S_0,double K,double r,double mu,double sigma,int nsteps);
    double Call_steps(double t,double T,double S_0,double K,double r,double mu,double sigma,int nsteps,int N_rolls);
    double Put_steps(double t,double T,double S_0,double K,double r,double mu,double sigma,int nsteps,int N_rolls);



    private:

    Random* m_rnd;





};