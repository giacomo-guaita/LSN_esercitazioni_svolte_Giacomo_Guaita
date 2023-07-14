#pragma once

#include <cmath>


class integrand: public function{
    public:

    integrand(double mu,double sigma){
        m_mu=mu;
        m_sigma=sigma;
    };
    ~integrand(){};

    double eval(double x) const override{
        return pow(x,4)-pow(x,2)*5/2.0+(m_mu*m_mu-m_sigma*m_sigma+x*x-2*m_mu*x*tanh(m_mu*x/(m_sigma*m_sigma)))/(-2*pow(m_sigma,4));
    };

    void set_mu_sigma(double mu,double sigma){
        m_mu=mu;
        m_sigma=sigma;
    };

    private:
    double m_mu,m_sigma;

};