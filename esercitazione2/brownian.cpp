#include "brownian.h"
#include "statfunctions.h"


#include <cmath>
#include <iostream>
#include <iomanip>
#include <fstream>


using namespace std;



Brownian::Brownian(Random& rnd){
    m_rnd=&rnd;
}

void Brownian::xyzstep(int i){
    int choose = m_rnd->Rannyu(0,3);
    int dir = m_rnd->Rannyu(0,2);
    if(dir==0){
        dir=-1;
    }
    if(choose == 0){
        m_pos[i].Addx(dir);
    }else if(choose == 1){
        m_pos[i].Addy(dir);
    }else if(choose == 2){
        m_pos[i].Addz(dir);
    }
}

void Brownian::thetaphistep(int i){
    m_pos[i].Addrthetaphi(1,m_rnd->Rannyu(0,M_PI),m_rnd->Rannyu(0,2*M_PI));
}



void Brownian::xyzsimulate(vector<double>& radius, int nsteps, int N){
    radius.resize(nsteps);
    m_pos.resize(N);
    for(int i=0;i<N;i++){
        m_pos[i] = Position();
    }
    for(int i=0;i<nsteps;i++){
        radius[i]=0;
        for(int isim=0;isim<N;isim++){
            xyzstep(isim);
            radius[i]+= m_pos[isim].Getr2();
        }
        radius[i]=sqrt(radius[i]/N);
    }
}


void Brownian::thetaphisimulate(vector<double>& radius, int nsteps, int N){
    radius.resize(nsteps);
    m_pos.resize(N);
    for(int i=0;i<N;i++){
        m_pos[i] = Position();
    }
    for(int i=0;i<nsteps;i++){
        radius[i]=0;
        for(int isim=0;isim<N;isim++){
            thetaphistep(isim);
            radius[i]+= m_pos[isim].Getr2();
        }
        radius[i]=sqrt(radius[i]/N);
    }
}



void Brownian::blockxyzsimulate(vector<double>& mean, vector<double>& uncertainty, int nsteps, int N, int nblocks){
    mean.resize(nsteps);
    uncertainty.resize(nsteps);
    m_pos.resize(N*nblocks);
    vector<double> radius;
    std::ofstream of("Draw_xyz.dat");

    for(int i=0;i<N*nblocks;i++){
        m_pos[i] = Position();
    }
    for(int i=0;i<nsteps;i++){
        radius.resize(0);
        for(int iblock=0;iblock<nblocks;iblock++){
            radius.push_back(0);
            for(int isim=iblock*N;isim<(iblock+1)*N;isim++){
                xyzstep(isim);
                if(isim==0) of << i << setw(15) << m_pos[isim].Getx() << setw(15) << m_pos[isim].Gety() << setw(15) << m_pos[isim].Getz() << std::endl;
                radius[iblock]+= m_pos[isim].Getr2();
            }
            radius[iblock]=sqrt(radius[iblock]/N);
        }
        meandstd(radius,mean[i],uncertainty[i]);
    }
    of.close();
}


void Brownian::blockthetaphisimulate(vector<double>& mean, vector<double>& uncertainty, int nsteps, int N, int nblocks){
    mean.resize(nsteps);
    uncertainty.resize(nsteps);
    m_pos.resize(N*nblocks);
    vector<double> radius;
    std::ofstream of("Draw_thetaphi.dat");

    for(int i=0;i<N*nblocks;i++){
        m_pos[i] = Position();
    }
    for(int i=0;i<nsteps;i++){
        radius.resize(0);
        for(int iblock=0;iblock<nblocks;iblock++){
            radius.push_back(0);
            for(int isim=iblock*N;isim<(iblock+1)*N;isim++){
                thetaphistep(isim);
                if(isim==0) of << i << setw(15) << m_pos[isim].Getx() << setw(15) << m_pos[isim].Gety() << setw(15) << m_pos[isim].Getz() << std::endl;
                radius[iblock]+= m_pos[isim].Getr2();
            }
            radius[iblock]=sqrt(radius[iblock]/N);
        }
        meandstd(radius,mean[i],uncertainty[i]);
    }
    of.close();
}


