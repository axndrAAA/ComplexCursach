#pragma once
#include"TModel.h"
#define _USE_MATH_DEFINES
#include<vector>
class Satellite
{
protected:
	double mu = 398600.436e9;//геоцентрическая гравитационная постоянная;
	double a = 29378137.0;//большая полуось
	double e = 0.0;//эксцентриситет
	double omega = 0;//аргумент перицентра
	double p = a * (1 - e * e);//фокальный параметр



	TVector Xcur;
	TVector X0;


	TVector OsculToGeo(double Theta, double omega, double OMEGA, double i);
	double getVn(double Theta);
	double getVr(double Theta);
public:
	Satellite();
	Satellite(TVector xo);
	Satellite(std::vector<double> _x0);
	Satellite(double Theta, double i, double OMEGA, double H);
	//Satellite operator = (Satellite &stl);

	TVector *getRight(const TVector &arg_v, double _t, TVector &k_i);
	TVector getXcur();
	void setXcur(const TVector newX); 

	static double ToRad(double grad);
};

