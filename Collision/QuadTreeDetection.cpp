#include "QuadTreeDetection.h"
#include <algorithm>
#include <limits>
#include <functional>


namespace Collision
{

	void QuadTreeDetection::divide(QuadTreeNode* node, Point squarePt, double side) {
		
		if (node == NULL)
			return;

		double halfSide = side / 2;

		Point squarePts[4] = { squarePt, squarePt, squarePt, squarePt };

		squarePts[1].x += halfSide;
		squarePts[2].y += halfSide;
		squarePts[3].x += halfSide;
		squarePts[3].y += halfSide;

		std::vector<Segment> add[4];		

		for (Segment seg : node->segments) {	

			for (int i = 0; i < 4; i++) {
				if (seg.insideSquare(squarePts[i], halfSide)) 
					add[i].push_back(seg);
			}
		}
	
		for (int i = 0; i < 4; i++) {

			if (add[i].size() > 0) {
				node->child[i] = new QuadTreeNode();
			}

			for (Segment seg : add[i]) {
				node->child[i]->segments.push_back(seg);
				node->segments.erase(std::remove(node->segments.begin(), node->segments.end(), seg), node->segments.end());
			}
		}

		for (int i = 0; i < 4; i++)
		{			
			divide(node->child[i], squarePts[i], halfSide);
		}
	}



	QuadTreeDetection::QuadTreeDetection(std::vector<Segment>& allSegments) {

		root = new QuadTreeNode();
		root->segments = allSegments;

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
		
		squareRange = Point(minx, miny);
		sideSquareRange = std::max(maxx - minx, maxy - miny);
		divide(root, squareRange, sideSquareRange);
	}



	std::pair<Segment*, Point> QuadTreeDetection::getIntersection(Segment query) {
		
		std::function<void(QuadTreeNode* root, Point squarePt, double side)> traverse;

		Point& startPoint = query.first;
		Point intersectionPoint;
		double minDist = std::numeric_limits<double>::max();
		Point closest;
		Segment* segmentIntersection = NULL;

		traverse = [&query, &traverse, &intersectionPoint, &segmentIntersection, &startPoint, &minDist, &closest]
		(QuadTreeNode* node, Point squarePt, double side) {

			if (node == NULL) return;

			if (query.first.insideSquare(squarePt, side) || query.second.insideSquare(squarePt, side)) {
				// Test against current node's segments
				for (unsigned int i = 0; i < node->segments.size(); i++) {

					if (node->segments[i].intersects(query)) {

						intersectionPoint = node->segments[i].intersectionPoint(query);
						double dist = distance(startPoint, intersectionPoint);
						if (dist < minDist) {
							minDist = dist;
							closest = intersectionPoint;
							segmentIntersection = &node->segments[i];
						}
					}
				}
			} 

			double halfSide = side / 2;

			Point squarePts[4]{ squarePt, squarePt, squarePt, squarePt };
			squarePts[1].x += halfSide;
			squarePts[2].y += halfSide;
			squarePts[3].x += halfSide;
			squarePts[3].y += halfSide;

			for (int i = 0; i < 4; i++) {
				traverse(node->child[i], squarePts[i], halfSide);
			}			
		};

		traverse(root, squareRange, sideSquareRange);			

		return std::make_pair(segmentIntersection, closest);
	}

	int QuadTreeDetection::countTotalSegments() {
		std::function<int(QuadTreeNode*)> count;
		count = [&count](QuadTreeNode* node)->int {
			if (node == NULL)
				return 0;	
			return node->segments.size() + 
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
