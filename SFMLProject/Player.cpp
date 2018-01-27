#pragma once

#include <SFML/Graphics.hpp>
#include"Entity.cpp"
#include"AnimatedSprite.hpp"
#include<vector>
#include"Bullet.cpp"

#define _USE_MATH_DEFINES
#include<math.h>

#define LOOKING_LEFT         3.141593
#define LOOKING_DOWN         1.5708
#define LOOKING_UP			-1.5708
#define LOOKING_RIGHT        0
#define LOOKING_UP_RIGHT    -0.785398
#define LOOKING_DOWN_RIGHT  -0.785398
#define LOOKING_UP_LEFT      2.35619
#define LOOKING_DOWN_LEFT   -2.35619

using std::cout;
using std::endl;


class Player : public Entity {
public:
	sf::Sprite sprite;
	sf::Vector2f movement;
	
	Player(sf::RenderWindow* window)
		:window(window){
		idle.loadFromFile(spritesPath + "characters/1.png");
		down.loadFromFile(spritesPath + "characters/1_south2.png");
		up.loadFromFile(spritesPath + "characters/1_north.png");
		upRight.loadFromFile(spritesPath + "characters/1_diagup.png");
		upLeft.loadFromFile(spritesPath + "characters/1_diagup.png");
		downLeft.loadFromFile(spritesPath + "characters/1_diagdown.png");
		downRight.loadFromFile(spritesPath + "characters/1_diagdown.png");
		left.loadFromFile(spritesPath + "characters/1_side.png");
		right.loadFromFile(spritesPath + "characters/1_side.png");

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

	virtual void update() override {
		cout << "X: " << x << ", Y: " << y << endl;
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
			if (sprite.getTexture() != &idle) sprite.setTexture(idle);
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

		//std::cout << x << ", " << y << std::endl;
		/*
		if (x + spriteSizeX > windowX) {
			x = windowX - spriteSizeX;
		}

		if (y + spriteSizeY > windowY) {
			y = windowY - spriteSizeY;
		}

		if (x < 0) {
			x = 0;
		}
		if (y < 0) {
			y = 0;
		}
		sprite.setOrigin((spriteSizeX * scale) / 2 + x, (spriteSizeY * scale) / 2 + y);
		sf::Vector2f mouse = getVectorToMouse();
		moveToMouse(mouse);
		*/
		//moveToMouse();
		//std::thread first;

	}

	void fire() {
		Bullet* bullet = new Bullet(getAngleToMouse(), midPointX, midPointY , 1);
		bullets.emplace_back(bullet);
	}

	void fireShotgun() {
		for (int i = 0; i < 4; ++i) {
			float random = util::randomRange(getAngleToMouse() - 0.5f, getAngleToMouse() +  0.5f);
			std::cout << random << std::endl;
			std::cout << "Angle" << getAngleToMouse() << std::endl;


			Bullet* bullet = new Bullet(random, midPointX, midPointY, 5);
			bullets.emplace_back(bullet);
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

	sf::Texture pistol;

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
	void drawBullets() {
		size_t bulletsSize = bullets.size();
		//std::cout << bulletsSize << std::endl;
		// we're going to include the logic for destroying them here as well

		for (size_t i = bulletsSize - 1; i > 0 ; --i) {
			// looping backwards to avoid shifting when we remove bullets
			if (util::getDistance(midPointX, midPointY, bullets[i]->x, bullets[i]->y) < bulletDecay) {	
				bullets[i]->update();
				window->draw(bullets[i]->sprite);
			}
			else {
				Bullet* bullet_ptr = bullets[i];

				// we probably don't want to be removing things from an array while looping
				bullets.erase(bullets.begin() + i);
				delete bullet_ptr;
			}
		}
	}

	sf::Vector2f getVectorToMouse() {

		sf::Vector2f vector;
		float angle = atan2(mouseY - (y + (spriteSizeY * scale / 2)), mouseX - (x + (spriteSizeX * scale / 2)));

		vector.x = cos(angle);
		vector.y = sin(angle);
		return vector;
	}
	// radians

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

	}
	
};