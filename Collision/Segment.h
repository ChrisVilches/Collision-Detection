#pragma once

#include "Point.h"

namespace Collision
{

	class Segment {
		bool onSegment(Point p, Point q, Point r);
		int orientation(Point p, Point q, Point r);
		double Segment::evalX(double);
	public:
		Point first;
		Point second;
		Point intersectionPoint(Segment);
		Segment(Point, Point);
		Segment();
		bool intersects(Segment);
		friend bool operator==(const Segment&, const Segment&);
		friend bool operator<(const Segment&, const Segment&);
		friend std::ostream& operator<<(std::ostream&, const Segment&);
	};

}