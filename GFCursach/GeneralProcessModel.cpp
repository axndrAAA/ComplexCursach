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
	//������������ ������ ��������-���������� ��� �������
	//��������������, ��� ������� ��������� ��������� ������� ������� - 
	// - ��� ������ GLONASS.getSatNumber()*6 ��������� �������� ������� arg_v


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
	//������������ ������ ��������-���������� ��� GPS
	//��������������, ��� ������� ��������� ��������� ������� ������� - 
	// - ��� ������ GLONASS.getSatNumber()*6 ��������� �������� ������� arg_v
	//����� �� ����, ���� GPS.getSatNumber()*6 ��������� �������� ��������� 
	//��������� ������� GPS


	//TODO: �� �������� � �������
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
	//����������, ��� ��������� �����������, ��� ��������� 6 �������� � arg_v
	TVector ret(6);
	int ISZconsumerFirstIndx = arg_v.getSize() - 6;
	for (int i = ISZconsumerFirstIndx; i < arg_v.getSize(); i++) {
		ret[i - ISZconsumerFirstIndx] = arg_v[i];
	}
	return ret;
}

void GeneralProcessModel::addNoiseToICGlonass()
{
	////���������� ��������� ������� ������������� ��������� �������
	//for (int i = 0; i < GLONASS.getSatNumber(); i++)
	//{
	//	//������� ��������� � ��������� �����������
	//	GausianExtention wng(GLONASS.satellites[i].getX0(), TVector(Kglonass, 6));

	//	//�������� ������� ������ X0
	//	TVector x0 = GLONASS.satellites[i].getX0();

	//	//��������� � X0 ��� (�.�. ��� ���������� � ���������� �� �������)
	//	x0 = x0 + wng.getNext();

	//	//������ �� �� �����������
	//	GLONASS.satellites[i].setX0(x0);
	//}
}

void GeneralProcessModel::addNoiseToICGps()
{
	////���������� ��������� ������� ������������� ��������� GPS
	//for (int i = 0; i < GPS.getSatNumber(); i++)
	//{
	//	//������� ��������� � ��������� �����������
	//	GausianExtention wng(GPS.satellites[i].getX0(), TVector(Kgps, 6));

	//	//�������� ������� ������ X0
	//	TVector x0 = GPS.satellites[i].getX0();

	//	//��������� � X0 ��� (�.�. ��� ���������� � ���������� �� �������)
	//	x0 = x0 + wng.getNext();

	//	//������ �� �� �����������
	//	GPS.satellites[i].setX0(x0);
	//}
}

void GeneralProcessModel::addNoiseToICconsumer()
{
	////���������� ��������� ������� ��������-�����������
	////������� ��������� � ��������� �����������
	//GausianExtention wng(ISZ_consumer.getX0(), TVector(Kconsumer, 6));
	////�������� ������� ������ X0
	//TVector x0 = ISZ_consumer.getX0();
	////��������� � X0 ��� (�.�. ��� ���������� � ���������� �� �������)
	//x0 = x0 + wng.getNext();
	////������ �� �� �����������
	//ISZ_consumer.setX0(x0);
}

vector<NavSatellite> GeneralProcessModel::pullVectorToModel(const TVector & v, double t)
{
	//�������� ������ ��������, ���������� �� ������� � ������ ��� � �������
	vector<TVector> glonassArgs = getGlonassArgList(v);
	for (size_t i = 0; i < GLONASS.getSatNumber(); i++)
	{
		GLONASS.satellites[i].setXcur(glonassArgs[i]);
	}

	//�������� ������ ��������, ���������� �� GPS � ������ ��� � �������
	vector<TVector> gpsArgs = getGpsArgList(v);
	for (size_t i = 0; i < GPS.getSatNumber(); i++)
	{
		GPS.satellites[i].setXcur(gpsArgs[i]);
	}

	//��������� � ����������� ������ �����������
	TVector consumerArg = getISZ_consumerArg(v);
	ISZ_consumer.setXcur(consumerArg);

	//������������ ��������� ������ ���� ������������� ���������
	vector<NavSatellite> NavSatellites = vector<NavSatellite>(GLONASS.satellites);
	copy(GPS.satellites.begin(), NavSatellites.end(), back_inserter(NavSatellites));

	return NavSatellites;
}

vector<NavSatellite> GeneralProcessModel::getBestConstellation(vector<NavSatellite> navSats)
{
	//TODO: ����� ���������
	vector<NavSatellite> out = vector<NavSatellite>(4);


	return vector<NavSatellite>();
}

bool GeneralProcessModel::isVisble(Satellite conSat, NavSatellite nSat)
{
	//TODO: ���������

	TVector r_con_nav = conSat.getXcur() + nSat.getXcur()*(-1.0);
	float r_con_mod = conSat.getXcur().getMagnitude();
	float r_con_nav_mod = r_con_nav.getMagnitude();

	float gamma = M_PI - acos(conSat.getXcur() * r_con_nav
		/ r_con_mod * r_con_nav_mod);
	float alpha = acos(6371000.0 / r_con_mod);

	if (gamma > alpha) {
		return true;
	}
	else {
		return false;
	}
}


GeneralProcessModel::GeneralProcessModel()
{
}

GeneralProcessModel::GeneralProcessModel(double t0, double t1, double smlInc):TModel(t0,t1,smlInc)
{
	//�������� ������� ���� ������ �������� ����� ������ � �����������
	count_of_ur = GLONASS.getSatNumber() * 6 + GPS.getSatNumber() * 6 + 2 + 6;

	//���������� ��������� ������� ������������� ��������� �������
	//addNoiseToICGlonass();

	//���������� ��������� ������� ������������� ��������� GPS
	//addNoiseToICGps();


	//���������� ��������� ������� ������� ������� � GPS � ������� ������ ������������ �������
	TVector _x0(count_of_ur);
	for (int i = 0; i < GLONASS.getSatNumber(); i++)
	{
		for (int j = 0; j < 6; j++)
		{
			_x0[i*6 + j] = GLONASS.satellites[i].getX0()[j];
			_x0[(i + GLONASS.getSatNumber()) * 6 + j] = GPS.satellites[i].getX0()[j];
		}
	}

	//�������� ����������� �� ��� �������� ������ �������� ��������������� � ��������������
	//�� - N(0,1);
	wng_ro_dro = WhiteNoiseGenerator(t0, t1, smlInc,2);

	//����� ���� ��� ���������� �� �� ������������ �������
	_x0[GLONASS.getSatNumber() * 6 * 2] = m_cr_ion_ro;//��� ���������������
	_x0[GLONASS.getSatNumber() * 6 * 2 + 1] = m_sys_dro;//��� ��������������
	

	//�������� ��������-�����������
	ISZ_consumer = Satellite(Theta, omega, OMEGA, i, a, e);

	//���������� ��������� ������� ��������-�����������
	//addNoiseToICconsumer();

	//���������� ��������� ������� ��������-����������� � ������� ������ ������������ �������
	int ISZ_consumer_initIndex = _x0.getSize() - 6;
	for (int i = ISZ_consumer_initIndex; i < _x0.getSize(); i++) {
		_x0[i] = ISZ_consumer.getX0()[i-ISZ_consumer_initIndex];
	}
	std::cout << "X0: "; _x0.print();
	setX0(_x0);
	
	
}

TVector * GeneralProcessModel::getRight(const TVector & arg_v, double _t, TVector & k_i)
{
	//��������� ��������� ��� ��������� �������
	vector<TVector> glonassArgList = getGlonassArgList(arg_v);

	//��������� ������ ������ ��� ��������� �������
	vector<TVector> glonass_rhs = GLONASS.getRHSs(glonassArgList, _t);

	//������� ������ ������ ������� � �������� ������ ������ ������
	for (int i = 0; i < glonass_rhs.size(); i++)
	{
		for (int j = 0; j < 6; j++)
		{
			k_i[i*6 + j] = glonass_rhs[i][j];
			j = j;
		}
	}

	// ���� �����, ��� GPS

	//��������� ��������� ��� ��������� GPS
	vector<TVector> gpsArgList = getGpsArgList(arg_v);

	//��������� ������ ������ ��� ��������� GPS
	vector<TVector> gps_rhs = GPS.getRHSs(gpsArgList, _t);

	//������� ������ ������ GPS � �������� ������ ������ ������
	for (int i = 0; i < gps_rhs.size(); i++)
	{
		for (int j = 0; j < 6; j++)
		{
			k_i[(i + GLONASS.getSatNumber()) * 6 + j] = gps_rhs[i][j];
		}
	}


	//��� �� ������������ �������
	k_i[GLONASS.getSatNumber() * 6 * 2] = -m_ro * arg_v[GLONASS.getSatNumber() * 6 * 2]
		+ sqrt(2.0*sigma_ro*sigma_ro) * wng_ro_dro.getVal(_t)[0];//��� ���������������
	k_i[GLONASS.getSatNumber() * 6 * 2 + 1] = -m_ro * arg_v[GLONASS.getSatNumber() * 6 * 2 + 1]
		+ sqrt(2.0*sigma_dro*sigma_dro) * wng_ro_dro.getVal(_t)[1];//��� ��������������

	//��������� ��������� �����������
	TVector isz_consumer_args = getISZ_consumerArg(arg_v);
	//std::cout << "isz_consumer_args: "; isz_consumer_args.print();

	//��������� ������ ������ �����������
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
	/*������ �������� ������ � �������� ������� ����������� � ������ � GPS � ������ ��� �������� ���������� ������
	� �������� ������ ���� ������������� ���������*/
	vector<NavSatellite> navSats = pullVectorToModel(vect,t);

	//��������� 4� ��������� ��� ���������
	navSats = getBestConstellation(navSats);

	//����� ��������� ����� �������� ���������, 

	//���������

	//� ��� ������ ������� �������


	//��������
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
