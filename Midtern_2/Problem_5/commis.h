#ifndef COMMIS_H_
#define COMMIS_H_
#include "employ.h"

class CommisionWorker : public Employee {
private:
	double salary;
	double commision;
	int quantityPerWeek;

public:
	CommisionWorker(char *, char *, double, double, int);
	CommisionWorker(const Employee &, double, double, int);
	double earning() const;
	void print() const;
};

#endif // !COMMIS_H_



