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
		bool contains(Point);
		bool contains(Segment);
		bool intersects(Segment);
		friend std::ostream& operator<<(std::ostream&, const Square&);


	};
}

