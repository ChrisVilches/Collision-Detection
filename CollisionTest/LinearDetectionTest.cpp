#include "stdafx.h"
#include "CppUnitTest.h"
#include "../Collision/LinearDetection.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace Collision;

namespace CollisionTest
{
	TEST_CLASS(LinearDetectionTest)
	{
	public:

		TEST_METHOD(LinearDetection_NoIntersection)
		{
			std::vector<Segment> segments;
			segments.push_back(Segment(Point(1, 1), Point(1, 10)));
			segments.push_back(Segment(Point(2, 1), Point(2, 10)));
			segments.push_back(Segment(Point(3, 1), Point(3, 10)));
			segments.push_back(Segment(Point(4, 1), Point(4, 10)));
			segments.push_back(Segment(Point(5, 1), Point(5, 10)));
			LinearDetection ld(segments);

			auto result1 = ld.getIntersection(Segment(Point(3.00000000001, 1), Point(3.9999999999, 10)));
			Assert::IsTrue(result1.first == NULL);

			auto result2 = ld.getIntersection(Segment(Point(5.00000000001, 1), Point(5.9999999999, 1)));
			Assert::IsTrue(result2.first == NULL);

			auto result3 = ld.getIntersection(Segment(Point(5.00000000001, 1), Point(5.00000000001, 10)));
			Assert::IsTrue(result3.first == NULL);

			auto result4 = ld.getIntersection(Segment(Point(0, 10), Point(100, 10.00000000001)));
			Assert::IsTrue(result4.first == NULL);
		}

		TEST_METHOD(LinearDetection_YesIntersectionVertical)
		{
			std::vector<Segment> segments;
			segments.push_back(Segment(Point(1, 1), Point(1, 10)));
			segments.push_back(Segment(Point(2, 1), Point(2, 10)));
			segments.push_back(Segment(Point(3, 1), Point(3, 10)));
			segments.push_back(Segment(Point(4, 1), Point(4, 10)));
			segments.push_back(Segment(Point(5, 1), Point(5, 10)));
			LinearDetection ld(segments);

			auto result1 = ld.getIntersection(Segment(Point(-1, 5), Point(11, 5)));
			Assert::IsTrue(*result1.first == Segment(Point(1, 1), Point(1, 10)));
			Assert::IsTrue(result1.second == Point(1, 5));

			auto result2 = ld.getIntersection(Segment(Point(1.00000001, 5), Point(3.00001, 5)));
			Assert::IsTrue(*result2.first == Segment(Point(2, 1), Point(2, 10)));
			Assert::IsTrue(result2.second == Point(2, 5));
		}

		TEST_METHOD(LinearDetection_YesIntersectionSlope)
		{
			std::vector<Segment> segments;
			segments.push_back(Segment(Point(0, 0), Point(1, 1)));
			segments.push_back(Segment(Point(2, 0), Point(3, 5)));
			segments.push_back(Segment(Point(6, 0), Point(4, 2)));
			LinearDetection ld(segments);
			auto result = ld.getIntersection(Segment(Point(0, 5.5), Point(5.5, 0)));
			Assert::IsTrue(*result.first == Segment(Point(2, 0), Point(3, 5)));
			Assert::IsTrue(std::abs(result.second.x - 2.58333) < 0.00001);
			Assert::IsTrue(std::abs(result.second.y - 2.91667) < 0.00001);
		}
	};
}
