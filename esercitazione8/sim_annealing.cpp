#include <iostream>
#include <fstream>
#include <iomanip>

#include "sim_annealing.h"


using namespace std;

sim_annealing::sim_annealing(Random* rnd){
    m_Rand = rnd;
    init=false;

}

void sim_annealing::initialize(double T_i,double T_f, double progression,double mu_i,double sigma_i,int n_operatios_per_block,int n_int_blocks,int n_int_steps){
    init=true;
    T=T_i;
    m_Tfin=T_f;
    m_prog=progression;
    nopt=n_operatios_per_block;
    mustep=0.1;
    sigmastep=0.1;
    nblocks=n_int_blocks;
    nsteps=n_int_steps;


    mu=mu_i;
    sigma=sigma_i;
}

void sim_annealing::optimize(double& bestmu,double& bestsigma,vector<double>& integral, vector<double>& uncertainty){
    
    if(init==false){
        cerr << "simulated annealing not initialized: initialize with initialize method." << endl;
        cerr << "exiting program!" << endl;
        exit(-1);
    }
    MetroIntegral integ(m_Rand, 1);
    psi2 wavefunction2(mu,sigma);
    integrand psiH(mu,sigma);
    
    double beta=1/T;
    double oldintvalue=integ.BlckIntegrate(nblocks,nsteps,psiH,wavefunction2);

    double blockcounter=1;
    double extraction;
    ofstream intvalue("int_optimization.dat");
    ofstream paravalue("parameter_optimization.dat");
    double integral_1,uncertainty_1;



    while(T>m_Tfin){
        
        accepted=0;
        attempted=0;
        do{
            do{

		        attempted++;

                newmu=mu+m_Rand->Rannyu(-mustep,mustep);
                newsigma=sigma+m_Rand->Rannyu(-sigmastep,sigmastep);
                while(newsigma<0) newsigma=sigma+m_Rand->Rannyu(-sigmastep,sigmastep);
		        wavefunction2.set_mu_sigma(newmu,newsigma);
                psiH.set_mu_sigma(newmu,newsigma);
                newintvalue=integ.BlckIntegrate(nblocks,nsteps,psiH,wavefunction2);

                //Per grossi valori di mu e piccoli valori di sigma le due gaussiane della funzione d'onda 
                //si allontanano molto e l'algoritmo di metropolis non è in grado di campionare la funzione
                //d'onda correttamente, dando dei valori dell'integrale assurdi.

                //Per questo ho aggiunto un controllo sul valore dell'integrale, se questo è assurdo viene scartato 
                //e viene motrato un messaggo di errore.
                if(newintvalue<-2){
                    cout << newintvalue << endl;
                    cout << "mu= " << newmu << "    sigma=" << newsigma << endl << "Integral value too high, exiting" << endl;

                }
                //cout << newintvalue << "       " << oldintvalue << endl;
                extraction=m_Rand->Rannyu();
	        }while((extraction>=exp(-beta*(newintvalue-oldintvalue)) or newintvalue<-2) and attempted < nopt);
	        
            if(extraction<exp(-beta*(newintvalue-oldintvalue)) and newintvalue>-2){
                accepted++;
                mu=newmu;
                sigma=newsigma;
                oldintvalue=newintvalue;
            }
        }while(attempted<nopt);
        cout << "Block: " << blockcounter << endl << "T= " << T << endl << "Beta = " << beta << endl << "Acceptance rate = ";
        cout << accepted/(double)attempted << endl << "step = " << mustep << endl << "Mu= " << mu << "     Sigma= " << sigma << endl;
        cout << "---------------------------------------------------" << endl << endl;

        
        integral_1=integ.BlckIntegrate(100,nsteps,psiH,wavefunction2,uncertainty_1);

        intvalue << blockcounter << setw(15) << T << setw(15) << integral_1 << setw(15) << uncertainty_1 << endl;
        paravalue << blockcounter << setw(15) << T << setw(15) << mu << setw(15) << sigma << endl;
        


        //modificatore di passo, il passo si allunga per bassa accettazione e si accorcia per alta accettzazione
        sigmastep*=(1+1.9*(accepted/(double)attempted-0.5));
        mustep*=(1+1.9*(accepted/(double)attempted-0.5));
    
        blockcounter++;
        T*=m_prog;
        beta=1/T;
    }

    wavefunction2.set_mu_sigma(newmu,newsigma);
    psiH.set_mu_sigma(newmu,newsigma);

    
    ofstream camp("campionamento.dat");
    integ.BlckIntegrate(500,nsteps,psiH,wavefunction2,integral,uncertainty,camp);
    camp.close();
    


    cout << "Optimization complete: passing optimized parameters and precise integral value to main" << endl;
    bestmu=mu;
    bestsigma=sigma;

    intvalue.close();
    paravalue.close();
}