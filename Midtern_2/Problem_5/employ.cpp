#include "employ.h"
#include <iostream>

Employee::Employee(char * fn, char * ln) {
	firstname = fn;
	lastname = ln;
}

Employee::Employee(const Employee & em) {
	firstname = em.firstname;
	lastname = em.lastname;
}

Employee::~Employee() {

}

Employee & Employee::operator=(const Employee & em) {
	if (this == &em)
		return *this;
	firstname = em.firstname;
	lastname = em.lastname;
	return *this;
}

void Employee::print() const {
	std::cout << "Name : " << firstname << " " << lastname << std::endl;
}