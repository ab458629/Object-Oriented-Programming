#include <iostream>
#include <cstdlib>
#include <ctime>
#include "matrix.h"

namespace MATRIX {
	const double MAX = 10;
	const double MIN = 0;

	using namespace std;

	Matrix::Matrix() {
		cout << "預設建構子: " << endl;
		n = 2;		
		arr = new double *[n];

		for (int i = 0; i < n; i++) {
			arr[i] = new double[n];
		}

		for (int i = 0; i < n; i++) {
			for (int j = 0; j < n; j++) {
				arr[i][j] = (MAX - MIN)*rand() / (RAND_MAX + 1) + MIN; // 產生[0, 10]的浮點數
				cout << arr[i][j] << " ";
			}
			cout << endl;
		}
	}

	Matrix::Matrix(unsigned int _n) {
		cout << "指定維度建構子" << endl;
		n = _n;
		arr = new double *[n];

		for (int i = 0; i < n; i++) {
			arr[i] = new double[n];
		}

		for (int i = 0; i < n; i++) {
			for (int j = 0; j < n; j++) {
				arr[i][j] = (MAX - MIN)*rand() / (RAND_MAX + 1) + MIN; // 產生[0, 10]的浮點數
				cout << arr[i][j] << " ";
			}
			cout << endl;
		}
	}

	Matrix::Matrix(double ** _arr, unsigned int _n) :arr(_arr), n(_n) {
		cout << "指定二維動態陣列與維度建構子: " << endl;
		for (int i = 0; i < n; i++) {
			for (int j = 0; j < n; j++) {
				cout << arr[i][j] << " ";
			}
			cout << endl;
		}
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
		cout << "呼叫解構子! " << endl;
		for (int i = 0; i < n; i++) {
			delete[] arr[i];
		}
		delete[] arr;
		arr = nullptr;
	}

	Matrix & Matrix::operator=(const Matrix & b) {
		cout << "指定運算子: " << endl;
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
				cout << arr[i][j];
			}
			cout << endl;
		}
		return *this;
	}

	double ** Matrix::operator +(const Matrix & b) const {
		double ** a = new double *[n];
		for (int i = 0; i < n; i++) {
			a[i] = new double[n];
		}
		for (int i = 0; i < n; i++){
			for (int j = 0; j < n; j++){
				a[i][j] = arr[i][j] + b.arr[i][j];
			}
		}
		return a;
	}

	double ** Matrix::operator -(const Matrix & b) const {
		double ** a = new double *[n];
		for (int i = 0; i < n; i++) {
			a[i] = new double[n];
		}
		for (int i = 0; i < n; i++) {
			for (int j = 0; j < n; j++) {
				a[i][j] = arr[i][j] - b.arr[i][j];
			}
		}
		return a;
	}

	double ** Matrix::operator *(const Matrix & b) const {
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
		return a;
	}
	
	ostream & operator << (ostream& os, const Matrix& A) {
		os << A.arr;
		return os;
	}

}