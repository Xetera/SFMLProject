#pragma once
#include"Entity.h"

class Enemy : public Entity {
	std::vector<Enemy*> *enemies;
	int id;
public:
	sf::Texture idle;
	Enemy(std::vector<Enemy*> *enemies);
	virtual void update() override;
	void hit(const int& damage);
	void die();
};