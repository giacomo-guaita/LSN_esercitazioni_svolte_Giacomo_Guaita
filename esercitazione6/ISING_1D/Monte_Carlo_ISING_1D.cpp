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
#include <fstream>
#include <ostream>
#include <cmath>
#include <iomanip>
#include "Monte_Carlo_ISING_1D.h"

using namespace std;

int main()
{ 
  Input(); //Inizialization
  for(int iblk=1; iblk <= nblk; ++iblk) //Simulation
  {
    Reset(iblk);   //Reset block averages
    for(int istep=1; istep <= nstep; ++istep)
    {
      Move(metro);
      Measure();
      Accumulate(); //Update block averages
    }
    Averages(iblk);   //Print results for current block
  }
  ConfFinal(); //Write final configuration

  return 0;
}


void Input(void)
{
  ifstream ReadInput;

  cout << "Classic 1D Ising model             " << endl;
  cout << "Monte Carlo simulation             " << endl << endl;
  cout << "Nearest neighbour interaction      " << endl << endl;
  cout << "Boltzmann weight exp(- beta * H ), beta = 1/T " << endl << endl;
  cout << "The program uses k_B=1 and mu_B=1 units " << endl;

//Read seed for random numbers
   int p1, p2;
   ifstream Primes("Primes");
   Primes >> p1 >> p2 ;
   Primes.close();

   ifstream input("seed.in");
   input >> seed[0] >> seed[1] >> seed[2] >> seed[3];
   rnd.SetRandom(seed,p1,p2);
   input.close();
  
//Read input informations
  ReadInput.open("input.dat");

  ReadInput >> temp;
  beta = 1.0/temp;
  cout << "Temperature = " << temp << endl;

  ReadInput >> nspin;
  cout << "Number of spins = " << nspin << endl;

  ReadInput >> J;
  cout << "Exchange interaction = " << J << endl;

  ReadInput >> h;
  cout << "External field = " << h << endl << endl;
    
  ReadInput >> metro; // if=1 Metropolis else Gibbs

  ReadInput >> nblk;

  ReadInput >> nstep;

  ReadInput >> inconf;

  if(metro==1) cout << "The program perform Metropolis moves" << endl;
  else cout << "The program perform Gibbs moves" << endl;
  if(inconf==0) cout << "The program starts from a random configuration" << endl;
  else cout << "The program starts from the previous configuration" << endl;
  cout << "Number of blocks = " << nblk << endl;
  cout << "Number of steps in one block = " << nstep << endl << endl;
  ReadInput.close();


//Prepare arrays for measurements
  iu = 0; //Energy
  ic = 1; //Heat capacity
  im = 2; //Magnetization
  ix = 3; //Magnetic susceptibility
 
  n_props = 4; //Number of observables

//initial configuration
  if(inconf==0){ //random configuration
    for (int i=0; i<nspin; ++i)
    {
      if(rnd.Rannyu() >= 0.5) s[i] = 1;
      else s[i] = -1;
    }
  }else{         //previous configuration
    ifstream conf("config.final");
    if(!conf.is_open()) cerr << "Not able to open config.final" << endl;
    int sp;
    for (int i=0; i<nspin; ++i){
      conf >> sp;
      s[i]=sp;
    }
    conf.close();
  }
  
//Evaluate energy etc. of the initial configuration
  Measure();

//Print initial values for the potential energy and virial
  cout << "Initial energy = " << walker[iu] << endl;
}


void Move(int metro)
{
  int o;
  double energy_old, energy_new;
  //double energy_up, energy_down;

  for(int i=0; i<nspin; ++i)
  {
    attempted++;
  //Select randomly a particle (for C++ syntax, 0 <= o <= nspin-1)
    o = (int)(rnd.Rannyu()*nspin);

    if(metro==1) //Metropolis
    {
      energy_old=walker[iu];
      energy_new=energy_old-Boltzmann(s[o],o);
      s[o]*=-1;
      energy_new+=Boltzmann(s[o],o); 
      if(rnd.Rannyu()<exp(-beta*(energy_new-energy_old))){
        walker[iu]=energy_new;
        accepted++;
      }else s[o]*=-1;
      

    }
    else //Gibbs sampling
    {
      if(rnd.Rannyu()<1/(1+exp(-2*beta*(J*(s[Pbc(o-1)]+s[Pbc(o+1)])+h)))) s[o]=1;
      else s[o]=-1;

    }
  }
}

double Boltzmann(int sm, int ip)
{
  double ene = -J * sm * ( s[Pbc(ip-1)] + s[Pbc(ip+1)] ) - h * sm;
  return ene;
}

void Measure()
{
  //int bin;
  double u = 0.0, m = 0.0, Hi = 0.0, stot = 0.0;

//cycle over spins
  for (int i=0; i<nspin; ++i)
  {
    stot += s[i];
    Hi = -J * s[i] * s[Pbc(i+1)] - 0.5 * h * (s[i] + s[Pbc(i+1)]);
    u += Hi;
    m += Hi*Hi;
  }
  u /= nspin;
  m /= nspin;

  walker[iu] = u;
  walker[ic] = beta*beta*(m-u*u);
  walker[ix] = beta*stot*stot/nspin;
  walker[im] = stot/nspin;
}


void Reset(int iblk) //Reset block averages
{
   
   if(iblk == 1)
   {
       for(int i=0; i<n_props; ++i)
       {
           glob_av[i] = 0;
           glob_av2[i] = 0;
       }
   }

   for(int i=0; i<n_props; ++i)
   {
     blk_av[i] = 0;
   }
   blk_norm = 0;
   attempted = 0;
   accepted = 0;
}


void Accumulate(void) //Update block averages
{

   for(int i=0; i<n_props; ++i)
   {
     blk_av[i] = blk_av[i] + walker[i];
   }
   blk_norm = blk_norm + 1.0;
}


void Averages(int iblk) //Print results for current block
{
    
   ofstream Ene, Heat, Mag, Chi;
   const int wd=12;
    
    cout << "Block number " << iblk << endl;
    if(metro==1) cout << "Acceptance rate " << accepted/attempted << endl << endl;
    
    Ene.open("output.ene.0",ios::app);
    Heat.open("output.heat.0",ios::app);
    Mag.open("output.mag.0",ios::app);
    Chi.open("output.chi.0",ios::app);
    for(int i=0;i<n_props;i++){
      stima[i] = blk_av[i]/blk_norm;
      glob_av[i]  += stima[i];
      glob_av2[i] += stima[i]*stima[i];
      err[i]=Error(glob_av[i],glob_av2[i],iblk);
    }
    Ene << setw(wd) << iblk <<  setw(wd) << stima[iu] << setw(wd) << glob_av[iu]/(double)iblk << setw(wd) << err[iu] << endl;
    Ene.close();
    Heat << setw(wd) << iblk <<  setw(wd) << stima[ic] << setw(wd) << glob_av[ic]/(double)iblk << setw(wd) << err[ic] << endl;
    Heat.close();
    Mag << setw(wd) << iblk <<  setw(wd) << stima[im] << setw(wd) << glob_av[im]/(double)iblk << setw(wd) << err[im] << endl;
    Mag.close();
    Chi << setw(wd) << iblk <<  setw(wd) << stima[ix] << setw(wd) << glob_av[ix]/(double)iblk << setw(wd) << err[ix] << endl;
    Chi.close();


    cout << "----------------------------" << endl << endl;
}


void ConfFinal(void)
{
  ofstream WriteConf;

  cout << "Print final configuration to file config.final " << endl << endl;
  WriteConf.open("config.final");
  for (int i=0; i<nspin; ++i)
  {
    WriteConf << s[i] << endl;
  }
  WriteConf.close();

  const int wd=12;

  ofstream Data;
  cout << "Print global averege of properties to file data.out " << endl << endl;
  Data.open("data.out",ios::app);
  Data << temp;
  for (int i=0; i<n_props; ++i)
  {
    Data << setw(wd) << glob_av[i]/(double)nblk << setw(wd) << err[i];
  }
  Data << endl;
  Data.close();

  rnd.SaveSeed();
}

int Pbc(int i)  //Algorithm for periodic boundary conditions
{
    if(i >= nspin) i = i - nspin;
    else if(i < 0) i = i + nspin;
    return i;
}

double Error(double sum, double sum2, int iblk)
{
    if(iblk==1) return 0.0;
    else return sqrt((sum2/(double)iblk - pow(sum/(double)iblk,2))/(double)(iblk-1));
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
