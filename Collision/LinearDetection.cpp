#include "LinearDetection.h"
#include "Segment.h"
#include <vector>
#include <cstddef>

namespace Collision
{

	LinearDetection::LinearDetection(std::vector<Segment>& allSegments) {
		this->allSegments = allSegments;
	}

	std::pair<Segment*, Point> LinearDetection::getIntersection(Segment query) {

		Point& startPoint = query.first;
		Point intersectionPoint(0, 0);
		double minDist = std::numeric_limits<double>::max();
		Point closest(0, 0);
		Segment* segmentIntersection = NULL;

		for (unsigned int i = 0; i < allSegments.size(); i++) {
			if (allSegments[i].intersects(query)) {

				intersectionPoint = allSegments[i].intersectionPoint(query);
				
				double dist = distance(startPoint, intersectionPoint);
				if (dist < minDist) {
					minDist = dist;
					closest = intersectionPoint;
					segmentIntersection = &allSegments[i];
				}
			}
		}

		return std::make_pair(segmentIntersection, closest);
	}

	LinearDetection::~LinearDetection() {
	}

}
