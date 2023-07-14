#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>
#include <vector>
#include <cmath>
#include "random.h"
#include "statfunctions.h"

using namespace std;
 
int main (int argc, char *argv[]){

    Random rnd;
    rnd.FileSetRandom("Primes","seed.in");

    int N_blocks=3000;
    vector<double> pi;

    int N_thr=1000;
    int N_hit;

    double L=3;
    double d=4;

    double y1;
    double x2;
    double y2;

    for(int j=0;j<N_blocks;j++){
        N_hit=0;
        for(int i=0;i<N_thr;i++){
            y1=rnd.Rannyu(0,d);
            do{
                x2=rnd.Rannyu(-L,L+0.1);
                y2=rnd.Rannyu(-L,L+0.1);
            }while(x2*x2+y2*y2>L*L);
            if(y1+y2*L/sqrt(x2*x2+y2*y2)>=d or y1+y2*L/sqrt(x2*x2+y2*y2)<=0){
            N_hit++; 
            }
        }
        pi.push_back(2*L*N_thr/(N_hit*d));
    }

    vector<double> pi_mean;
    vector<double> pi_uncertainty;

    blockmeanstdm(pi,pi_mean,pi_uncertainty);


    ofstream fout("Pi.dat");
    if (fout.is_open()){
        fout << N_thr << endl;
        for(int i=0;i<N_blocks;i++){
            fout << setw(20) << i+1 << setw(20) << pi_mean[i] << setw(20) << pi_uncertainty[i] << endl;
        }

    }else cerr << "Error: Unable to open Pi.dat" << endl;
    fout.close();







    return 0;
}