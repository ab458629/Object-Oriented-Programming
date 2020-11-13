#ifndef QUEUE_H
#define QUEUE_H

class Customer {
private:
	long arrive;
	int processtime;

public:
	Customer() :arrive(0), processtime(0) {}
	void set(long when);
	long when() const { return arrive; }
	int ptime() const { return processtime; }
};

typedef Customer Item;

class Queue {
private:
	struct Node { 
		Item item; 
		struct Node *next;
	};
	/* 
	將Node宣告置於Queue類別內，使其具有類別範疇，
	可用來宣告類別成員，以及類別成員函數中當作型態名稱，
	此方法可以不必擔心這Node的宣告會和全域宣告，
	或其他類別內宣告的Node相衝突
	*/
	enum { Q_SIZE = 10 };
	Node * front;
	Node * rear;
	int items;
	const int qsize;
	
	Queue(const Queue & q) :qsize(0) {}
	Queue & operator=(const Queue & q) { return *this; }

public:
	Queue(int qs = Q_SIZE);
	~Queue();
	bool isempty() const;
	bool isfull() const;
	int queuecount() const;
	bool enqueue(const Item &item);
	bool dequeue(Item &item);
};

#endif // !QUEUE_H
