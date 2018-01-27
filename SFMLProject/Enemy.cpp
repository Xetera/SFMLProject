#include"Entity.h"
#include <SFML/Graphics.hpp>
#include"Common.h"
#include"Collision.h"
#include<iostream>
#include"Util.h"
Enemy::Enemy(std::vector<Enemy*> *enemies)
	:enemies(enemies) {
	id = util::generateID();
	std::cout << id << std::endl;
	enemies->emplace_back(this);
	std::cout << "Enemies size in Enemy: " << enemies->size() << std::endl;
	Collision::CreateTextureAndBitmask(idle, spritesPath + "monster/slime1_front.png");
	x = 400; 
	y = 300;
}

void Enemy::update() {
	
}

void Enemy::hit(const int& damage) {
	if (health -= damage > 0) {
		die();
		return;
	}
	health -= damage;
}

void Enemy::die() {
	size_t size = enemies->size();
	for (std::vector<Enemy*>::size_type i = 0; i < size; ++i) {
		Enemy* enemy = enemies->at(i);
		if (enemy->id == this->id) {
			enemies->erase(enemies->begin() + i);
		}
	}
}