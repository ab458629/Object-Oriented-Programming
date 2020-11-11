#ifndef	HW02_H
#define HW02_H
#include <iostream>

class Point{
private:									// �G���I�y��
	float x;
	float y;

public:
	Point() :x(0.f), y(0.f){};					// �w�](0,0)�A�o�˼g���²�u�B�ֳt (member initializer list)
	Point(float _x, float _y) :x(_x), y(_y) {};	// �Ѽƫغc�l
	~Point();									// �Ѻc�l
	// void Set_data(float, float);				// �p���ݭn�]�wdata�ϥ�
	float operator[](int i) const;				// Subscript operator [0]��x [1]��y
	friend std::istream & operator >> (std::istream &, Point &);			// ���� >> Ū�ɨϥ�
	friend std::ostream & operator << (std::ostream &, const Point &);		// ���� << ��X�ϥ�
};

class QuadtreeNode{
private:
	const Point *data;						// �O�����`�I���I���
	QuadtreeNode *nextNode[4];				// ���V���`�I���|�Ӥl�`�I 
	const Point separate_point;				// �`�I�����Τ��� 
	const float size;						// �O�����`�I��������ɪ���

public:
	QuadtreeNode() :size(0.f) {};			// �򩳫غc�l�A�����O�N���ϥΡA�нվ�Ϩ�L�k�Q�I�s�A�o�O�]��root������(0,0)�Y�i
	QuadtreeNode(const Point &, const Point &, const float);			// �T�ӰѼƫغc�l (data, separate_point, size)
	QuadtreeNode(const QuadtreeNode &);									// �ƻs�غc�l (deep copy) �`�N���ݦb�᭱�[�Wconst
	~QuadtreeNode();													// �Ѻc�l�A����ʺA�Ŷ�
	bool InsertPoint(const Point &);									// �N�I�ǤJ�ô��J�|����
	const Point *FindClosestPoint(const Point &);					    // �N�I�ǤJ�A�M��ǤJ�I���ݪ��l�`�I�A�ñN�w�ݩ�Ӥl�`�I���I�^��
};

#endif // HW02_H
