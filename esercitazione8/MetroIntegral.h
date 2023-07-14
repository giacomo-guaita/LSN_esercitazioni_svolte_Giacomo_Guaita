#pragma once

#include <vector>

#include "random.h"
#include "function.h"

class MetroIntegral{

  public:
	MetroIntegral(Random *rand, double step){
		m_Rand = rand;
		m_step=step;
	};
	~MetroIntegral(){};

	double BlckIntegrate(unsigned int nblocks,unsigned int npoints,const function& f,const function& distrib);
	double BlckIntegrate(unsigned int nblocks,unsigned int npoints,const function& f,const function& distrib,double& uncertainty);
	void BlckIntegrate(unsigned int nblocks,unsigned int npoints,const function& f,const function& distrib,
	std::vector<double>& media,std::vector<double>& incertezza, std::ofstream& of);
	double ErrorIntegrate(double abs_err,const function& f,const function& distrib);
	double Integrate(unsigned int npoints,const function& f,const function& distrib);
	double Integrate(unsigned int npoints,const function& f,const function& distrib, std::ofstream& of);
	double Move(double x, const function& distrib);
	void Reset();


	void Set_step(double step);


	const double Get_acceptancerate();
	const double Get_usedstep();

  private:
	Random *m_Rand;
	double m_step,m_usedstep;
	//double m_steppos,m_stepneg;
	double stepattempt;
	int attempted, accepted;
	double IntMedia;
};

