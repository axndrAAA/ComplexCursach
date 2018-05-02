#include "stdafx.h"
#include "GeneralProcessModel.h"
#include"GLONASSsystem.h"
#include<vector>
using namespace std;

GeneralProcessModel::GeneralProcessModel()
{
}

GeneralProcessModel::GeneralProcessModel(double t0, double t1):TModel(t0,t1)
{
	//создание моделей ГНСС систем
	
	
}

TVector * GeneralProcessModel::getRight(const TVector & arg_v, double _t, TVector & k_i)
{
	return nullptr;
}
