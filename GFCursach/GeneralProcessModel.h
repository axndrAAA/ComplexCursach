#pragma once
#include"TModel.h"
#include"Satelite.h"
#include"GLONASSsystem.h"
#include"GPSSystem.h"
#include"CalmanFilter.h"
#include"WhiteNoiseGenerator.h"
#include<vector>
class GeneralProcessModel: public TModel
{
public:
	GLONASSsystem GLONASS;
	GPSSystem GPS;
	Satellite ISZ_consumer;
	CalmanFilter filter;

	//TODO: ��� ������ ���� ����� �� ����������, ��� � � ������� �������
	WhiteNoiseGenerator wng_ro_dro;

private:
	int(*incProgressBar)() = nullptr;

	//��������� ������ ���-�����������
	double Theta = Satellite::ToRad(60);
	double omega = Satellite::ToRad(0);
	double OMEGA = Satellite::ToRad(0);
	double i = Satellite::ToRad(0);
	double a = 500 * 1000;
	double e = Satellite::ToRad(0);

	//�������� ���������� ��������� ������� ��������� �������� ���������
	const double Kglonass[6] = {13.0, 13.0, 13.0, 0.3, 0.3, 0.3};
	const double Kgps[6] = {10.0, 10.0, 10.0, 0.1, 0.1 , 0.1};
	const double Kconsumer[6] = { 100.0, 100.0, 100.0, 1.0, 1.0 , 1.0 };

	//��������� ���������� ��������� ���������������
	double sigma_cr_ion_ro = 0.0;
	double m_cr_ion_ro = 0.0;

	//��������� ���������� ��������� ��������������
	double sigma_sys_dro = 0.0;
	double m_sys_dro = 0.0;

	//��������� ������������ ������� ���������������
	double m_ro = 0.0;
	double sigma_ro = 15;//m

	//��������� ������������ ������� ��������������
	double m_dro = 0.0;
	double sigma_dro = 0.1;//m/s




	vector<TVector> getGlonassArgList(const TVector& arg_v);
	vector<TVector> getGpsArgList(const TVector& arg_v);
	TVector getISZ_consumerArg(const TVector& arg_v);
	void addNoiseToICGlonass();
	void addNoiseToICGps();
	void addNoiseToICconsumer();

	//��� �������:

	//������� ���������� ������� ������� � ������ ������ ���������
	vector<int> getSats(const TVector &arg_v,double t);
	
public:
	GeneralProcessModel();
	GeneralProcessModel(double t0, double t1,double smlInc);

	TVector *getRight(const TVector &arg_v, double _t, TVector &k_i);
	
	void AddResult(TVector &vect, double t);
	void addProgressBarIncrementor(int(*incFunction)(void));
};

