#pragma once

#include <vector>

using namespace std;

double mean(const vector<double> data );
//double mean(vector<int>);
double stdd(const vector<double> data );
//double std(vector<int>);
void meandstd(const vector<double> data ,double& mean,double& std);
//double meandstd(vector<int>,vector<int>,vector<int>);
void blockmeanstdm(const vector<double> data ,vector<double>& mean,vector<double>& stdm); 
double chi2(const vector<double> data,double expectation);
double chi2(const vector<int> data,double expectation);
void bin(double x,vector<int>& bins,double dimbin,double xmin,int imin,int numbin);
