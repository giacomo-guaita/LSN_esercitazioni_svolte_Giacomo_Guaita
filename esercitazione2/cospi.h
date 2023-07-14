#pragma once

#include <cmath>


class cospi: public function{
    public:

    double eval(double x) const override{
        return M_PI/2*cos(M_PI*x/2);
    };

};