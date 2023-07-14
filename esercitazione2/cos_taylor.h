#pragma once

#include <cmath>
#include "distrib.h"


class CosTaylor: public Distrib{
    public:
    CosTaylor(Random& rand){
        m_rand=&rand;
    }
    double eval(double x)const override{
        return -2*(x-1);
    }
    double extract()const override{
        return 1+sqrt(1-m_rand->Rannyu());
    }

};