/*
HW05_02.cpp
航太所碩一 P46091204 蔡承穎  Copyright (C) 2020
Lambda expression => 省去另外定義函數的麻煩
*/

#include <iostream>
#include <initializer_list>

template <class T>
T average_list(std::initializer_list<T> ril);

int main(){
	using namespace std;
	// list of double deduced from list contents
	auto q = average_list({ 15.4, 10.7, 9.0 });
	cout << q << endl;
	// list of int deduced from list contents
	cout << average_list({ 20, 30, 19, 17, 45, 38 }) << endl;
	// forced list of double
	auto ad = average_list<double>({ 'A', 70, 65.33 });			// 這裡 'A'會依照ASCII code轉換成65
	cout << ad << endl;

	system("pause");
	return 0;
}

template <class T>
T average_list(std::initializer_list<T> ril) {
	double tot = 0;
	int n = ril.size();
	double ave = 0.0;
	if (n > 0) {
		for (auto p = ril.begin(); p != ril.end(); p++)
			tot += *p;
		ave = tot / n;
	}
	return ave;
}

