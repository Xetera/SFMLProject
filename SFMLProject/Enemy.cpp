#include"Entity.h"
#include <SFML/Graphics.hpp>
#include"Common.h"
#include"Collision.h"
#include<iostream>
#include"Util.h"
Enemy::Enemy(std::vector<Enemy*> *enemies, const int health)
	:enemies(enemies), health(health) {
	id = util::generateID();



	std::cout << id << std::endl;
	enemies->emplace_back(this);
	std::cout << "Enemies size in Enemy: " << enemies->size() << std::endl;
	Collision::CreateTextureAndBitmask(idle, spritesPath + "monster/slime1_front.png");
	sprite.setTexture(idle);

	x = 400; 
	y = 300;
	sprite.setPosition(x, y);
}

Enemy::~Enemy() {
	std::cout << "Enemy killed" << std::endl;
}

void Enemy::update() {
	//std::cout << health << std::endl;
}

bool Enemy::hit(const int& damage) {
	health -= damage;
	std::cout << health << std::endl;
	if (health < 0) {
		return true;
	}
	return false;
}
