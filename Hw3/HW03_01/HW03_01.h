#ifndef HW03_01_H
#define HW03_01_H
#include <iostream>

/*
	改寫第二次作業的點類別，並用向量的觀念進行改版
	因為C++沒有Interface這個字眼，故用ABC的觀念來實現
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
	// The following function are pure virtual function because they all have "=0". 中文可以說是"引言"
	virtual double Area() = 0;			// 表面積
	virtual double Perimeter() = 0;		// 周長
	virtual double Volume() = 0;		// 體積
};

class Trapezoid : public IGeometry {	// 梯形體 (根據題目所說，三組邊長，表示梯形體上下為正方形)
private :
	Point* vertices;	// 8個頂點私有成員
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
	double r;	// 上下兩個三角形的邊長長度
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

