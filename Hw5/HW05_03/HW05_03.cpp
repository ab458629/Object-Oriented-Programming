#include <iostream>

#include "HW05_03.h"

Point::Point(const Point & p) {
	x = p.x;
	y = p.y;
	z = p.z;
}

Point & Point::operator=(const Point & p) {
	if (this == &p)
		return *this;
	x = p.x;
	y = p.y;
	z = p.z;
	return *this;
}

float Point::operator[](int i) const {
	float data[3];
	data[0] = x;			// �ϱooperator[0] �N��private��x��
	data[1] = y;			// �ϱooperator[1] �N��private��y��
	data[2] = z;			// �ϱooperator[2] �N��private��z��
	return data[i];
}

bool Point::operator<(Point & p) const{
	if ((x*x + y*y + z*z) < (p.x*p.x + p.y*p.y + p.z*p.z))
		return true;
	else
		return false;
}

bool Point::operator>(Point & p) const {
	if ((x*x + y*y + z*z) > (p.x*p.x + p.y*p.y + p.z*p.z))
		return true;
	else
		return false;
}

bool Point::operator==(Point & p) const {
	return (x == p.x) && (y == p.y) && (z == p.z);
}

bool Point::operator<=(Point & p) const {
	if ((x*x + y*y + z*z) <= (p.x*p.x + p.y*p.y + p.z*p.z))
		return true;
	else
		return false;
}


bool Point::operator>=(Point & p) const {
	if ((x*x + y*y + z*z) >= (p.x*p.x + p.y*p.y + p.z*p.z))
		return true;
	else
		return false;
}

Point::~Point() {			// �Ѻc
}

std::istream & operator >> (std::istream &s, Point &p) {			// >> �����B��l
	s >> p.x >> p.y >> p.z;
	return s;
}

std::ostream & operator << (std::ostream &s, const Point &p) {		// << �����B��l
	s << "(" << p.x << " , " << p.y << " , "<< p.z << ")";
	return s;
}