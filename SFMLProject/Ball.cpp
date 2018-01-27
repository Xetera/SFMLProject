#pragma once 

#include <SFML/Graphics.hpp>
#include"Common.h"
#include<iostream>
#include"Entity.cpp"



class Ball : public Entity {
public:
	sf::CircleShape sprite;
	float radius;

	float x;
	float y;

	float xSpeed;
	float ySpeed;

	Ball() {
		radius = 10.f;
		sf::CircleShape shape(radius);
		shape.setOrigin(shape.getRadius(), shape.getRadius());
		shape.setFillColor(sf::Color::Red);
		this->sprite = shape;

	}
	void updateSpeed(float xSpeed, float ySpeed) {
		this->xSpeed = xSpeed;
		this->ySpeed = ySpeed;
	}

	void update() {

	}

private:
};
