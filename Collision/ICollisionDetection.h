#pragma once

#include "Segment.h"

namespace Collision 
{
	class ICollisionDetection {
	public:
		virtual ~ICollisionDetection() {};
		virtual std::pair<Segment*, Point> getIntersection(Segment query) = 0;
	};

}




