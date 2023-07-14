#include <iostream>
#include <iomanip>
#include <fstream>
#include <vector>
#include "random.h"

using namespace std;
 
int main (int argc, char *argv[]){

    Random rnd;
    rnd.FileSetRandom("Primes","seed.in");

    int N[]{1,2,10,100};
    int iterations=10000;
    double lambda=1;
    double mu=0;
    double Gamma=1;
    double sum;

    ofstream fout("Exp.dat");
    if (fout.is_open()){

        for(int k=0;k<4;k++){
            fout << "Mean value of " << N[k] << " exponential distributions" << endl;
            for(int i=0;i<iterations;i++){
                sum=0;
                for(int j=0;j<N[k];j++){
                    sum+=rnd.Exp(lambda);
                }
                fout << sum/N[k] << endl;
            }
            fout << endl << endl << endl;
        }
    }else cerr << "Error: Unable to open Exp.dat" << endl;
    fout.close();

    fout.open("Lorentz.dat");
    if (fout.is_open()){

        for(int k=0;k<4;k++){
            fout << "Mean value of " << N[k] << " Lorentz-Cauchy distributions" << endl;
            for(int i=0;i<iterations;i++){
                sum=0;
                for(int j=0;j<N[k];j++){
                    sum+=rnd.Lorentz(mu,Gamma);
                }
                fout << sum/N[k] << endl;
            }
            fout << endl << endl << endl;
        }
    }else cerr << "Error: Unable to open Lorentz.dat" << endl;
    fout.close();

    
    fout.open("Dice.dat");
    if (fout.is_open()){

        for(int k=0;k<4;k++){
            fout << "Mean value of " << N[k] << "dice rolls" << endl;
            for(int i=0;i<iterations;i++){
                sum=0;
                for(int j=0;j<N[k];j++){
                    sum+=rnd.Dice();
                }
                fout << sum/N[k] << endl;
            }fout << endl << endl << endl;
        }
    }else cerr << "Error: Unable to open Dice.dat" << endl;
    fout.close();

   
    return 0;
}