/*
   HW01_01.cpp
   ��өҺӤ@ P46091204 ���ӿo  Copyright (C) 2020
												   */
#include <iostream>
#include <ctime>
#include "HW01_02.h"

using namespace std;
// using namespace MyGeometry; �ɶq���ϥ�using�o�ӫ��O�A���ӷ|��֨ϥ� using namespace std
// �ɶq���X�j using namespace xxx �Ҽv�T���ϰ�A���ثe���F�ѬO���g�bheader��(.h)
int main() {
	double START, END;
	START = clock();
	MyGeometry::Report("Point_HW1.txt");
	END = clock();
	cout << "����{���Ҫ�ɶ�: " <<(END - START) / CLOCKS_PER_SEC << "s" << endl;
	system("pause");
	return 0;
}