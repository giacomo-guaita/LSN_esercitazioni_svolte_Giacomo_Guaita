#include "statfunctions.h"
#include <cmath>
#include <iostream>

using namespace std;

double mean(const vector<double> data ){
    double summ=0;
    for(unsigned int i=0;i<data.size();i++){
        summ+=data[i];
    }
    return summ/data.size();
}
//double mean(vector<int>);
double stdd(const vector<double> data ){
    double accumulo=0;
    double accumulo2=0;

    for(unsigned int i=0;i<data.size();i++){
        accumulo+=data[i];
        accumulo2+=data[i]*data[i];
    }
    accumulo/=data.size();

    if(data.size()==1){
        cerr << "Only one number, cannot compute standard deviation" << endl;
        return 0;
    } else{
        return sqrt(accumulo2/data.size()-accumulo*accumulo);
    }


}
//double std(vector<int>);
void meandstd(const vector<double> data ,double& mean,double& std){
    double accumulo=0;
    double accumulo2=0;

    for(unsigned int i=0;i<data.size();i++){
        accumulo+=data[i];
        accumulo2+=data[i]*data[i];
    }
    accumulo/=data.size();

    mean=accumulo;

    if(data.size()==1){
        cerr << "Only one number, cannot compute standard deviation" << endl;
        return;
    } else{
        std = sqrt(accumulo2/data.size()-accumulo*accumulo);
    }
    return;
}

//double meandstd(vector<int>,vector<int>,vector<int>);

void blockmeanstdm(const vector<double> data ,vector<double>& mean,vector<double>& stdm){

    double accumulo=0;
    double accumulo2=0;

    double uncertainty;
    double expectation;

    for(unsigned int i=0;i<data.size();i++){
        accumulo+=data[i];
        accumulo2+=data[i]*data[i];


        expectation=accumulo/(i+1);
        if(i==0){
            uncertainty=0;
        } else{
            uncertainty=sqrt((accumulo2/(i+1)-expectation*expectation)/i);
        }

        mean.push_back(expectation);
        stdm.push_back(uncertainty);


    } 

}

double chi2(const vector<double> data,double expectation){
   double chi=0;
   for(unsigned int i=0;i<data.size();i++){
      chi+=(data[i]-expectation)*(data[i]-expectation);
   }
   return chi/expectation;
}

double chi2(const vector<int> data,double expectation){
   double chi=0;
   for(unsigned int i=0;i<data.size();i++){
      chi+=(data[i]-expectation)*(data[i]-expectation);
   }
   return chi/expectation;
}

void bin(double x,vector<int>& bins,double dimbin,double xmin,int imin,int numbin){
    if(numbin==1){
        bins[imin]++;
        return;
    }
    if(x<xmin+dimbin*int(numbin/2)){
        bin(x,bins,dimbin,xmin,imin,numbin/2);
    }else /*if(x>=xmin+dimbin*int(numbin/2))*/{
        bin(x,bins,dimbin,xmin+dimbin*int(numbin/2),imin+int(numbin/2),ceil(double(numbin)/2));
    }
}