#pragma once

#ifndef __OBJECT_H__
#define __OBJECT_H__

#include <SFML/System/Vector2.hpp>
#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/RectangleShape.hpp>

class Object {
public:
	Object();
	float					x;
	float					y;
	float					width;
	float					height;

	Object(float x, float y, float width, float height);

	void					Draw(sf::RenderTarget &canvas);

private:
	sf::RectangleShape		shape;
};

#endif