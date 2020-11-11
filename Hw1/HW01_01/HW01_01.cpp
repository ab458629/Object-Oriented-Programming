/*
   HW01_01.cpp
   航太所碩一 P46091204 蔡承穎  Copyright (C) 2020
												   */

#include <iostream>
#include <ctime>
#include <cstring>

using namespace std;

void swap(int &p1, int &p2) {
	int temp = p1;
	p1 = p2;
	p2 = temp;
}

template <typename T>						// 利用Template + Class解，封裝且泛用的概念
class Maximum {
private:
	T * a;
	int l;
public:
	Maximum() {
		l = 8;
		a = new T[l];						// 跟記憶體要一段空間
	}
	void RandomNum() {						// 產生亂數陣列
		a = new T[l];
		srand(time(0));						// 設定亂數種
		cout << "未排序前: ";
		for (int i = 0; i < l; i++) {
			a[i] = (T)rand();
		}
		for (int i = 0; i < l; i++) {
			cout << a[i] << " ";
		}
		cout << endl;
	};
	void Shellsort() {						// 這裡因為陣列個數較小，故選擇Shellsort (Pseudocode 附在第二題)
		int Gap = l / 2;					// 薛耳排序法 平均時間複雜度O(nlogn) 用來減少插入排序法中元素搬移的次數，增快速度
		while (Gap > 0) {
			for (int k = 0; k < Gap; k++) {
				for (int i = k + Gap; i < l; i += Gap) {
					for (int j = i - Gap; j >= k; j -= Gap) {
						if (a[j] > a[j + Gap]) {
							swap(a[j], a[j + Gap]);
						}
						else
							break;
					}
				}
			}
			Gap /= 2;
		}
	};
	void PrintSort() {						// 列印出結果
		cout << "已排序後: ";
		for (int i = 1; i < l; i++) {
			cout << a[i] << " ";
		}
		cout << endl;
		cout << "故所求最大值為: " << a[l - 1] << endl;
		delete[] a;							// 釋放記憶體 避免Memory leak
											// C++ -> new delete  C-> malloc free
	};
};

template<>									// 樣板特製化測試
class Maximum<char> {
public:
	void MaxStr(char ** pt) {				// 計算最長字串的index並回傳位址
		int max = strlen(pt[0]);
		int index = 0;
		for (int i = 1; i < 8; i++) {
			if (strlen(pt[i]) > max) {
				max = strlen(pt[i]);
				index++;
			}
		}
		cout << endl;
		cout << pt[index] << " 長度為: " << max << " 地址為: " << &pt[index] << endl;
	}
};



int main() {
	cout << "----------------" << endl;
	cout << "|  找尋最大值  |" << endl;
	cout << "----------------" << endl;
	cout << "Short型態的陣列" << endl;
	Maximum<short>test1;
	test1.RandomNum();
	test1.Shellsort();
	test1.PrintSort();

	cout << endl;

	cout << "Double型態的陣列" << endl;
	Maximum<double>test2;
	test2.RandomNum();
	test2.Shellsort();
	test2.PrintSort();
	cout << endl;

	cout << "--------------------" << endl;
	cout << "| 尋找最長字串地址 |" << endl;
	cout << "--------------------" << endl;
	cout << "測試一" << endl;						// 這裡我使用連續的記憶體空間做測試
	char **pt = new char*[8];						// const * char pt = "string" 一維 (例如 : printf(const * char) ， print的引數本來就是位址)
	pt[0] = new char[2]{ "h" };						// const ** char pt = {"string1", "string2"} 二維
	pt[1] = new char[3]{ "he" };
	pt[2] = new char[4]{ "hel" };
	pt[3] = new char[5]{ "hell" };
	pt[4] = new char[6]{ "hello" };
	pt[5] = new char[7]{ "helloo" };
	pt[6] = new char[8]{ "hellooo" };
	pt[7] = new char[8]{ "hellooo" };
	for (int i = 0; i < 8; i++) {
		cout << pt[i] << " : " << &pt[i] << endl;
	}
	Maximum<char>test3;
	test3.MaxStr(pt);
	for (int i = 0; i < 8; i++) {
		delete[] pt[i];
	}
	delete[] pt;

	cout << "測試二" << endl;
	char **pt1 = new char*[8];
	pt1[0] = new char[2]{ "h" };
	pt1[1] = new char[3]{ "he" };
	pt1[2] = new char[4]{ "hel" };
	pt1[3] = new char[5]{ "hell" };
	pt1[4] = new char[6]{ "hello" };
	pt1[5] = new char[7]{ "helloo" };
	pt1[6] = new char[8]{ "hellooo" };
	pt1[7] = new char[8]{ "hellooo" };
	for (int i = 0; i < 8; i++) {
		cout << pt1[i] << " : " << &pt1[i] << endl;
	}
	Maximum<char>test4;
	test4.MaxStr(pt1);
	for (int i = 0; i < 8; i++) {
		delete[] pt1[i];
	}
	delete[] pt1;
	system("pause");
	return 0;
}

/* 找字串長度 (函數的方法)
int String_len(char *a) {
int i = 0;
while (a[i] != '\0') { i++; }
return i;
}
*/