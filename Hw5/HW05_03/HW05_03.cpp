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
	data[0] = x;			// 使得operator[0] 代表private的x值
	data[1] = y;			// 使得operator[1] 代表private的y值
	data[2] = z;			// 使得operator[2] 代表private的z值
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

Point::~Point() {			// 解構
}

std::istream & operator >> (std::istream &s, Point &p) {			// >> 重載運算子
	s >> p.x >> p.y >> p.z;
	return s;
}

std::ostream & operator << (std::ostream &s, const Point &p) {		// << 重載運算子
	s << "(" << p.x << " , " << p.y << " , "<< p.z << ")";
	return s;
}