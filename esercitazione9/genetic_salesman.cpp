#include <iostream>
#include <fstream>
#include <iomanip>

#include "classes.h"
#include "random.h"



using namespace std;

int main(int argc, char *argv[]){

    if(argc!=2){
        cout << "Passare al programma il tipo di configurazione delle città da simulare:" << endl;
        cout << "0 ------> città su una circonferenza" << endl << "1 ------> città in un quadrato" << endl;
        return -1;
    }


    int ncities=34;
    int type = stoi(argv[1]);
    int npop=ncities*ncities;
    int ncycles=1000;

    Random rnd;
    rnd.FileSetRandom("Primes","seed.in"); 

    population pop(&rnd);  
    pop.init(ncities,npop,type);
    pop.checkall();
    pop.order();

    ofstream best("best.dat");
    ofstream mean("mean.dat");
    ofstream draw("draw.dat");

    best << "Generation" << setw(20) << "Length" << endl;
    mean << "Generation" << setw(20) << "Length" << endl;
    best << 0 << setw(20) << pop.getbestlength() << endl;
    mean << 0 << setw(20) << pop.getmeanlength() << endl;


    for(int i=0;i<ncycles;i++){
        pop.evolve();
        pop.checkall();
        pop.measure();
        pop.order();

        best << i+1 << setw(20) << pop.getbestlength() << endl;
        mean << i+1 << setw(20) << pop.getmeanlength() << endl;
    }
    pop.printbestcoordinates(&draw);


    best.close();
    mean.close();
    draw.close();

    return 0;
}


