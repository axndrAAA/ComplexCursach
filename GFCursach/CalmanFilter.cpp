#include "stdafx.h"
#include "CalmanFilter.h"


TMatrix CalmanFilter::getH(const TVector & Xcr, double t)
{
	double r;
	TMatrix H(6, 6);

	return H;
}

CalmanFilter::CalmanFilter()
{
}

void CalmanFilter::doStep(const Satellite & consumer, const vector<NavSatellite>& navSats, double t)
{
	//формиуем измерения
}
