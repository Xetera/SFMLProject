#pragma once
#include <SFML/Graphics.hpp>
#include"Common.h"
#include<iostream>
#include"Entity.h"



void Entity::updateMousePosition(sf::Vector2f mouse) {
	mouseX = mouse.x;
	mouseY = mouse.y;
}

void Entity::update(){
	x += sprite.getPosition().x;
	y += sprite.getPosition().y;

	sprite.move(sf::Vector2f(xVelocity * speed, y * speed));
	//std::cout << x << ", " << y << std::endl;
	if (x + radius > windowX) {
		x = windowX - radius;
		xVelocity = xVelocity * -1;
	}
	if (y + radius > windowY) {
		y = windowY - radius;
		yVelocity = yVelocity * -1;
	}

	if (x < 0) {
		x = radius;  
		xVelocity = xVelocity * -1;
	}
	if (y < 0) {
		y = radius;
		yVelocity = yVelocity * -1;
	}
}
/*
Entity::resolveDirection(sf::Vector2f direction) {
	if ()
}

*/