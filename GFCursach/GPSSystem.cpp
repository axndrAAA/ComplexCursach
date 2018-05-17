#include "stdafx.h"
#include "GPSSystem.h"


GPSSystem::GPSSystem()
{
	satellites = vector<NavSatellite>(24);

	//������� ��������
	for (int i = 0; i < satellites.size(); i++) {
		//�.�. �������� ���������� ������ = 0, �� �������� �������� Theta
		//����� ��������� ������ u
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
		//������ ������ ������ ��� i-�� ��������
		TVector rhs_i = satellites[i].getRHS(args_sats[i], _t);
		ret[i] = rhs_i;
	}
	return ret;
}

int GPSSystem::getSatNumber()
{
	return satellites.size();
}
