#pragma once

#include <cmath>


class psi2: public function{
    public:

    psi2(double mu,double sigma){
        m_mu=mu;
        m_sigma=sigma;
    };
    ~psi2(){};

    double eval(double x) const override{
        return pow(exp(-(x-m_mu)*(x-m_mu)/(2*m_sigma*m_sigma))+exp(-(x+m_mu)*(x+m_mu)/(2*m_sigma*m_sigma)),2);
    };

    void set_mu_sigma(double mu,double sigma){
        m_mu=mu;
        m_sigma=sigma;
    };

    private:
    double m_mu,m_sigma;

};