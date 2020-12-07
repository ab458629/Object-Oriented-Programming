/*
useHW03_01.cpp
航太所碩一 P46091204 蔡承穎  Copyright (C) 2020
*/

#include "HW03_01.h"
#include <iostream>
#include <ctime>

using std::cout;
using std::endl;

int main() {
	srand(time(0));

	IGeometry** arr = new IGeometry*[3];	cout << "(1) 測試梯形體: " << endl;	arr[0] = new Trapezoid();
	cout << endl;
	cout << "表面積為: " << arr[0]->Area() << endl;
	cout << "周長為: " << arr[0]->Perimeter() << endl;
	cout << "體積為: " << arr[0]->Volume() << endl;
	cout << endl;

	cout << "(2) 測試正三角柱: " << endl;
	arr[1] = new Prism();
	cout << endl;
	cout << "表面積為: " << arr[1]->Area() << endl;
	cout << "周長為: " << arr[1]->Perimeter() << endl;
	cout << "體積為: " << arr[1]->Volume() << endl;
	cout << endl;

	cout << "(3) 測試圓錐: " << endl;
	arr[2] = new Cone();
	cout << endl;
	cout << "表面積為: " << arr[2]->Area() << endl;
	cout << "周長為: " << arr[2]->Perimeter() << endl;
	cout << "體積為: " << arr[2]->Volume() << endl;
	cout << endl;

	for (int i = 0; i < 3; i++) {
		delete arr[i];
	}
	delete[] arr;

	system("pause");
	return 0;
}