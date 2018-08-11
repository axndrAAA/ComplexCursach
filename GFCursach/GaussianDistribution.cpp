#include "stdafx.h"
#include "GaussianDistribution.h"
#define _USE_MATH_DEFINES
#include<math.h>
#include<vector>
using namespace std;

GaussianDistribution::GaussianDistribution()
{
	m = vector<double>(1);
	m[0] = 0.0;
	sigma = vector<double>(1);
	sigma[0] = 1.0;
}

GaussianDistribution::GaussianDistribution(const vector<double>& _m, const vector<double>& _sigma, double _intensive)
{
	m = _m;
	sigma = _sigma;
	intensive = _intensive;
}




GaussianDistribution::~GaussianDistribution()
{
}

vector<double> GaussianDistribution::getRndByDefaultParameters()
{
	vector<double> ret = getRndByParameters(m, sigma, intensive);
	return ret;
}

TVector GaussianDistribution::getRndVectByDefaultParameters()
{
	vector<double> rnd = getRndByDefaultParameters();
	TVector ret = TVector(rnd.size());
	for (int i = 0; i < ret.getSize(); i++) {
		ret[i] = rnd[i];
	}
	return ret;
}

vector<double> GaussianDistribution::getRndByParameters(const vector<double>& _m, const vector<double>& _sigma, double _intensive)
{
	vector<double> ret = vector<double>(_m.size());
	for (int i = 0; i < _m.size(); i++) {
		ret[i] = _m[i] + Z_d(_sigma[i])*sin(2.0 * M_PI*(((double)rand() / RAND_MAX))) * _intensive;
	}
	return ret;
}

TVector GaussianDistribution::getRndVectByParameters(const vector<double>& _m, const vector<double>& _sigma, double _intensive)
{
	vector<double> rnd = getRndByParameters(_m,_sigma,_intensive);
	TVector ret = TVector(rnd.size());
	for (int i = 0; i < ret.getSize(); i++) {
		ret[i] = rnd[i];
	}
	return ret;
}

void GaussianDistribution::setDefaultM(const vector<double>& _m)
{
	m = _m;
}

void GaussianDistribution::setDefaultSigma(const vector<double>& _sigma)
{
	sigma = _sigma;
}

void GaussianDistribution::setDefaultIntensive(const double _intensive)
{
	intensive = _intensive;
}

double GaussianDistribution::Z_d(double _d)
{
	return sqrt(2.0*_d*log(1.0 / ((double)rand() / RAND_MAX)));
}