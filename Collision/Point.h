#pragma once

#include <ostream>

namespace Collision
{
	class Point {
	public:
		double x;
		double y;
		Point(double, double);
		Point();		
		friend double distance(const Point&, const Point&);
		friend bool operator<(const Point&, const Point&);
		friend bool operator==(const Point&, const Point&);
		friend std::ostream& operator<<(std::ostream&, const Point&);
	};

}


