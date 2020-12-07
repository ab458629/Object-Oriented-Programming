/*
useHW03_01.cpp
��өҺӤ@ P46091204 ���ӿo  Copyright (C) 2020
*/

#include "HW03_01.h"
#include <iostream>
#include <ctime>

using std::cout;
using std::endl;

int main() {
	srand(time(0));

	IGeometry** arr = new IGeometry*[3];	cout << "(1) ���ձ����: " << endl;	arr[0] = new Trapezoid();
	cout << endl;
	cout << "���n��: " << arr[0]->Area() << endl;
	cout << "�P����: " << arr[0]->Perimeter() << endl;
	cout << "��n��: " << arr[0]->Volume() << endl;
	cout << endl;

	cout << "(2) ���ե��T���W: " << endl;
	arr[1] = new Prism();
	cout << endl;
	cout << "���n��: " << arr[1]->Area() << endl;
	cout << "�P����: " << arr[1]->Perimeter() << endl;
	cout << "��n��: " << arr[1]->Volume() << endl;
	cout << endl;

	cout << "(3) ���ն��@: " << endl;
	arr[2] = new Cone();
	cout << endl;
	cout << "���n��: " << arr[2]->Area() << endl;
	cout << "�P����: " << arr[2]->Perimeter() << endl;
	cout << "��n��: " << arr[2]->Volume() << endl;
	cout << endl;

	for (int i = 0; i < 3; i++) {
		delete arr[i];
	}
	delete[] arr;

	system("pause");
	return 0;
}