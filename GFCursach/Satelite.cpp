#include "stdafx.h"
#include "Satelite.h"
#include<math.h>


//double Satellite::getVn(double Theta)
//{
//	return sqrt(mu / p)*(1.0 + e * cos(Theta));
//}
//
//double Satellite::getVr(double Theta)
//{
//	return  sqrt(mu / p)*e*sin(Theta);
//}

Satellite::Satellite()
{
}

Satellite::Satellite(TVector x0)
{
	this->X0 = TVector(x0);
	this->Xcur = TVector(x0);
}

Satellite::Satellite(std::vector<double> _x0)
{
	X0 = TVector(6);
	for (int i = 0; i < 6; i++) {
		X0[i] = _x0[i];
	}
	Xcur = TVector(X0);
}

Satellite::Satellite(double Theta, double omega, double OMEGA, double i, double a, double e)
{
	X0 = OsculToGeo(Theta, omega, OMEGA, i, a, e);
	Xcur = X0;
}

/*Satellite Satellite::operator=(Satellite & stl)
{
	Satellite ret;
	ret.X0 = stl.X0;
	ret.Xcur = stl.Xcur;
	return ret;
}*/

TVector Satellite::OsculToGeo(double Theta, double omega, double OMEGA, double i, double a, double e)
{
	//оскулирующие элементы
	//Theta - истнная аномалия
	//omega - аргумент перицентра
	//OMEGA - долгота восходящего узла
	//i - наклонение орбиты
	//a - большя полуось
	//e - эксцентриситет
	TVector ret(6);
	double r = a*(1.0-e * e) / (1 + e * cos(Theta));//радиус-вектор
	double u = omega + Theta;//аргумент широты
	double h = sqrt(mu*a*(1.0 - e * e));//specific angular momentum
	double p = a * (1.0 - e * e);////фокальный параметр

	ret[0] = r * (cos(u)*cos(OMEGA) - sin(u)*sin(OMEGA)*cos(i));
	ret[1] = r * (cos(u)*sin(OMEGA) - sin(u)*cos(OMEGA)*cos(i));
	ret[2] = r * sin(u)*sin(i);

	ret[3] = (ret[0] * h*e*sin(Theta) / (r*p)) - (h / r)*(sin(u)*cos(OMEGA) + cos(u)*sin(OMEGA)*cos(i));
	ret[4] = (ret[1] * h*e*sin(Theta) / (r*p)) - (h / r)*(sin(u)*sin(OMEGA) - cos(u)*cos(OMEGA)*cos(i));
	ret[5] = (ret[3] * h*e*sin(Theta) / (r*p)) + (h / r)*(cos(u)*sin(i));

	//ret[3] = ret[0] * getVr(Theta) / r + (-sin(u)*cos(OMEGA) - cos(u)*sin(OMEGA)*cos(i))*getVn(Theta);
	//ret[3] = ret[1] * getVr(Theta) / r + (-sin(u)*sin(OMEGA) - cos(u)*cos(OMEGA)*cos(i))*getVn(Theta);
	//ret[4] = ret[2] * getVr(Theta) / r + cos(u)*sin(i)*getVn(Theta);
	return ret;
}

TVector Satellite::getRHS(const TVector & arg_v, double _t)
{
	TVector ret(6);
	double r = sqrt(pow(arg_v[0], 2)+ pow(arg_v[1], 2)+ pow(arg_v[2], 2));
	ret[0] = arg_v[3];
	ret[1] = arg_v[4];
	ret[2] = arg_v[5];
	ret[3] = -mu * arg_v[0] / (r*r*r);
	ret[4] = -mu * arg_v[1] / (r*r*r);
	ret[5] = -mu * arg_v[2] / (r*r*r);

	return ret;
}

TVector Satellite::getXcur()
{
	return Xcur;
}

void Satellite::setXcur(const TVector& newX)
{
	Xcur = TVector(newX);
}

TVector Satellite::getX0()
{
	return X0;
}

void Satellite::setX0(const TVector newX0)
{
	X0 = newX0;
}

double Satellite::ToRad(double grad)
{
	return grad * M_PI / 180.0;
}

double Satellite::ToDeg(double rad)
{
	double ret = (rad / M_PI)*180.0;
	return ret;
}
