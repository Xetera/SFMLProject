#include <SFML/Graphics.hpp>
#include"Entity.cpp"
#include"Common.h"
#include"Util.h"
#include<iostream>
#include<math.h>
#include"Collision.h"
#include<vector>

class Bullet {
	sf::Texture spriteTexture;
	
	std::vector<Enemy*> *enemies;

	float xVelocity;
	float yVelocity;
public:
	float x;
	float y;
	float speed;
	float damage; 
	sf::Sprite sprite;

	Bullet(const float angle, const float x, const float y, const float speed, const int& damage, std::vector<Enemy*> *enemies)
		: x(x), y(y), speed(speed), damage(damage), enemies(enemies) {
		Collision::CreateTextureAndBitmask(spriteTexture, spritesPath + "other/bulletb.png");
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

	void checkCollisions() {
		size_t size = enemies->size();
		for (int i = size; i >= 0; --i) {
			Enemy* enemy = enemies->at(i);
			if (Collision::PixelPerfectTest(sprite, enemy->sprite)) {
				enemy->hit(damage);
			}
		}
		
	}

};