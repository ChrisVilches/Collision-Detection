#include "stdafx.h"
#include "CppUnitTest.h"
#include "../Collision/QuadTreeDetection.h"
#include <sstream>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace Collision;

namespace CollisionTest
{
	TEST_CLASS(QuadTreeDetectionTest)
	{
	public:

		TEST_METHOD(QuadTreeDetection_NoIntersection)
		{
			std::vector<Segment> segments;
			segments.push_back(Segment(Point(1, 1), Point(1, 10)));
			segments.push_back(Segment(Point(2, 1), Point(2, 10)));
			segments.push_back(Segment(Point(3, 1), Point(3, 10)));
			segments.push_back(Segment(Point(4, 1), Point(4, 10)));
			segments.push_back(Segment(Point(5, 1), Point(5, 10)));
			QuadTreeDetection qt(segments);
			Assert::IsTrue(qt.countTotalSegments() == segments.size());

			auto result1 = qt.getIntersection(Segment(Point(3.00000000001, 1), Point(3.9999999999, 10)));
			Assert::IsTrue(result1.first == NULL);

			auto result2 = qt.getIntersection(Segment(Point(5.00000000001, 1), Point(5.9999999999, 1)));
			Assert::IsTrue(result2.first == NULL);

			auto result3 = qt.getIntersection(Segment(Point(5.00000000001, 1), Point(5.00000000001, 10)));
			Assert::IsTrue(result3.first == NULL);

			auto result4 = qt.getIntersection(Segment(Point(0, 10), Point(100, 10.00000000001)));
			Assert::IsTrue(result4.first == NULL);
		}


		TEST_METHOD(QuadTreeDetection_YesIntersectionVertical)
		{
			std::vector<Segment> segments;
			segments.push_back(Segment(Point(1, 1), Point(1, 10)));
			segments.push_back(Segment(Point(2, 1), Point(2, 10)));
			segments.push_back(Segment(Point(3, 1), Point(3, 10)));
			segments.push_back(Segment(Point(4, 1), Point(4, 10)));
			segments.push_back(Segment(Point(5, 1), Point(5, 10)));
			segments.push_back(Segment(Point(50, 10), Point(50, 100)));
			QuadTreeDetection qt(segments);
			Assert::IsTrue(qt.countTotalSegments() == segments.size());

			auto result1 = qt.getIntersection(Segment(Point(-1, 5), Point(11, 5)));
			Assert::IsTrue(*result1.first == Segment(Point(1, 1), Point(1, 10)));
			Assert::IsTrue(result1.second == Point(1, 5));
			
			auto result2 = qt.getIntersection(Segment(Point(1.00000001, 5), Point(3.00001, 5)));
			Assert::IsTrue(*result2.first == Segment(Point(2, 1), Point(2, 10)));
			Assert::IsTrue(result2.second == Point(2, 5));
		}

		TEST_METHOD(QuadTreeDetection_YesIntersectionSlope)
		{
			std::vector<Segment> segments;
			segments.push_back(Segment(Point(0, 0), Point(1, 1)));
			segments.push_back(Segment(Point(2, 0), Point(3, 5)));
			segments.push_back(Segment(Point(6, 0), Point(4, 2)));
			segments.push_back(Segment(Point(5000, 1000), Point(5000, 10000)));
			QuadTreeDetection qt(segments);
			Assert::IsTrue(qt.countTotalSegments() == segments.size());

			auto result = qt.getIntersection(Segment(Point(0, 5.5), Point(5.5, 0)));
			Assert::IsTrue(*result.first == Segment(Point(2, 0), Point(3, 5)));
			Assert::IsTrue(std::abs(result.second.x - 2.58333) < 0.00001);
			Assert::IsTrue(std::abs(result.second.y - 2.91667) < 0.00001);
		}

		TEST_METHOD(QuadTreeDetection_YesIntersection_ManyNodes)
		{
			std::vector<Segment> segments;
			for (int i = 0; i < 100; i++) {
				for (int j = 0; j < 100; j++) {
					segments.push_back(Segment(Point(j, i), Point(j + 1, i + 1)));
				}
			}
			QuadTreeDetection qt(segments);
			Assert::IsTrue(qt.countTotalSegments() == 100 * 100);			

			auto result = qt.getIntersection(Segment(Point(0, 0.5), Point(0.5, 0)));
			Assert::IsTrue(*result.first == Segment(Point(0, 0), Point(1, 1)));
			Assert::IsTrue(result.second.x == 0.25);
			Assert::IsTrue(result.second.y == 0.25);

			auto result2 = qt.getIntersection(Segment(Point(8.315, 8.63), Point(10, 12)));
			Assert::IsTrue(*result2.first == Segment(Point(8, 9), Point(9, 10)));
			Assert::IsTrue(std::abs(result2.second.x - 9) < 0.00001);
			Assert::IsTrue(std::abs(result2.second.y - 10) < 0.00001);

			auto result3 = qt.getIntersection(Segment(Point(69.8, 64.9), Point(70.2, 65.1)));
			Assert::IsTrue(*result3.first == Segment(Point(70, 65), Point(71, 66)));
			Assert::IsTrue(std::abs(result3.second.x - 70) < 0.00001);
			Assert::IsTrue(std::abs(result3.second.y - 65) < 0.00001);		

			auto result4 = qt.getIntersection(Segment(Point(4, 5), Point(67, 90)));
			Assert::IsTrue(*result4.first == Segment(Point(3, 4), Point(4, 5)));
			Assert::IsTrue(std::abs(result4.second.x - 4) < 0.00001);
			Assert::IsTrue(std::abs(result4.second.y - 5) < 0.00001);

			auto result5 = qt.getIntersection(Segment(Point(29.5, 30.895), Point(33.001, 27.6898)));
			Assert::IsTrue(*result5.first == Segment(Point(29, 30), Point(30, 31)));
			Assert::IsTrue(std::abs(result5.second.x - 29.7062) < 0.0001);
			Assert::IsTrue(std::abs(result5.second.y - 30.7062) < 0.0001);
		
		}


		TEST_METHOD(QuadTreeDetection_YesIntersection_Time)
		{

			std::vector<Segment> segments;

			for (int i = 0; i < 100; i++) {
				for (int j = 0; j < 100; j++) {
					segments.push_back(Segment(Point(j, i), Point(j + 1, i + 1)));
				}
			}
			QuadTreeDetection qt(segments);

			for (int i = 0; i < 600; i++) {
				qt.getIntersection(Segment(Point(0, 0.5), Point(0.5, 0)));
			}
		}

		TEST_METHOD(QuadTreeDetection_YesIntersection_Time2)
		{

			std::vector<Segment> segments;

			for (int i = 0; i < 100; i++) {
				for (int j = 0; j < 100; j++) {
					segments.push_back(Segment(Point(j, i), Point(j + 1, i + 1)));
				}
			}
			QuadTreeDetection qt(segments);

			for (int i = 0; i < 600; i++) {
				qt.getIntersection(Segment(Point(0.5, 0.5), Point(97.8, 97.6)));
			}
		}

		TEST_METHOD(QuadTreeDetection_YesIntersection_Time3)
		{

			std::vector<Segment> segments;

			for (int i = 0; i < 100; i++) {
				for (int j = 0; j < 100; j++) {
					segments.push_back(Segment(Point(j, i), Point(j + 1, i + 1)));
				}
			}
			QuadTreeDetection qt(segments);

			for (int i = 0; i < 1000; i++) {
				qt.getIntersection(Segment(Point(0.5, 0.5), Point(97.8, 97.6)));
			}
		}


		TEST_METHOD(QuadTreeDetection_DoesntCrossLine)
		{

			std::vector<Segment> seg;
			std::vector<Segment> queries;
			seg.push_back(Segment(Point(1000, 0), Point(1000, 1000)));
			
			QuadTreeDetection qt(seg);

			queries.push_back(Segment(Point(1000, 568), Point(2000, 800)));
			queries.push_back(Segment(Point(0, 540), Point(2000, 999)));
			queries.push_back(Segment(Point(10, 9.55), Point(2000, 1000)));
			queries.push_back(Segment(Point(100, 98.78), Point(2000, 0)));
			queries.push_back(Segment(Point(578, 985.6), Point(2000, 456)));
			queries.push_back(Segment(Point(958.89, 54), Point(2000, 555)));
			queries.push_back(Segment(Point(515.05555, 777), Point(2000, 756)));
			queries.push_back(Segment(Point(666.88, 666), Point(2000, 235)));
			queries.push_back(Segment(Point(119.777, 888), Point(2000, 858)));			

			for (const Segment& query : queries) {
				auto result = qt.getIntersection(query);
				Assert::IsTrue(result.first != NULL);
				Assert::IsTrue(result.second.x == 1000);
				Assert::IsTrue(result.second.y >= 0);
				Assert::IsTrue(result.second.y <= 1000);
			}
		}




	};
}
