#include "hourly.h"
#include <iostream>

HourlyWorker::HourlyWorker(char * fn, char * ln, double wg, double hr) : Employee(fn, ln), wage(wg), hours(hr) {}

HourlyWorker::HourlyWorker(const Employee & em, double wg, double hr) : Employee(em), wage(wg), hours(hr) {}

double HourlyWorker::earning() const {
	return wage * hours;
}

void HourlyWorker::print() const {
	Employee::print();
	std::cout << "The month salary of HourlyWorker is " << HourlyWorker::earning() << std::endl;
}