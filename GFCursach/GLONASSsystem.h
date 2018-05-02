#pragma once
#include"NavSatellite.h"
#include<vector>
class GLONASSsystem
{
private:
	std::vector<NavSatellite> satellites;
	double Horb = 19100 * 1000;//m
	double T = 11 * 60 * 60 + 15 * 60;//c
	int orbNumber = 3;
	int satOnOrbNumber = 8;
	double orbMood = Satellite::ToRad(64.8);//оно же i
	const double OMEGAS[3] = { Satellite::ToRad(11 + 15 / 60), Satellite::ToRad(131 + 15 / 60),Satellite::ToRad(251 + 15 / 60) };
public:
	GLONASSsystem();
};

