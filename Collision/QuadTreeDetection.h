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

		// Global data for recursive call
		Point queryIntersectionPoint;
		double queryMinDist;
		Point queryClosest;
		Segment* querySegmentIntersection;
		Segment query;
		void QuadTreeDetection::traverse(QuadTreeNode* node, Square square);
		QuadTreeNode* root = NULL;
		Square squareRange;
		

	public:
		QuadTreeDetection(std::vector<Segment>&);
		std::pair<Segment*, Point> getIntersection(Segment);
		~QuadTreeDetection();
		long countTotalSegments();
		long countNodes();
	};

}

