#pragma once
#include <vector>
#include "ICollisionDetection.h"
#include "Segment.h"


namespace Collision
{
	class TreeDetection : public ICollisionDetection {
		
	public:
		TreeDetection(std::vector<Segment>&);
		std::pair<Segment*, Point> getIntersection(Segment);
		~TreeDetection();
	};

}

