/*
useHW02.cpp
��өҺӤ@ P46091204 ���ӿo  Copyright (C) 2020
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
	Point *null = NULL;										// ��ldata
	Point sep(0, 0);						    // ��l�����I
	QuadtreeNode Quadtree(*null, sep, 200);				// ��l�|����

	Point *pt = LoadPoint("Point_HW2.txt", nPoint);			// Ū��Point_HW2.txt���I

															
	for (int i = 0; i < POINTS; i++) {						// �i�H�ΨӬݦ��S��Ū���I
		cout << pt[i] << endl;								// ���ժ��ɭԤ]��Ѧ�
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
			if (abs(input[0]) > BOUND || abs(input[1]) > BOUND){				// �P�_��J�O�_�W�X�]�w���
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

	cout << "\n\n�{������..." << endl;
	/*
	�ϥνƻs�غc�l�ƻs�|����A�æP�˨ϥΦ����禡
	FindClosestPoint ��X��J�I���ݤl�`�I�����I�y�Шèϥο�X�ɦV�B��l�C�L��ܤp���I�U 3 ��
	*/

	cout << "\n\n";
	cout << "���OPoint��default constructor�Pdestructor�i�H��compiler�ۤv�w�]���A\n"
		 << "�o�O�]��compiler����R�A�Ŷ����B�z�S���ƻ���D�A\n"
		 << "�M�Ӧ]��compiler���ʺA�Ŷ����B�z�D�`���n�A�]�N�O���e���S���R���b�y���{��crash�����D\n"
		 << "�G��new���ɭԡA�]�N�OQuadtree�̪������禡���Ψ�new�A����غc�l�P�Ѻc�l���o�ѵ{���]�p�v�ۤv�w�q�A\n" 
		 << "�_�h�ιw�]�Ѻc�l�u��R���̪쪺node�A�����Щҫ��V���Ŷ����¦s�b�C" << endl;
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