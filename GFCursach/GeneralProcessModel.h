#pragma once
#include"TModel.h"
#include"Satelite.h"
#include"GLONASSsystem.h"
#include<vector>
class GeneralProcessModel: public TModel
{
private:
	GLONASSsystem GLONASS;




	vector<TVector> getGlonassArgList(const TVector& arg_v);
public:
	GeneralProcessModel();
	GeneralProcessModel(double t0, double t1);

	TVector *getRight(const TVector &arg_v, double _t, TVector &k_i);
};

