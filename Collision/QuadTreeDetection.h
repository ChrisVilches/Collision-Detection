#pragma once
#include <vector>
#include "ICollisionDetection.h"
#include "Segment.h"


namespace Collision
{

	struct QuadTreeNode {
		QuadTreeNode* child[4];
		std::vector<Segment> segments;
		QuadTreeNode()
		{
			child[0] = NULL;
			child[1] = NULL;
			child[2] = NULL;
			child[3] = NULL;
		}
	};


	class QuadTreeDetection : public ICollisionDetection {		
		QuadTreeNode* root;
		void divide(QuadTreeNode* node, Point squarePt, double side);
		Point squareRange;
		double sideSquareRange;
	public:
		QuadTreeDetection(std::vector<Segment>&);
		std::pair<Segment*, Point> getIntersection(Segment);
		~QuadTreeDetection();
		int countTotalSegments();
	};

}

