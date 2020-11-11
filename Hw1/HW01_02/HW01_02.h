#pragma once
#include <string>

namespace MyGeometry {
	struct Point{
		float x;
		float y;
		double Length();
		std::string CoutPoint();
	};

	Point * LoadPoint(const char*, unsigned int &);
	int MinDistance(Point *, int);
	Point * SortbyLength(Point *, int);
	void Report(const char *);
}