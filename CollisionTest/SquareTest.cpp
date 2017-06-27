#include "stdafx.h"
#include "CppUnitTest.h"
#include "../Collision/Segment.h"
#include "../Collision/Point.h"
#include "../Collision/Square.h"
#include <cmath>
#include <exception>

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

			Assert::IsTrue(Square(Point(0, -10), 20).contains(a));
			Assert::IsFalse(Square(Point(0, -10.0000000001), 20).contains(a));

			Assert::IsTrue(Square(Point(0, 0), 5).contains(b));
			Assert::IsFalse(Square(Point(0, 0), 4.9999999).contains(b));

			Assert::IsTrue(Square(Point(-5.6, 5), 92).contains(c));
			Assert::IsFalse(Square(Point(-5.59999, 5), 92).contains(c));
		}

		TEST_METHOD(Square_QuadrantWrongArgument)
		{
			Square s(Point(1, 2), 10);

			int c = 0;

			for (int i = -2; i < 5; i++) {

				try {
					s.getQuadrant(i);
				}
				catch (std::exception e) {
					c++;
				}
			}

			// -2, -1, 4
			Assert::IsTrue(c == 3);
		}

		TEST_METHOD(Square_QuadrantCorrectArgument)
		{
			Square s(Point(1, 2), 10);

			Square s0 = s.getQuadrant(0);
			Square s1 = s.getQuadrant(1);
			Square s2 = s.getQuadrant(2);
			Square s3 = s.getQuadrant(3);

			Assert::IsTrue(s0.bottomLeftPoint == Point(1, 2));
			Assert::IsTrue(s0.sideLength == 5);

			Assert::IsTrue(s1.bottomLeftPoint == Point(6, 2));
			Assert::IsTrue(s1.sideLength == 5);

			Assert::IsTrue(s2.bottomLeftPoint == Point(6, 7));
			Assert::IsTrue(s2.sideLength == 5);

			Assert::IsTrue(s3.bottomLeftPoint == Point(1, 7));
			Assert::IsTrue(s3.sideLength == 5);

			Square s21 = s2.getQuadrant(1);

			Assert::IsTrue(s21.bottomLeftPoint == Point(8.5, 7));
			Assert::IsTrue(s21.sideLength == 2.5);
		}


	};
}