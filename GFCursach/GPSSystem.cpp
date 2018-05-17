#include "stdafx.h"
#include "GPSSystem.h"


GPSSystem::GPSSystem()
{
	satellites = vector<NavSatellite>(24);

	//создаем спутники
	for (int i = 0; i < satellites.size(); i++) {
		//т.к. аргумент перицентра принят = 0, То истинная аномалия Theta
		//равна оргументу широты u
		satellites[i] = NavSatellite(u[i], omega, OMEGAS[i / 4], i, a, e);
	}

}


GPSSystem::~GPSSystem()
{
}

vector<TVector> GPSSystem::getRHSs(const vector<TVector>& args_sats, double _t)
{
	vector<TVector> ret(satellites.size());
	for (int i = 0; i < satellites.size(); i++)
	{
		//вектор правых частей для i-го спутника
		TVector rhs_i = satellites[i].getRHS(args_sats[i], _t);
		ret[i] = rhs_i;
	}
	return ret;
}

int GPSSystem::getSatNumber()
{
	return satellites.size();
}
