#include "BSprice.h"

#include <cmath>

using namespace std;



BSprice :: BSprice(Random& rnd){
    m_rnd=&rnd;
}



double BSprice :: Brown(double t_i,double T_f, double X_i){
    return X_i + m_rnd->Gauss(0,1)*sqrt(T_f-t_i);
}
double BSprice :: Brown(double t_i,double T_f, double mu, double sigma, double X_i){
    return X_i + mu*(T_f-t_i) + sigma*m_rnd->Gauss(0,1)*sqrt(T_f-t_i);
}


double BSprice :: GeoBrown(double t_i,double T_f,  double mu, double sigma, double X_i){
    return X_i*exp((mu-0.5*sigma*sigma)*(T_f-t_i)+sigma*m_rnd->Gauss(0,1)*sqrt(T_f-t_i));
}
double BSprice :: GeoBrown_steps(double t_i,double T_f,  double mu, double sigma, double X_i,int nsteps){
    double GB_steps=X_i;
    for(int j=0;j<nsteps;j++){
        GB_steps=GeoBrown(t_i+j*(T_f-t_i)/nsteps,t_i+(j+1)*(T_f-t_i)/nsteps,mu,sigma,GB_steps);
    }
    return GB_steps;
}




double BSprice :: Call(double t,double T,double S_0,double K,double r,double mu,double sigma){
    return GeoBrown(t,T,mu,sigma,S_0)-K*exp(-r*(T-t));
}
double BSprice :: Put(double t,double T,double S_0,double K,double r,double mu,double sigma){
    return -GeoBrown(t,T,mu,sigma,S_0)+K*exp(-r*(T-t));
}
double BSprice :: Call(double t,double T,double S_0,double K,double r,double mu,double sigma,int N_rolls){
    double mean=0;
    for(int i=0;i<N_rolls;i++){
        mean+=max(Call(t,T,S_0,K,r,mu,sigma),double(0));
    }
    return mean/N_rolls;
}
double BSprice :: Put(double t,double T,double S_0,double K,double r,double mu,double sigma,int N_rolls){
    double mean=0;
    for(int i=0;i<N_rolls;i++){
        mean+=max(Put(t,T,S_0,K,r,mu,sigma),double(0));
    }
    return mean/N_rolls;
}




double BSprice :: Call_steps(double t,double T,double S_0,double K,double r,double mu,double sigma,int nsteps){
    return GeoBrown_steps(t,T,mu,sigma,S_0,nsteps)-K*exp(-r*(T-t));
}
double BSprice :: Put_steps(double t,double T,double S_0,double K,double r,double mu,double sigma,int nsteps){
    return -GeoBrown_steps(t,T,mu,sigma,S_0,nsteps)+K*exp(-r*(T-t));
}
double BSprice :: Call_steps(double t,double T,double S_0,double K,double r,double mu,double sigma,int nsteps,int N_rolls){
    double mean=0;
    for(int i=0;i<N_rolls;i++){
        mean+=max(Call_steps(t,T,S_0,K,r,mu,sigma,nsteps),double(0));
    }
    return mean/N_rolls;
}
double BSprice :: Put_steps(double t,double T,double S_0,double K,double r,double mu,double sigma,int nsteps,int N_rolls){
    double mean=0;
    for(int i=0;i<N_rolls;i++){
        mean+=max(Put_steps(t,T,S_0,K,r,mu,sigma,nsteps),double(0));
    }
    return mean/N_rolls;
}
   