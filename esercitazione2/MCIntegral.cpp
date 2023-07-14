#include "MCIntegral.h"
#include <iostream>

using namespace std;

double MCIntegral::Unif(double xmin, double xmax, unsigned int npoints, const function& f){
    if(xmin<=xmax){
	    IntMedia=0;
	    for(unsigned int i=0;i<npoints;i++){
		    IntMedia+=f.eval(m_Rand->Rannyu(xmin,xmax));
	    }
	    IntMedia*=(xmax-xmin)/double(npoints);
	    return IntMedia;
    }else cerr << "Inserire estremi ordinati! Deve essere xmin<=xmax" << endl;
    return 0;
}


double MCIntegral::ImpSamp(double xmin, double xmax, unsigned int npoints, const function& f,Distrib& p){
    if(xmin<=xmax){
		double value;
	    IntMedia=0;
	    for(unsigned int i=0;i<npoints;i++){
			value=p.extract();
		    IntMedia+=f.eval(value)/p.eval(value);
	    }
	    IntMedia*=(xmax-xmin)/double(npoints);
	    return IntMedia;
    }else cerr << "Inserire estremi ordinati! Deve essere xmin<=xmax" << endl;
    return 0;
}