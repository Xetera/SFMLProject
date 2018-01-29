#include"Entity.h"
#include"Quadtree.h"
#include<math.h>


void Quad::insert(Node* node) {
	if (node == nullptr) return;

	if (!inBoundary(node->entity)) return;


	if (abs(minBound.x - maxBound.x) <= 1 &&
		abs(minBound.y - maxBound.y) <= 1) {
		if (n == nullptr) {
			// we can't subdivide but the node space is empty
			n = node;
		}
	}

	if ((maxBound.x + minBound.x) / 2 >= node->entity->x) {
		// node is on the left side of the quadtree
		if ((minBound.y + maxBound.y) / 2 >= node->entity->y) {
			// point is in the top part of the quad 
			if (nw == nullptr) {
				nw = new Quad(
					Point(minBound.x, minBound.x),
					Point((minBound.x + maxBound.x) / 2 ,(minBound.y + maxBound.y) / 2)
				);
				nw->insert(node);
			}
		}
		else { 
			// point is in bottom part of the quad
			if (sw == nullptr) {
				sw = new Quad(
					Point(minBound.x, (minBound.x + maxBound.y) / 2),
					Point((minBound.x + maxBound.x) / 2, maxBound.y)
				);
				sw->insert(node);
			}
		}
	}
	else {
		// point is on the right side 

		if ((minBound.y + maxBound.y) / 2 >= node->entity->y) {
			// point is on the top
			if (ne == nullptr) {
				ne = new Quad(
					Point((minBound.x + maxBound.x) / 2, minBound.y),
					Point(maxBound.x, (minBound.y + maxBound.y)/ 2)
				);
				ne->insert(node);
			}
			
		}
		else {
			// point is on the bottom
			if (se == nullptr) {
				se = new Quad(
					Point((minBound.x + maxBound.y) / 2, (minBound.y + maxBound.y) / 2),
					Point(maxBound.x, maxBound.y)
				);
				se->insert(node);
			}
		}
	}
}

Node* Quad::search(Node* p) {
	if (!inBoundary(p)) return NULL;
	if (n != nullptr) return n;

	if ((minBound.x + maxBound.x) / 2 >= p->entity->x)
	{
		// Indicates topLeftTree
		if ((minBound.y + maxBound.y) / 2 >= p->entity->y)
		{
			if (nw == NULL)
				return NULL;
			return nw->search(p);
		}

		// Indicates botLeftTree
		else
		{
			if (sw == NULL)
				return NULL;
			return sw->search(p);
		}
	}
	else
	{
		// Indicates topRightTree
		if ((minBound.y + maxBound.y) / 2 >= p->y)
		{
			if (ne == NULL)
				return NULL;
			return ne->search(p);
		}

		// Indicates botRightTree
		else
		{
			if (se == NULL)
				return NULL;
			return se->search(p);
		}
	}
}

bool Quad::inBoundary(Node* p) {
	return (
		p->x >= minBound.x && 
		p->x <= maxBound.x && 
		p->y >= minBound.y &&
		p->y <= maxBound.y
		);
}