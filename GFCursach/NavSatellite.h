#pragma once
#include "Satelite.h"
class NavSatellite : public Satellite
{
public:
	NavSatellite();
	NavSatellite(double Theta, double i, double OMEGA, double H) :Satellite(Theta, i, OMEGA, H) {}
};

