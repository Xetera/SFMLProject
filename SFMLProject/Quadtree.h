#pragma once

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
	Entity* entity;
	Node(Entity* _entity)
		: entity(_entity) {}

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
		maxBound = Point(0, 0);
		n  = nullptr;
		nw = nullptr;
		ne = nullptr;
		sw = nullptr;
		se = nullptr;
	}
	Quad(Point min, Point max)
		: minBound(min), maxBound(max) {
		n  = nullptr;
		nw = nullptr;
		ne = nullptr;
		sw = nullptr;
		se = nullptr;

	}
	void insert(Node*);
	Node* search(Node*);
	bool inBoundary(Node*);
};