#include "stdafx.h"
#include "GeneralProcessModel.h"
#include"GLONASSsystem.h"
#include<vector>
using namespace std;

vector<TVector> GeneralProcessModel::getGlonassArgList(const TVector & arg_v)
{
	//формирование списка векторов-аргументов для ГЛОНАСС
	//предполагается, что вектора состояния спутников системы глонасс - 
	// - это первые GLONASS.getSatNumber()*6 компонент фазового вектора arg_v


	vector<TVector> args_glonass(GLONASS.getSatNumber());
	double temp = 0.0;
	for (int i = 0; i < args_glonass.size(); i++)
	{
		TVector arg_sat_i(6);
		for (int j = 0; j < arg_sat_i.getSize(); j++)
		{
			temp = arg_v[i + j];
			arg_sat_i[j] = temp;
		}
		args_glonass[i] = arg_sat_i;
	}
	return args_glonass;
}

GeneralProcessModel::GeneralProcessModel()
{
}

GeneralProcessModel::GeneralProcessModel(double t0, double t1):TModel(t0,t1)
{
	//создание моделей ГНСС систем проходит перед входом в конструктор
	count_of_ur = GLONASS.getSatNumber() * 6;


	//инициализация начальных условий
	TVector _x0(GLONASS.getSatNumber() * 6);
	for (int i = 0; i < GLONASS.getSatNumber(); i++)
	{
		for (int j = 0; j < 6; j++)
		{
			_x0[i + j] = GLONASS.satellites[i].getX0()[j];
		}
	}
	setX0(_x0);
	
	
}

TVector * GeneralProcessModel::getRight(const TVector & arg_v, double _t, TVector & k_i)
{
	vector<TVector> glonassArgList = getGlonassArgList(arg_v);
	vector<TVector> glonass_rhs = GLONASS.getRHSs(glonassArgList, _t);
	//TODO: высерается неверная размерность













	for (int i = 0; i < glonass_rhs.size(); i++)
	{
		for (int j = 0; j < 6; j++)
		{
			k_i[i + j] = glonass_rhs[i][j];
		}
	}

	return &k_i;
}
