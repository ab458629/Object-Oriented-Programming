#include <iostream>
#include <ctime>
#include "matrix.h"

using namespace std;
using namespace MATRIX;

int main() {
	srand(time(0));
	int n;
	char symbol;
	cout << "��J����: ";
	cin >> n;
	cout << "Matrix_A = " << endl;
	Matrix Matrix_A(n);
	cout << "Matrix_B = " << endl;
	Matrix Matrix_B(n);

	cout << "��J�Ÿ�: ";

	Matrix Matrix_C;

	while (cin >> symbol){
		if (symbol == '+'){
			Matrix_C = Matrix_A + Matrix_B;
		}

		else if (symbol == '-') {
			Matrix_C = Matrix_A - Matrix_B;
		}

		else if (symbol == '*'){
			Matrix_C = Matrix_A *  Matrix_A;
		}
		else
			break;
		cout << "�B�⵲�G" << endl;
		cout << "Matrix_C = " << endl;
		cout << Matrix_C << endl;
	}

	cout << "\n\n";
	cout << "�ƻs�غc�l����: " << endl;
	Matrix Copy_Matrix_A(Matrix_A);
	Matrix Copy_Matrix_B(Matrix_B);

	while (cin >> symbol) {
		if (symbol == '+') {
			Matrix_C = Copy_Matrix_A + Copy_Matrix_B;
		}

		else if (symbol == '-') {
			Matrix_C = Copy_Matrix_A - Copy_Matrix_B;
		}

		else if (symbol == '*') {
			Matrix_C = Copy_Matrix_A *  Copy_Matrix_B;
		}
		else
			break;

		cout << "�B�⵲�G" << endl;
		cout << "Matrix_C = " << endl;
		cout << Matrix_C << endl;
	}

	cout << "���w�B��l���աA�NB���w��A" << endl;
	Copy_Matrix_A = Copy_Matrix_B;
	cout << Copy_Matrix_A;
	system("PAUSE");
	return 0;
}
