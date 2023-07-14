#include "position.h"

#include <cmath>


using namespace std;



Position::Position(){
        x=0;
        y=0;
        z=0;
        }
Position::Position(double xx, double yy ,double zz){
        x=xx;
        y=yy;
        z=zz;
}




double Position::Getr2()const{
    return x*x+y*y+z*z;
}
double Position::Getr()const{
    return sqrt(x*x+y*y+z*z);
}
double Position::Getx()const{
    return x;
}
double Position::Gety()const{
    return y;
}
double Position::Getz()const{
    return z;
}
double Position::Gettheta()const{
    return acos(z/Getr());
}
double Position::Getphi()const{
    if(x==0){
        if(y==0){return 0;}
        else if(y>0){return M_PI/2;}
        else if(y<0){return -M_PI/2;}
    }
    if(x>0){
        return atan(y/x);
    }
    if(x<0){
        return M_PI +atan(y/x);
    }
    
}

void Position::Addxyz(double xx,double yy, double zz){
    x+=xx;
    y+=yy;
    z+=zz;
}
void Position::Addrthetaphi(double r,double theta ,double phi){
    x+=r*sin(theta)*cos(phi);
    y+=r*sin(theta)*sin(phi);
    z+=r*cos(theta);
}
void Position::Addx(double xx){
    x+=xx;
}
void Position::Addy(double yy){
    y+=yy;
}
void Position::Addz(double zz){
    z+=zz;
}

void Position::Setxyz(double xx, double yy, double zz){
    x=xx;
    y=yy;
    z=zz;
}
