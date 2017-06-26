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
			throw std::invalid_argument("invalid quadrant value");
		}
		return ret;
	}
	

	bool Square::containsPoint(Point point) {
		return
			bottomLeftPoint.y <= point.y &&
			point.y <= bottomLeftPoint.y + sideLength &&
			bottomLeftPoint.x <= point.x &&
			point.x <= bottomLeftPoint.x + sideLength;
	}

	bool Square::containsSegment(Segment segment) {
		return containsPoint(segment.first) && containsPoint(segment.second);
	}

	Square::~Square()
	{
	}

}
