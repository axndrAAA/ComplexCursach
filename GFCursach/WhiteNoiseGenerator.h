#pragma once
#include<vector>
#include"Matrix_classes.h"

using namespace std;

class WhiteNoiseGenerator
{
private:
	double T0 = 0;
	double T1;

	//�������� ����������
	double tk;

	//������ ���.��������
	vector<double> m;
	//������ ���
	vector<double> sko;//������ ���

	vector<TVector> values;

public:
	WhiteNoiseGenerator() {};
	WhiteNoiseGenerator(double _T0, double _T1, double _tk, int size);
	WhiteNoiseGenerator(double _T0, double _T1, double _tk);
	WhiteNoiseGenerator(double _T0, double _T1, double _tk,
		vector<double> &_m, vector<double> &_sko);
	~WhiteNoiseGenerator();

	TVector getVal(double t);
	vector<double> getStdVectVal(double t);
};

