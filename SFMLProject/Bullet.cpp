#include <SFML/Graphics.hpp>
#include"Entity.cpp"
#include"Common.h"
#include"Util.h"
#include<iostream>
#include<math.h>

class Bullet {
	sf::Texture spriteTexture;



	float xVelocity;
	float yVelocity;
public:
	float x;
	float y;
	float speed;
	sf::Sprite sprite;

	Bullet(float angle, float x, float y, float speed)
		: x(x), y(y), speed(speed) {
		spriteTexture.loadFromFile(spritesPath + "other/bulletb.png");
		sprite.setTexture(spriteTexture);
		sprite.rotate(util::radiansToDegrees(angle));
		sprite.setPosition(x, y);
		xVelocity = cos(angle);
		yVelocity = sin(angle);
	}
	
	~Bullet() {
		std::cout << "Destroyed" << std::endl;
	}

	void update() {
		x += xVelocity;
		y += yVelocity;
		sprite.move(xVelocity * speed, yVelocity * speed);
	}

	void fire() {
		
	}
};