#pragma once
#include"TModel.h"
#include"Satelite.h"
#include"GLONASSsystem.h"
#include"GPSSystem.h"
#include<vector>
class GeneralProcessModel: public TModel
{
public:
	GLONASSsystem GLONASS;
	GPSSystem GPS;
	Satellite ISZ_consumer;

private:
	int(*incProgressBar)() = nullptr;

	//параматры орбиты ИСЗ-потребителя
	double Theta = Satellite::ToRad(60);
	double omega = Satellite::ToRad(0);
	double OMEGA = Satellite::ToRad(0);
	double i = Satellite::ToRad(0);
	double a = 500 * 1000;
	double e = Satellite::ToRad(0);

	//параметы зашумления начальных услловй истинного движения спутников
	const double Kglonass[6] = {13.0, 13.0, 13.0, 0.3, 0.3, 0.3};
	const double Kgps[6] = {10.0, 10.0, 10.0, 0.1, 0.1 , 0.1};
	const double Kconsumer[6] = { 100.0, 100.0, 100.0, 1.0, 1.0 , 1.0 };



	vector<TVector> getGlonassArgList(const TVector& arg_v);
	vector<TVector> getGpsArgList(const TVector& arg_v);
	TVector getISZ_consumerArg(const TVector& arg_v);
	void addNoiseToICGlonass();
	void addNoiseToICGps();
	void addNoiseToICconsumer();
public:
	GeneralProcessModel();
	GeneralProcessModel(double t0, double t1,double smlInc);

	TVector *getRight(const TVector &arg_v, double _t, TVector &k_i);
	
	void AddResult(TVector &vect, double t);
	void addProgressBarIncrementor(int(*incFunction)(void));
};

