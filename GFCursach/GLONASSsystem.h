#pragma once
#include"NavSatellite.h"
#include<vector>
class GLONASSsystem
{
private:
	double getU(int sat_num);

public:
	std::vector<NavSatellite> satellites;


	const double Horb = 19100 * 1000;//m
	const  double T = 11 * 60 * 60 + 15 * 60;//c
	const int orbNumber = 3;
	const int satOnOrbNumber = 8;
	const  double i = Satellite::ToRad(64.8);//���������� ������
	const  double OMEGAS[3] = { Satellite::ToRad(11 + 15 / 60), Satellite::ToRad(131 + 15 / 60),Satellite::ToRad(251 + 15 / 60) };
	double omega = Satellite::ToRad(90.0);//�������� ���������� ������[rad]
	double a = 25420.0 * 1000;// ������� �������[�]
	double e = 0;//��������������[rad]



	GLONASSsystem();
	//��������� ������ ������ ��������� ��� ���� ���������
	vector<TVector> getRHSs(const vector<TVector> &args_sats, double _t);

	int getSatNumber() { return satellites.size(); }

};

