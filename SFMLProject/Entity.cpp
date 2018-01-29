#pragma once
#include <SFML/Graphics.hpp>
#include"Common.h"
#include<iostream>
#include"Entity.h"
//#include"Quadtree.h"
//#include <Box2D.h>


void Entity::updateMousePosition(sf::Vector2f mouse) {
	mouseX = mouse.x;
	mouseY = mouse.y;
}

/*
void Entity::update(){
	x += sprite.getPosition().x;
	y += sprite.getPosition().y;

	sprite.move(sf::Vector2f(xVelocity * speed, y * speed));
	//std::cout << x << ", " << y << std::endl;
	
}
*/

/*
Entity::resolveDirection(sf::Vector2f direction) {
	if ()
}

*/