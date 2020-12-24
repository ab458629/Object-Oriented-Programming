#ifndef  HOURLY_H_
#define HOURLY_H_
#include "employ.h"

class HourlyWorker : public Employee {
private:
	double wage;
	double hours;

public:
	HourlyWorker(char *, char *, double, double);
	HourlyWorker(const Employee &, double, double);
	double earning() const;
	void print() const;
};

#endif // ! HOURLY_H_
