#include"Entity.h"

struct Point {
	float x;
	float y;
	Point(const float _x, const float _y)
		: x(_x), y(_y) {}
	Point() {
		x = 0;
		y = 0;
	}
};


struct Node {
	Point pos;
	Entity* entity;
	Node(Point _pos, Entity* _entity)
		: pos(_pos), entity(_entity) {}
};

class Quad {
	// boundary points of the quad
	Point minBound;
	Point maxBound;

	Node* n;

	// iterative pointers
	Quad* nw;
	Quad* ne;
	Quad* sw;
	Quad* se;

public:
	Quad() {
		minBound = Point(0, 0);
	}
	Quad(Point min, Point max)
		: minBound(min), maxBound(max) {}
	void insert(Node*);
	Node* search(Point);
};