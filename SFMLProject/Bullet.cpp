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
		//std::cout << "Destroyed" << std::endl;
	}

	void update() {
		x += xVelocity;
		y += yVelocity;
		sprite.move(xVelocity * speed, yVelocity * speed);
		checkCollisions();
	}

	void fire() {
		
	}

	void checkCollisions() {
		size_t size = enemies->size();
		for (int i = size; i > 0; --i) {
			Enemy* enemy = enemies->at(i);
			/*
			if (Collision::PixelPerfectTest(sprite, enemy->sprite)) {
				std::cout << "HIT" << std::endl;
				bool isDead = enemy->hit(damage);
				if (isDead)	{
					kill(enemy, i);
				}

			}
			*/
		}
		
	}

	template<typename T>
	void kill(T* obj, const size_t& index) {
		// everything we're gonna be calling delete on here will be a 'new' word object
		enemies->erase(enemies->begin() + index);
		delete obj;

	}

};