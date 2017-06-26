#pragma once
#include <vector>
#include "ICollisionDetection.h"
#include "Segment.h"
#include "Square.h"

namespace Collision
{

	struct QuadTreeNode {
		QuadTreeNode* child[4];
		std::vector<Segment> segments;
		QuadTreeNode() : child { NULL, NULL, NULL, NULL }
		{
		}
	};

	class QuadTreeDetection : public ICollisionDetection {		
		QuadTreeNode* root;
		void divide(QuadTreeNode* node, Square square);
		Square squareRange;
	public:
		QuadTreeDetection(std::vector<Segment>&);
		std::pair<Segment*, Point> getIntersection(Segment);
		~QuadTreeDetection();
		int countTotalSegments();
	};

}

