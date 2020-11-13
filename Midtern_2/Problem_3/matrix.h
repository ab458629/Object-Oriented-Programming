#ifndef MATRIX_H
#define MATRIX_H

#include <iostream>

namespace MATRIX {
	using namespace std;

	class Matrix {
	private:
		double ** arr;
		unsigned int n;

	public:
		Matrix();
		Matrix(unsigned int);
		Matrix(double **, unsigned int);
		Matrix(const Matrix &);
		~Matrix();
		Matrix & operator =(const Matrix &);
		Matrix operator +(const Matrix &)const;
		Matrix operator -(const Matrix &)const;
		Matrix operator *(const Matrix &)const;
		friend ostream & operator << (ostream&, const Matrix&);
	};
}
#endif // !MATRIX_H
