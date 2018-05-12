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

GeneralProcessModel::GeneralProcessModel(double t0, double t1, double smlInc):TModel(t0,t1,smlInc)
{
	//создание моделей ГНСС систем проходит перед входом в конструктор
	count_of_ur = GLONASS.getSatNumber() * 6 + 6;


	//инициализация начальных условий системы ГЛОНАСС
	TVector _x0(count_of_ur);
	for (int i = 0; i < GLONASS.getSatNumber(); i++)
	{
		for (int j = 0; j < 6; j++)
		{
			_x0[i + j] = GLONASS.satellites[i].getX0()[j];
		}
	}

	Satellite ISZ_conumer(Theta, omega, OMEGA, i, a, e);
	int ISZ_consumer_initIndex = _x0.getSize() - 6;
	for (int i = ISZ_consumer_initIndex; i < _x0.getSize(); i++) {
		_x0[i] = ISZ_conumer.getX0()[i-ISZ_consumer_initIndex];
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

void GeneralProcessModel::AddResult(TVector & vect, double t)
{
	TModel::AddResult(vect, t);
	//incProgressBar();

}

void GeneralProcessModel::addProgressBarIncrementor(int(*incFunction)(void))
{
	incProgressBar = incFunction;
}
