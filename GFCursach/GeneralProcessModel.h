#pragma once
#include"TModel.h"
#include"Satelite.h"
#include"GLONASSsystem.h"
#include<vector>
class GeneralProcessModel: public TModel
{
public:
	GLONASSsystem GLONASS;

private:
	int(*incProgressBar)();

	//параматры орбиты ИСЗ-потребителя
	double Theta = Satellite::ToRad(60);
	double omega = Satellite::ToRad(0);
	double OMEGA = Satellite::ToRad(0);
	double i = Satellite::ToRad(0);
	double a = 500 * 1000;
	double e = Satellite::ToRad(0);



	vector<TVector> getGlonassArgList(const TVector& arg_v);
public:
	GeneralProcessModel();
	GeneralProcessModel(double t0, double t1,double smlInc);

	TVector *getRight(const TVector &arg_v, double _t, TVector &k_i);
	
	void AddResult(TVector &vect, double t);
	void addProgressBarIncrementor(int(*incFunction)(void));
};

