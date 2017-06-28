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


		TEST_METHOD(LinearDetection_YesIntersection_Many)
		{

			std::vector<Segment> segments;
			for (int i = 0; i < 100; i++) {
				for (int j = 0; j < 100; j++) {
					segments.push_back(Segment(Point(j, i), Point(j + 1, i + 1)));
				}
			}
			LinearDetection ld(segments);

			auto result = ld.getIntersection(Segment(Point(0, 0.5), Point(0.5, 0)));
			Assert::IsTrue(*result.first == Segment(Point(0, 0), Point(1, 1)));
			Assert::IsTrue(result.second.x == 0.25);
			Assert::IsTrue(result.second.y == 0.25);

			auto result2 = ld.getIntersection(Segment(Point(8.315, 8.63), Point(10, 12)));
			Assert::IsTrue(*result2.first == Segment(Point(8, 9), Point(9, 10)));
			Assert::IsTrue(std::abs(result2.second.x - 9) < 0.00001);
			Assert::IsTrue(std::abs(result2.second.y - 10) < 0.00001);

			auto result3 = ld.getIntersection(Segment(Point(69.8, 64.9), Point(70.2, 65.1)));
			Assert::IsTrue(*result3.first == Segment(Point(69, 64), Point(70, 65)));
			Assert::IsTrue(std::abs(result3.second.x - 70) < 0.00001);
			Assert::IsTrue(std::abs(result3.second.y - 65) < 0.00001);
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


		TEST_METHOD(LinearDetection_YesIntersection_Time)
		{

			std::vector<Segment> segments;

			for (int i = 0; i < 100; i++) {
				for (int j = 0; j < 100; j++) {
					segments.push_back(Segment(Point(j, i), Point(j + 1, i + 1)));
				}
			}
			LinearDetection ld(segments);

			for (int i = 0; i < 600; i++) {
				ld.getIntersection(Segment(Point(0, 0.5), Point(0.5, 0)));
			}

		}


		TEST_METHOD(LinearDetection_YesIntersection_Time2)
		{

			std::vector<Segment> segments;

			for (int i = 0; i < 100; i++) {
				for (int j = 0; j < 100; j++) {
					segments.push_back(Segment(Point(j, i), Point(j + 1, i + 1)));
				}
			}
			LinearDetection ld(segments);

			for (int i = 0; i < 600; i++) {
				ld.getIntersection(Segment(Point(0.5, 0.5), Point(97.8, 97.6)));
			}
		}

		TEST_METHOD(LinearDetection_YesIntersection_Time3)
		{

			std::vector<Segment> segments;

			for (int i = 0; i < 100; i++) {
				for (int j = 0; j < 100; j++) {
					segments.push_back(Segment(Point(j, i), Point(j + 1, i + 1)));
				}
			}
			LinearDetection ld(segments);

			for (int i = 0; i < 1000; i++) {
				ld.getIntersection(Segment(Point(0.5, 0.5), Point(97.8, 97.6)));
			}
		}


	};
}
