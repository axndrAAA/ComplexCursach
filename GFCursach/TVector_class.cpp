#pragma once
#include"stdafx.h"
#include"Matrix_classes.h"
#include"TQuaternion.h"
#include<vector>
using namespace std;


TVector::TVector(int i) {
	vect = vector<double>(i, 0.0);
}

TVector::~TVector() {
	vect.clear();
}

TVector::TVector():TVector(0){}

TVector::TVector(const TVector &B) {
	vect = vector<double>(B.vect);
}

TVector::TVector(const double * arr, int _size)
{
	vect = vector<double>(_size);
	for (int i = 0; i < vect.size(); i++)
	{
		vect[i] = arr[i];
	}
}

int TVector::getMinSize(TVector a, TVector b)const {
	if (a.vect.size() > b.vect.size())return b.vect.size();
	else return a.vect.size();
}

std::vector<double> TVector::getStdVector()
{
	return vector<double>(vect);
}

TVector TVector::sub(int beg, int end)
{
	if (beg < 0 || beg > vect.size() || end < 0 || end > vect.size())
		return TVector();

	TVector ret(end - beg);

	for (size_t i = beg; i < end; i++)
	{
		ret[i - beg] = vect[i];
	}
	
	return ret;
}



TQuaternion TVector::operator*(const TQuaternion &_quat)
{
	TVector this_vect_copy(3);
	this_vect_copy[0] = vect[0];
	this_vect_copy[1] = vect[1];
	this_vect_copy[2] = vect[2];
	return TQuaternion(_quat.getsclr() - this_vect_copy *_quat.getvect(),this_vect_copy*_quat.getsclr() + this_vect_copy.crossProduct(_quat.getvect()));
}

TVector TVector::RotateByRodrigFormula(TVector _e, double _phi) const
{
	//ось вращения
	TVector e(_e * (1.0 / _e.getMagnitude()));

	TVector teta(3);
	teta[0] = 2 * tan(_phi / 2.0)*e[0];
	teta[1] = 2 * tan(_phi / 2.0)*e[1];
	teta[2] = 2 * tan(_phi / 2.0)*e[2];

	TVector this_vect_copy(3);
	this_vect_copy[0] = vect[0];
	this_vect_copy[1] = vect[1];
	this_vect_copy[2] = vect[2];
	//return e*(e*this_vect_copy)*(1 - cos(_phi)) + e.crossProduct(this_vect_copy)*sin(_phi) + this_vect_copy*cos(_phi);
	return TVector(this_vect_copy + (teta * (1.0 / (1+pow(tan(_phi/2),2)))).crossProduct(this_vect_copy + (teta * 0.5).crossProduct(this_vect_copy)) );
}

TVector TVector::RotateByQuaternion(const TQuaternion &_quat)
{
	TVector this_vect_copy(3);
	this_vect_copy[0] = vect[0];
	this_vect_copy[1] = vect[1];
	this_vect_copy[2] = vect[2];

	TQuaternion vectQuat(0.0, vect[0], vect[1], vect[2]);// this_vect_copy

	return TQuaternion(_quat * (vectQuat *_quat.conj())).getvect();
}

TVector& TVector::operator =(const TVector& B) {
	if (this == &B) return *this;
	vect.clear();
	vect = vector<double>(B.vect);
	return *this;

}


TVector TVector::operator+(const TVector& _v)const {
	TVector buf(min(vect.size(),_v.vect.size()));
	for (int i = 0; i < buf.vect.size(); i++)
		buf[i] = (*this)[i] + _v[i];
	return buf;
}

TVector TVector::crossProduct(const TVector _v)const  {
	if (vect.size() == 3 || _v.vect.size() == 3) {
		TVector result(3);

		result[0] = vect[1] * _v[2] - vect[2] * _v[1];
		result[1] = vect[2] * _v[0] - vect[0] * _v[2];
		result[2] = vect[0] * _v[1] - vect[1] * _v[0];
		return result;

	}
	else throw IncorrectSizeException();
}

double& TVector::operator[](int i) {
	if (i > vect.size() || i < 0) throw IncorrectIndexException();
	return vect[i];
}

double TVector::operator [](int i) const {
	if (i > vect.size() || i < 0) throw IncorrectIndexException();
	return vect[i];
}

int TVector::getSize()const {
	return vect.size();
}

double TVector::getMagnitude() const {
	double res = 0;
	for (int i = 0; i < vect.size(); i++)res += pow(vect[i], 2);
	return sqrt(res);
}

TVector TVector::operator*(const double &d)const {
	TVector buf(vect.size());
	for (int i = 0; i < vect.size(); i++)
		buf[i] = vect[i] * d;
	return buf;
}

TVector TVector::operator/(const double &d) const
{
	TVector buf(vect.size());
	for (int i = 0; i < vect.size(); i++)buf[i] = vect[i] / d;
	return buf;
}

double TVector::operator*(const TVector& B)const {

	double summ = 0;
	for (int i = 0; i < getMinSize(*this, B); i++) {
		summ += vect[i] * B.vect[i];
	}
	return summ;
}

TVector TVector::operator*(const TMatrix& B) {
	int lim_size = 0;
	if (vect.size() >= B.getRowCount()) lim_size = B.getRowCount();
	else lim_size = vect.size();

	TMatrix _B(B);

	TVector buf(lim_size);
	for (int k = 0; k < buf.vect.size(); k++) {
		double sum_el = 0;
		for (int i = 0; i < lim_size; i++)
			sum_el += vect[i] * _B[i][k];
		buf[k] = sum_el;
		sum_el = 0;
	}
	return buf;
}

void TVector::setElement(int i, double d) {
	if (i < 0 || i > vect.size())  throw IncorrectIndexException();
	vect[i] = d;
}

void TVector::setLenght(int new_size) {
	TVector buf(*this);

	vect.clear();
	vect = vector<double>(new_size);
	int lim = 0;
	if (vect.size() > new_size) lim = new_size;
	else
	{
		lim = vect.size();
	}
	for (int i = 0; i < lim; i++)
		vect[i] = buf[i];
}