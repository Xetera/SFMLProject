#pragma once
#include"Entity.h"

class Enemy : public Entity {
	std::vector<Enemy*> *enemies;
	int id;
	int health;
public:
	sf::Texture idle;
	Enemy(std::vector<Enemy*> *enemies, const int health);
	~Enemy();
	virtual void update() override;
	
    // returns true if enemy is dead
	bool hit(const int& damage);
};