#pragma once
#include"Matrix_classes.h"
#include<string.h>

class WhiteNoiseGenerator
{
private:
	double tk;
	double T0;
	double T1;

	double intensive = 1.0;//������������ ����
	int size;//������ �������������� �������

	TVector M;//������ ���. ��������
	TVector K;//������ ��� !!!

public:
	TVector realization;

	~WhiteNoiseGenerator();
	WhiteNoiseGenerator();
	WhiteNoiseGenerator(double _t0, double _T1, double _tk = 0.005);
	WhiteNoiseGenerator(TVector _M,TVector _K, double _intensive = 1);

	TVector getNext();

	double operator [](double i)const;
	double getStepLimit() { return tk; }
	double Z_d(double _d);
	int toFile(std::string out, double Step);
};
