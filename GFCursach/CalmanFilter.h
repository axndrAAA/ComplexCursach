#pragma once
#include"Matrix_classes.h"


class CalmanFilter
{


public:
	CalmanFilter();

	void doStep(const TVector &arg, const TVector &y);
};

