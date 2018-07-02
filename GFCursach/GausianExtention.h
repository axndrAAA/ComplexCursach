#pragma once
#include"Matrix_classes.h"
#include<list>
#include<string.h>

class GausianExtention
{
private:
	double step = 1.0;//������ ������

	double intensive = 1.0;//������������ ����
	int size;//������ �������������� �������

	TVector M;//������ ���. ��������
	TVector K;//������ ��� !!!

	double Z_d(double _d);
public:
	std::list<TVector> realization;

	~GausianExtention();
	GausianExtention();
	GausianExtention(TVector _M,TVector _K, double _intensive = 1);

	TVector getNext();

	double getW(double t);

	int toFile(std::string out);
};
