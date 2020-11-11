/*
   HW01_01.cpp
   航太所碩一 P46091204 蔡承穎  Copyright (C) 2020
												   */
#include <iostream>
#include <ctime>
#include "HW01_02.h"

using namespace std;
// using namespace MyGeometry; 盡量不使用using這個指令，未來會減少使用 using namespace std
// 盡量不擴大 using namespace xxx 所影響的區域，但目前的了解是不寫在header檔(.h)
int main() {
	double START, END;
	START = clock();
	MyGeometry::Report("Point_HW1.txt");
	END = clock();
	cout << "執行程式所花時間: " <<(END - START) / CLOCKS_PER_SEC << "s" << endl;
	system("pause");
	return 0;
}