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
		Point intersectionPoint(Segment s);
		Segment(Point, Point);
		bool intersects(Segment);
		friend bool operator==(const Segment&, const Segment&);
	};

}