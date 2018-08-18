#pragma once
#include"stdafx.h"
#include"Matrix_classes.h"
#include"math.h"
#include<exception>
#include<iostream>

using namespace std;

void show(TMatrix _m) {
	for (int i = 0; i < _m.getRowCount(); i++) {
		for (int j = 0; j < _m.getColCount(); j++)
			cout << _m[i][j] << " ";
		cout << endl;
	}
	cout << endl;
}

void show(TVector _m) {
	for (int i = 0; i < _m.getSize(); i++)
		cout << _m[i] << " ";
	cout << endl;
}

int min(int a, int b) {
	if (a < b)return a;
	else return b;
}


// определение класса TMatrix
TMatrix::TMatrix() {
	
}

TMatrix::TMatrix(int _i, int _j) {

	matrix = vector<TVector>(_i);
	for (int i = 0; i < _i; i++) {
		matrix[i] = TVector(_j);
	}
}

TMatrix::~TMatrix() {
	matrix.clear();
}

TMatrix::TMatrix(const TMatrix& B) {

	matrix = vector<TVector>(B.matrix);
	//matrix.size() = B.matrix.size();
	//matrix[0].getSize() = B.matrix[0].getSize();

	//matrix = new TVector[matrix.size()];
	//for (int i = 0; i < matrix.size(); i++) {
	//	matrix[i] = TVector(matrix[0].getSize());
	//}
	//for (int i = 0; i < matrix.size(); i++)
	//		matrix[i] = B[i];
}

TVector& TMatrix::operator [](int i) {
	if ((i >= 0 && i<matrix.size()))  return matrix[i];
	else throw IncorrectIndexException();
}

TVector TMatrix::operator [](int i)const {
	if ((i >= 0 && i<matrix.size()))  return matrix[i];
	else throw IncorrectIndexException();
}

TMatrix& TMatrix::operator =(const TMatrix& B) {


	matrix.clear();
	matrix = vector<TVector>(B.matrix);
	//this->matrix.size() = B.matrix.size();
	//this->matrix[0].getSize() = B.matrix[0].getSize();

	//
	//matrix = new TVector[matrix.size()];
	//for (int i = 0; i < matrix.size(); i++) {
	//	matrix[i] = TVector(matrix[0].getSize());
	//}

	//for (int i = 0; i < matrix.size(); i++)
	//		matrix[i] = B.matrix[i];
	return *this;
}

TMatrix TMatrix::operator+(const TMatrix& B) {
	int lim_i = min(matrix.size(), B.getRowCount());
	int lim_j = min(matrix.size(), B.getColCount());


	TMatrix buf(lim_i, lim_j);

	for (int i = 0; i < lim_i; i++)
			buf.matrix[i] = matrix[i]+ B.matrix[i];
	return buf;

}

bool TMatrix::checkSymmetric() const {
	if (matrix.size() == matrix[0].getSize()) {
		for (int i = 0; i < matrix.size(); i++)
			for (int j = 0; j < matrix[0].getSize(); j++)
				if (matrix[i][j] != matrix[j][i]) return false;
	}
	else return false;
	return true;
}

TMatrix TMatrix::flip() {
	TMatrix buf(matrix[0].getSize(), matrix.size());

	for (int i = 0; i < buf.matrix.size(); i++)
		for (int j = 0; j < buf.matrix[0].getSize(); j++) {
			buf.matrix[i][j] = matrix[j][i];
		}
	return buf;
}

int TMatrix::getColCount() const {
	return matrix[0].getSize();
}

int TMatrix::getRowCount() const {
	return matrix.size();
}

TMatrix TMatrix::operator*(double d) {
	TMatrix buf(*this);

	for (int i = 0; i < matrix.size(); i++)
			buf.matrix[i] = buf.matrix[i] * d;
	return buf;
}

TMatrix TMatrix::operator*(const TMatrix& B) {
	int lim_i = min(matrix.size(), B.getRowCount());
	int lim_j = min(matrix[0].getSize(), B.getColCount());


	TMatrix buf(lim_i, lim_j);

	for (int i = 0; i < buf.matrix.size(); i++) {
		for (int j = 0; j < buf.matrix[0].getSize(); j++) {
			double s = 0;
			for (int inner = 0; inner < matrix[0].getSize(); inner++) {
				s += matrix[i][inner] * B.matrix[inner][j];
				buf[i][j] = s;
			}
		}
	}
	return buf;
}

TVector TMatrix::operator*(const TVector& v) {
	int lim_i = 1;
	int lim_j = min(matrix[0].getSize(), v.getSize());

	TVector buf(matrix.size());
	for (int i = 0; i < matrix.size(); i++) {
		double sum_el = 0;
		for (int j = 0; j < lim_j; j++)
			sum_el += matrix[i][j] * v[j];
		buf[i] = sum_el;
		sum_el = 0;
	}
	return buf;
}

void TMatrix::SetElement(int i, int j, double d) {
	matrix[i][j] = d;
}

void TMatrix::setSize(int _i, int _j) {

	TMatrix buf(*this);

	matrix.clear();

	matrix = vector<TVector>(_i);
	for (int i = 0; i < matrix.size(); i++) {
		matrix[i] = TVector(_j);
	}
	
	int lim_i;
	int lim_j;
	if (matrix.size() >= buf.getRowCount()) lim_i = buf.getRowCount();
	else lim_i = matrix.size();
	if (matrix[0].getSize() >= buf.getColCount()) lim_j = buf.getColCount();
	else lim_j = matrix[0].getSize();

	for (int i = 0; i < lim_i; i++)
		for (int j = 0; j < lim_j; j++)
			matrix[i][j] = buf.matrix[i][j];
			
	//show(*this);
}

TMatrix TMatrix::getE_Matrix(int sz)
{
	TMatrix ret(sz, sz);
	for (size_t i = 0; i < ret.getRowCount(); i++)
	{
		ret[i][i] = 1.0;
	}
	return ret;
}

TMatrix TMatrix::inverse() {
	//Метод Гаусса
	//создаем новую матрицу, приводим к квадратной

	TMatrix temp(*this);
	int siz = min(temp.getColCount(), temp.getRowCount());
	temp.setSize(siz, siz);
	//проверка отсутствия нулей на главной диагонали
	int i = 0;

	//show(temp);
	//cout << temp(1, 1) << endl;
	//дополнение матрицы единичной
	temp.setSize(temp.getRowCount(), temp.getColCount() * 2);
	//show(temp);

	for (int i = 0; i < temp.getRowCount(); i++)
		for (int j = temp.getColCount() / 2; j < temp.getColCount(); j++)
			if (i + temp.getColCount() / 2 == j) { temp[i][j] = 1; break; }//
			else continue;


			//прямой прогон
			i = 0;
			bool progon_end = false;
			bool nul_on_diag_exp = false;

			
			for (int j = 0; j < temp.getColCount(); j++) {
				if (temp[i][j]) {
					double mnog = temp[i][j];
					for (int k = j; k < temp.getColCount(); k++) temp[i][j] = temp[i][j] / mnog;
					//show(temp);
					if (i + 1 == temp.getRowCount()) { progon_end = true; }
					for (int i2 = i + 1; i2 < temp.getRowCount(); i2++) {

						mnog = temp[i2][j];
						for (int j2 = j; j2 < temp.getColCount(); j2++) {
							temp[i2][j2] = temp[i2][j2] - temp[i][j2] * mnog;
						}
					}
					//show(temp);
					if (!progon_end)i++;
					else break;

				}
				else {
					for (int i1 = i + 1; i1 < temp.getRowCount(); i1++)
						if (i1 != temp.getRowCount()) {
							if (temp[i1][j]) {
								for (int m = 0; m < temp.getColCount(); m++) {
									//temp(i, m) = temp(i, m) + temp(i1, m);
									double tmp = temp[i][m];
									temp[i][m] = temp[i1][m];
									temp[i1][m] = tmp;
								}
								//show(temp);
								break;
							}
							else i1++;
						}
						else
							for (int m = 0; m < temp.getColCount(); m++) {
								//temp(i, m) = temp(i, m) + temp(i1 - 1, m);
								double tmp = temp[i][m];
								temp[i][m] = temp[i1 - 1][m];
								temp[i1 - 1][m] = tmp;
							}
					//show(temp);
					j--;
				}
			}





			//обратный прогон
			progon_end = false;
			i = temp.getRowCount() - 1;
			for (int j = temp.getColCount() / 2 - 1; j >= 0; j--) {
				double mnog = temp[i][j];
				if (i == 0) { progon_end = true; }

				for (int i2 = i - 1; i2 >= 0; i2--) {
					mnog = temp[i2][j];
					for (int j2 = j; j2 < temp.getColCount(); j2++) {
						temp[i2][j2] = temp[i2][j2] - temp[i][j2] * mnog;
					}

				}
				if (!progon_end)i--;
				else break;
			}
			TMatrix returned(temp.getRowCount(), temp.getRowCount());
			//обрезаем нужные значения

			for (int i = 0; i < temp.getRowCount(); i++)
				for (int j = temp.getColCount() / 2; j < temp.getColCount(); j++) {
					returned[i][ (j - temp.getRowCount())] = temp[i][j];
				}
			return TMatrix(returned);
}


// Реализация TSymetricMatrix

void  TSymmetricMatrix::setElement(int i, int j, double d) {
	matrix[i][j] = d;
	matrix[j][i] = d;
}

TMatrix TSymmetricMatrix::inverse() {
	//метод Xолецкого

	TMatrix L(matrix.size(), matrix[0].getSize());
	int i = 0;
	for (int j = 0; j < matrix[0].getSize(); j++) {
		if (matrix[i][j]) {}
		else {
			for (int i1 = i + 1; i1 < matrix.size(); i1++)
				if (i1 != matrix.size()) {
					if (matrix[i1][j]) {
						for (int m = 0; m < matrix[0].getSize(); m++) {
							//temp(i, m) = temp(i, m) + temp(i1, m);
							double tmp = matrix[i][m];
							matrix[i][m] = matrix[i1][m];
							matrix[i1][m] = tmp;
						}
						break;
					}
					else i1++;
				}
				else {
					for (int m = 0; m < matrix[0].getSize(); m++) {
						//temp(i, m) = temp(i, m) + temp(i1 - 1, m);
						double tmp = matrix[i][m];
						matrix[i][m] = matrix[i1 - 1][m];
						matrix[i1 - 1][m] = tmp;
					}
				}

		}

	}

	//заполнение первого столбца и строки
	for (int j = 0; j < L.getColCount(); j++)
		L[0][j] = matrix[0][j];
	for (int i = 1; i < L.getRowCount(); i++)
		L[i][0] = matrix[i][0] / L[0][0];



	//заполнение u и l элементами

	for (int i = 1; i < L.getRowCount(); i++) {
		for (int j = i; j < L.getRowCount(); j++) {
			double sum = 0;
			for (int k = 0; k < i; k++)
				sum += L[i][k] *L[k][j];
			L[i][j] = matrix[i][j] - sum;
			sum = 0;
		}
		if (!L[i][i]) throw OtherException();
		for (int ii = i + 1; ii < L.getRowCount(); ii++) {
			double sum = 0;
			for (int k = 0; k < i; k++)
				sum += L[ii][k] *L[k][i];
			L[ii][i] = (matrix[ii][i] - sum) / L[i][i];
		}
	}


	//show(L);
	TMatrix returned(matrix.size(), matrix[0].getSize());
	//вычисление обратной матрицы

	for (int i = returned.getRowCount() - 1; i >= 0; i--)
		for (int j = returned.getColCount() - 1; j >= 0; j--) {
			double sum = 0;
			if (i == j) {
				for (int p = j + 1; p < returned.getColCount(); p++)
					sum += L[j][p] *returned[p][j];
				returned[j][j] = (1 - sum) / L[j][j];
				sum = 0;
				//show(returned);
			}
			else if (i < j) {
				for (int p = i + 1; p < returned.getRowCount(); p++)
					sum += L[i][p] *returned[p][j];
				returned[i][j] = -sum / L[i][i];
				sum = 0;
				//show(returned);
			}
			else {
				for (int p = j + 1; p < returned.getColCount(); p++)
					sum += returned[i][p] *L[p][j];
				returned[i][j] = -sum;
				sum = 0;
				//show(returned);
			}

		}
	//show(returned);

	return returned;
}

TSymmetricMatrix::TSymmetricMatrix() {
	matrix = vector<TVector>(0);
}

TSymmetricMatrix::TSymmetricMatrix(int _i, int _j) {
	int lim_ind = min(_i, _j);
		
	matrix = vector<TVector>(lim_ind);
	for (int i = 0; i < matrix.size(); i++) {
		matrix[i] = TVector(lim_ind);
	}
}

TSymmetricMatrix::TSymmetricMatrix(const TMatrix& B) {
	int min_size = min(B.getColCount(), B.getRowCount());

	
	matrix = vector<TVector>(min_size);
	for (int i = 0; i < matrix.size(); i++) {
		matrix[i] = TVector(min_size);
	}
	int k = 0;
	for (int i = 0; i < matrix.size(); i++) {
		for (int j = k; j < matrix[0].getSize(); j++) {
			matrix[i][j] = B[i][j];
			matrix[j][i] = B[i][j];
		}
		k++;
	}
}

TMatrix::TMatrix(const TSymmetricMatrix& B) {

	matrix = vector<TVector>(B.matrix);
}



TSymmetricMatrix& TSymmetricMatrix::operator =(const TMatrix& B) throw(IncorrectIndexException) {
	

	int lim_ind = min(B.getColCount(), B.getRowCount());

	matrix = vector<TVector>(lim_ind);

	for (int i = 0; i < matrix.size(); i++) {
		matrix[i] = TVector(lim_ind);
	}
	int k = 0;
	for (int i = 0; i < matrix.size(); i++) {
		for (int j = k; j < matrix[0].getSize(); j++) {
			matrix[i][j] = B[i][j];
			matrix[j][i] = B[i][j];
		}
		k++;
	}
	return *this;
}


