/*
useHW05_03.cpp
��өҺӤ@ P46091204 ���ӿo  Copyright (C) 2020
*/

#include <fstream>
#include <iostream>
#include <iomanip>
#include <chrono>
#include <vector>
#include <algorithm>

#include "HW05_03.h"

Point* LoadPoint(const char*, unsigned int&);

void QuickSort(Point* p, int left, int right);

int main(){
	using std::cout;
	using std::endl;

	std::chrono::steady_clock::time_point start, end;	// �����ɶ����ܼ�

	start = std::chrono::steady_clock::now();	// ����Ū�ɶ}�l�ɶ�
	unsigned int nPoint;
	Point* point_array = LoadPoint("HW5-3-2.bin", nPoint);//Ū�I
	end = std::chrono::steady_clock::now();		// ����Ū�ɵ����ɶ�
	cout << "Time of Load Point : " << std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count() << " ms" << endl;
	cout << "Number of point " << nPoint << endl;
	cout << "\n\n" << endl;

	/*
	�k�@ : ���Q�Χֳt�ƧǪk���ƧǡA�A�P�_�O�_����
	*/
	cout << "�k�@ : ��g�t��k����(Quick sort)" << endl;
	start = std::chrono::steady_clock::now();	// �������������I�}�l�ɶ�

	QuickSort(point_array, 0, nPoint - 1);		// �Q��Quick sort�Ƨ�

	int count = 0;
	for (int i = 0; i < nPoint; i++) {
		if ((point_array[i] == point_array[i+1]) == 0)
			count++;
	}

	end = std::chrono::steady_clock::now();		// �������������I�����ɶ�
	cout << "Cost Time " << std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count() << " ms" << endl;
	cout << "�@��" << count << "���I" << endl;

	cout << "\n\n" << endl;

	/*
	�k�G : ��STL��Vector��
	*/
	cout << "�k�G : ��STL��Vector��" << endl;
	start = std::chrono::steady_clock::now();	// �������������I�}�l�ɶ�

	std::vector<Point> point_vector(point_array, point_array + nPoint);
	std::sort(point_vector.begin(), point_vector.end());
	point_vector.erase(std::unique(point_vector.begin(), point_vector.end()), point_vector.end());

	end = std::chrono::steady_clock::now();		// �������������I�����ɶ�

	cout << "Cost Time " << std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count() << " ms" << endl;
	cout << "�@��" << point_vector.size() << "���I" << endl;

	cout << "\n\n" << endl;

	/*
	�k�T : �T�hfor�j��
	*/

	cout << "�k�T : �T�hfor�j���" << endl;
	start = std::chrono::steady_clock::now();	// �������������I�}�l�ɶ�
	for (int i = 0; i < nPoint; i++) {
		for (int j = i + 1; j < nPoint; j++) {				// ����o�I�P�U���I�O�_�ۦP
			if (point_array[j][0] == point_array[i][0] 
				&& point_array[j][1] == point_array[i][1] 
				&& point_array[j][2] == point_array[i][2]) {
				for (int k = j + 1; k < nPoint; k++) {
					point_array[k - 1] = point_array[k];	// �Y���ۦP�I�A���}�C�e���@�ӧY�i  
				}
				nPoint--;                                    
				j--;
			}
		}
	
	}
	end = std::chrono::steady_clock::now();		// �������������I�����ɶ�

	cout << "Cost Time " << std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count() << " ms" << endl;
	cout << "�@��" << nPoint << "���I" << endl;

	delete [] point_array;
	system("pause");
	return 0;
}

Point* LoadPoint(const char* filename, unsigned int& nPoint)		// �q��r��Ū�J�h���I���
{
	using namespace std;
	Point* pPoint;

	try {
		if (!filename)
			throw new exception("�޼ƿ��~");

		ifstream fin;
		fin.open(filename, ios::in | ios::binary);
		if (!fin.good())
			throw new exception("�ɦW�θ��|���~! �L�k�}���ɮ�!");

		const unsigned int tmpLen = 80;
		char tmpBuff[tmpLen];

		//read Header
		fin.read(tmpBuff, tmpLen);
		if (!fin.good())
			throw new exception("�榡���X(header���~)");

		//how many point ?
		fin.read((char *)&nPoint, 4);//unsigned long, must be 4 bytes
		if (!fin.good())
			throw new exception("�榡���X(�T������ƿ��~)");

		//allocate array memory
		if (nPoint == 0)
		{
			throw new exception("NO Point!");
		}
		pPoint = new Point[nPoint];

		//read triangles
		fin.seekg(84, ios::beg);
		for (int i = 0; i < nPoint; i++)
		{
			fin.read(tmpBuff, 14);
			if (!fin.good())
				throw new exception("�榡���X");
			int gc = fin.gcount();
			if (gc < 14)
				throw;

			memcpy(&pPoint[i], tmpBuff, 12);
		}
		fin.clear();
		fin.close();
	}
	catch (exception *){
		pPoint = 0;
		return (Point *)0;
	}

	return pPoint;
}


void QuickSort(Point* p, int left, int right) {
	int lower = left;
	int upper = right + 1;
	Point pivot = p[left];

	if (lower < upper) {
		while (1) {
			while (p[++lower] < pivot && lower <= right);
			while (p[--upper] > pivot && upper > left);
			if (lower < upper) {
				Point temp = p[lower];
				p[lower] = p[upper];
				p[upper] = temp;
			}
			else {
				break;
			}
		}
		if (lower > upper) {
			Point temp = p[left];
			p[left] = p[upper];
			p[upper] = temp;
		}
		QuickSort(p, left, upper - 1);
		QuickSort(p, upper + 1, right);
	}
}

