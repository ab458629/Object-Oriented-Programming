/*
HW02.cpp
��өҺӤ@ P46091204 ���ӿo  Copyright (C) 2020
*/
#include <iostream>
#include "HW02.h"

/*
void Point::Set_data(float a, float b) {		// �i�H�Ψӳ]�w�I�y�СA�i�Υi����
	x = a;
	y = b;
}
*/

float Point::operator[](int i) const {
	float data[2];
	data[0] = x;			// �ϱooperator[0] �N��private��x��
	data[1] = y;			// �ϱooperator[1] �N��private��y��
	return data[i];
}

Point::~Point() {			// �Ѻc

}

std::istream & operator >> (std::istream &s, Point &p) {			// >> �����B��l
	s >> p.x >> p.y;
	return s;
}

std::ostream & operator << (std::ostream &s, const Point &p) {		// << �����B��l
	s << "(" << p.x << " , " << p.y << ")";
	return s;
}

QuadtreeNode::QuadtreeNode(const Point &_data, const Point &_separate_point, const float _size) :data(&_data), separate_point(_separate_point), size(_size){
	nextNode[4] = { NULL };			// ��l�ơA�U�Ӹ`�I�ҫ��Vnullptr�A�bbinary tree �٤�child pointer
}									// ��seperate_point�i�H�ݦ� parent ���bbinary tree�����СA�o�̤]�i�令 QuadTreeNode *parent �b.h���
									// 0�BNULL�Bsnullptr�ҥi�ϥ�
/*
-------------------------------
|       const Point* data     |
-------------------------------
|       const float size      |
-------------------------------
|  const Point separate_point |
-------------------------------
| QuadtreeNode* nextNode[4]   |    <======   �|��pointer
-------------------------------
*/

// �ƻs�|����
QuadtreeNode::QuadtreeNode(const QuadtreeNode & src): data(src.data), separate_point(src.separate_point), size(src.size) {
	for (int i = 0; i < 4; i++) {
		if (src.nextNode[i] != NULL)									// �U�Ӹ`�I����nullptr�~�|new
			this->nextNode[i] = new QuadtreeNode(*src.nextNode[i]);
		else
			this->nextNode[i] = NULL;
	}
	// std::cout << "�ګغc�F \n";
}

QuadtreeNode::~QuadtreeNode() {				// �Ѻc
	QuadtreeNode *current = this;
	for (int i = 0; i < 4; i++) {
		if (current->nextNode[i] != NULL) {
			current->nextNode[i]->~QuadtreeNode();
			delete nextNode[i];
			nextNode[i] = NULL;
		}
	}
		
	 // std::cout << "�ڸѺc�F \n"; // �i�H�ΨӽT�w�O�_�u���O��20��QuadNode�Ѻc�F
}

/*
�۹��m��index q
1 0
2 3
*/

bool QuadtreeNode::InsertPoint(const Point &p) {	
	
	QuadtreeNode *current = this;
	bool success = false;		

	while (success == false) {
		int differ_x = p[0] - current->separate_point[0];		// x���t
		int differ_y = p[1] - current->separate_point[1];		// y���t

		if (differ_x == 0 && differ_y == 0){					// ��n�b�����I�W�A����break
			break;                                                                       
		}

		// �]�������j�A�G�H�U�P�_�bInsert�I�b�����I����V(�k�W�B�k�U�B���W�B���U)�O�ΤG���k�A���C�ɶ�������O
		if (differ_x >= 0) {									// x > 0 ��ܥk�b��
			if (differ_y >= 0) {								// x > 0 && y > 0 ��ܥk�W�� (�Ĥ@�H��)
				if (current->nextNode[0] == NULL){
					const Point temp(current->separate_point[0] + (current->size) / 4, current->separate_point[1] + (current->size) / 4);
					current->nextNode[0] = new QuadtreeNode(p, temp, (current->size) / 2);
					if (current->data != NULL){					// �Y�{�b��Node�AData�O���Ȫ��A�ݭn���j�����VNULL
						const Point *temp1 = current->data;		// ���Ndata�x�s
						current->data = NULL;					// �A�Ndata���VNULL
						current->InsertPoint(*temp1);			// �A�N��Insert�i��
					}											// �]�N�O���u��Leaf��Data���ȡAInternal node���঳
					success = true;								// �ؾ𦨥\
				}
				current = current->nextNode[0];		
			}
			else {												// x > 0 && y < 0 ��ܥk�W�� (�ĥ|�H��)
				if (current->nextNode[3] == NULL)
				{
					const Point temp(current->separate_point[0] + (current->size) / 4, current->separate_point[1] - (current->size) / 4);
					current->nextNode[3] = new QuadtreeNode(p, temp, (current->size) / 2);
					if (current->data != NULL) {
						const Point *temp1 = current->data;
						current->data = NULL;
						current->InsertPoint(*temp1);
					}
					success = true;
				}
				current = current->nextNode[3];
			}
		}
		else {														// x < 0��ܥ��b��
			if (differ_y >= 0) {									// x < 0 && y > 0��ܥ��W�� (�ĤG�H��)
				if (current->nextNode[1] == NULL) {
					const Point tmp(current->separate_point[0] - (current->size) / 4, current->separate_point[1] + (current->size) / 4);
					current->nextNode[1] = new QuadtreeNode(p, tmp, (current->size) / 2);
					if (current->data != NULL) {
						const Point *temp1 = current->data;
						current->data = NULL;
						current->InsertPoint(*temp1);
					}
					success = true;
				}
				current = current->nextNode[1];
			}
			else {													// x < 0 && y < 0��ܥ��W�� (�ĤT�H��)
				if (current->nextNode[2] == NULL)
				{
					const Point tmp(current->separate_point[0] - (current->size) / 4, current->separate_point[1] - (current->size) / 4);
					current->nextNode[2] = new QuadtreeNode(p, tmp, (current->size) / 2);
					if (current->data != NULL)
					{
						const Point *temp1 = current->data;
						current->data = NULL;
						current->InsertPoint(*temp1);
					}
					success = true;
				}
				current = current->nextNode[2];
			}
		}
	}
	return success;
}

const Point* QuadtreeNode::FindClosestPoint(const Point &p){
	
	QuadtreeNode *current = this;
	QuadtreeNode *previous = 0;

	/*
	�H�U�Q�Υ|�ӱ���P�_�b�����I�����Ӧ�m�A���p���b�k�W�A
	���N�Ncurrent���Ы��VnextNode[0]�A��previous��ܤW�@�ʡA
	����current����nullptr�A�h�����Npreviouse��data�Ǧ^�Y�i
	*/

	while (current != NULL) {
		previous = current;
		if (p[0] >= current->separate_point[0] && p[1] > current->separate_point[1]) {			// �k�W
			current = current->nextNode[0];														
		}
		else if (p[0] < current->separate_point[0] && p[1] >= current->separate_point[1]) {		// ���W
			current = current->nextNode[1];
		}
		else if (p[0] <= current->separate_point[0] && p[1] < current->separate_point[1]) {		// ���U
			current = current->nextNode[2];
		}
		else if (p[0] > current->separate_point[0] && p[1] <= current->separate_point[1]) {     // �k�U
			current = current->nextNode[3];
		}
	}

	return previous->data;
}
