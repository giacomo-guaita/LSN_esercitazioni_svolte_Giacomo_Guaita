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
#include "statfunctions.h"

using namespace std;
 
int main (int argc, char *argv[]){

   Random rnd;
   rnd.FileSetRandom("Primes","seed.in");


   int L=100;           // numero per blocco
   int N=100;           // numero blocchi



   
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

   vector<double> mean_mean;
   vector<double> mean_uncertainty;

   vector<double> sigma2_mean;
   vector<double> sigma2_uncertainty;

   blockmeanstdm(v_mean,mean_mean,mean_uncertainty);
   blockmeanstdm(v_sigma2,sigma2_mean,sigma2_uncertainty);



   ofstream fout1("Media.dat");
   ofstream fout2("Sigma2.dat");
   if (fout1.is_open()and fout2.is_open()){
         fout1 << L << endl;
         fout2 << L << endl;
      for(int i=0;i<N;i++){
         fout1 << setw(20) << i+1 << setw(20) << mean_mean[i] << setw(20) << mean_uncertainty[i] << endl;
         fout2 << setw(20) << i+1 << setw(20) << sigma2_mean[i] << setw(20) << sigma2_uncertainty[i] << endl;
      }

         
   }else cerr << "Error: Unable to open Media.dat or Sigma2.dat" << endl;
      
   fout2.close();
   fout1.close();


   int iterations=500;
   int M=100;
   int n=10000;
   vector<int> bins(M);
   
   fout1.open("Chi2.dat");


   if (fout1.is_open()){
      for(int j=0;j<iterations;j++){
         fill(bins.begin(), bins.end(), 0);
         for(int i=0;i<n;i++){
            bin(rnd.Rannyu(),bins,double(1)/M,0,0,M);
         }
         fout1 << chi2(bins,double(n)/M) << endl;
         /*for(int i=0;i<M;i++){
            cout << bins[i] << endl;
         }
         cout << endl << endl << endl;*/
      }
   }else cerr << "Error: Unable to open Chi2.dat" << endl;

   


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
