#pragma once

#include "Point.h"
#include "Segment.h"

namespace Collision
{
	class Square
	{
	public:
		Point bottomLeftPoint;
		double sideLength;
		Square getQuadrant(int num);
		Square(Point, double);
		~Square();
		bool containsPoint(Point);
		bool Square::containsSegment(Segment);
	};
}

