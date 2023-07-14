#include <iostream>
#include <iomanip>
#include <fstream>
#include <vector>


#include "random.h"
#include "MCIntegral.h"
#include "cospi.h"
#include "cos_taylor.h"
#include "statfunctions.h"




using namespace std;
 
int main (int argc, char *argv[]){

   Random rnd;
   rnd.FileSetRandom("Primes","seed.in");
   CosTaylor taylor(rnd);
   int N=1000;
   int L=100;
   int M=100;
   cospi coseno;
   MCIntegral integral(&rnd);

   vector<double> v_intunif;
   vector<double> v_intimpsamp;
   double unifsum, impsampsum;

   for(int j=0;j<M;j++){
      unifsum=0;
      impsampsum=0;
      for(int i=0;i<L;i++){
         unifsum+=integral.Unif(0,1,N,coseno); 
         impsampsum+=integral.ImpSamp(0,1,N,coseno,taylor);
      }
      v_intunif.push_back(unifsum/L);
      v_intimpsamp.push_back(impsampsum/L);
   }
   


   vector<double> mean_unif;
   vector<double> sigma_unif;
   vector<double> mean_impsamp;
   vector<double> sigma_impsamp;

   blockmeanstdm(v_intunif,mean_unif,sigma_unif);
   blockmeanstdm(v_intimpsamp,mean_impsamp,sigma_impsamp);



   ofstream fout1("unif.dat");
   ofstream fout2("impsamp.dat");
   
   if (fout1.is_open()and fout2.is_open()){
      fout1 << N << endl;
      fout2 << N << endl;
      for(int i=0;i<M;i++){
         fout1 << setw(20) << i+1 << setw(20) << mean_unif[i] << setw(20) << sigma_unif[i] << endl;
         fout2 << setw(20) << i+1 << setw(20) << mean_impsamp[i] << setw(20) << sigma_impsamp[i] << endl;

      }
   

   }else cerr << "Error: Unable to open unif.dat or impsamp.dat" << endl; 

   fout1.close();
   fout2.close();


   return 0;
}