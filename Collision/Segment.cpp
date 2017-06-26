#include "Segment.h"
#include "Point.h"
#include <algorithm>
#include <limits>

namespace Collision
{

	Segment::Segment(Point first, Point second) : first(first), second(second) {

	}

	bool Segment::onSegment(Point p, Point q, Point r) {
		if (q.x <= std::max(p.x, r.x) && q.x >= std::min(p.x, r.x) &&
			q.y <= std::max(p.y, r.y) && q.y >= std::min(p.y, r.y))
			return true;
		return false;
	}

	bool operator==(const Segment& s, const Segment& t) {
		return s.first == t.first && s.second == t.second;
	}


	double Segment::evalX(double x) {
		double dx = (this->second.x - this->first.x);
		if (dx == 0) {
			return std::numeric_limits<double>::quiet_NaN();
		}
		double m = (this->second.y - this->first.y) / dx;
		return this->first.y = (m * (x - this->first.x)) + this->first.y;
	}


	Point Segment::intersectionPoint(Segment s) {

		double dx1 = this->second.x - this->first.x;
		double dx2 = s.second.x - s.first.x;
		
		// Both are vertical
		if (dx1 == 0 && dx1 == dx2) {
			auto NaN = std::numeric_limits<double>::quiet_NaN();
			return Point(NaN, NaN);
		}

		if (dx1 == 0) {
			return Point(this->first.x, s.evalX(this->first.x));
		}

		if (dx2 == 0) {
			return Point(s.first.x, this->evalX(s.first.x));
		}

		double m1 = (this->second.y - this->first.y) / dx1;
		double m2 = (s.second.y - s.first.y) / dx2;

		// They have the same slope
		if (m1 == m2) {
			auto NaN = std::numeric_limits<double>::quiet_NaN();
			return Point(NaN, NaN);
		}

		double x = (-this->first.y + s.first.y + (m1 * this->first.x) - (m2 * s.first.x)) / (m1 - m2);		
		double y = m1 * (x - this->first.x) + this->first.y;
		return Point(x, y);
	}


	int Segment::orientation(Point p, Point q, Point r) {
		float val = (q.y - p.y) * (r.x - q.x) -
			(q.x - p.x) * (r.y - q.y);
		if (val == 0) return 0;
		return (val > 0) ? 1 : 2;
	}

	bool Segment::intersects(Segment s) {
		Point& p1 = this->first;
		Point& q1 = this->second;
		Point& p2 = s.first;
		Point& q2 = s.second;
		int o1 = orientation(p1, q1, p2);
		int o2 = orientation(p1, q1, q2);
		int o3 = orientation(p2, q2, p1);
		int o4 = orientation(p2, q2, q1);

		if (o1 != o2 && o3 != o4)
			return true;

		if (o1 == 0 && onSegment(p1, p2, q1)) return true;
		if (o2 == 0 && onSegment(p1, q2, q1)) return true;
		if (o3 == 0 && onSegment(p2, p1, q2)) return true;
		if (o4 == 0 && onSegment(p2, q1, q2)) return true;
		return false;
	}

}
