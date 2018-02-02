#pragma once
#include"Entity.h"
#include"Common.h"
#include"Util.h"
#include"Quadtree.h"
#include"Bullet.h"
#include"Collision.h"

#include<math.h>
#include<SFML/Graphics.hpp>
#include<iostream>
#include<vector>


Bullet::Bullet(const float angle, const float x, const float y, const float speed, const int& damage, std::vector<Enemy*> *enemies)
	: x(x), y(y), speed(speed), damage(damage), enemies(enemies) {
	Collision::CreateTextureAndBitmask(spriteTexture, spritesPath + "other/bulletb.png");
	sprite.setTexture(spriteTexture);
	sprite.rotate(util::radiansToDegrees(angle));
	sprite.setPosition(x, y);
	xVelocity = cos(angle);
	yVelocity = sin(angle);
}
	
Bullet::~Bullet() {
	//std::cout << "Destroyed" << std::endl;
}

bool Bullet::update() {
	x += xVelocity;
	y += yVelocity;
	sprite.move(xVelocity * speed, yVelocity * speed);
	return checkCollisions();
}


bool Bullet::checkCollisions() {
	size_t size = enemies->size();
	if (size == 0) return false;
	for (std::vector<Enemy*>::size_type i = size; i > 0; --i) {
		std::vector<Enemy*>::size_type index = i - 1;
		Enemy* enemy = enemies->at(index);
			
		if (Collision::BoundingBoxTest(sprite, enemy->sprite)) {

			bool isDead = enemy->hit(damage);

			if (isDead)	{
				kill(enemy, index);
			}

			return false;
		}
	}
	return false;
}

template<typename T>
void Bullet::kill(T* obj, const size_t& index) {
	// everything we're gonna be calling delete on here will be a 'new' word object
	enemies->erase(enemies->begin() + index);
	delete obj;

}

