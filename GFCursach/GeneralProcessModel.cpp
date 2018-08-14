#pragma once
#include "stdafx.h"
#include "GeneralProcessModel.h"
#include"GLONASSsystem.h"
#include<vector>
#include<iostream>
#include<math.h>

//#include"GausianExtention.h"
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
	////зашумление начальных условий навигационных спутников ГЛОНАСС
	//for (int i = 0; i < GLONASS.getSatNumber(); i++)
	//{
	//	//создаем генератор с заданными параметрами
	//	GausianExtention wng(GLONASS.satellites[i].getX0(), TVector(Kglonass, 6));

	//	//получаем текущий вектор X0
	//	TVector x0 = GLONASS.satellites[i].getX0();

	//	//добавляем к X0 шум (т.к. шум аддитивный и гаусовский по условию)
	//	x0 = x0 + wng.getNext();

	//	//меняем НУ на зашумленные
	//	GLONASS.satellites[i].setX0(x0);
	//}
}

void GeneralProcessModel::addNoiseToICGps()
{
	////зашумление начальных условий навигационных спутников GPS
	//for (int i = 0; i < GPS.getSatNumber(); i++)
	//{
	//	//создаем генератор с заданными параметрами
	//	GausianExtention wng(GPS.satellites[i].getX0(), TVector(Kgps, 6));

	//	//получаем текущий вектор X0
	//	TVector x0 = GPS.satellites[i].getX0();

	//	//добавляем к X0 шум (т.к. шум аддитивный и гаусовский по условию)
	//	x0 = x0 + wng.getNext();

	//	//меняем НУ на зашумленные
	//	GPS.satellites[i].setX0(x0);
	//}
}

void GeneralProcessModel::addNoiseToICconsumer()
{
	////зашумление начальных условий спутника-потребителя
	////создаем генератор с заданными параметрами
	//GausianExtention wng(ISZ_consumer.getX0(), TVector(Kconsumer, 6));
	////получаем текущий вектор X0
	//TVector x0 = ISZ_consumer.getX0();
	////добавляем к X0 шум (т.к. шум аддитивный и гаусовский по условию)
	//x0 = x0 + wng.getNext();
	////меняем НУ на зашумленные
	//ISZ_consumer.setX0(x0);
}

vector<NavSatellite> GeneralProcessModel::pullVectorToModel(const TVector & v, double t)
{
	//получаем список векторов, отвечающих за ГЛОНАСС и пихаем его в систему
	vector<TVector> glonassArgs = getGlonassArgList(v);
	for (size_t i = 0; i < GLONASS.getSatNumber(); i++)
	{
		GLONASS.satellites[i].setXcur(glonassArgs[i]);
	}

	//получаем список векторов, отвечающих за GPS и пихаем его в систему
	vector<TVector> gpsArgs = getGpsArgList(v);
	for (size_t i = 0; i < GPS.getSatNumber(); i++)
	{
		GPS.satellites[i].setXcur(gpsArgs[i]);
	}

	//получение и запихивание вектоа потребителя
	TVector consumerArg = getISZ_consumerArg(v);
	ISZ_consumer.setXcur(consumerArg);

	//формирование выходного списка всех навигационных спутников
	vector<NavSatellite> NavSatellites = vector<NavSatellite>(GLONASS.satellites);
	copy(GPS.satellites.begin(), GPS.satellites.end(), back_inserter(NavSatellites));

	return NavSatellites;
}

vector<NavSatellite> GeneralProcessModel::getBestConstellation(const vector<NavSatellite> &navSats)
{
	//TODO: поиск созвездия
	vector<NavSatellite> out = vector<NavSatellite>(4);

	float pdopMin = 1e10;

	for (size_t a = 0; a < navSats.size() - 3; a++)
	{
		if (isVisble(ISZ_consumer, navSats[a])) {
			for (size_t b = a + 1; b < navSats.size(); b++)
			{
				if (isVisble(ISZ_consumer, navSats[b])) {
					for (size_t c = b + 1; c < navSats.size(); c++)
					{
						if (isVisble(ISZ_consumer, navSats[c])) {
							for (size_t d = c + 1; d < navSats.size(); d++)
							{
								if (isVisble(ISZ_consumer, navSats[d])) {
									//формируем матрицу A
									TMatrix A(4, 4);

									//делаем так же как в методичке (у Олега А домножена на -1)
									TVector r_a_con = (navSats[a].getXcur() + ISZ_consumer.getXcur()*(-1.0)).sub(0, 4);
									float r_a_con_mod = sqrt(pow(r_a_con[0], 2) + pow(r_a_con[1], 2) + pow(r_a_con[2], 2));
									r_a_con = r_a_con * (1.0 / r_a_con_mod);
									r_a_con[3] = -1.0;
									A[0] = r_a_con;

									TVector r_b_con = (navSats[b].getXcur() + ISZ_consumer.getXcur()*(-1.0)).sub(0, 4);
									float r_b_con_mod = sqrt(pow(r_b_con[0], 2) + pow(r_b_con[1], 2) + pow(r_b_con[2], 2));
									r_b_con = r_b_con * (1.0 / r_b_con_mod);
									r_b_con[3] = -1.0;
									A[1] = r_b_con;

									TVector r_c_con = (navSats[c].getXcur() + ISZ_consumer.getXcur()*(-1.0)).sub(0, 4);
									float r_c_con_mod = sqrt(pow(r_c_con[0], 2) + pow(r_c_con[1], 2) + pow(r_c_con[2], 2));
									r_c_con = r_c_con * (1.0 / r_c_con_mod);
									r_c_con[3] = -1.0;
									A[2] = r_c_con;

									TVector r_d_con = (navSats[d].getXcur() + ISZ_consumer.getXcur()*(-1.0)).sub(0, 4);
									float r_d_con_mod = sqrt(pow(r_d_con[0], 2) + pow(r_d_con[1], 2) + pow(r_d_con[2], 2));
									r_d_con = r_d_con * (1.0 / r_d_con_mod);
									r_d_con[3] = -1.0;
									A[3] = r_d_con;

									TMatrix Q = (A.flip()*A).inverse();

									float PDOP = sqrt(pow(Q[0][0], 2) + pow(Q[1][1], 2) + pow(Q[2][2], 2));

									if (PDOP < pdopMin) {
										pdopMin = PDOP;
										out = {
											navSats[a],
											navSats[b],
											navSats[c],
											navSats[d],
										};
									}
								}
							}
						}
					}
				}
			}
		}
	}

	return out;
}

bool GeneralProcessModel::isVisble(const Satellite &conSat, const NavSatellite &nSat)
{
	//радиус-векторы потребителя и навигационного НИСЗ
	TVector r_con = conSat.getXcur().sub(0, 3);   
	TVector r_ns = nSat.getXcur().sub(0, 3);
	TVector r_con_nav = r_con + r_ns*(-1.0);

	double r_con_mod = r_con.getMagnitude();
	double r_con_nav_mod = r_con_nav.getMagnitude();

	double gamma = M_PI - acos(r_con * r_con_nav
		/ (r_con_mod * r_con_nav_mod));
	double alpha = acos(6371000.0 / r_con_mod);

	if (gamma > alpha) {
		return true;
	}else {
		return false;
	}
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

	//создание генераторов БШ для имитации ошибок измеений псевдодальности и псевдоскорости
	//БШ - N(0,1);
	wng_ro_dro = WhiteNoiseGenerator(t0, t1, smlInc,2);

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
			j = j;
		}
	}

	// тоже самое, для GPS

	//получение аргумента для спутников GPS
	vector<TVector> gpsArgList = getGpsArgList(arg_v);

	//получение правых частей для спутников GPS
	vector<TVector> gps_rhs = GPS.getRHSs(gpsArgList, _t);

	//перенос правых частей GPS в выходной вектор правых частей
	for (int i = 0; i < gps_rhs.size(); i++)
	{
		for (int j = 0; j < 6; j++)
		{
			k_i[(i + GLONASS.getSatNumber()) * 6 + j] = gps_rhs[i][j];
		}
	}


	//два ДУ формирующего фильтра
	k_i[GLONASS.getSatNumber() * 6 * 2] = -m_ro * arg_v[GLONASS.getSatNumber() * 6 * 2]
		+ sqrt(2.0*sigma_ro*sigma_ro) * wng_ro_dro.getVal(_t)[0];//для псевдодальности
	k_i[GLONASS.getSatNumber() * 6 * 2 + 1] = -m_ro * arg_v[GLONASS.getSatNumber() * 6 * 2 + 1]
		+ sqrt(2.0*sigma_dro*sigma_dro) * wng_ro_dro.getVal(_t)[1];//для псевдоскорости

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
	/*делаем выгрузку данных и фазового вектора интегратора в классы в GPS и ГЛНАСС для удобства дальнейшей работы
	и получаем список всех навигационных спутников*/
	vector<NavSatellite> navSats = pullVectorToModel(vect,t);

	//получение 4х спутников для измерений
	navSats = getBestConstellation(navSats);

	//здесь реализуем выбор рабочего созвездия, 

	//измерения

	//и шаг самого фильтра Кламана


	//заглушка
	TModel::AddResult(vect, t);
	std::cout << "t: " << t << endl;
	if (t >= T1-SamplingIncrement) {
		std::cout << "Done." << endl;
	}



}

void GeneralProcessModel::addProgressBarIncrementor(int(*incFunction)(void))
{
	incProgressBar = incFunction;
}
