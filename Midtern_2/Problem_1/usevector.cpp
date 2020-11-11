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

	cout << "\n";
	Vector c_vector1(vector1);
	Vector c_vector2(vector2);

	cout << "\n\n";
	cout << "Asign vector2 to vector1" << endl;
	c_vector1 = c_vector2;
	cout << "\n";

	cout << "Assign (1, 2, 3) to vector3" << endl;
	double *arr = new double[3]{ 1, 2, 3 };
	Vector vector3(arr, sizeof(arr));
	
	system("pause");
	return 0;
}
