#include "commis.h"
#include <iostream>

CommisionWorker::CommisionWorker(char * fn, char * ln, double sl, double com, int pk)
	:Employee(fn, ln), salary(sl), commision(com), quantityPerWeek(pk) {}

CommisionWorker::CommisionWorker(const Employee & em, double sl, double com, int pk)
	: Employee(em), salary(sl), commision(com), quantityPerWeek(pk) {}

double CommisionWorker::earning() const {
	return salary + 4 * commision * quantityPerWeek;
}

void CommisionWorker::print() const {
	Employee::print();
	std::cout << "The month salary of CommisionWorker is " << CommisionWorker::earning() << std::endl;
}