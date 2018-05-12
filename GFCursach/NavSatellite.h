#pragma once
#include "Satelite.h"
class NavSatellite : public Satellite
{


public:
	NavSatellite();
	NavSatellite(double Theta, double omega, double OMEGA, double i,double a,double e) :Satellite(Theta,omega, OMEGA, i,a,e) {}
};

