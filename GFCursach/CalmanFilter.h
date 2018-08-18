#pragma once
#include"Matrix_classes.h"
#include"NavSatellite.h"

class CalmanFilter
{

private:
	TMatrix getH(const TVector &Xcr, double t);

public:
	CalmanFilter();

	void doStep(const Satellite &consumer, const vector<NavSatellite> &navSats,double t);
};

