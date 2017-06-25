#pragma once

#include <vector>
#include "ICollisionDetection.h"
#include "Segment.h"

namespace Collision 
{
	class LinearDetection : public ICollisionDetection {

		std::vector<Segment> allSegments;
	public:
		LinearDetection(std::vector<Segment>&);
		std::pair<Segment*, Point> getIntersection(Segment);
		~LinearDetection();
	};

}

