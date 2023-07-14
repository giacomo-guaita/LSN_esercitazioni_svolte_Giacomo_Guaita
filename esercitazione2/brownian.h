#pragma once

#include<vector>

#include "random.h"
#include "position.h"


class Brownian{

    public:

    Brownian(Random&);
    ~Brownian(){;}

    void xyzstep(int i);
    void thetaphistep(int i);

    void xyzsimulate(std::vector<double>& radius, int nsteps, int N);
    void thetaphisimulate(std::vector<double>& radius, int nsteps, int N);

    void blockxyzsimulate(std::vector<double>& mean, std::vector<double>& uncertainty, int nsteps, int N, int nblocks);
    void blockthetaphisimulate(std::vector<double>& mean, std::vector<double>& uncertainty, int nsteps, int N, int nblocks);



    private:

    Random* m_rnd;
    std::vector<Position> m_pos;

};