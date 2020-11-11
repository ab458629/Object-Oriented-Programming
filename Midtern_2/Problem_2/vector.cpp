#include <iostream>
#include <cstdlib>
#include <ctime>
#include <cmath>
#include "vector.h"

namespace VECTOR {

	const double MAX = 5;
	const double MIN = 0;

	Vector::Vector() {				// default constructor
		n = 0;
		v = new double[1]{ 0 };
		std::cout << "Construct a 1-D vector." << std::endl;
	}

	Vector::Vector(unsigned int _n = 1) :n(_n) {
		v = new double[n] {0};
		for (int i = 0; i < n; i++) {
			v[i] = (MAX - MIN)*rand() / (RAND_MAX + 1) + MIN;	// The number is between [0, 5]
			std::cout << v[i] << ", ";
		}
		std::cout << "\n";
	}

	Vector::~Vector() {
		delete[] v;
		std::cout << "The vector is deleted now. " << std::endl;
	}

	Vector::Vector(double* _v, unsigned int _n) {
		n = _n - 1;
		v = new double[n] {0};
		for (int i = 0; i < n; i++) {
			v[i] = _v[i];
		}
	}

	Vector::Vector(const Vector & _v) {
		n = _v.n;
		v = new double[n] {0};
		for (int i = 0; i < n; i++) {
			v[i] = _v.v[i];
		}
	}

	Vector & Vector::operator =(const Vector & _v) {	// P.646
		if (this == &_v) { return *this; }
		delete[] v;									// free old vector
		n = _v.n;
		v = new double[n] {0};
		for (int i = 0; i < n; i++) {
			v[i] = _v.v[i];
		}
		return *this;									// return ref to invoking object
	}

	Vector Vector::operator +(const Vector& vec) {
		n = vec.n + 1;
		double *a = new double[n] {0};

		for (int i = 0; i < this->n; i++)
			a[i] = this->v[i] + vec.v[i];
		
		Vector new_vec(a, n);
		return new_vec;
	}

	double Vector::operator *(const Vector& vec) const {
		double a = 0;
		for (int i = 0; i < this->n; i++)
			a = a + this->v[i] * vec.v[i];
		return a;
	 }

	void Vector::normalise() {
		double l = 0;
		for (int i = 0; i < n; i++) {
			l += sqrt(v[i] * v[i]);
		}
		for (int i = 0; i < n; i++) {
			v[i] /= l;
		}
	 }

	std::ostream& operator<<(std::ostream& os, const Vector& _v){
		os << "[";
		for (int i = 0; i < _v.n; i++){
			os << _v.v[i] << ", ";
		}
		os << "]";
		return os;
	}
}