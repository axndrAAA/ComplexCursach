#include "stdafx.h"
#include "GeneralProcessModel.h"
#include"GLONASSsystem.h"
#include<vector>
#include<iostream>
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
			temp = arg_v[i*6 + j];
			arg_sat_i[j] = temp;
		}
		args_glonass[i] = arg_sat_i;
	}
	return args_glonass;
}

vector<TVector> GeneralProcessModel::getGpsArgList(const TVector & arg_v)
{
	//формирование списка векторов-аргументов для GPS
	//предполагается, что вектора состояния спутников системы глонасс - 
	// - это первые GLONASS.getSatNumber()*6 компонент фазового вектора arg_v
	//далее за ними, идут GPS.getSatNumber()*6 элементов векторов состояния 
	//спутников системы GPS


	//TODO: по аналогии с ГЛОНАСС
	vector<TVector> args_gps(GPS.getSatNumber());
	double temp = 0.0;
	for (int i = 0; i < args_gps.size(); i++)
	{
		TVector arg_sat_i(6);
		for (int j = 0; j < arg_sat_i.getSize(); j++)
		{
			temp = arg_v[(i + GLONASS.getSatNumber()) * 6 + j];
			arg_sat_i[j] = temp;
		}
		args_gps[i] = arg_sat_i;
	}
	return args_gps;
}

TVector GeneralProcessModel::getISZ_consumerArg(const TVector & arg_v)
{
	//условились, что аргументы потребиетля, это последние 6 значений в arg_v
	TVector ret(6);
	int ISZconsumerFirstIndx = arg_v.getSize() - 6;
	for (int i = ISZconsumerFirstIndx; i < arg_v.getSize(); i++) {
		ret[i - ISZconsumerFirstIndx] = arg_v[i];
	}
	return ret;
}

GeneralProcessModel::GeneralProcessModel()
{
}

GeneralProcessModel::GeneralProcessModel(double t0, double t1, double smlInc):TModel(t0,t1,smlInc)
{
	//создание моделей ГНСС систем проходит перед входом в конструктор
	count_of_ur = GLONASS.getSatNumber() * 6 + GPS.getSatNumber() * 6 + 6;


	//инициализация начальных условий системы ГЛОНАСС и GPS
	TVector _x0(count_of_ur);
	for (int i = 0; i < GLONASS.getSatNumber(); i++)
	{
		for (int j = 0; j < 6; j++)
		{
			_x0[i*6 + j] = GLONASS.satellites[i].getX0()[j];
			_x0[(i + GLONASS.getSatNumber()) * 6 + j] = GPS.satellites[i].getX0()[j];
		}
	}
	

	//создание спутника-потребителя
	ISZ_consumer = Satellite(Theta, omega, OMEGA, i, a, e);

	//Инициализация начальных условий спутника-потребителя
	int ISZ_consumer_initIndex = _x0.getSize() - 6;
	for (int i = ISZ_consumer_initIndex; i < _x0.getSize(); i++) {
		_x0[i] = ISZ_consumer.getX0()[i-ISZ_consumer_initIndex];
	}
	std::cout << "X0: "; _x0.print();
	setX0(_x0);
	
	
}

TVector * GeneralProcessModel::getRight(const TVector & arg_v, double _t, TVector & k_i)
{
	//получение аргумента для спутников ГЛОНАСС
	vector<TVector> glonassArgList = getGlonassArgList(arg_v);

	//получение правых частей для спутников ГЛОНАСС
	vector<TVector> glonass_rhs = GLONASS.getRHSs(glonassArgList, _t);

	//перенос правых частей ГЛОНАСС в выходной вектор правых частей
	for (int i = 0; i < glonass_rhs.size(); i++)
	{
		for (int j = 0; j < 6; j++)
		{
			k_i[i*6 + j] = glonass_rhs[i][j];
		}
	}

	//здесь тоже самое, для GPS

	//получение аргумента для спутников GPS
	vector<TVector> gpsArgList = getGpsArgList(arg_v);

	//получение правых частей для спутников ГЛОНАСС
	vector<TVector> gps_rhs = GPS.getRHSs(glonassArgList, _t);

	//перенос правых частей ГЛОНАСС в выходной вектор правых частей
	for (int i = 0; i < gps_rhs.size(); i++)
	{
		for (int j = 0; j < 6; j++)
		{
			k_i[(i + GLONASS.getSatNumber()) * 6 + j] = gps_rhs[i][j];
		}
	}



	//получение аргумента потребителя
	TVector isz_consumer_args = getISZ_consumerArg(arg_v);
	//std::cout << "isz_consumer_args: "; isz_consumer_args.print();

	//получение правых частей потребителя
	TVector isz_consumer = ISZ_consumer.getRHS(isz_consumer_args,_t);
	//std::cout << "isz_consumer_rhs: "; isz_consumer.print();

	int ISZconsumerFirstIndx = arg_v.getSize() - 6;
	for (int i = ISZconsumerFirstIndx; i < arg_v.getSize(); i++) {
		k_i[i] = isz_consumer[i - ISZconsumerFirstIndx];
	}
	//std::cout << "k_i: "; k_i.print();


	return &k_i;
}

void GeneralProcessModel::AddResult(TVector & vect, double t)
{
	TModel::AddResult(vect, t);
	std::cout << "t: " << t << endl;
	if (t >= T1-SamplingIncrement) {
		std::cout << "Done." << endl;
	}



	if (incProgressBar) {
		incProgressBar();
	}

}

void GeneralProcessModel::addProgressBarIncrementor(int(*incFunction)(void))
{
	incProgressBar = incFunction;
}
