#pragma once
#include <SFML/Graphics.hpp>

class Entity {
public:
	float x;
	float y;

	float xVelocity;
	float yVelocity;

	float mouseX;
	float mouseY;

	int maxHealth;
	int health;

	inline void updateMousePosition(sf::Vector2f mouse);
	inline virtual void update();
protected:
	float speed;
	float radius;
	sf::Sprite sprite;


	enum EDirection {
		RIGHT,
		DOWN_RIGHT,
		DOWN,
		DOWN_LEFT,
		LEFT,
		UP_LEFT,
		UP,
		UP_RIGHT
	};

	EDirection resolveDirection(sf::Vector2f);
};