/*
useHW02.cpp
航太所碩一 P46091204 蔡承穎  Copyright (C) 2020
*/
#include <iostream>
#include <fstream>
#include <sstream> 
#include <cstdlib>
#include <string>
#include <cmath>
#include "HW02.h"

const int POINTS = 20;
const int BOUND = 100;

Point * LoadPoint(const char *, int &);

int main() {		
	using std::cin;
	using std::endl;
	using std::cout;

	int nPoint = 0;
	Point *null = NULL;										// 初始data
	Point sep(0, 0);						    // 初始分離點
	QuadtreeNode Quadtree(*null, sep, 200);				// 初始四元樹

	Point *pt = LoadPoint("Point_HW2.txt", nPoint);			// 讀取Point_HW2.txt的點

															
	for (int i = 0; i < POINTS; i++) {						// 可以用來看有沒有讀到點
		cout << pt[i] << endl;								// 測試的時候也能參考
	}
	cout << "\n\n";

	for (int i = 0; i < POINTS; i++) {
		Quadtree.InsertPoint(pt[i]);
	}


	Point input;
	bool ok = false;
	while (1) {
		cout << "Please input a point (The range of (x , y) : -100 ~ 100) : " 
			<< "\n" << "( Just input other symbols, then you can break the loop )"<< endl;
		cin >> input;
		if (cin.fail()) {
			cout << "Error type of input ! Please check the type of input. " << endl;
			break;
		}
		else if (input[0] == 0 && input[1] == 0) {
			cout << "Please don't input (0 , 0), input correct point again. " << "\n\n";
		}
		else {
			if (abs(input[0]) > BOUND || abs(input[1]) > BOUND){				// 判斷輸入是否超出設定邊界
				cout << "Unsatisfy the the boundary of the Quadtree" << endl;
			}
			else {
				const Point * closest = Quadtree.FindClosestPoint(input);
				if (closest != NULL) {
					cout << "The nearest point is " << *closest << endl;
					ok = true;
				}
				else {
					cout << "This region is empty. " << endl;
				}
				break;
			}
		}
	}

	if (ok) {
		QuadtreeNode CopyQuadtree(Quadtree);
		Quadtree.~QuadtreeNode();

		cout << "\n Copy Quadtree : " << endl;

		const Point * closest = CopyQuadtree.FindClosestPoint(input);

		cout << "The nearest point is " << *closest << endl;

		CopyQuadtree.~QuadtreeNode();
	}

	cout << "\n\n程式結束..." << endl;
	/*
	使用複製建構子複製四元樹，並同樣使用成員函式
	FindClosestPoint 找出輸入點所屬子節點內的點座標並使用輸出導向運算子列印其至小數點下 3 位
	*/

	cout << "\n\n";
	cout << "類別Point的default constructor與destructor可以用compiler自己預設的，\n"
		 << "這是因為compiler對於靜態空間的處理沒有甚麼問題，\n"
		 << "然而因為compiler對於動態空間的處理非常不好，也就是說容易沒有刪乾淨造成程式crash的問題\n"
		 << "故當有new的時候，也就是Quadtree裡的成員函式有用到new，那麼建構子與解構子都得由程式設計師自己定義，\n" 
		 << "否則用預設解構子只能刪除最初的node，但指標所指向的空間依舊存在。" << endl;
	system("pause");
	return 0;
}

Point * LoadPoint(const char * filename, int & nPoint) {
	std::string line;
	std::ifstream in_file;
	in_file.open(filename);
	while (getline(in_file, line, '\n')) {
		nPoint++;
	}
	in_file.close();

	in_file.open(filename);
	Point *pt = new Point[nPoint];
	for (int i = 0; i < nPoint; i++) {
		in_file >> pt[i];
	}
	in_file.close();
	return pt;
}