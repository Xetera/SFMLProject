#pragma once

#include <SFML/Graphics.hpp>
#define _USE_MATH_DEFINES
#include<math.h>
#include<vector>

#include"Entity.cpp"
#include"Bullet.cpp"
#include"Collision.h"
#include"Quadtree.h"
#include"Weapon.h"

using std::cout;
using std::endl;
using namespace Weapons;

class Player : public Entity {
public:
	sf::Sprite sprite;
	sf::Vector2f movement;
	
	int damage = 5; /* we're going to update this later to be a part of the weapons class */

	Player(sf::RenderWindow* window, std::vector<Enemy*> *enemies)
		:window(window), enemies(enemies) {

		Collision::CreateTextureAndBitmask(idle, spritesPath + "characters/1.png");
		Collision::CreateTextureAndBitmask(down, spritesPath + "characters/1_south2.png");
		Collision::CreateTextureAndBitmask(up, spritesPath + "characters/1_north.png");
		Collision::CreateTextureAndBitmask(upRight, spritesPath + "characters/1_diagup.png");
		Collision::CreateTextureAndBitmask(upLeft, spritesPath + "characters/1_diagup.png");
		Collision::CreateTextureAndBitmask(downLeft, spritesPath + "characters/1_diagdown.png");
		Collision::CreateTextureAndBitmask(downRight, spritesPath + "characters/1_diagdown.png");
		Collision::CreateTextureAndBitmask(left, spritesPath + "characters/1_side.png");
		Collision::CreateTextureAndBitmask(right, spritesPath + "characters/1_side.png");


		Collision::CreateTextureAndBitmask(shotgunSprite, spritesPath + "guns/shotgun/shot_diagdown.png");

		sprite.setTexture(idle);
		//sprite.setTextureRect(sf::IntRect(30, 0, 20, 24));
		scale = 1;
		//sprite.setScale(scale, scale);
		spriteSizeX = sprite.getTexture()->getSize().x/4;
		spriteSizeY = (sprite.getTexture()->getSize().y);
		sprite.setOrigin(x, y);

		sprite.setPosition(windowX / 2, windowY / 2);
		movement.x = 0;
		movement.y = 0;
	}

	~Player() {
		size_t bulletsSize = bullets.size();
		if (bulletsSize > 0) {
			for (int i = 0; i < bulletsSize; ++i) { // could be an off-by-one error here
				bullets[i].erase;
			}
		}

		delete shotgun;
	}

	void moveRight() {
		movement.x += (1.f * maxSpeed);
	}

	void moveLeft() {
		movement.x += (-1.f * maxSpeed);
	}

	void moveUp()   {
		movement.y += (-1.f * maxSpeed);
	}

	void moveDown() {
		movement.y += (1.f * maxSpeed);	
	}


	void updateVelocity(float xVelocity, float yVelocity) {
		float additionX = xVelocity > maxSpeed ? maxSpeed : xVelocity;
		float additionY = yVelocity > maxSpeed ? maxSpeed : yVelocity;

		this->xVelocity = additionX;
		this->yVelocity = additionY;
	}

	/*overloading*/
	void updateVelocity(sf::Vector2f position) {
		xVelocity = position.x;
		yVelocity = position.y;
	}

	virtual void update() {
		//cout << "X: " << x << ", Y: " << y << endl;
		x = sprite.getPosition().x;
		y = sprite.getPosition().y;


		midPointX = x + (spriteSizeX * scale) / 2;
		midPointY = y + (spriteSizeY * scale) / 2;

		if (bullets.size() != 0) {
			drawBullets();

		}

		//xVelocity = 0.f;
		//xVelocity = 0.f;

		if (util::vectorEmpty(movement)) { // our guy is not moving
			if (sprite.getTexture() != &idle) idleAnimation();
			return;
		}

		sf::Vector2f unitVector = util::getUnitVector(movement);
		sprite.move(unitVector);

		if (movement.x > 0 && movement.y == 0) {
			cycleRightAnimation();
		}

		else if (movement.x < 0 && movement.y == 0) {
			cycleLeftAnimation();
		}

		else if (movement.x == 0 && movement.y < 0) {
			cycleUpAnimation();
		}
		else if (movement.x == 0 && movement.y > 0) {
			cycleDownAnimation();
		}

		else if (movement.x < 0 && movement.y) {
			cycleUpLeftAnimation();
		}

		else if (movement.x > 0 && movement.y < 0) {
			cycleUpRightAnimation();
		}

		else if (movement.x > 0 && movement.y > 0) {
			cycleDownRightAnimation();
		}

		else if (movement.x < 0 && movement.y > 0) {
			cycleDownLeftAnimation();

		}
	
		movement.x = 0;
		movement.y = 0;

	}

	void fire() {

		Bullet* bullet = new Bullet(getAngleToMouse(), midPointX, midPointY, 1, damage, enemies);
		//Node bulletNode(bullet);
		bullets.emplace_back(bullet);
		//quad.insert(&bulletNode);
		
	}

	void fireShotgun() {
		//if (currentWeapon != EWeapons::Shotgun) return;
		for (int i = 0; i < 4; ++i) {
			Bullet* bullet = new Bullet(getAngleToMouse() + util::randomRange(-1.f, 1.f), midPointX, midPointY, 5, damage, enemies);
			bullets.emplace_back(bullet);
		}
		
			
	}
	
	void switchWeapon(sf::Keyboard::Key key) {
		switch(key) {
		case sf::Keyboard::Num1:
			currentWeapon = EWeapons::Pistol;
			break;
		case sf::Keyboard::Num2:
			currentWeapon = EWeapons::Shotgun;
			break;
		}
	}

private:
	std::vector<Bullet*> bullets;
	sf::Texture texture;
	sf::Texture idle;
	sf::Texture down;
	sf::Texture downRight;
	sf::Texture downLeft;
	sf::Texture left;
	sf::Texture up;
	sf::Texture upLeft;
	sf::Texture upRight;
	sf::Texture right;

	sf::Texture shotgunSprite;

	sf::Texture pistol;
	std::vector<Enemy*>* enemies;
	sf::RenderWindow* window;

	
	float x;
	float y;
	float xVelocity;
	float yVelocity;

	float maxSpeed = 1;
	
	float spriteSizeX;
	float spriteSizeY;

	float midPointX;
	float midPointY;

	float scale;

	int spriteCycle;
	int cycleOffset = 0;

	int bulletDecay = 100;

	EWeapons currentWeapon;
	Weapons::Shotgun* shotgun;
	
	void drawBullets() {
		size_t bulletsSize = bullets.size();
		// std::cout << bulletsSize << std::endl;
		// we're going to include the logic for destroying them here as well

		for (size_t i = bulletsSize - 1; i > 0 ; --i) {
			// looping backwards to avoid shifting when we remove bullets
			if (util::getDistance(midPointX, midPointY, bullets[i]->x, bullets[i]->y) < bulletDecay) {	
				bool hit = bullets[i]->update();
				if (hit){
					destroyBullet(i);
				}
				window->draw(bullets[i]->sprite);
			}
			else {
				destroyBullet(i);
			}
		}
	}

	void destroyBullet(size_t index) {
		Bullet* bullet_ptr = bullets[index];

		// we probably don't want to be removing things from an array while looping
		bullets.erase(bullets.begin() + index);
		delete bullet_ptr;
	}

	sf::Vector2f getVectorToMouse() {

		sf::Vector2f vector;
		float angle = atan2(mouseY - (y + (spriteSizeY * scale / 2)), mouseX - (x + (spriteSizeX * scale / 2)));

		vector.x = cos(angle);
		vector.y = sin(angle);
		return vector;
	}
	// radians

	void newWeapon(EWeapons gun) {
		switch (gun) {
		case EWeapons::Shotgun:
			shotgun = new Shotgun(shotgunSprite);+
		}
	}


	float getAngleToMouse() {
		return atan2(mouseY - midPointY, mouseX - midPointX);
	}


	void moveToMouse() {
		float angle = atan2(mouseY - (y + (spriteSizeY * scale/2)), mouseX - (x + (spriteSizeX * scale/2)));

		xVelocity = cos(angle);
		yVelocity = sin(angle);
	}

	void cycleDownAnimation() {
		cycleOffset++;
		sprite.setTexture(down);

		if (spriteCycle == 4) {
			spriteCycle = 0;
		}

		if (cycleOffset >= 20) {
			sprite.setTextureRect(sf::IntRect(20 * spriteCycle, 0, 20, 24));
			cycleOffset = 0;
			spriteCycle++;
		}
	}

	void cycleDownRightAnimation() {
		cycleOffset++;
		sprite.setTexture(downRight);

		if (spriteCycle == 4) {
			spriteCycle = 0;
		}

		if (cycleOffset >= 20) {
			sprite.setTextureRect(sf::IntRect(20 * spriteCycle, 0, 20, 24));
			cycleOffset = 0;
			spriteCycle++;
		}
	}

	void cycleRightAnimation() {
		cycleOffset++;
		sprite.setTexture(right);

		if (spriteCycle == 4) {
			spriteCycle = 0;
		}

		if (cycleOffset >= 20) {
			sprite.setTextureRect(sf::IntRect(20 * spriteCycle, 0, 20, 24));
			cycleOffset = 0;
			spriteCycle++;
		}
	}
	void cycleUpAnimation() {
		cycleOffset++;
		sprite.setTexture(up);

		if (spriteCycle == 4) {
			spriteCycle = 0;
		}

		if (cycleOffset >= 20) {
			sprite.setTextureRect(sf::IntRect(20 * spriteCycle, 0, 20, 24));
			cycleOffset = 0;
			spriteCycle++;
		}
	}

	void cycleUpRightAnimation() {
		cycleOffset++;
		sprite.setTexture(upLeft);

		if (spriteCycle == 4) {
			spriteCycle = 0;
		}

		if (cycleOffset >= 20) {
			sprite.setTextureRect(sf::IntRect(20 * spriteCycle, 0, 20, 24));
			cycleOffset = 0;
			spriteCycle++;
		}
	}

	void cycleUpLeftAnimation() {
		cycleOffset++;
		sprite.setTexture(upRight);

		if (spriteCycle == 4) {
			spriteCycle = 0;
		}

		if (cycleOffset >= 20) {
			sprite.setTextureRect(sf::IntRect(20 + (20 * spriteCycle), 0, -20, 24));
			cycleOffset = 0;
			spriteCycle++;
		}
	}

	void cycleLeftAnimation() {
		cycleOffset++;
		sprite.setTexture(left);

		if (spriteCycle == 4) {
			spriteCycle = 0;
		}

		if (cycleOffset >= 20) {
			sprite.setTextureRect(sf::IntRect(20 + (20 * spriteCycle), 0, -20, 24));
			cycleOffset = 0;
			spriteCycle++;
		}
	}

	void cycleDownLeftAnimation() {
		cycleOffset++;
		sprite.setTexture(downLeft);

		if (spriteCycle == 4) {
			spriteCycle = 0;
		}

		if (cycleOffset >= 20) {
			sprite.setTextureRect(sf::IntRect(20 + (20 * spriteCycle), 0, -20, 24));
			cycleOffset = 0;
			spriteCycle++;
		}
	}

	void idleAnimation() {
		
		sprite.setTexture(idle);
		sprite.setTextureRect(sf::IntRect(0, 0, 16, 21));
	}
	
};