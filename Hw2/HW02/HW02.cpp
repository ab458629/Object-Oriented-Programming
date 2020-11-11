/*
HW02.cpp
航太所碩一 P46091204 蔡承穎  Copyright (C) 2020
*/
#include <iostream>
#include "HW02.h"

/*
void Point::Set_data(float a, float b) {		// 可以用來設定點座標，可用可不用
	x = a;
	y = b;
}
*/

float Point::operator[](int i) const {
	float data[2];
	data[0] = x;			// 使得operator[0] 代表private的x值
	data[1] = y;			// 使得operator[1] 代表private的y值
	return data[i];
}

Point::~Point() {			// 解構

}

std::istream & operator >> (std::istream &s, Point &p) {			// >> 重載運算子
	s >> p.x >> p.y;
	return s;
}

std::ostream & operator << (std::ostream &s, const Point &p) {		// << 重載運算子
	s << "(" << p.x << " , " << p.y << ")";
	return s;
}

QuadtreeNode::QuadtreeNode(const Point &_data, const Point &_separate_point, const float _size) :data(&_data), separate_point(_separate_point), size(_size){
	nextNode[4] = { NULL };			// 初始化，下個節點皆指向nullptr，在binary tree 稱之child pointer
}									// 而seperate_point可以看成 parent 但在binary tree為指標，這裡也可改成 QuadTreeNode *parent 在.h更改
									// 0、NULL、snullptr皆可使用
/*
-------------------------------
|       const Point* data     |
-------------------------------
|       const float size      |
-------------------------------
|  const Point separate_point |
-------------------------------
| QuadtreeNode* nextNode[4]   |    <======   四個pointer
-------------------------------
*/

// 複製四元樹
QuadtreeNode::QuadtreeNode(const QuadtreeNode & src): data(src.data), separate_point(src.separate_point), size(src.size) {
	for (int i = 0; i < 4; i++) {
		if (src.nextNode[i] != NULL)									// 下個節點不為nullptr才會new
			this->nextNode[i] = new QuadtreeNode(*src.nextNode[i]);
		else
			this->nextNode[i] = NULL;
	}
	// std::cout << "我建構了 \n";
}

QuadtreeNode::~QuadtreeNode() {				// 解構
	QuadtreeNode *current = this;
	for (int i = 0; i < 4; i++) {
		if (current->nextNode[i] != NULL) {
			current->nextNode[i]->~QuadtreeNode();
			delete nextNode[i];
			nextNode[i] = NULL;
		}
	}
		
	 // std::cout << "我解構了 \n"; // 可以用來確定是否真的是有20個QuadNode解構了
}

/*
相對位置的index q
1 0
2 3
*/

bool QuadtreeNode::InsertPoint(const Point &p) {	
	
	QuadtreeNode *current = this;
	bool success = false;		

	while (success == false) {
		int differ_x = p[0] - current->separate_point[0];		// x的差
		int differ_y = p[1] - current->separate_point[1];		// y的差

		if (differ_x == 0 && differ_y == 0){					// 剛好在分離點上，直接break
			break;                                                                       
		}

		// 因為有遞迴，故以下判斷在Insert點在分離點的方向(右上、右下、左上、左下)是用二分法，降低時間複雜度O
		if (differ_x >= 0) {									// x > 0 表示右半邊
			if (differ_y >= 0) {								// x > 0 && y > 0 表示右上角 (第一象限)
				if (current->nextNode[0] == NULL){
					const Point temp(current->separate_point[0] + (current->size) / 4, current->separate_point[1] + (current->size) / 4);
					current->nextNode[0] = new QuadtreeNode(p, temp, (current->size) / 2);
					if (current->data != NULL){					// 若現在的Node，Data是有值的，需要遞迴到其指向NULL
						const Point *temp1 = current->data;		// 先將data儲存
						current->data = NULL;					// 再將data指向NULL
						current->InsertPoint(*temp1);			// 再將其Insert進來
					}											// 也就是說只能Leaf有Data的值，Internal node不能有
					success = true;								// 建樹成功
				}
				current = current->nextNode[0];		
			}
			else {												// x > 0 && y < 0 表示右上角 (第四象限)
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
		else {														// x < 0表示左半面
			if (differ_y >= 0) {									// x < 0 && y > 0表示左上角 (第二象限)
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
			else {													// x < 0 && y < 0表示左上角 (第三象限)
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
	以下利用四個條件判斷在分裂點的哪個位置，假如說在右上，
	那就將current指標指向nextNode[0]，而previous表示上一動，
	直到current指到nullptr，則直接將previouse的data傳回即可
	*/

	while (current != NULL) {
		previous = current;
		if (p[0] >= current->separate_point[0] && p[1] > current->separate_point[1]) {			// 右上
			current = current->nextNode[0];														
		}
		else if (p[0] < current->separate_point[0] && p[1] >= current->separate_point[1]) {		// 左上
			current = current->nextNode[1];
		}
		else if (p[0] <= current->separate_point[0] && p[1] < current->separate_point[1]) {		// 左下
			current = current->nextNode[2];
		}
		else if (p[0] > current->separate_point[0] && p[1] <= current->separate_point[1]) {     // 右下
			current = current->nextNode[3];
		}
	}

	return previous->data;
}
