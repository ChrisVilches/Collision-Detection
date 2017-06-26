#pragma once

namespace Collision
{
	class Point {
	public:
		double x;
		double y;
		Point(double, double);
		Point();
		bool insideSquare(Point bottomLeftCorner, double side);
		friend double distance(const Point&, const Point&);
		friend bool operator<(const Point&, const Point&);
		friend bool operator==(const Point&, const Point&);
	};

}


