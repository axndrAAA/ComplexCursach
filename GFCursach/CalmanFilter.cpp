#include "stdafx.h"
#include "CalmanFilter.h"
#include "Satelite.h"



TMatrix CalmanFilter::getH(const Satellite & consumer, const vector<NavSatellite>& navSats, double t)
{
	TVector Xcon= consumer.getXcur();
	TMatrix H(6,6);

	for (int i = 0; i < 3; i++) {
		TVector Xnav_i = navSats[i].getXcur();
		double r = sqrt(pow(Xnav_i[0] - Xcon[0], 2) + pow(Xnav_i[1] - Xcon[1], 2) + pow(Xnav_i[2] - Xcon[2], 2));
		H[i][0] = (Xcon[0] - Xnav_i[0]) / r;
		H[i][1] = (Xcon[1] - Xnav_i[1]) / r;
		H[i][2] = (Xcon[2] - Xnav_i[2]) / r;
		double dr = sqrt(pow(Xnav_i[3] - Xcon[3], 2) + pow(Xnav_i[4] - Xcon[4], 2) + pow(Xnav_i[5] - Xcon[5], 2));
		H[i][3] = (Xcon[3] - Xnav_i[3]) / dr;
		H[i][4] = (Xcon[4] - Xnav_i[4]) / dr;
		H[i][5] = (Xcon[5] - Xnav_i[5]) / dr;
	}
	
	return H;
}

TMatrix CalmanFilter::getFi(const TVector & X, double dt)
{
	double mu = Satellite::mu;
	double r = sqrt(pow(X[0], 2) + pow(X[1], 2) + pow(X[2], 2));
	TMatrix A(6, 6);

	A[0][3] = 1.0;
	A[1][4] = 1.0;
	A[2][5] = 1.0;
	
	A[3][0] = -mu * (1.0 - 3.0*X[0] * X[0] / (r*r)) / (r*r*r);
	A[3][1] = 3.0*mu *X[0] * X[1] / pow(r, 5);
	A[3][2] = 3.0*mu *X[0] * X[2] / pow(r, 5);
	
	A[4][0] = 3.0*mu *X[0] * X[1] / pow(r, 5);
	A[4][1] = -mu * (1.0 - 3.0*X[1] * X[1] / (r*r)) / (r*r*r);
	A[4][2] = 3.0*mu *X[1] * X[3] / pow(r, 5);

	A[5][0] = 3.0*mu *X[0] * X[2] / pow(r, 5);
	A[5][1] = 3.0*mu *X[1] * X[3] / pow(r, 5);
	A[5][2] = -mu * (1.0 - 3.0*X[2] * X[2] / (r*r)) / (r*r*r);

	TMatrix E = TMatrix::getE_Matrix(6);
	TMatrix Fi = E + A * dt;
	return Fi;
}

CalmanFilter::CalmanFilter()
{
}

void CalmanFilter::doStep(const Satellite & consumer, const vector<NavSatellite>& navSats,const TVector &y, double t)
{
	double dt = t - prev_t;
	TMatrix Fi = getFi(X_zv_cur,dt);

	//прогноз
	TMatrix P_kr_next = Fi * P_zv_cur*Fi.flip();
	TVector X_kr_next = Fi * X_zv_cur;


	TMatrix H = getH(consumer,navSats,t);
	//оценка
	TMatrix P_zv_next = (P_kr_next.inverse() + H.flip()*D_etta.flip()*H).flip();
	TVector X_zv_next = X_kr_next + P_zv_next * H.flip()*D_etta.flip()*(y + (H * X_kr_next)*(-1.0));

	P_zv_cur = P_zv_next;
	X_zv_cur = X_zv_next;
	prev_t = t;
}
