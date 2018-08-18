#pragma once
#include"Matrix_classes.h"
#include"NavSatellite.h"

class CalmanFilter
{

private:
	TMatrix D_etta;

	TMatrix P_zv_cur;
	TVector X_zv_cur;
	double prev_t = 0;

	TMatrix getH(const Satellite & consumer, const vector<NavSatellite>& navSats, double t);
	TMatrix getFi(const TVector &X, double dt);
	

public:
	CalmanFilter();

	void doStep(const Satellite & consumer, const vector<NavSatellite>& navSats, const TVector &y, double t);
};

