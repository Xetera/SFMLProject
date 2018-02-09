#pragma once
#include"Entity.h"

class Enemy : public Entity {

	int health;
	std::vector<Enemy*>* enemies;
public:
	float x;
	float y;

	sf::Texture idle;
	Enemy(float x, float y, const int health, std::vector<Enemy*>*);
	~Enemy();
	void update();
	void move(sf::Vector2f vector);

    // returns true if enemy is dead
	bool hit(const int& damage);
};