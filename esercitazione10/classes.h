#pragma once

#include <vector>
#include <fstream>
#include <string>
#include "random.h"



class chromosome{
    public:

    void Randominit(int ncities,Random* rnd);                  //Initialization with random path

    const void check(int ncities);                 //Checks for errors in the chromosome and prints an error message if it finds any
    const double Get_length();
    void Set_length(double l);

    const int Get_order(int i);
    void Set_order(int i, int x);
    
    

    protected:
    std::vector<int> order;
    double length;

};

struct city{
   double x; 
   double y;
};


//Function used to compare two chromosomes by length
bool comparelength(chromosome a, chromosome b);


class territory{
    public:

    void Mayor(int ncities,int type);             //Randomly initialises the position of the cities on a circumference or inside a square
    void Set_city_positions(int i,double x,double y);
    const double Get_icity_x(int i);
    const double Get_icity_y(int i);

    protected:
    Random* m_Rand;
    int m_ncities;
    std::vector<city> positions;
};





class population: public territory{

    public:

    population(Random *rand);                       //Declaration
    void init(int ncities,int npop,int type);       //Randomly initialises city position and population
    void fileinit(int ncities,int npop,std::string filename); //Initializes city positions from file and randomly initializes poulation
    void chrinit(int ncities,int npop);

    void evolve();                                  //Evolves the population to the next generation, through hereditate and mutate operators
    void hereditate();                              //Transforms population, new population is made of chromosomes created through crossover of pairs of chromosomes of the old population, selected through the choose operator
    void mutate();                                  //Mutates each chromosome with the four beneath operators each with probability m_probmut

    void pairpermutation(int n);                    //Swaps two random numbers of the n-th chromosome
    void shift(int n);                              //Shifts of a random distance a random set of contigous numbers of the n-th chromosome
    void grouppermutation(int n);                   //Swaps two random sets of contigous numbers of the n-th chromosome
    void groupinversion(int n);                     //Inverts the order of a random set of contigous numbers of the n-th chromosome

    void measure();                                 //Measures the length of the path of the whole population
    void order();                                   //Orders population by path length
    const int choose();                             //Chooses a chromosome from the population(output chromosome index), prefers longer or shorter paths according to p--->(high p-->short path, low p-->long path)

    const void checkall();                          //Checks the whole population with the chromosome class check operator

    const void printchr(int n);                     //Prints the n-th chromosome
    const void printpop();                          //Prinst the whole population
    const void printlength();                       //Prints the lengths of the whole population
    const void printbestlength();                   //Prints the shortest length of the population(one must first order the population with the order operator)

    const double getbestlength();                   //Outputs the shortest length of the population(one must first order the population with the order operator)
    const double getmeanlength();                   //Outputs the mean of the shortest half of the population(one must first order the population with the order operator)
    const void printbestcoordinates(std::ofstream* fout);     //Prints on given file the coordinates of the shortest path(one must first order the population with the order operator)
    const int Get_order_ichr(int i,int j);


    void Set_order_ichr(int i,int j,int x);
    

    
    private:

    std::vector<chromosome> pop;
    int m_npop;
    double p=2;
    double m_probmut=0.1;
};
