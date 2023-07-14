/****************************************************************
*****************************************************************
    _/    _/  _/_/_/  _/       Numerical Simulation Laboratory
   _/_/  _/ _/       _/       Physics Department
  _/  _/_/    _/    _/       Universita' degli Studi di Milano
 _/    _/       _/ _/       Prof. D.E. Galli
_/    _/  _/_/_/  _/_/_/_/ email: Davide.Galli@unimi.it
*****************************************************************
*****************************************************************/

#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>
#include <vector>
#include <cmath>
#include "random.h"

using namespace std;
 
int main (int argc, char *argv[]){

   Random rnd;
   int seed[4];
   int p1, p2;
   ifstream Primes("Primes");
   if (Primes.is_open()){
      Primes >> p1 >> p2 ;
   } else cerr << "PROBLEM: Unable to open Primes" << endl;
   Primes.close();

   ifstream input("seed.in");
   string property;
   if (input.is_open()){
      while ( !input.eof() ){
         input >> property;
         if( property == "RANDOMSEED" ){
            input >> seed[0] >> seed[1] >> seed[2] >> seed[3];
            rnd.SetRandom(seed,p1,p2);
         }
      }
      input.close();
   } else cerr << "PROBLEM: Unable to open seed.in" << endl;

   /*for(int i=0; i<20; i++){
      cout << rnd.Rannyu() << endl;
   }*/

   


   int M=10000;     // numero lanci
   int N=100;           // numero blocchi
   int L=double(M)/N;   // numero di tiri per blocco, scegliere M multiplo di N



   
   vector<double> v_mean;
   vector<double> v_sigma2;
   double sum;
   double sum2;
   double appo;

   for(int i=0;i<N;i++){
      sum=0;
      sum2=0;
      for(int j=0;j<L;j++){
         appo=rnd.Rannyu();
         sum+=appo;
         sum2+=(appo-0.5)*(appo-0.5);

      }
      v_mean.push_back(double(sum)/L);
      v_sigma2.push_back(sum2/L);
   }


   double accumulo=0;
   double accumulo2=0;
   double expectation;
   double uncertainty;

   double accsigma2=0;
   double accsigma4=0;
   double sigma2;
   double uncertaintysigma2;

   


   ofstream fout1("Media.dat");
   ofstream fout2("Sigma2.dat");
   if (fout1.is_open()and fout2.is_open()){
      fout1 << setw(20) << L << endl;
      fout2 << setw(20) << L << endl;
      for(int i=0;i<N;i++){
         accumulo+=v_mean[i];
         accumulo2+=v_mean[i]*v_mean[i];

         accsigma2+=v_sigma2[i];
         accsigma4+=v_sigma2[i]*v_sigma2[i];


         expectation=accumulo/(i+1);
         sigma2=accsigma2/(i+1);
         if(i==0){
            uncertainty=0;
            uncertaintysigma2=0;
         } else{
            uncertainty=sqrt((accumulo2/(i+1)-expectation*expectation)/i);
            uncertaintysigma2=sqrt((accsigma4/(i+1)-sigma2*sigma2)/i);
         }

         fout1 << setw(20) << i+1 << setw(20) << expectation << setw(20) << uncertainty << endl;
         fout2 << setw(20) << i+1 << setw(20) << sigma2 << setw(20) << uncertaintysigma2 << endl;


      }
   }else cerr << "Error: Unable to open Media.dat or Sigma2.dat" << endl;
      
   







   fout2.close();
   fout1.close();
   rnd.SaveSeed();
   return 0;
}

/****************************************************************
*****************************************************************
    _/    _/  _/_/_/  _/       Numerical Simulation Laboratory
   _/_/  _/ _/       _/       Physics Department
  _/  _/_/    _/    _/       Universita' degli Studi di Milano
 _/    _/       _/ _/       Prof. D.E. Galli
_/    _/  _/_/_/  _/_/_/_/ email: Davide.Galli@unimi.it
*****************************************************************
*****************************************************************/
