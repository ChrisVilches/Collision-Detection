#include "stdafx.h"
#include "CppUnitTest.h"
#include <cstdlib>
#include "../Collision/ICollisionDetection.h"
#include "../Collision/QuadTreeDetection.h"
#include "../Collision/LinearDetection.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace Collision;

#define RANDOM(n) (double)(rand() % n)

namespace CollisionTest
{
	TEST_CLASS(ICollisionDetectionTest)
	{
	public:

		TEST_METHOD(All_Implementations_Test)
		{
			int queries = 2000;
			int nSegments = 10000;
			srand(2222222);
			std::vector<Segment> segments;					

			for (int i = 0; i < nSegments; i++) {
				segments.push_back(Segment(
					Point(RANDOM(1000), RANDOM(1000)),
					Point(RANDOM(1000), RANDOM(1000))));
			}
			
			QuadTreeDetection qd(segments);
			LinearDetection ld(segments);

			Assert::IsTrue(qd.countTotalSegments() == nSegments);

			// Test random queries and check results for all ICollisionDetection implementations are the same
			for (int i = 0; i < queries; i++) {				

				Segment query = Segment(Point(RANDOM(1000), RANDOM(1000)), Point(RANDOM(1000), RANDOM(1000)));

				auto resultQd = qd.getIntersection(query);
				auto resultLd = ld.getIntersection(query);				

				if (resultQd.first == NULL || resultLd.first == NULL) {
					Assert::IsTrue(resultQd.first == resultLd.first);
				} else {
					Assert::IsTrue(*resultQd.first == *resultLd.first);
					Assert::IsTrue(resultQd.second == resultLd.second);
				}
			}
		}
	};
}
