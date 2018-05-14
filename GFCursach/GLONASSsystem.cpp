#include "stdafx.h"
#include "GLONASSsystem.h"
#include"NavSatellite.h"
#include<vector>
using namespace std;

double GLONASSsystem::getU(int sat_num)
{
	//TODO

	double ret = Satellite::ToDeg(omega) + 15 * (27 - 3 * sat_num + 25 * ((int)(sat_num - 1) / 8));
	if (ret < 0)
		ret += 360.0;
	if (ret > 360)
		ret -= 360.0;
	return ret;
}

GLONASSsystem::GLONASSsystem()
{
	satellites = vector<NavSatellite>(24);
	

	////аршумент широты
	////double u = 0;

	////истинная аномалия
	////double Theta = u - omega;
	////satellites[0] = NavSatellite(Theta, omega, OMEGAS[0], i, a, e);

	//создаем спутники ГЛОНАСС
	for (int i = 0; i < satellites.size(); i++)
	{
		double Theta = getU(i + 1);
		Theta = Satellite::ToRad(Theta);
		satellites[i] = NavSatellite(Theta, omega, OMEGAS[i / 8], i, a, e);
	}


}

vector<TVector> GLONASSsystem::getRHSs(const vector<TVector> &args_sats, double _t)
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
