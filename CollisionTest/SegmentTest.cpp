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
	TEST_CLASS(SegmentTest)
	{
	public:

		TEST_METHOD(SegmentConstructor)
		{
			Segment s(Point(-11, 0.444), Point(6767667.67676, 1111.1199));
			Assert::IsTrue(s.first.x == -11 && s.first.y == 0.444);
			Assert::IsTrue(s.second.x == 6767667.67676 && s.second.y == 1111.1199);
		}

		TEST_METHOD(SegmentCopy)
		{
			Segment s(Point(-11, 0.444), Point(6767667.67676, 1111.1199));
			Segment z = s;
			z.first.x++;
			z.second.y++;
			Assert::IsTrue(s.first.x == -11 && s.first.y == 0.444);
			Assert::IsTrue(s.second.x == 6767667.67676 && s.second.y == 1111.1199);
			Assert::IsTrue(z.first.x == -10 && z.first.y == 0.444);
			Assert::IsTrue(z.second.x == 6767667.67676 && z.second.y == 1112.1199);
		}

		TEST_METHOD(SegmentIntersect)
		{
			Segment a(Point(0, 5), Point(10, 5));
			Segment b(Point(1, 0), Point(1, 20));
			Assert::IsTrue(a.intersects(b));

			Segment c(Point(0, 5), Point(10, 5));
			Segment d(Point(0, 6), Point(10, 6));
			Assert::IsFalse(c.intersects(d));

			Segment e(Point(0, 5), Point(10, 5));
			Segment f(Point(0, 6), Point(10.1, 5));
			Assert::IsFalse(e.intersects(f));
			
			Segment g(Point(0, 5), Point(10, 5));
			Segment h(Point(0, 6), Point(10.1, 4));
			Assert::IsTrue(g.intersects(h));
		}

		TEST_METHOD(SegmentIntersectionPoint)
		{
			Segment a(Point(-10, -10), Point(10, 10));
			Segment b(Point(-10, 0), Point(10, 0));
			Assert::IsTrue(a.intersectionPoint(b) == Point(0, 0));

			Segment c(Point(0, 0), Point(-1, 2));
			Segment d(Point(-0.5, 0), Point(0, 1));
			Assert::IsTrue(c.intersectionPoint(d) == Point(-0.25, 0.5));

			Segment e(Point(0, 0), Point(-0.5, 2));
			Segment f(Point(-1, 0), Point(0, 1));
			Assert::IsTrue(e.intersectionPoint(f) == Point(-0.2, 0.8));
		}

		TEST_METHOD(SegmentIntersectionPoint_Parallel)
		{
			auto NaN = std::numeric_limits<double>::quiet_NaN();

			Segment a(Point(0, 0), Point(5, 5));
			Segment b(Point(0, 5), Point(5, 10));
			Assert::IsTrue(std::isnan(a.intersectionPoint(b).x));
			Assert::IsTrue(std::isnan(a.intersectionPoint(b).y));

			Segment c(Point(5, -10), Point(5, 10));
			Segment d(Point(6, -10), Point(6, 10));
			Assert::IsTrue(std::isnan(c.intersectionPoint(d).x));
			Assert::IsTrue(std::isnan(c.intersectionPoint(d).y));
		}

		TEST_METHOD(SegmentIntersectionPoint_Vertical)
		{
			Segment a(Point(5, -10), Point(5, 10));
			Segment b(Point(0, 0), Point(5, 5));
			Assert::IsTrue(a.intersectionPoint(b) == Point(5, 5));

			Segment c(Point(3, -10), Point(3, 10));
			Segment d(Point(0, 0), Point(10, 5));
			Assert::IsTrue(c.intersectionPoint(d) == Point(3, 1.5));

			Segment e(Point(0, 2), Point(2, 0));
			Segment f(Point(0.5, 0), Point(0.5, 1));
			Assert::IsTrue(e.intersectionPoint(f) == Point(0.5, 1.5));
		}


	};
}