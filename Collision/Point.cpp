#include "Point.h"
#include <cmath>

namespace Collision
{

	Point::Point(double x, double y) :
		x{ x }, y{ y } {
	}

	Point::Point() : x{ 0 }, y{ 0 } {

	}
	
	double distance(const Point& p, const Point& q) {
		return sqrt(pow(p.x - q.x, 2) + pow(p.y - q.y, 2));
	}

	bool operator<(const Point& p, const Point& q) {
		return (p.x < q.x) || (p.x == q.x && p.y < q.y);
	}

	bool operator==(const Point& p, const Point& q) {
		return p.x == q.x && p.y == q.y;
	}

	std::ostream& operator<<(std::ostream &os, const Point& p) {
		return os << "(" << p.x << ", " << p.y << ")";
	}

}
