#include "stdafx.h"
#include "CppUnitTest.h"
#include "../Collision/Segment.h"
#include "../Collision/Point.h"
#include "../Collision/Square.h"
#include <cmath>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace Collision;

namespace CollisionTest
{
	TEST_CLASS(SquareTest)
	{
	public:

		TEST_METHOD(Square_SegmentInside)
		{
			Segment a(Point(5, -10), Point(5, 10));
			Segment b(Point(0, 0), Point(5, 5));
			Segment c(Point(1, 5), Point(-5.6, 97));

			Assert::IsTrue(Square(Point(0, -10), 20).containsSegment(a));
			Assert::IsFalse(Square(Point(0, -10.0000000001), 20).containsSegment(a));

			Assert::IsTrue(Square(Point(0, 0), 5).containsSegment(b));
			Assert::IsFalse(Square(Point(0, 0), 4.9999999).containsSegment(b));

			Assert::IsTrue(Square(Point(-5.6, 5), 92).containsSegment(c));
			Assert::IsFalse(Square(Point(-5.59999, 5), 92).containsSegment(c));

		}


	};
}