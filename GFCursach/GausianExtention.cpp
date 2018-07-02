#include "stdafx.h"
#include "GausianExtention.h"
#include<fstream>
#include<string.h>
#define _USE_MATH_DEFINES
#include<math.h>

using namespace std;


GausianExtention::GausianExtention()
{
}


GausianExtention::~GausianExtention()
{
}


GausianExtention::GausianExtention(TVector _M, TVector _K, double _intensive)
{
	M = _M;
	K = _K;
	size = _M.getSize();
	intensive = _intensive;
}

TVector GausianExtention::getNext()
{
	TVector ret(size);
	for(int i = 0; i < ret.getSize();i++)
		ret[i] = M[i] + Z_d(K[i])*sin(2.0 * M_PI*(((double)rand() / RAND_MAX))) * intensive;
	realization.push_back(ret);
	return ret;
}



double GausianExtention::Z_d(double _d)
{
	return sqrt(2.0*_d*log(1.0 / ((double)rand() / RAND_MAX)));
}

int GausianExtention::toFile(std::string out)
{

	ofstream fout(out, ios_base::out | ios_base::trunc);
	if (!fout) {
		return 1;
	}
	fout.setf(ios::fixed);

	fout << "t ";
	for (int i = 0; i < size; i++)
		fout << "wn_" << i << " ";
	fout << endl;

	int t = 0;
	while (!realization.empty())
	{
		fout << t << " ";
		TVector str = realization.front();
		for (int j = 0; j < str.getSize(); j++)
		{
			fout << str[j] << " ";
		}
		fout << endl;
		realization.pop_front();
		t += step;

	}

	fout.close();
	return 0;
}