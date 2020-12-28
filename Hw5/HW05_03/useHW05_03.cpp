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

	std::chrono::steady_clock::time_point start, end;	// 紀錄時間的變數

	start = std::chrono::steady_clock::now();	// 紀錄讀檔開始時間
	unsigned int nPoint;
	Point* point_array = LoadPoint("HW5-3-3.bin", nPoint);//讀點
	end = std::chrono::steady_clock::now();		// 紀錄讀檔結束時間
	cout << "Time of Load Point : " << std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count() << " ms" << endl;
	cout << "Number of point " << nPoint << endl;
	cout << "\n\n" << endl;

	/*
	法一 : 先利用快速排序法做排序，再判斷是否重複
	*/
	cout << "法一 : 手寫演算法測試(Quick sort)" << endl;
	start = std::chrono::steady_clock::now();	// 紀錄移除重複點開始時間

	QuickSort(point_array, 0, nPoint - 1);		// 利用Quick sort排序
	int count = 0;
	for (int i = 0; i < nPoint; i++) {
		if ((point_array[i] == point_array[i+1]) == 0)
			count++;
	}

	end = std::chrono::steady_clock::now();		// 紀錄移除重複點結束時間
	cout << "Cost Time " << std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count() << " ms" << endl;
	cout << "共有" << count << "個點" << endl;

	cout << "\n\n" << endl;

	/*
	法二 : 用STL中Vector解
	*/
	cout << "法二 : 用STL中Vector解" << endl;
	start = std::chrono::steady_clock::now();	// 紀錄移除重複點開始時間

	std::vector<Point> point_vector(point_array, point_array + nPoint);
	std::sort(point_vector.begin(), point_vector.end());
	point_vector.erase(std::unique(point_vector.begin(), point_vector.end()), point_vector.end());

	end = std::chrono::steady_clock::now();		// 紀錄移除重複點結束時間

	cout << "Cost Time " << std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count() << " ms" << endl;
	cout << "共有" << point_vector.size() << "個點" << endl;

	delete [] point_array;
	system("pause");
	return 0;
}

Point* LoadPoint(const char* filename, unsigned int& nPoint)		// 從文字檔讀入多個點資料
{
	using namespace std;
	Point* pPoint;

	try {
		if (!filename)
			throw new exception("引數錯誤");

		ifstream fin;
		fin.open(filename, ios::in | ios::binary);
		if (!fin.good())
			throw new exception("檔名或路徑錯誤! 無法開啟檔案!");

		const unsigned int tmpLen = 80;
		char tmpBuff[tmpLen];

		//read Header
		fin.read(tmpBuff, tmpLen);
		if (!fin.good())
			throw new exception("格式不合(header錯誤)");

		//how many point ?
		fin.read((char *)&nPoint, 4);//unsigned long, must be 4 bytes
		if (!fin.good())
			throw new exception("格式不合(三角網格數錯誤)");

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
				throw new exception("格式不合");
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
			while (p[++lower] <= pivot && lower <= right);
			while (p[--upper] >= pivot && upper > left);
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

