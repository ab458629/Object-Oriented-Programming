/*
   HW01_01.cpp
   航太所碩一 P46091204 蔡承穎  Copyright (C) 2020
												   */
#include <iostream>
#include <string>
#include <fstream>
#include <cmath>
#include <sstream> // 使用StringStream
#include <cstdlib>
#include "HW01_02.h"

using namespace std;

namespace MyGeometry {

	double Point::Length() { // 計算兩點的長
		double length;
		length = sqrt(x * x + y * y);
		return length;
	}

	string Point::CoutPoint() {
		string s1;
		stringstream s2; // 這是為了將float轉成string字串
		s2 << "(" << x << "," << y << ")";
		s2 >> s1;
		if (!s2) cout << "error type !" << endl; // 確定是否有轉換成功
		return s1;
	}

	Point * LoadPoint(const char * filename, unsigned int & nPoint) { // 讀數點
		string line;
		ifstream in_file;
		in_file.open(filename);
		while (getline(in_file, line, '\n')) {
			nPoint++;
		}
		in_file.close();

		in_file.open(filename);
		Point *pt = new Point[nPoint];
		for (int i = 0; i < nPoint; i++) {
			in_file >> pt[i].x;
			in_file >> pt[i].y;
		}
		in_file.close();
		return pt;
	}


	int MinDistance(Point * numbers, int n) {                // 計算哪個點距離x+y=5最近 (利用index)
		int index;
		double min = (abs(numbers[0].y + numbers[0].x) - 5) / sqrt(2);
		for (int i = 0; i < n; i++) {
			if ((abs((numbers[i].y + numbers[i].x) - 5)) / sqrt(2) < min) {
				min = (abs((numbers[i].y + numbers[i].x) - 5)) / sqrt(2);
				index = i;
			}
		}
		return index;
	}

	
	Point * SortbyLength(Point * numbers, int l) {                      // Shell sort
		int Gap = l / 2;
		while (Gap > 0) {
			for (int k = 0; k < Gap; k++) {
				for (int i = k + Gap; i < l; i += Gap) {
					for (int j = i - Gap; j >= k; j -= Gap) {
						if (sqrt(pow(numbers[j].x, 2) + pow(numbers[j].y, 2)) > sqrt(pow(numbers[j + Gap].x, 2) + pow(numbers[j + Gap].y, 2))) {
							float a = numbers[j].x;                     // swap
							float b = numbers[j].y;
							numbers[j].x = numbers[j + Gap].x;
							numbers[j].y = numbers[j + Gap].y;
							numbers[j + Gap].x = a;
							numbers[j + Gap].y = b;
						}
						else
							break;
					}
				}
			}
			Gap /= 2;  
		}
		return numbers;
	}

	/* Pseudocode of ShellSort
		Procedure ShellSort(int A[], int N)
		Begin
		Gap = N / 2
			while (Gap > 0){
				for (k = 0; k < Gap; k++){
					for (i = k + Gap; i < MAX; i += Gap){
						for (j = i- Gap; j >= k; j-=Gap){
							if (A[j] > A[j + Gap]){
								SWAP(A[j], A[j + Gap])
								}
								else break;
							}
						}
					}
	*/


	void Report(const char * filename) {
		unsigned int nPoint = 0;
		Point * numbers = LoadPoint(filename, nPoint);

		string min = numbers[MinDistance(numbers, nPoint)].CoutPoint();
		Point *pt = SortbyLength(numbers, nPoint);
		string close = pt[nPoint - 1].CoutPoint();
		double close_length = pt[nPoint - 1].Length();

		ofstream out_file("Output.txt");
		out_file << "物件導向程式設計第一次作業" << endl;
		out_file << "P46091204 蔡承穎" << endl;
		out_file << "點數目： " << nPoint << endl;
		out_file << "最接近 x+y=5 的點：" << min << endl;
		out_file << "與原點距離最近的點： " << close << " 、距離為： " << close_length << endl;
	}

}