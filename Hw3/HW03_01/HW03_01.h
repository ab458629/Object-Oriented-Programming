#ifndef HW03_01_H
#define HW03_01_H
#include <iostream>

/*
	��g�ĤG���@�~���I���O�A�åΦV�q���[���i��睊
	�]��C++�S��Interface�o�Ӧr���A�G��ABC���[���ӹ�{
*/

class Point {
private:
	double x, y, z;
public:
	Point();
	Point(double _x, double _y, double _z);
	~Point();
	Point(const Point& a);
	Point& operator=(const Point& a);
	Point operator+(const Point& a);
	Point operator-(const Point& a);
	double operator*(const Point& a);
	Point operator*(double a);
	Point operator^(const Point& a);
	Point operator/(double a);
	double len();
	Point normalise();
	// double getx() { return x; }
	// double gety() { return y; }
	// double getz() { return z; }
	friend std::ostream& operator<<(std::ostream& os, const Point& a);
};

// Abstract Base Class
class IGeometry {			// I represents Interface
public:
	// The following function are pure virtual function because they all have "=0". ����i�H���O"�ި�"
	virtual double Area() = 0;			// ���n
	virtual double Perimeter() = 0;		// �P��
	virtual double Volume() = 0;		// ��n
};

class Trapezoid : public IGeometry {	// ����� (�ھ��D�ةһ��A�T������A��ܱ����W�U�������)
private :
	Point* vertices;	// 8�ӳ��I�p������
public :
	Trapezoid();
	~Trapezoid();
	Trapezoid(const Trapezoid& a);
	Trapezoid& operator=(const Trapezoid& a);
	double Area();
	double Perimeter();
	double Volume();
	double* SideLength();
	double* SideArea();
	friend std::ostream& operator<<(std::ostream& os, const Trapezoid& a);
};

class Prism :public IGeometry {
private:
	Point Top;
	Point Bottom;
	double r;	// �W�U��ӤT���Ϊ��������
public:
	Prism();
	~Prism();
	Prism(const Prism& a);
	Prism& operator=(const Prism& a);
	double Area();
	double Perimeter();
	double Volume();
	double Height();
	double BottomArea();
	double SideArea();
	friend std::ostream& operator<<(std::ostream& os, const Prism& a);
};

class Cone : public IGeometry {
private:
	Point Top;
	Point Center;
	double r;
public:
	Cone();
	~Cone();
	Cone(const Cone& a);
	Cone& operator=(const Cone& a);
	double Area();
	double Perimeter();
	double Volume();
	double Height();
	double Angle();
	friend std::ostream& operator<<(std::ostream& os, const Cone& a);
};

#endif // !HW03_01_H

