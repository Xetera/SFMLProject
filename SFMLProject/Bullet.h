#pragma once

class Bullet : public Entity {
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

	Bullet(const float angle, const float x, const float y, const float speed, const int& damage, std::vector<Enemy*> *enemies);
	~Bullet();
	bool update();
	bool checkCollisions();

	template<typename T>
	void kill(T* obj, const size_t& index);
};