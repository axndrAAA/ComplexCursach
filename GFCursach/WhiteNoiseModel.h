#pragma once
#include"Matrix_classes.h"
#include<string>
using namespace std;

class WhiteNoiseModel
{
private:
	double tk;
	double intensive = 1.0;

	double T0;
	double T1;

public:
	TVector realization;
	WhiteNoiseModel() { }
	WhiteNoiseModel(double _t0, double _T1, double _tk = 0.005);
	double operator [](double i)const;
	double getStepLimit() { return tk; }
	double Z_d(double _d);

	int toFile(string out, double Step);
};

