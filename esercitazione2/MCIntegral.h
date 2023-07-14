#pragma once



#include "random.h"
#include "function.h"
#include "distrib.h"

class MCIntegral{

  public:
	MCIntegral(Random *rand){
		m_Rand = rand;

	};
	~MCIntegral(){};
	
	double Unif(double xmin, double xmax, unsigned int npoints,const function& f );
	double ImpSamp(double xmin, double xmax, unsigned int npoints,const function& f,Distrib& p);
  private:
	Random *m_Rand;
	double IntMedia;
};

