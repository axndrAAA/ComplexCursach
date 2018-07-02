#include "stdafx.h"
#include "GeneralProcessModel.h"
#include"GLONASSsystem.h"
#include<vector>
#include<iostream>
#include"GausianExtention.h"
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

void GeneralProcessModel::addNoiseToICGlonass()
{
	//зашумление начальных условий навигационных спутников ГЛОНАСС
	for (int i = 0; i < GLONASS.getSatNumber(); i++)
	{
		//создаем генератор с заданными параметрами
		GausianExtention wng(GLONASS.satellites[i].getX0(), TVector(Kglonass, 6));

		//получаем текущий вектор X0
		TVector x0 = GLONASS.satellites[i].getX0();

		//добавляем к X0 шум (т.к. шум аддитивный и гаусовский по условию)
		x0 = x0 + wng.getNext();

		//меняем НУ на зашумленные
		GLONASS.satellites[i].setX0(x0);
	}
}

void GeneralProcessModel::addNoiseToICGps()
{
	//зашумление начальных условий навигационных спутников GPS
	for (int i = 0; i < GPS.getSatNumber(); i++)
	{
		//создаем генератор с заданными параметрами
		GausianExtention wng(GPS.satellites[i].getX0(), TVector(Kgps, 6));

		//получаем текущий вектор X0
		TVector x0 = GPS.satellites[i].getX0();

		//добавляем к X0 шум (т.к. шум аддитивный и гаусовский по условию)
		x0 = x0 + wng.getNext();

		//меняем НУ на зашумленные
		GPS.satellites[i].setX0(x0);
	}
}

void GeneralProcessModel::addNoiseToICconsumer()
{
	//зашумление начальных условий спутника-потребителя
	//создаем генератор с заданными параметрами
	GausianExtention wng(ISZ_consumer.getX0(), TVector(Kconsumer, 6));
	//получаем текущий вектор X0
	TVector x0 = ISZ_consumer.getX0();
	//добавляем к X0 шум (т.к. шум аддитивный и гаусовский по условию)
	x0 = x0 + wng.getNext();
	//меняем НУ на зашумленные
	ISZ_consumer.setX0(x0);
}

vector<int> GeneralProcessModel::getSats(const TVector & arg_v, double t)
{
	//TODO: реализация по геометрическим сотношениям
	return vector<int>();
}

GeneralProcessModel::GeneralProcessModel()
{
}

GeneralProcessModel::GeneralProcessModel(double t0, double t1, double smlInc):TModel(t0,t1,smlInc)
{
	//создание моделей ГНСС систем проходит перед входом в конструктор
	count_of_ur = GLONASS.getSatNumber() * 6 + GPS.getSatNumber() * 6 + 2 + 6;

	//зашумление начальных условий навигационных спутников ГЛОНАСС
	//addNoiseToICGlonass();

	//зашумление начальных условий навигационных спутников GPS
	//addNoiseToICGps();


	//перегрузка начальных условий системы ГЛОНАСС и GPS в фазовый вектор моделируемой системы
	TVector _x0(count_of_ur);
	for (int i = 0; i < GLONASS.getSatNumber(); i++)
	{
		for (int j = 0; j < 6; j++)
		{
			_x0[i*6 + j] = GLONASS.satellites[i].getX0()[j];
			_x0[(i + GLONASS.getSatNumber()) * 6 + j] = GPS.satellites[i].getX0()[j];
		}
	}

	//далее идут два компонента от ДУ формирующего фильтра
	_x0[GLONASS.getSatNumber() * 6 * 2] = m_cr_ion_ro;//для псевдодальности
	_x0[GLONASS.getSatNumber() * 6 * 2 + 1] = m_sys_dro;//для псевдоскорости
	

	//создание спутника-потребителя
	ISZ_consumer = Satellite(Theta, omega, OMEGA, i, a, e);

	//зашумление начальных условий спутника-потребителя
	//addNoiseToICconsumer();

	//перегрузка начальных условий спутника-потребителя в фазовый вектор моделируемой системы
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


	//два ДУ формирующего фильтра
	k_i[GLONASS.getSatNumber() * 6 * 2] = -m_ro*arg_v[GLONASS.getSatNumber() * 6 * 2] 
		+ sqrt(2.0*sigma_ro*sigma_ro)*wng_ro.getW(_t);//для псевдодальности
	k_i[GLONASS.getSatNumber() * 6 * 2 + 1] = -m_dro*arg_v[GLONASS.getSatNumber() * 6 * 2 + 1]
		+ sqrt(2.0*sigma_ro*sigma_ro)*wng_dro.getW(_t);//для псевдоскорости

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
