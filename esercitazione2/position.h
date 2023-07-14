#pragma once



class Position{
    public:

    Position();
    Position(double xx, double yy ,double zz);
    ~Position(){;}

    double Getr2()const;
    double Getr() const;
    double Getx()const;
    double Gety()const;
    double Getz()const;
    double Gettheta()const;
    double Getphi()const;

    void Addxyz(double xx,double yy, double zz);
    void Addrthetaphi(double r,double theta ,double phi);
    void Addx(double xx);
    void Addy(double yy);
    void Addz(double zz);

    void Setxyz(double xx, double yy, double zz);


    protected:
    double x, y, z;

};