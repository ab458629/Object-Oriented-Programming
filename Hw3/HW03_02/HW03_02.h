#ifndef HW03_02_H
#define HW03_02_H
#include <iostream>

template<class KeyType>
class Queue {
private:
	int front, rear;	// ����ܼ�
	KeyType* queue;		// �@�Ӥ@���}�C
	int MaxSize;
public:
	Queue(int MaxSize = 10);	// default MaxSize = 10
	~Queue();
	Queue(const Queue& q);
	Queue& operator=(const Queue& q);
	bool IsFull();
	bool IsEmpty();
	void Add(const KeyType& item);
	KeyType* Delete();
	void PrintQueue();
};

/*
	�o�̱o�g�b�P�@���ɮסA����t�~�gcpp
	�t�~�H�U�L�{���naive�A�N���t�~����
	�j�P�W�N�O���Nfront�Brear�]�w��-1
	�A�ھڱ`��enque�Bdeque���覡�F��
*/

using std::cout;
using std::endl;

template<class KeyType>
Queue<KeyType>::Queue(int MaxSize = 10) :front(-1), rear(-1), MaxSize(MaxSize) {
	queue = new KeyType[MaxSize]{ 0 };
}

template<class KeyType>
Queue<KeyType>::~Queue() {
	delete[] queue;
}

template<class KeyType>
Queue<KeyType>::Queue(const Queue& q) {
	rear = q.rear;
	front = q.front;
	delete[] queue;
	MaxSize = q.MaxSize;
	queue = new KeyType[MaxSize]{0};
	for (int i = 0; i < MaxSize; i++) {
		queue[i] = q.queue[i];
	}
}

template<class KeyType>
Queue<KeyType>& Queue<KeyType>::operator=(const Queue& q) {
	if (this == &q) return *this;
	rear = q.rear;
	front = q.front;
	delete[] queue;
	MaxSize = q.MaxSize;
	queue = new KeyType[MaxSize]{0};
	for (int i = 0; i < MaxSize; i++) {
		queue[i] = q.queue[i];
	}
	return *this;
}

template<class KeyType>
bool Queue<KeyType>::IsFull() {
	if (rear == (MaxSize - 1)) {
		return true;
	}
	else {
		return false;
	}
}

template<class KeyType>
bool Queue<KeyType>::IsEmpty() {
	if (front == rear) {
		return true;
	}
	else {
		return false;
	}
}

template<class KeyType>
void Queue<KeyType>::Add(const KeyType& item) {
	if (IsFull()) {
		cout << "Queue is full." << endl;
	}
	else {
		queue[++rear] = item;
	}
}

template<class KeyType>
KeyType* Queue<KeyType>::Delete() {
	if (IsEmpty()) {
		cout << "Queue is empty." << endl;
		return nullptr;
	}
	else {
		return &queue[++front];
	}
}


template<class KeyType>
void Queue<KeyType>::PrintQueue() {
	cout << "The element of Queue is";
	for (int i = front + 1; i <= rear; i++) {
		cout << " " << queue[i];
	}
	cout << endl;
}

#endif // !HW03_02_H
