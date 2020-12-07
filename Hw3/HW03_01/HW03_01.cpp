#include "HW03_01.h"
#include <stdlib.h>
#include <cmath>

// Class Point
Point::Point() {
	// 隨機產生[-10, 10)數字
	x = (10 - (-10)) * rand() / (RAND_MAX + 1.0) - 10;
	y = (10 - (-10)) * rand() / (RAND_MAX + 1.0) - 10;
	z = (10 - (-10)) * rand() / (RAND_MAX + 1.0) - 10;
}

Point::Point(double _x, double _y, double _z) :x(_x), y(_y), z(_z) {}

Point::~Point() {}

Point::Point(const  Point& a) {
	x = a.x;
	y = a.y;
	z = a.z;
}

Point& Point::operator=(const Point &a) {
	if (this == &a) return *this;
	x = a.x;
	y = a.y;
	z = a.z;
	return *this;
}

Point Point::operator+(const  Point& a) {
	Point temp;
	temp.x = x + a.x;
	temp.y = y + a.y;
	temp.z = z + a.z;
	return temp;
}

Point Point::operator-(const  Point& a) {
	Point temp;
	temp.x = x - a.x;
	temp.y = y - a.y;
	temp.z = z - a.z;
	return temp;
}

double Point::operator*(const Point& a) {
	return (x*a.x + y*a.y + z*a.z);
}

Point Point::operator*(double a) {
	Point temp;
	temp.x = a * x;
	temp.y = a * y;
	temp.z = a * z;
	return temp;
}

Point Point::operator^(const Point& a) {
	Point temp;
	temp.x = y*a.z - z*a.y;
	temp.y = z*a.x - x*a.z;
	temp.z = x*a.y - y*a.x;
	return temp;
}

Point Point::operator/(double a) {
	Point temp;
	temp.x = x / a;
	temp.y = y / a;
	temp.z = z / a;
	return temp;
}

double Point::len() {
	return sqrt(x*x + y*y + z*z);
}

Point Point::normalise() {
	Point temp;
	temp.x = x / len();
	temp.y = y / len();
	temp.z = z / len();
	return temp;
}

std::ostream& operator<<(std::ostream& os, const Point& a) {
	os << "(" << a.x << ", " << a.y << ", " << a.z << ")";
	return os;
}

/* 
Class Trapezoid
這裡我假設成正金字塔，
上方為一個小正方形，
下方為一個大正方形，
下方正方形的長度為上方的兩倍，
編號順序為逆時針，由上而下。
		0	3
		1	2
	4			7
	5			6
*/
Trapezoid::Trapezoid() {
	vertices = new Point[8];
	double scale = (10 - (1)) * rand() / (RAND_MAX + 1.0) + 1;
	Point a(scale * 1, 0, 0);
	Point b(0, scale * 1, 0);
	vertices[1] = vertices[0] + a;
	vertices[3] = vertices[0] + b;
	vertices[2] = vertices[3] + a;
	double height = (10 - (1)) * rand() / (RAND_MAX + 1.0) + 1;
	// std::cout << "產生的梯形高為 : " << height << std::endl;	// 此高為Ground truth，因為接下來會假設不知道，用投影的方式求解
	vertices[4] = vertices[0] - Point(0, 0, height) - Point(scale * 1 / 2, 0, 0) - Point(0, scale * 1 / 2, 0);
	vertices[5] = vertices[4] + a * 2;
	vertices[7] = vertices[4] + b * 2;
	vertices[6] = vertices[7] + a * 2;
	std::cout << "梯形體的八個點為: " << std::endl;
	for (int i = 0; i < 8; i++) {
		std::cout << vertices[i] << std::endl;
	}
}

Trapezoid::~Trapezoid() {
	delete[] vertices;
}

Trapezoid::Trapezoid(const Trapezoid& a) {
	delete[] vertices;
	Point* vertices = new Point[8];
	for (int i = 0; i < 4; i++) {
		vertices[i] = a.vertices[i];
	}
}

Trapezoid& Trapezoid::operator=(const Trapezoid& a) {
	if (this == &a) return *this;
	delete[] vertices;
	Point* vertices = new Point[8];
	for (int i = 0; i < 8; i++) {
		vertices[i] = a.vertices[i];
	}
	return *this;
}

double Trapezoid::Area() {
	return (SideArea()[0] + 4 * SideArea()[1] + SideArea()[2]);	// 上下若非正方形，這裡要改掉
}

double Trapezoid::Perimeter() {
	return (SideLength()[0] + SideLength()[1] + SideLength()[2]) * 4;
}

double Trapezoid::Volume() {
	double H = abs((vertices[1] - vertices[5]) * ((vertices[4] - vertices[5]) ^ (vertices[6] - vertices[5])).normalise());	// 這裡假設亂數產生的高不知道，並用外積加投影的觀念求出高
	double V = ((vertices[1] - vertices[0]).len() * (vertices[2] - vertices[1]).len()
		+ (vertices[5] - vertices[4]).len() * (vertices[6] - vertices[5]).len()
		+ ((vertices[1] - vertices[0]).len() + (vertices[5] - vertices[4]).len()) * ((vertices[2] - vertices[1]).len() + (vertices[6] - vertices[5]).len())) * H / 6;
	return V;
}

double* Trapezoid::SideLength() {
	double L[3];
	L[0] = (vertices[1] - vertices[0]).len();
	L[1] = (vertices[1] - vertices[5]).len();
	L[2] = (vertices[6] - vertices[5]).len();
	return L;
}

double* Trapezoid::SideArea() {
	double A[3];
	A[0] = (vertices[1] - vertices[0]).len() * (vertices[1] - vertices[0]).len();
	Point proj_point = (((vertices[6] - vertices[5])
		* ((vertices[6] - vertices[5]).normalise() * (vertices[1] - vertices[5]))) + vertices[5]);
	double H = (vertices[1] - proj_point).len();	// 這裡利用投影的概念求出側面梯形的高
	A[1] = ((vertices[1] - vertices[2]).len() + (vertices[5] - vertices[6]).len()) * H / 2;
	A[2] = (vertices[6] - vertices[5]).len() * (vertices[6] - vertices[5]).len();
	return A;
}

std::ostream& operator<<(std::ostream& os, const Trapezoid& a) {
	for (int i = 0; i < 8; i++) {
		os << a.vertices[i] << std::endl;
	}
	return os;
}

/*
Prism
*/

Prism::Prism() : r((10 - (1)) * rand() / (RAND_MAX + 1.0) + 1) {
	std::cout << "上面的中心點: " << Top << "\n"
		<< "下面的中心點: " << Bottom << "\n"
		<< "正三角形的邊長: " << r << std::endl;
}

Prism::~Prism() {
}

Prism::Prism(const Prism& a) {
	Top = a.Top;
	Bottom = a.Bottom;
	r = a.r;
}

Prism& Prism::operator=(const Prism& a) {
	if (this == &a) return *this;
	Top = a.Top;
	Bottom = a.Bottom;
	r = a.r;
	return *this;
}

double Prism::Area() {
	return (BottomArea() * 2 + SideArea());
}

double Prism::Perimeter() {
	return (Height() * 3 + r * 6);
}

double Prism::Volume() {
	return (BottomArea() * Height());
}

double Prism::Height() {
	return	((Top - Bottom).len());
}

double Prism::BottomArea() {
	return (0.25 * r * r * sqrt(3));
}

double Prism::SideArea() {
	return (r * Height());
}

std::ostream& operator<<(std::ostream& os, const Prism& a) {
	os << "上面的中心點: " << a.Top << "\n"
		<< "下面的中心點: " << a.Bottom << "\n"
		<< "正三角形的邊長: " << a.r;
	return os;
}

/*
Class Cone
*/
#define PI 3.1415962

Cone::Cone() : r((10 - (1)) * rand() / (RAND_MAX + 1.0) + 1) {
	std::cout << "上面的頂點: " << Top << "\n"
		<< "圓形中心點: " << Center << "\n"
		<< "圓形半徑: " << r << std::endl;
}

Cone::~Cone() {}

Cone::Cone(const Cone& a) {
	Top = a.Top;
	Center = a.Center;
}

Cone& Cone::operator=(const Cone& a) {
	if (this == &a) return *this;
	Top = a.Top;
	Center = a.Center;
	return *this;
}

double Cone::Area(){
	double l = sqrt(Height() * Height() + r * r);
	return (PI * r * r + PI * l * l * Angle());
}

double Cone::Perimeter() {
	double l = sqrt(Height() * Height() + r * r);
	return (2 * l + 2 * PI * r);
}

double Cone::Volume() {
	return (PI * r * r * Height());
}

double Cone::Height() {
	return ((Top - Center).len());
}

double Cone::Angle() {
	double l = sqrt(Height() * Height() + r * r);
	return (r / l);		// 若要degree，乘上360
}

std::ostream& operator<<(std::ostream& os, const Cone& a) {
	os << "上面的頂點: " << a.Top << "\n"
		<< "圓形中心點: " << a.Center << "\n"
		<< "圓形半徑: " << a.r;
	return os;
}