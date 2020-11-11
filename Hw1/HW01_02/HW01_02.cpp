/*
   HW01_01.cpp
   ��өҺӤ@ P46091204 ���ӿo  Copyright (C) 2020
												   */
#include <iostream>
#include <string>
#include <fstream>
#include <cmath>
#include <sstream> // �ϥ�StringStream
#include <cstdlib>
#include "HW01_02.h"

using namespace std;

namespace MyGeometry {

	double Point::Length() { // �p����I����
		double length;
		length = sqrt(x * x + y * y);
		return length;
	}

	string Point::CoutPoint() {
		string s1;
		stringstream s2; // �o�O���F�Nfloat�নstring�r��
		s2 << "(" << x << "," << y << ")";
		s2 >> s1;
		if (!s2) cout << "error type !" << endl; // �T�w�O�_���ഫ���\
		return s1;
	}

	Point * LoadPoint(const char * filename, unsigned int & nPoint) { // Ū���I
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


	int MinDistance(Point * numbers, int n) {                // �p������I�Z��x+y=5�̪� (�Q��index)
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
		out_file << "����ɦV�{���]�p�Ĥ@���@�~" << endl;
		out_file << "P46091204 ���ӿo" << endl;
		out_file << "�I�ƥءG " << nPoint << endl;
		out_file << "�̱��� x+y=5 ���I�G" << min << endl;
		out_file << "�P���I�Z���̪��I�G " << close << " �B�Z�����G " << close_length << endl;
	}

}