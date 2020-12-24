#include "employ.h"
#include "boss.h"
#include "commis.h"
#include "hourly.h"
#include "piece.h"
#include <iostream>
#include <iomanip>

using namespace std;

void ViaPointer(const Employee *);
void ViaReference(const Employee &);

int main() {
	cout << setiosflags(ios::fixed | ios::showpoint) << setprecision(2);

	Boss b("John", "Smith", 800.00);
	b.print();
	ViaPointer(&b);
	ViaReference(b);
	cout << endl;

	CommisionWorker c("Bob", "Lewis", 200.0, 3.0, 150);
	c.print();
	ViaPointer(&c);
	ViaReference(c);
	cout << endl;

	PieceWorker p("Sue", "Jones", 2.5, 200);
	p.print();
	ViaPointer(&p);
	ViaReference(p);
	cout << endl;

	HourlyWorker h("Karen", "Price", 13.75, 40);
	h.print();
	ViaPointer(&h);
	ViaReference(h);
	cout << endl;

	system("pause");
	return 0;
}

void ViaPointer(const Employee * base) {
	base->print();
}

void ViaReference(const Employee & base) {
	base.print();
}