#pragma once
#include <vector>
#include"Matrix_classes.h"

using namespace std;
//����� �������� �������� ��������� ���������� ������
//�������� ������� �� ��������������
//�� ��������� ������ ������� 1, m = 0, sko = 1
class GaussianDistribution
{
private:
	//default midle
	vector<double> m;

	//default sko
	vector<double> sigma;

	//default intensive (���������� ��� ����)
	double intensive = 1.0;

	//��������� ������� ������
	double Z_d(double _d);
public:
	GaussianDistribution();
	GaussianDistribution(const vector<double> &_m, const vector<double> &_sigma, double _intensive = 1.0);
	~GaussianDistribution();

	vector<double> getRndByDefaultParameters();
	TVector getRndVectByDefaultParameters();
	vector<double> getRndByParameters(const vector<double> &_m, const vector<double> &_sigma, double _intensive = 1.0);
	TVector getRndVectByParameters(const vector<double> &_m, const vector<double> &_sigma, double _intensive = 1.0);


	void setDefaultM(const vector<double> &_m);
	void setDefaultSigma(const vector<double> &_sigma);
	void setDefaultIntensive(const double _intensive);

};

