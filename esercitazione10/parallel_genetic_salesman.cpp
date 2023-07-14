#include <iostream>
#include <iomanip>

#include "mpi.h"
#include "classes.h"
#include "random.h"


using namespace std;

int main(int argc, char* argv[]){

    int ncities=50;
    //int type=0;
    int npop=ncities*ncities;
    int ncycles=500;
    int N_migr=5;
    double frac_migr=5;

    MPI_Init(&argc, &argv);

    int size,rank;
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);


    Random rnd;

    //Inizializzazione differenziata per i generatori di numeri casuali per i diversi processi paalleli
    int seeds[4];
    int p1, p2;
    ifstream Primes("Primes");
    if (Primes.is_open()){
        for(int i=0;i<rank;i++){
            Primes >> p1 >> p1;
        }
        Primes >> p1 >> p2 ;
    }else cerr << "PROBLEM: Unable to open Primes" << endl;
    Primes.close();

    ifstream input("seed.in");
    string property;
    if (input.is_open()){
        while ( !input.eof() ){
            input >> property;
            if( property == "RANDOMSEED" ){
                input >> seeds[0] >> seeds[1] >> seeds[2] >> seeds[3];
                rnd.SetRandom(seeds,p1,p2);
            }
        }
        input.close();
    } else cerr << "PROBLEM: Unable to open seed.in" << endl;




    //Divisione della popolazione complessiva tra i processi paralleli
    // e inizializzazione della popolazione locale di ogni processo

    int mypop=npop/size;
    if(rank<npop%size) mypop++;
    population pop(&rnd);  
    pop.fileinit(ncities,mypop,"American_capitals.dat");
    
   
    

    pop.checkall();
    pop.order();

    int migrationtarget;
    int migrationreceiver;
    int msgrcv;
    int msgsnd;

    double mymean,mybest;
    vector<double> thebest;
    vector<double> themean;

    //Ritrovamento del miglior cromosoma a livello complessivo
    // e calcolo della media della miglior metà a livello compessivo

    mybest = pop.getbestlength();
    mymean = pop.getmeanlength();

    if(rank%size!=0){
        MPI_Send(&mybest,1,MPI_DOUBLE_PRECISION,0,0,MPI_COMM_WORLD);
        MPI_Send(&mymean,1,MPI_DOUBLE_PRECISION,0,1,MPI_COMM_WORLD);
    }
    if(rank%size==0){
        thebest.push_back(mybest);
        themean.push_back(mymean);
        for(int i=1;i<size;i++){
            MPI_Recv(&mybest,1,MPI_DOUBLE_PRECISION,i,0,MPI_COMM_WORLD,MPI_STATUS_IGNORE);
            MPI_Recv(&mymean,1,MPI_DOUBLE_PRECISION,i,1,MPI_COMM_WORLD,MPI_STATUS_IGNORE);
            thebest.push_back(mybest);
            themean.push_back(mymean);
        }
    }


    

    if(rank%size==0){

        ofstream best("best.dat",ios::app);
        ofstream mean("mean.dat",ios::app);

        mymean=0;
        mybest=thebest[0];

        
        for(int j=0;j<size;j++){
            mymean+=themean[j];
            if(thebest[j]<mybest) mybest=thebest[j];
        }

        
        
        best << "Generation" << setw(20) << "Length" << endl;
        mean << "Generation" << setw(20) << "Length" << endl;
        best << 0 << setw(20) << mybest << endl;
        mean << 0 << setw(20) << mymean/size << endl;

        best.close();
        mean.close();
    }

    int sendindex;
    int bestsearch=0;
    //ciclo di evoluzione della popolazione
    for(int i=1;i<ncycles+1;i++){
        pop.evolve();
        
        


        pop.checkall();
        pop.measure();
        pop.order();

        //Migrazione: passaggio e ricezione dei migliori cromosomi agli e dagli altri processi

        if(i%N_migr==0){
            
            migrationtarget=(rank+1)%size;
            migrationreceiver=(rank-1)%size;


            for(int j=0;j<mypop/frac_migr;j++){
                sendindex = pop.choose();

                for(int k=0;k<ncities;k++){
                    msgsnd=pop.Get_order_ichr(sendindex,k);
                    MPI_Send(&msgsnd,1,MPI_INT,migrationtarget,0,MPI_COMM_WORLD);
                    MPI_Recv(&msgrcv,1,MPI_INT,migrationreceiver,0,MPI_COMM_WORLD,MPI_STATUS_IGNORE);
                    pop.Set_order_ichr(mypop-1-j,k,msgrcv);

                }
            }

            pop.checkall();
            pop.measure();
            pop.order();

        }



        //Ritrovamento del miglior cromosoma a livello complessivo
        // e calcolo della media della miglior metà a livello compessivo


        mybest = pop.getbestlength();
        mymean = pop.getmeanlength();
        if(rank%size!=0){
            MPI_Send(&mybest,1,MPI_DOUBLE_PRECISION,0,2*i,MPI_COMM_WORLD);
            MPI_Send(&mymean,1,MPI_DOUBLE_PRECISION,0,2*i+1,MPI_COMM_WORLD);
        }
        if(rank%size==0){

            thebest[0]=mybest;
            themean[0]=mymean;
            for(int j=1;j<size;j++){
                MPI_Recv(&mybest,1,MPI_DOUBLE_PRECISION,j,2*i,MPI_COMM_WORLD,MPI_STATUS_IGNORE);
                MPI_Recv(&mymean,1,MPI_DOUBLE_PRECISION,j,2*i+1,MPI_COMM_WORLD,MPI_STATUS_IGNORE);
                thebest[j]=mybest;
                themean[j]=mymean;
            }
        

            ofstream best("best.dat",ios::app);
            ofstream mean("mean.dat",ios::app);

            mymean=0;
            mybest=thebest[0];

            for(int j=0;j<size;j++){
                mymean+=themean[j];
                if(thebest[j]<mybest){
                    mybest=thebest[j];
                    if(i==ncycles-1){
                      bestsearch=j;
                    }
                }
            }

            best << i << setw(20) << mybest << endl;
            mean << i << setw(20) << mymean/size << endl;

            best.close();
            mean.close();
        } 
        
    }

    if(rank%size!=0){
        for(int k=0;k<ncities;k++){
            msgsnd=pop.Get_order_ichr(0,k);
            MPI_Send(&msgsnd,1,MPI_INT,0,5*ncycles,MPI_COMM_WORLD);
        }
    }

    if(rank%size==0){
        if(bestsearch!=0){
            for(int k=0;k<ncities;k++){
                MPI_Recv(&msgrcv,1,MPI_INT,bestsearch,5*ncycles,MPI_COMM_WORLD,MPI_STATUS_IGNORE);
                pop.Set_order_ichr(0,k,msgrcv);
            }
        }
        ofstream draw("draw.dat");
        pop.printbestcoordinates(&draw);
        draw.close();
    }
   


    MPI_Finalize();
    return 0;
}