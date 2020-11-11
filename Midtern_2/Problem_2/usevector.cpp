#include <iostream>
#include <cstdlib>
#include <ctime>
#include "vector.h"

int main() {
	using namespace std;
	using namespace VECTOR;
	unsigned int n1, n2;

	srand(time(0));

	cout << "The number of vector 1:  ";
	cin >> n1;
	Vector vector1(n1);

	cout << "The number of vector 2:  ";
	cin >> n2;
	Vector vector2(n2);

	if (n1 != n2) { return 0; }

	char symbol;
	double *a = new double[n1] {0};
	Vector vec(a, n1);
	double d = 0;

	cout << "輸入符號: ";

	while (cin >> symbol) {
		if (symbol == '+') {
			cout << "結果: " << endl;
			vec = vector1 + vector2;
			cout << vec;
		}
		else if (symbol == '*') {
			cout << "結果: " << endl;
			d = vector1 * vector2;
			cout << d;
		}
		else
			break;
	}
	
	vec.normalise();
	cout << vec;

	system("pause");
	return 0;
}
