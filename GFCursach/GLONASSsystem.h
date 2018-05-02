#pragma once
#include"NavSatellite.h"
#include<vector>
class GLONASSsystem
{
private:


public:
	std::vector<NavSatellite> satellites;


	const double Horb = 19100 * 1000;//m
	const  double T = 11 * 60 * 60 + 15 * 60;//c
	const int orbNumber = 3;
	const int satOnOrbNumber = 8;
	const  double orbMood = Satellite::ToRad(64.8);//оно же i
	const  double OMEGAS[3] = { Satellite::ToRad(11 + 15 / 60), Satellite::ToRad(131 + 15 / 60),Satellite::ToRad(251 + 15 / 60) };



	GLONASSsystem();
	//получение правых частей уравнений для всех спутников
	vector<TVector> getRHSs(const vector<TVector> &args_sats, double _t);

	int getSatNumber() { return satellites.size(); }

};

