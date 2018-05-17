#pragma once
#include"NavSatellite.h"
#include<vector>

using namespace std;

class GPSSystem
{
public:
	vector<NavSatellite> satellites;
	
	const double Horb = 20180 * 1000;//m
	const  double T = 12 * 60 * 60;//c
	const int orbNumber = 6;
	const int satOnOrbNumber = 4;
	const  double i = Satellite::ToRad(55);//наклонение орбиты
	const  double OMEGAS[6] = { 
		Satellite::ToRad(317), 
		Satellite::ToRad(17),
		Satellite::ToRad(77),
		Satellite::ToRad(137),
		Satellite::ToRad(197),
		Satellite::ToRad(257)
	};
	const double u[24] = {
		Satellite::ToRad(80),
		Satellite::ToRad(120),
		Satellite::ToRad(210),
		Satellite::ToRad(340),
		Satellite::ToRad(20),
		Satellite::ToRad(140),
		Satellite::ToRad(230),
		Satellite::ToRad(280),
		Satellite::ToRad(40),
		Satellite::ToRad(80),
		Satellite::ToRad(160),
		Satellite::ToRad(300),
		Satellite::ToRad(100),
		Satellite::ToRad(200),
		Satellite::ToRad(240), 
		Satellite::ToRad(340),
		Satellite::ToRad(0), 
		Satellite::ToRad(40),
		Satellite::ToRad(140),
		Satellite::ToRad(260),
		Satellite::ToRad(60), 
		Satellite::ToRad(160),
		Satellite::ToRad(280),
		Satellite::ToRad(320)
	};
	const double omega = Satellite::ToRad(0);//аргумент перицентра орбиты[rad] 
	const double a =  (20180 + 6357)* 1000;// большая полуось[м]
	const double e = Satellite::ToRad(0);//эксцентриситет[rad]
public:
	GPSSystem();
	~GPSSystem();

	//получение правых частей уравнений для всех спутников
	vector<TVector> getRHSs(const vector<TVector> &args_sats, double _t);

	int getSatNumber();

};

