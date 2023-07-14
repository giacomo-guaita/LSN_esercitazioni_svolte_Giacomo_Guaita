#include <iostream>
#include <cmath>
#include <fstream>
#include <iomanip>
#include <vector>

#include "random.h"
#include "sim_annealing.h"


using namespace std;


int main(){

    Random rnd;
    rnd.FileSetRandom("Primes","seed.in");

    //starting values for integral parameters
    double mu = 1;
    double sigma = 1;
    vector<double> bestintegral,besterror;

    //integral steps and blocks
    int nsteps=1000;
    int nblocks=50;

    //simulated annealing parameters
    double prog=0.8;
    double starting_T=1;
    double final_T=pow(10,-3);
    int n_operations_per_block=30;

    //simulated annealing class initialization
    sim_annealing sim(&rnd);
    sim.initialize(starting_T,final_T,prog,mu,sigma,n_operations_per_block,nblocks,nsteps);

    sim.optimize(mu,sigma,bestintegral,besterror);

    cout << "Optimized mu: " << mu << endl;
    cout << "Optimized sigma: " << sigma << endl;
    cout << "Integral value for these parameters: " << bestintegral[bestintegral.size()-1] << endl;
    cout << "Integral uncertainty for these parameters: " << besterror[besterror.size()-1] << endl;


    ofstream bestint("opt_int_blocks.dat");
    
    for(unsigned int i=0;i<bestintegral.size();i++){
        bestint << i+1 << setw(15) << bestintegral[i] << setw(15) << besterror[i] << endl;
    }
    bestint.close();

    return 0;
}