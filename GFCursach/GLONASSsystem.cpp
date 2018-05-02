#include "stdafx.h"
#include "GLONASSsystem.h"
#include"NavSatellite.h"
#include<vector>
using namespace std;

GLONASSsystem::GLONASSsystem()
{
	satellites = vector<NavSatellite>(1);
	
	satellites[0] = NavSatellite(0, orbMood, OMEGAS[0], Horb);

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
