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
