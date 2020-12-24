#ifndef PIECE_H_
#define PIECE_H_
#include "employ.h"

class PieceWorker : public Employee {
private:
	double wagePerPiece;
	int quantityPerWeek;

public:
	PieceWorker(char *, char *, double, int);
	PieceWorker(const Employee &, double, int);
	double earning() const;
	void print() const;
};

#endif // !PIECE_H_
