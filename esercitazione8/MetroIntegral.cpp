#include "MetroIntegral.h"
#include "statfunctions.h"
#include <iostream>
#include <fstream>
#include <vector>
#include <cmath>

using namespace std;



double MetroIntegral::BlckIntegrate(unsigned int nblocks,unsigned int npoints,const function& f,const function& distrib){

	vector<double> integrals;
	for(unsigned int i=0;i<nblocks;i++){
        integrals.push_back(Integrate(npoints,f,distrib));
    }

    return mean(integrals);
}

double MetroIntegral::BlckIntegrate(unsigned int nblocks,unsigned int npoints,const function& f,const function& distrib,double& uncertainty){

	vector<double> integrals;
	for(unsigned int i=0;i<nblocks;i++){
        integrals.push_back(Integrate(npoints,f,distrib));
    }
	double media;
	meandstd(integrals,media,uncertainty);
	uncertainty/=sqrt(integrals.size());
    return media;
}

void MetroIntegral::BlckIntegrate(unsigned int nblocks,unsigned int npoints,const function& f,
const function& distrib,vector<double>& media,vector<double>& incertezza, ofstream& of){

	vector<double> integrals;
	for(unsigned int i=0;i<nblocks;i++){
        integrals.push_back(Integrate(npoints,f,distrib,of));
    }
	blockmeanstdm(integrals,media,incertezza);
}


double MetroIntegral::Integrate(unsigned int npoints, const function& f,const function& distrib){

	Reset();
	IntMedia=0;
	double x=0;
	ofstream of("campionamento.dat",ios::app);
	for(unsigned int i=0;i<npoints;i++){
		x = Move(x,distrib);
		IntMedia+=f.eval(x)/(double)npoints;
	}

	m_usedstep=m_step;
	m_step*=(1+1.9*(Get_acceptancerate()-0.5));
		

	return IntMedia;
}

double MetroIntegral::Integrate(unsigned int npoints, const function& f,const function& distrib,ofstream& of){

	Reset();
	IntMedia=0;
	double x=0;
	for(unsigned int i=0;i<npoints;i++){
		x = Move(x,distrib);
		IntMedia+=f.eval(x)/(double)npoints;
		of << x << endl;
	}

	m_usedstep=m_step;
	m_step*=(1+1.9*(Get_acceptancerate()-0.5));
		
	return IntMedia;
}

double MetroIntegral::Move(double x, const function& distrib){

	if(distrib.eval(x)==0){
		x+=m_step;
		ofstream randnum("check.dat",ios::app);
		randnum << 1 << endl;   //debugging
		randnum.close();
	} 

	attempted++;
	stepattempt=x+(m_Rand->Rannyu()-0.5)*2*m_step;

	if(m_Rand->Rannyu()<distrib.eval(stepattempt)/distrib.eval(x)){

		accepted++;
		return stepattempt;
	}

	return x;
}


void  MetroIntegral::Reset(){
	accepted=0;
	attempted=0;
}

const double MetroIntegral::Get_acceptancerate(){
	return accepted/(double)attempted;
}

const double MetroIntegral::Get_usedstep(){
	return m_usedstep;
}

void MetroIntegral::Set_step(double step){
	m_step=step;
}
