#pragma once
#include"TModel.h"
#include"Satelite.h"
#include"GLONASSsystem.h"
#include<vector>
class GeneralProcessModel: TModel
{
private:
	GLONASSsystem GLONASS;
public:
	GeneralProcessModel();
	GeneralProcessModel(double t0, double t1);

	TVector *getRight(const TVector &arg_v, double _t, TVector &k_i);
};

