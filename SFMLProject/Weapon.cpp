#pragma once

#include<SFML\Graphics.hpp>
#include<vector>
#include"Common.h"
#include"Weapon.h"
#include"Util.h"
#include"Enemy.h"
#include"Bullet.h"

Weapon::Weapon(sf::Texture& texture, sf::Sprite& sprite, int damage, std::vector<Enemy*>* enemies) 
	: texture(texture), sprite(sprite), damage(damage), enemies(enemies) {
}

bool Weapon::checkFiringConditions(const int bulletsToFire) {
	if (bulletsToFire < ammo) {
		return false;
	}
	return true;
}

void Weapon::addDamage(int damage) {
	this->damage += damage;
}

Shotgun::Shotgun(sf::Texture& texture, sf::Sprite& sprite, int damage)
	: Weapon::Weapon(texture, sprite, damage, enemies) {
	bulletsPerShot = 4;
}

void Shotgun::fire(const float angle, std::vector<Bullet*>& bullets, const float x, const float y){
	if (!checkFiringConditions(bulletsPerShot)) {
		return;
	}
	for (int i = 0; i < 4; ++i) {
		float random = util::randomRange(angle - 0.5f, angle + 0.5f);
		//std::cout << random << std::endl;
		//std::cout << "Angle" << getAngleToMouse() << std::endl;


		Bullet* bullet = new Bullet(random, x, y, 5, damage, enemies);
		bullets.emplace_back(bullet);
	}
}



Radiate::Radiate(sf::Texture&, sf::Sprite&, int damage, float& playerOriginX, float& playerOriginY)
	: Weapon::Weapon(texture, sprite, damage, enemies),
	playerOriginX(playerOriginX), playerOriginY(playerOriginY) {
	bulletsPerShot = 36;
}