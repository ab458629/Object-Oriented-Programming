/*
useHW03_02.cpp
航太所碩一 P46091204 蔡承穎  Copyright (C) 2020
*/

#include "HW03_02.h"
#include <iostream>

using std::cout;
using std::cin;
using std::endl;

int main() {
	int number;
	Queue<int> q;
	int item;

	cout << "The first Queue test : " << endl;
	cout << "(1) Add Element\n(2) Delete Element\n(3) Print Element\n(4) Break the loop" << endl;
	while (1) {
		cin >> number;
		switch (number) {
		case 1: cout << "Please input a element you wanna add : ";
			cin >> item;
			q.Add(item);
			break;
		case 2: item = *q.Delete();
			if (&item != nullptr)
				cout << item << " is a element deleted from the queue. \n";
			break;
		case 3: q.PrintQueue();
			break;
		default:
			break;
		}
		if (number == 4) break;
	}

	cout << "The second Queue test : " << endl;
	Queue<int> w(5);
	cout << "(1) Add Element\n(2) Delete Element\n(3) Print Element\n(4) Break the loop" << endl;
	while (1) {
		cin >> number;
		switch (number) {
		case 1: cout << "Please input a element you wanna add : ";
			cin >> item;
			w.Add(item);
			break;
		case 2: item = *w.Delete();
			if (&item != nullptr)
				cout << item << " is a element deleted from the queue. \n";
			break;
		case 3: w.PrintQueue();
			break;
		default:
			break;
		}
		if (number == 4) break;
	}

	cout << "Assignment operator test (Queue1 = Queue2)" << endl;
	q = w;
	q.PrintQueue();

	cout << "Constructor test (Queue3(Queue2))" << endl;
	Queue<int> e(w);
	e.PrintQueue();
	cout << endl;
	
	system("pause");
	return 0;
}
