#include "Square.h"
#include "Point.h"
#include <stdexcept>

namespace Collision
{

	Square::Square(Point pt, double side) : bottomLeftPoint(pt), sideLength(side)
	{
	}

	Square Square::getQuadrant(int num) {
		Square ret = *this;
		ret.sideLength /= 2;
		switch (num) {
		case 0:
			break;
		case 1:
			ret.bottomLeftPoint.x += ret.sideLength;
			break;
		case 2:
			ret.bottomLeftPoint.x += ret.sideLength;
			ret.bottomLeftPoint.y += ret.sideLength;
			break;
		case 3:
			ret.bottomLeftPoint.y += ret.sideLength;
			break;
		default:
			throw std::invalid_argument("invalid quadrant index");
		}
		return ret;
	}
	

	bool Square::contains(Point point) {
		return
			bottomLeftPoint.y <= point.y &&
			point.y <= bottomLeftPoint.y + sideLength &&
			bottomLeftPoint.x <= point.x &&
			point.x <= bottomLeftPoint.x + sideLength;
	}

	bool Square::contains(Segment segment) {
		return contains(segment.first) && contains(segment.second);
	}
	
	bool Square::intersects(Segment segment) {

		double x = bottomLeftPoint.x;
		double y = bottomLeftPoint.y;

		return contains(segment.first) || contains(segment.second) ||
			Segment(Point(x, y), Point(x + sideLength, y)).intersects(segment) ||
			Segment(Point(x, y), Point(x, y + sideLength)).intersects(segment) ||
			Segment(Point(x, y + sideLength), Point(x + sideLength, y + sideLength)).intersects(segment) ||
			Segment(Point(x + sideLength, y), Point(x + sideLength, y + sideLength)).intersects(segment);
	}

	Square::~Square()
	{
	}

}
