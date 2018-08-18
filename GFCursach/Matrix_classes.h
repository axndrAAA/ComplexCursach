#pragma once
#include <string>
#include<iostream>
#include<vector>
using namespace std;

//�����������
class TMatrix;
class TQuaternion;
class TVector {
private:
	vector<double> vect;

public:	class IncorrectIndexException {};
		class IncorrectSizeException {};

public:	 TVector(int);
		 TVector();
		  ~TVector();
		 TVector(const TVector&);
		 TVector(const double* arr, int size);
		 TVector& operator =(const TVector&);
		 TVector operator +(const TVector&)const throw(IncorrectIndexException);
		 //��������� ������������
		 TVector crossProduct(const TVector) const throw(IncorrectSizeException);// ���� ������
		 double& operator [](int) throw(IncorrectIndexException);
		 double operator [] (int) const throw(IncorrectIndexException);
		 int getSize() const;
		 //������ �������
		 double getMagnitude() const;//�����
		 TVector operator *(const double&) const;
		 TVector operator /(const double&) const;
		 //��������� ������������
		 double operator *(const TVector&)const throw(IncorrectIndexException);//?
		 TVector operator*(const TMatrix& B) throw(IncorrectIndexException);
		 void setElement(int, double) throw(IncorrectIndexException);
		 void setLenght(int) throw(IncorrectIndexException);
		 int getMinSize(TVector, TVector)const;
		 std::vector<double> getStdVector();
		 TVector sub(int beg, int end);

		 void print() {
			 for (int i = 0; i < getSize(); i++)
				 std::cout << vect[i] << " ";
			 std::cout << std::endl;
		 }



		 //TQuaternion
		 TQuaternion operator*(const TQuaternion&);
		 //������ ��������
		 TVector RotateByRodrigFormula(TVector, double)const;
		 //�������� �� �����
		 TVector RotateByQuaternion(const TQuaternion&);
};

//����������o
class TSymmetricMatrix;
class TMatrix {
protected:
	//int size_i;
	//int size_j;
	//TVector *matrix;

	//������ ����� i ������ �������� j
	vector<TVector> matrix;
public:	class IncorrectIndexException {};
		class IncorrectSizeException {};
		class OtherException {};
public:
	TMatrix();
	TMatrix(int, int);
	 ~TMatrix();
	TMatrix(const TMatrix&);
	TMatrix(const TSymmetricMatrix&);
	TMatrix& operator =(const TMatrix&) throw(IncorrectIndexException);
	TMatrix operator +(const TMatrix&) throw(IncorrectIndexException);
	bool checkSymmetric() const;
	//����������������
	TMatrix flip();
	int getColCount() const;
	int getRowCount() const;
	TVector& operator [](int);
	TVector operator [](int)const;
	//���������
	TMatrix inverse();
	TMatrix operator *(double);
	TMatrix operator *(const TMatrix&)  throw(IncorrectIndexException);
	TVector operator *(const TVector&)  throw(IncorrectIndexException);
	void SetElement(int, int, double)  throw(IncorrectIndexException);
	void setSize(int, int)  throw(IncorrectIndexException);

};
//�����������
class TSymmetricMatrix : public TMatrix {


public:
	TSymmetricMatrix();
	TSymmetricMatrix(int, int);
	TSymmetricMatrix(const TMatrix&);


	TSymmetricMatrix& operator =(const TMatrix& B) throw(IncorrectIndexException);


public:
	TMatrix inverse();
	void setElement(int, int, double)  throw(IncorrectIndexException);

};

int min(int a, int b);
void show(TMatrix _m);

void show(TVector _m);
