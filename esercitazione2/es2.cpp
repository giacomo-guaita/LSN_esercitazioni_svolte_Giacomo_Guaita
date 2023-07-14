#include <iostream>
#include <iomanip>
#include <fstream>
#include <vector>
#include <cmath>


#include "random.h"
#include "brownian.h"



using namespace std;
 
int main (int argc, char *argv[]){

    Random rnd;
    rnd.FileSetRandom("Primes","seed.in");

    Brownian brown(rnd);
    
    int nsteps=100;
    int N=100; //numero simulazioni in un blocco
    int nblocks=100; //numero blocchi
    vector<double> meanxyz,uncertaintyxyz,meanthetaphi,uncertaintythetaphi;

    brown.blockxyzsimulate(meanxyz,uncertaintyxyz,nsteps,N,nblocks);
    brown.blockthetaphisimulate(meanthetaphi,uncertaintythetaphi,nsteps,N,nblocks);

    ofstream fout1("RWxyz.dat");
    ofstream fout2("RWthetaphi.dat");
    if (fout1.is_open()and fout2.is_open()){
        fout1 << N << endl;
        fout2 << N << endl;
        for(int i=0;i<nsteps;i++){
            fout1 << setw(20) << i+1 << setw(20) <<  meanxyz[i] << setw(20) << uncertaintyxyz[i]/sqrt(i) << endl;
            fout2 << setw(20) << i+1 << setw(20) <<  meanthetaphi[i] << setw(20) << uncertaintythetaphi[i]/sqrt(i) << endl;
        }
    }else cerr << "Error: Unable to open RWxyz.dat or RWthetaphi.dat" << endl;

   fout1.close();
   fout2.close();

    return 0;
}