#pragma once
#include"TModel.h"
#define _USE_MATH_DEFINES
#include<vector>
using namespace std;
class Satellite
{

protected:


	TVector Xcur;
	TVector X0;

	//���������� � ������������ ���������
	//Theta - ������� ��������
	//omega - �������� ����������
	//OMEGA - ������� ����������� ����
	//i - ���������� ������
	//a-������ �������
	//e - ��������������
	TVector OsculToGeo(double Theta, double omega, double OMEGA, double i, double a, double e);
	//double getVn(double Theta);
	//double getVr(double Theta);
public:
	static double mu;//��������������� �������������� ����������;



	Satellite();
	Satellite(TVector xo);//���������� � ���
	Satellite(std::vector<double> _x0);//���������� � ���, ��������� � std::vector

	//���������� � ������������ ���������
	//Theta - ������� ��������
	//omega - ������ ����������
	//OMEGA - ������� ����������� ����
	//i - ���������� ������
	//a-������ �������
	//e - ��������������
	Satellite(double Theta, double omega, double OMEGA, double i, double a, double e);

	TVector getRHS(const TVector &arg_v, double _t);
	TVector getXcur() const;
	void setXcur(const TVector &newX); 
	TVector getX0();
	void setX0(const TVector newX);



	static double ToRad(double grad);
	static double ToDeg(double rad);
};

