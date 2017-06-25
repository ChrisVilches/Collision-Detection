#include "stdafx.h"
#include "CppUnitTest.h"
#include "../Collision/Point.h"
#include <cmath>
#include <vector>
#include <algorithm>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace Collision;

namespace CollisionTest
{		
	TEST_CLASS(PointTest)
	{
	public:
		
		TEST_METHOD(PointConstructor)
		{
			Point a(4, 5);
			Assert::IsTrue(a.x == 4 && a.y == 5);

			Point b(-4, 0);
			Assert::IsTrue(b.x == -4 && b.y == 0);

			Point c(4.345345, 5.0000001);
			Assert::IsTrue(c.x == 4.345345 && c.y == 5.0000001);			
		}

		TEST_METHOD(PointCopy)
		{
			Point a(4.345345, 5.0000001);
			Point b = a;
			b.x++;
			Assert::IsTrue(a.x == 4.345345 && a.y == 5.0000001);
			Assert::IsTrue(b.x == 5.345345 && b.y == 5.0000001);
		}

		TEST_METHOD(PointDistance)
		{
			Point a(4.345345, 5.0000001);
			Point b(0.234, -2.33333);			
			Assert::IsTrue(std::abs(distance(a, b) - 8.40719) < 0.001);
			
			Point c(-4.34534345, 5.023000001);
			Point d(-230.2342, -2.33777999);
			Assert::IsTrue(std::abs(distance(c, d) - 226.009) < 0.001);			
		}

		TEST_METHOD(PointSort)
		{
			std::vector<Point> points;
			points.push_back(Point(0, 0));
			points.push_back(Point(0, 2));
			points.push_back(Point(0, 1));
			points.push_back(Point(2, -8));
			points.push_back(Point(5, 3));
			points.push_back(Point(5, 2));
			points.push_back(Point(-1, 5));
			points.push_back(Point(2, 1));

			std::sort(points.begin(), points.end());

			Assert::IsTrue(points[0] == Point(-1, 5));
			Assert::IsTrue(points[1] == Point(0, 0));
			Assert::IsTrue(points[2] == Point(0, 1));
			Assert::IsTrue(points[3] == Point(0, 2));
			Assert::IsTrue(points[4] == Point(2, -8));
			Assert::IsTrue(points[5] == Point(2, 1));
			Assert::IsTrue(points[6] == Point(5, 2));
			Assert::IsTrue(points[7] == Point(5, 3));
		}

	};
}