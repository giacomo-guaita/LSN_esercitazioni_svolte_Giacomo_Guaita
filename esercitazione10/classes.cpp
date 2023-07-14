#include <cmath>
#include <algorithm>
#include <iostream>
#include <iomanip>
#include <sstream>
#include "classes.h"

bool comparelength(chromosome a, chromosome b){
    return(a.Get_length()<b.Get_length());
}





void chromosome::Randominit(int ncities,Random* rnd){
    order.resize(ncities);
    int swap;
    int numswap;
    for(int i=0;i<ncities;i++){
        order[i]=i;
    }
    for(int i=1;i<ncities;i++){
        swap=order[i];
        numswap=rnd->Rannyu(1,ncities);
        order[i]=order[numswap];
        order[numswap]=swap;
    }
}
const void chromosome::check(int ncities){
    int sum=0;
    if(order[0]!=0) std::cerr << "First city is not starting city!!" << std::endl;
    for(int i=0;i<ncities;i++){
        sum+=order[i];
    }
    if(sum!=0.5*ncities*(ncities-1)) std::cerr << "There are double cities in the sequence" << std::endl;
}
const double chromosome::Get_length(){
    return length;
}
void chromosome::Set_length(double l){
    length = l;
}
const int chromosome::Get_order(int i){
    return order[i];
}
void chromosome::Set_order(int i, int x){
    order[i]=x;
}


void territory::Mayor(int ncities,int type){
    m_ncities=ncities;
    if(type==0){
        double angle;
        for(int i=0;i<ncities;i++){
            angle = m_Rand->Rannyu(0,2*M_PI);
            positions.push_back({cos(angle),sin(angle)});
        }
    }else if(type==1){
        for(int i=0;i<ncities;i++){
            positions.push_back({m_Rand->Rannyu(),m_Rand->Rannyu()});
        }
    }else{
        std::cerr << "Nono capisci niente, faccia di serpente." << std::endl;
        std::cerr << "type=0 ----> Cities on a circumference" << std::endl << "type=1 ------> Cities in a square" << std::endl;
    }
};
void territory::Set_city_positions(int i,double x,double y){
    positions[i]={x,y};
}
const double territory::Get_icity_x(int i){
    return positions[i].x;
}
const double territory::Get_icity_y(int i){
    return positions[i].y;
}



population::population(Random *rand){
	m_Rand = rand;
};
void population::init(int ncities,int npop,int type){
    m_npop=npop;
    Mayor(ncities,type);
    chromosome help;
    for(int i=0;i<m_npop;i++){
        help.Randominit(m_ncities,m_Rand);
        pop.push_back(help);
    }
}
void population::fileinit(int ncities,int npop,std::string filename){

    m_npop=npop;
    m_ncities=ncities;

    for(int i=0;i<ncities;i++) positions.push_back({0,0});

    std::ifstream pos(filename);
    if(!pos) std::cerr << "Unable to open file  " << filename << std::endl;

    std::string line;
    std::string appo;
    std::vector<std::string> data;
    double x, y;
    int i=0;

    std::getline(pos, line);
    
    while(std::getline(pos, line)){
        
        //std::cout << i << std::endl;

        std::istringstream iss(line);
        // Skip the first two columns (names)
        while(iss >> appo){
            data.push_back(appo);
            //std::cout << appo << std::endl;
        }
        
        x=std::stod(data[data.size()-2]);
        y=std::stod(data[data.size()-1]);

        //std::cout << x << "   " << y << std:: endl;
        Set_city_positions(i,x,y);
        
        i++;
    }

    pos.close();

    /*std::string appo;
    double x,y;
    pos >> appo >> appo >> appo >> appo;
    for(int i=0;i<m_ncities;i++){
        pos >> appo >> appo;
        pos >> x >> y;
        Set_city_positions(i,x,y);
    }

    pos.close();*/

    chromosome help;
    for(int i=0;i<m_npop;i++){
        help.Randominit(m_ncities,m_Rand);
        pop.push_back(help);
    }
}
void population::chrinit(int ncities,int npop){

    m_npop=npop;
    m_ncities=ncities;

    chromosome help;
    for(int i=0;i<m_npop;i++){
        help.Randominit(m_ncities,m_Rand);
        pop.push_back(help);
    }
}
void population::measure(){
    for(int n=0;n<m_npop;n++){
        pop[n].Set_length(0);
        for(int i=0;i<m_ncities-1;i++){
            pop[n].Set_length(pop[n].Get_length()+sqrt(pow(positions[pop[n].Get_order(i)].x-positions[pop[n].Get_order(i+1)].x,2)+pow(positions[pop[n].Get_order(i)].y-positions[pop[n].Get_order(i+1)].y,2)));
        }
        pop[n].Set_length(pop[n].Get_length()+sqrt(pow(positions[pop[n].Get_order(m_ncities-1)].x-positions[pop[n].Get_order(0)].x,2)+pow(positions[pop[n].Get_order(m_ncities-1)].y-positions[pop[n].Get_order(0)].y,2)));
        
    }
}
void population::order(){
    measure();
    std::sort(begin(pop),end(pop),comparelength);
}
const int population::choose(){
    return (int)m_npop*pow(m_Rand->Rannyu(),p);
}
void population::evolve(){
    hereditate();
    mutate();
    return;
}
void population::hereditate(){
    chromosome help(pop[0]);
    std::vector<chromosome> newgen;
    for(int i=0;i<m_npop;i++){
        newgen.push_back(help);
    }
    int index1,index2;
    int cutposition;
    int l;
    int f;
    int g;
    order();
    for(int i=0;i<m_npop/2;i++){
        index1=choose();
        index2=choose();
        cutposition=m_Rand->Rannyu(1,m_ncities+1);
        for(int j=0;j<cutposition;j++){
            newgen[2*i].Set_order(j,pop[index1].Get_order(j));
            newgen[2*i+1].Set_order(j,pop[index2].Get_order(j));
        }
        
        l=0;
        g=cutposition;
        while(g<m_ncities){
            f=0;
            while(pop[index2].Get_order(l)!=newgen[2*i].Get_order(f) and f<cutposition){
                f++;
            }
            if(f==cutposition) f--;
            //std::cout << f <<  std::endl;
            if(pop[index2].Get_order(l)!=newgen[2*i].Get_order(f)){
                newgen[2*i].Set_order(g,pop[index2].Get_order(l));
                //std::cout << l <<  std::endl;
                //std::cout << g <<  std::endl;
                //std::cout << cutposition <<  std::endl;
                g++;
            }
            l++;
        }
        l=0;
        g=cutposition;
        while(g<m_ncities){
            f=0;
            while(pop[index1].Get_order(l)!=newgen[2*i+1].Get_order(f) and f<cutposition){
                f++;
            }
            if(f==cutposition) f--;
            if(pop[index1].Get_order(l)!=newgen[2*i+1].Get_order(f)){
                newgen[2*i+1].Set_order(g,pop[index1].Get_order(l));
                g++;
            }
            l++;
        }
        
    }
    if(m_npop%2==1){
        newgen[m_npop-1]=pop[choose()];
    }
    pop=newgen;
    return;
}
void population::mutate(){
    for(int i=0;i<m_npop;i++){
        if(m_Rand->Rannyu()<m_probmut) pairpermutation(i);
        if(m_Rand->Rannyu()<m_probmut) shift(i);
        if(m_Rand->Rannyu()<m_probmut) grouppermutation(i);
        if(m_Rand->Rannyu()<m_probmut) groupinversion(i);
    }
}
void population::pairpermutation(int n){
    int swap;
    int swapindex1=m_Rand->Rannyu(1,m_ncities);
    int swapindex2=m_Rand->Rannyu(1,m_ncities);
    swap=pop[n].Get_order(swapindex1);
    pop[n].Set_order(swapindex1,pop[n].Get_order(swapindex2));
    pop[n].Set_order(swapindex2,swap);
    //std::cout << "pp" << n << std::endl;
    return;
}
void population::shift(int n){
    int shiftstart=m_Rand->Rannyu(1,m_ncities);
    int shiftdim=m_Rand->Rannyu(1,m_ncities-shiftstart);
    int shiftdistance=m_Rand->Rannyu(0,m_ncities-shiftstart-shiftdim+1);
    std::vector<int> swap;
    for(int i=shiftstart;i<shiftstart+shiftdim;i++) swap.push_back(pop[n].Get_order(i));
    for(int i=0;i<shiftdistance;i++) pop[n].Set_order(shiftstart+i,pop[n].Get_order(shiftstart+i+shiftdim));
    for(int i=0;i<shiftdim;i++) pop[n].Set_order(shiftstart+shiftdistance+i,swap[i]);
    //std::cout << "shift" << n << std::endl;
    return;
}
void population::grouppermutation(int n){
    int swapindex1=m_Rand->Rannyu(1,m_ncities);
    int swapindex2=m_Rand->Rannyu(1,m_ncities);
    int swapdim=m_Rand->Rannyu(0,std::min(abs(swapindex1-swapindex2)+1,std::min(m_ncities-swapindex1,m_ncities-swapindex2)+1));
    int swap;
    for(int i=0;i<swapdim;i++){
    swap=pop[n].Get_order(swapindex1+i);
    pop[n].Set_order(swapindex1+i,pop[n].Get_order(swapindex2+i));
    pop[n].Set_order(swapindex2+i,swap);
    }
    //std::cout << "gp" << n << std::endl;
    return;
}
void population::groupinversion(int n){
    int startindex=m_Rand->Rannyu(1,m_ncities);
    int inversiondim=m_Rand->Rannyu(1,m_ncities-startindex);
    int swap;
    for(int i=0;i<inversiondim/2;i++){
        swap=pop[n].Get_order(startindex+i);
        pop[n].Set_order(startindex+i,pop[n].Get_order(startindex+inversiondim-1-i));
        pop[n].Set_order(startindex+inversiondim-1-i,swap);
    }
    //std::cout << "gi" << n << std::endl;
    return;
}
const void population::printchr(int n){
    std::cout << "Squared length of the path: " << pop[n].Get_length() << std::endl;
    for(int i=0;i<m_ncities;i++){
        std::cout << pop[n].Get_order(i) << std::endl;
    }
}
const void population::printpop(){
    for(int i=0;i<m_npop;i++){
        std::cout << "Chromosome number " << i+1 << std::endl;
        printchr(i);
        std::cout << std::endl << std::endl;
    }
    
}
const void population::printlength(){
    for(int i=0;i<m_npop;i++){
        std::cout << pop[i].Get_length() << std::endl;
    }
}
const void population::printbestlength(){
    std::cout << pop[0].Get_length() << std::endl;
}
const void population::checkall(){
    for(int i=0;i<m_npop;i++){
        //std::cout << i << std::endl;
        pop[i].check(m_ncities);
    }
}
const double population::getbestlength(){
    return pop[0].Get_length();
}
const double population::getmeanlength(){
    double mean=0;
    for(int i=0;i<m_npop/2;i++){
        mean+=pop[i].Get_length();
    }
    return mean/int(m_npop/2);
}
const int population::Get_order_ichr(int i,int j){
    return pop[i].Get_order(j);
}
void population::Set_order_ichr(int i,int j,int x){
    pop[i].Set_order(j,x);
}
const void population::printbestcoordinates(std::ofstream *fout){
    for(int i=0;i<m_ncities;i++){
        *fout << std::setw(20) << positions[pop[0].Get_order(i)].x << std::setw(20) << positions[pop[0].Get_order(i)].y << std::endl;
    }
}


