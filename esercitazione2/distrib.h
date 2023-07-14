#pragma once


#include "random.h"


class Distrib{
    public:
    virtual double eval(double x)const=0;
    virtual double extract()const=0;


    protected:

    Random* m_rand;


};