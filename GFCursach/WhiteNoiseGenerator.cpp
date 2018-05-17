﻿#include "stdafx.h"
#include "WhiteNoiseGenerator.h"
#include<fstream>
#include<string.h>
#define _USE_MATH_DEFINES
#include<math.h>

using namespace std;


WhiteNoiseGenerator::WhiteNoiseGenerator()
{
}


WhiteNoiseGenerator::~WhiteNoiseGenerator()
{
}


WhiteNoiseGenerator::WhiteNoiseGenerator(double _t0, double _T1, double _tk)
{
	T0 = _t0;
	T1 = _T1;
	tk = _tk;

	int result_size = (int)((_T1 - _t0) / tk);
	double disp = 1.0 / tk;
	TVector _x0(result_size + 1);

	//srand(1);//time(0)////////////////////////////////////////////////////////////////////////////////////////////
	for (int i = 0; i < _x0.getSize(); i++) {
		_x0[i] = 0.0 + Z_d(disp)*sin(2.0 * M_PI*(((double)rand() / RAND_MAX))) * intensive;
		if (isnan(_x0[i])) {
			i = i;

		}
	}
	realization = _x0;
}

WhiteNoiseGenerator::WhiteNoiseGenerator(TVector _M, TVector _K, double _intensive)
{
	M = _M;
	K = _K;
	size = _M.getSize();
	intensive = _intensive;
}

TVector WhiteNoiseGenerator::getNext()
{
	TVector ret(size);
	for(int i = 0; i < ret.getSize();i++)
		ret[i] = M[i] + Z_d(K[i])*sin(2.0 * M_PI*(((double)rand() / RAND_MAX))) * intensive;
	return ret;
}

double WhiteNoiseGenerator::operator[](double t) const
{
	int i___ = (int)(t / tk);
	return realization[(int)(t / tk)];
}

double WhiteNoiseGenerator::Z_d(double _d)
{
	return sqrt(2.0*_d*log(1.0 / ((double)rand() / RAND_MAX)));
}

int WhiteNoiseGenerator::toFile(std::string out, double Step)
{

	ofstream fout(out, ios_base::out | ios_base::trunc);
	if (!fout) {
		return 1;//������ 
	}
	fout.setf(ios::fixed);

	//���������
	fout << "t WN" << endl;
	for (double i = T0; i < T1; i += Step) {
		fout << i << " " << this->operator[](i) << endl;
	}

	fout.close();
	return 0;
}