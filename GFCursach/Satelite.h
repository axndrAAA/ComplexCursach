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

	//координаты в оскулирующих элементах
	//Theta - истнна€ аномали€
	//omega - аргумент перицентра
	//OMEGA - долгота восход€щего узла
	//i - наклонение орбиты
	//a-больш€ полуось
	//e - эксцентриситет
	TVector OsculToGeo(double Theta, double omega, double OMEGA, double i, double a, double e);
	//double getVn(double Theta);
	//double getVr(double Theta);
public:
	static double mu;//геоцентрическа€ гравитационна€ посто€нна€;



	Satellite();
	Satellite(TVector xo);//координаты в √— 
	Satellite(std::vector<double> _x0);//координаты в √— , собранные в std::vector

	//координаты в оскулирующих элементах
	//Theta - истнна€ аномали€
	//omega - широта перицентра
	//OMEGA - долгота восход€щего узла
	//i - наклонение орбиты
	//a-больш€ полуось
	//e - эксцентриситет
	Satellite(double Theta, double omega, double OMEGA, double i, double a, double e);

	TVector getRHS(const TVector &arg_v, double _t);
	TVector getXcur() const;
	void setXcur(const TVector &newX); 
	TVector getX0();
	void setX0(const TVector newX);



	static double ToRad(double grad);
	static double ToDeg(double rad);
};

