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

	double **arr = nullptr;

	cout << "��J�Ÿ�: ";

	while (cin >> symbol){
		if (symbol == '+'){
			cout << "���G: " << endl;
			arr = Matrix_A + Matrix_B;
		}

		else if (symbol == '-') {
			cout << "���G: " << endl;
			arr = Matrix_A - Matrix_B;
		}

		else if (symbol == '*'){
			cout << "���G: " << endl;
			arr = Matrix_A *  Matrix_A;
		}
		else
			break;

		for (int i = 0; i < n; i++) {
			for (int j = 0; j < n; j++) {
				cout << arr[i][j] << " ";
			}
			cout << endl;
		}
	}
	if (arr != nullptr) {
		cout << "Matrix_C = " << endl;
		Matrix Matrix_C(arr, 3);
	}
	cout << "\n\n";
	cout << "�ƻs�غc�l����: " << endl;
	Matrix Copy_Matrix_A(Matrix_A);
	Matrix Copy_Matrix_B(Matrix_B);

	while (cin >> symbol) {
		if (symbol == '+') {
			cout << "���G: " << endl;
			arr = Copy_Matrix_A + Copy_Matrix_B;
		}

		else if (symbol == '-') {
			cout << "���G: " << endl;
			arr = Copy_Matrix_A - Copy_Matrix_B;
		}

		else if (symbol == '*') {
			cout << "���G: " << endl;
			arr = Copy_Matrix_A *  Copy_Matrix_B;
		}
		else
			break;

		for (int i = 0; i < n; i++) {
			for (int j = 0; j < n; j++) {
				cout << arr[i][j] << " ";
			}
			cout << endl;
		}
	}

	Copy_Matrix_A = Copy_Matrix_B;



	system("PAUSE");
	return 0;
}
