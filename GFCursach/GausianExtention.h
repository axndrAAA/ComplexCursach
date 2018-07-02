#pragma once
#include"Matrix_classes.h"
#include<list>
#include<string.h>

class GausianExtention
{
private:
	double step = 1.0;//часота выдачи

	double intensive = 1.0;//интенсвность шума
	int size;//размер генеирируемого вектора

	TVector M;//вектор мат. ожиданий
	TVector K;//вектор СКО !!!

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
