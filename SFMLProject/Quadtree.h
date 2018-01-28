#pragma once
/*
#ifndef __QUADTREE_H__
#define __QUADTREE_H__

#include <vector>
#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/RectangleShape.hpp>


using namespace std;

class Quadtree;

class Quadtree {
public:
	Quadtree(float x, float y, float width, float height, int level, int maxLevel);

	~Quadtree();

	void	AddObject(Entity *object);
	vector<Entity*>		GetObjectsAt(float x, float y);
	void	Clear();

	//void	SetFont(const sf::Font &font);
	void	Draw(sf::RenderTarget &canvas);

private:
	float	x;
	float	y;
	float	width;
	float	height;
	int					level;
	int					maxLevel;
	vector<Entity*>				objects;

	Quadtree *				parent;
	Quadtree *				NW;
	Quadtree *				NE;
	Quadtree *				SW;
	Quadtree *				SE;

	sf::RectangleShape			shape;


	bool					contains(Quadtree *child, Entity *object);
};

#endif
*/