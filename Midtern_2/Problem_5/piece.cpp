#include "piece.h"
#include <iostream>

PieceWorker::PieceWorker(char * fn, char * ln, double wg, int qu) 
	: Employee(fn, ln), wagePerPiece(wg), quantityPerWeek(qu) {}

PieceWorker::PieceWorker(const Employee & em, double wg, int qu)
	: Employee(em), wagePerPiece(wg), quantityPerWeek(qu) {}

double PieceWorker::earning() const {
	return 4 * wagePerPiece * quantityPerWeek;
}

void PieceWorker::print() const {
	Employee::print();
	std::cout << "The month salary of PieceWorker is " << PieceWorker::earning() << std::endl;
}
