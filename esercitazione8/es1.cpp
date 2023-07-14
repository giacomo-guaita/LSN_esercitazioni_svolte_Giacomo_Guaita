#include <iostream>
#include <vector>
#include <iomanip>
#include <fstream>


#include "random.h"
#include "MetroIntegral.h"
#include "psi2.h"
#include "Integrand.h"
#include "statfunctions.h"

int main(){

    Random rnd;
    rnd.FileSetRandom("Primes","seed.in");
    double step= 4;
    double mu = 1;
    double sigma = 0.5;
    int nsteps=1000;
    int nblocks=1000;
    vector<double> integrals;

    MetroIntegral integ(&rnd,step);
    psi2 wavefunction2(mu,sigma);
    integrand psiH(mu,sigma);

    ofstream out("integrals.dat");

    for(int i=0;i<nblocks;i++){
        
        integrals.push_back(integ.Integrate(nsteps,psiH,wavefunction2));
        cout << "Acceptance rate: " << integ.Get_acceptancerate() << endl;
        cout << "Step: " << integ.Get_usedstep() << endl;
        cout << endl << "-------------------------------------------------------------" << endl;
    }

    vector<double> intmean;
    vector<double> intsigma;

    blockmeanstdm(integrals,intmean,intsigma);

    for(int i=0;i<nblocks;i++){
        out << i << setw(20) << intmean[i] << setw(20) << intsigma[i] << endl;
    }


    cout << endl << endl << "Integral value: " << intmean[intmean.size()-1] << endl << "Integral uncertainty: " << intsigma[intsigma.size()-1] << endl;
    



    return 0;
}