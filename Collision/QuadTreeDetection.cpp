#include "QuadTreeDetection.h"
#include <algorithm>
#include <limits>
#include <functional>
#include "Square.h"

namespace Collision
{

	QuadTreeDetection::QuadTreeDetection(std::vector<Segment>& allSegments) : squareRange(Point(0, 0), 0) {

		root = new QuadTreeNode();

		double miny = std::numeric_limits<double>::max();
		double maxy = std::numeric_limits<double>::min();
		double minx = std::numeric_limits<double>::max();
		double maxx = std::numeric_limits<double>::min();

		for (const Segment& seg : allSegments) {
			miny = std::min(miny, seg.first.y);
			minx = std::min(minx, seg.first.x);
			maxy = std::max(maxy, seg.first.y);
			maxx = std::max(maxx, seg.first.x);
			miny = std::min(miny, seg.second.y);
			minx = std::min(minx, seg.second.x);
			maxy = std::max(maxy, seg.second.y);
			maxx = std::max(maxx, seg.second.x);
		}

		squareRange = Square(Point(minx, miny), std::max(maxx - minx, maxy - miny));

		std::function<void(Segment, QuadTreeNode*, Square)> addToTree;

		addToTree = [&addToTree](Segment segment, QuadTreeNode* node, Square square) {

			bool added = false;
			
			for (int i = 0; i < 4; i++) {
				if (square.getQuadrant(i).contains(segment)) {
					if(node->child[i] == NULL)
						node->child[i] = new QuadTreeNode();
					addToTree(segment, node->child[i], square.getQuadrant(i));
					added = true;
					break;
				}
			}
			if (!added) {
				node->segments.push_back(segment);
			}
		};

		for (const Segment& seg : allSegments) {			
			addToTree(seg, root, squareRange);
		}		
	}


	

	void QuadTreeDetection::traverse(QuadTreeNode* node, Square square) {

		if (node == NULL) 
			return;

		if (!square.intersects(query))
			return;

		unsigned int size = node->segments.size();
		for (unsigned int i = 0; i < size; i++) {			
			if (node->segments[i].intersects(query)) {
				queryIntersectionPoint = node->segments[i].intersectionPoint(query);
				double dist = distance(query.first, queryIntersectionPoint);
				if (dist < queryMinDist) {
					queryMinDist = dist;
					queryClosest = queryIntersectionPoint;
					querySegmentIntersection = &node->segments[i];
				}
			}
		}
	

		traverse(node->child[0], square.getQuadrant(0));
		traverse(node->child[1], square.getQuadrant(1));
		traverse(node->child[2], square.getQuadrant(2));
		traverse(node->child[3], square.getQuadrant(3));
	}
	
	
	std::pair<Segment*, Point> QuadTreeDetection::getIntersection(Segment q) {
		query = q;
		queryMinDist = std::numeric_limits<double>::max();
		querySegmentIntersection = NULL;
		traverse(root, squareRange);
		return std::make_pair(querySegmentIntersection, queryClosest);
	}




	long QuadTreeDetection::countTotalSegments() {

		std::function<long(QuadTreeNode*)> count;
		count = [&count](QuadTreeNode* node)->long {
			if (node == NULL)
				return 0;	
			return (long)node->segments.size() + 
				count(node->child[0]) +
				count(node->child[1]) +
				count(node->child[2]) +
				count(node->child[3]);
		};

		return count(root);
	}


	long QuadTreeDetection::countNodes() {

		std::function<long(QuadTreeNode*)> count;
		count = [&count](QuadTreeNode* node)->long {
			if (node == NULL)
				return 0;
			return 1 +
				count(node->child[0]) +
				count(node->child[1]) +
				count(node->child[2]) +
				count(node->child[3]);
		};
		
		return count(root);

	}


	QuadTreeDetection::~QuadTreeDetection() {
		std::function<void(QuadTreeNode* node)> destroyTree;
		destroyTree = [&destroyTree](QuadTreeNode* node){
			if (node == NULL)
				return;
			for (int i = 0; i < 4; i++) {
				destroyTree(node->child[i]);
			}
			delete node;
		};
		destroyTree(root);
	}
}
