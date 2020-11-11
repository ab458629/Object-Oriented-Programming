#ifndef VECTOR_H
#define VECTOR_H
#include <iostream>

namespace VECTOR {
	using std::ostream;

	class Vector {
	private:
		double *v;
		unsigned int n; // the number of elements

	public:
		Vector();
		Vector(unsigned int);
		~Vector();
		Vector(double*, unsigned int);			// multi argument
		Vector(const Vector &);					// copy constructor
		Vector & operator =(const Vector&);		// assign operator
		Vector operator +(const Vector&);
		double operator *(const Vector&) const;
		void normalise();
		friend std::ostream& operator<<(std::ostream&, const Vector&);
	};

}

#endif // !VECTOR_H
