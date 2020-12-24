#ifndef  BOSS_H_
#define BOSS_H_
#include "employ.h"

class Boss : public Employee {
private:
	double weeklySalary;

public:
	Boss(char *, char *, double);
	Boss(const Employee & em, double);
	double earning() const;
	void print() const;
};

#endif // ! BOSS_H_
