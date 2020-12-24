#include "boss.h"
#include <iostream>

Boss::Boss(char * fn, char * ln, double ws) : Employee(fn, ln), weeklySalary(ws) {}

Boss::Boss(const Employee & em, double ws) : Employee(em), weeklySalary(ws) {}

double Boss::earning() const {
	return 4 * weeklySalary;
}

void Boss::print() const {
	Employee::print();
	std::cout << "The month salary of Boss is " << Boss::earning() << std::endl;
}