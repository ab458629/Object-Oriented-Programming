#include <iostream>
#include <cstdlib>
#include <ctime>
#include "vector.h"

namespace VECTOR {

	const double MAX = 5;
	const double MIN = 0;

	Vector::Vector() {				// default constructor
		n = 0;
		v = new double[1]{0};
		std::cout << "Construct a 1-D vector." << std::endl;
	}

	Vector::Vector(unsigned int _n = 1) :n(_n) {		
		v = new double[n] {0};
		for (int i = 0; i < n; i++) {
			v[i] = (MAX - MIN)*rand() / (RAND_MAX + 1) + MIN;	// The number between [0, 5]
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
			std::cout << v[i] << ", ";
		}
		std::cout << "\n";
	}

	Vector::Vector(const Vector & _v) {
		std::cout << "Call Copy Constructor..." << std::endl;
		n = _v.n;
		v = new double[n] {0};
		for (int i = 0; i < n; i++) {
			v[i] = _v.v[i];
			std::cout << v[i] << ", ";
		}
		std::cout << "\n";
	}

	Vector & Vector::operator = (const Vector & _v) {	// P.646
		if (this == &_v) { return *this; }
		delete[] v;									// free old vector
		n = _v.n;
		v = new double[n] {0};
		for (int i = 0; i < n; i++) {
			v[i] = _v.v[i];
			std::cout << v[i] << ", ";
		}
		std::cout << "\n";
		return *this;									// return ref to invoking object
	}
}