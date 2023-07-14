#include <iostream>
#include <iomanip>
#include <fstream>
#include <vector>


#include "random.h"
#include "BSprice.h"
#include "statfunctions.h"




using namespace std;
 
int main (int argc, char *argv[]){

    Random rnd;
    rnd.FileSetRandom("Primes","seed.in");
    BSprice price(rnd);
   
    double T=1;
    double S_0=100;
    double r=0.1;
    double K=100;
    double sigma=0.25;
    double t=0;

    int nsteps=100; //nuero passi nel calcolo del moto browniano geometrico

    int N=100; //numero estrazioni per blocco
    int M=200; //numero blocchi


    vector<double> Call;
    vector<double> Put;
    vector<double> Call_steps;
    vector<double> Put_steps;


    for(int i=0;i<M;i++){
        Call.push_back(price.Call(t,T,S_0,K,r,0,sigma,N));
        Put.push_back(price.Put(t,T,S_0,K,r,0,sigma,N));
        Call_steps.push_back(price.Call_steps(t,T,S_0,K,r,0,sigma,nsteps,N));
        Put_steps.push_back(price.Put_steps(t,T,S_0,K,r,0,sigma,nsteps,N));
    }
    
    vector<double> mean_call;
    vector<double> dev_call;
    vector<double> mean_put;
    vector<double> dev_put;
    vector<double> mean_callsteps;
    vector<double> dev_callsteps;
    vector<double> mean_putsteps;
    vector<double> dev_putsteps;

    blockmeanstdm(Call,mean_call,dev_call);
    blockmeanstdm(Put,mean_put,dev_put);
    blockmeanstdm(Call_steps,mean_callsteps,dev_callsteps);
    blockmeanstdm(Put_steps,mean_putsteps,dev_putsteps);


    ofstream call("call.dat");
    ofstream put("put.dat");
    ofstream call_steps("callstp.dat");
    ofstream put_steps("putstp.dat");

    if (call.is_open()and put.is_open() and call_steps.is_open() and put_steps.is_open()){
        call << N << endl;
        call_steps << N << endl;
        put << N << endl;
        put_steps << N << endl;
        for(int i=0;i<M;i++){
            call << setw(20) << i+1 << setw(20) << mean_call[i] << setw(20) << dev_call[i] << endl;
            call_steps << setw(20) << i+1 << setw(20) << mean_callsteps[i] << setw(20) << dev_callsteps[i] << endl;
            put_steps << setw(20) << i+1 << setw(20) << mean_putsteps[i] << setw(20) << dev_putsteps[i] << endl;
            put << setw(20) << i+1 << setw(20) << mean_put[i] << setw(20) << dev_put[i] << endl;

        }

         
    }else cerr << "Error: Unable to open call.dat or put.dat or callstp.dat or putstp.dat" << endl;






    return 0;
}