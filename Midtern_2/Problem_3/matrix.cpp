#include <iostream>
#include <cstdlib>
#include <ctime>
#include "matrix.h"

namespace MATRIX {
	const double MAX = 10;
	const double MIN = 0;

	using namespace std;

	Matrix::Matrix() {
		// cout << "�w�]�غc�l: " << endl;
		n = 0;		
		arr = nullptr;
	}

	Matrix::Matrix(unsigned int _n) {
		//	cout << "���w���׫غc�l�A�üƲ��ͯx�}����" << endl;
		n = _n;
		arr = new double *[n];

		for (int i = 0; i < n; i++) {
			arr[i] = new double[n];
		}

		for (int i = 0; i < n; i++) {
			for (int j = 0; j < n; j++) {
				arr[i][j] = (MAX - MIN)*rand() / (RAND_MAX + 1) + MIN; // ����[0, 10]���B�I��
				cout << arr[i][j] << " ";
			}
			cout << endl;
		}
	}

	Matrix::Matrix(double ** _arr, unsigned int _n) :arr(_arr), n(_n) {
		// cout << "���w�G���ʺA�}�C�P���׫غc�l: " << endl;
		/*
		for (int i = 0; i < n; i++) {
			for (int j = 0; j < n; j++) {
				cout << arr[i][j] << " ";
			}
			cout << endl;
		}
		*/
	}

	Matrix::Matrix(const Matrix & _arr) {
		n = _arr.n;
		arr = new double *[n];
		for (int i = 0; i < n; i++)
			arr[i] = new double[n];

		n = _arr.n;
		for (int i = 0; i < n; i++) {
			for (int j = 0; j < n; j++) {
				arr[i][j] = _arr.arr[i][j];
			}
		}
	}

	Matrix::~Matrix() {
		// cout << "�I�s�Ѻc�l! " << endl;
		for (int i = 0; i < n; i++) {
			delete[] arr[i];
		}
		delete[] arr;
		arr = nullptr;
	}

	Matrix & Matrix::operator=(const Matrix & b) {
		// cout << "���w�B��l: " << endl;
		if (this == &b)
			return *this;
		for (int i = 0; i < n; i++) {
			delete[] arr[i];
		}
		delete[] arr;

		n = b.n;
		arr = new double *[n];
		for (int i = 0; i < n; i++)
			arr[i] = new double[n];

		for (int i = 0; i < n; i++) {
			for (int j = 0; j < n; j++) {
				arr[i][j]  = b.arr[i][j];
				// cout << arr[i][j];
			}
			// cout << endl;
		}
		return *this;
	}

	Matrix Matrix::operator +(const Matrix & b) const {
		double ** a = new double *[n];
		for (int i = 0; i < n; i++) {
			a[i] = new double[n];
		}
		for (int i = 0; i < n; i++){
			for (int j = 0; j < n; j++){
				a[i][j] = arr[i][j] + b.arr[i][j];
			}
		}
		Matrix Matrix_C(a, n);
		return Matrix_C;
	}

	Matrix Matrix::operator -(const Matrix & b) const {
		double ** a = new double *[n];
		for (int i = 0; i < n; i++) {
			a[i] = new double[n];
		}
		for (int i = 0; i < n; i++) {
			for (int j = 0; j < n; j++) {
				a[i][j] = arr[i][j] - b.arr[i][j];
			}
		}
		Matrix Matrix_C(a, n);
		return Matrix_C;
	}

	Matrix Matrix::operator *(const Matrix & b) const {
		double ** a = new double *[n];
		for (int i = 0; i < n; i++) {
			a[i] = new double[n];
		}
		for (int i = 0; i < n; i++) {
			for (int j = 0; j < n; j++) {
				a[i][j] = 0;
				for (int k = 0; k < n; k++) {
					a[i][j] = arr[i][k] * b.arr[k][j];
				}
			}
		}
		Matrix Matrix_C(a, n);
		return Matrix_C;
	}
	
	ostream & operator << (ostream& os, const Matrix& A) {
		for (int i = 0; i < A.n; i++) {
			for (int j = 0; j < A.n; j++) {
				os << A.arr[i][j] << ", ";
			}
			cout << endl;
		}
		return os;
	}

}