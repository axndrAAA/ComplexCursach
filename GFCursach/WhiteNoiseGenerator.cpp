#include "stdafx.h"
#include "WhiteNoiseGenerator.h"
#include"GaussianDistribution.h"


WhiteNoiseGenerator::WhiteNoiseGenerator(double _T0, double _T1, double _tk)
{
	T0 = _T0;
	T1 = _T1;
	tk = _tk;

}

WhiteNoiseGenerator::WhiteNoiseGenerator(double _T0, double _T1, double _tk, vector<double>& _m, vector<double>& _sko) :WhiteNoiseGenerator(_T0,_T1,_tk)
{
	m = _m;
	sko = _sko;
	
	//число "€чеек"
	int size = (T1 - T0) / tk;
	values = vector<TVector>(size);

	GaussianDistribution randomizer(m, sko);
	for (int i = 0; i < size; i++) {
		values[i] = randomizer.getRndVectByDefaultParameters();
	}

}

WhiteNoiseGenerator::~WhiteNoiseGenerator()
{
}

TVector WhiteNoiseGenerator::getVal(double t)
{
	int index = (int)(t / tk);
	TVector ret = values[index];
	return ret;
}

vector<double> WhiteNoiseGenerator::getStdVectVal(double t)
{
	TVector ret = getVal(t);
	return ret.getStdVector();
}
