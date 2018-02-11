#pragma once

#include<SFML\Graphics.hpp>
#include<vector>
#include"Common.h"
#include"Weapon.h"
#include"Util.h"
#include"Enemy.h"
#include"Bullet.h"

Weapons::Weapon::Weapon(sf::Texture& texture, int damage, std::vector<Enemy*>* enemies) 
	: texture(texture), damage(damage), enemies(enemies) {
	sprite.setTexture(texture);
}

bool Weapons::Weapon::checkFiringConditions(const int bulletsToFire) {
	if (bulletsToFire < ammo) {
		return false;
	}
	return true;
}

void Weapons::Weapon::addDamage(int damage) {
	this->damage += damage;
}

Weapons::Shotgun::Shotgun(sf::Texture& texture, int damage, std::vector<Enemy*>* enemies)
	: Weapon::Weapon(texture, damage, enemies) {
	bulletsPerShot = 4;
}

void Weapons::Shotgun::fire(const float angle, std::vector<Bullet*>& bullets, const float x, const float y){
	if (!checkFiringConditions(bulletsPerShot)) {
		return;
	}
	for (int i = 0; i < bulletsPerShot; ++i) {
		float random = util::randomRange(angle - accuracy, angle + accuracy);
		//std::cout << random << std::endl;
		//std::cout << "Angle" << getAngleToMouse() << std::endl;


		Bullet* bullet = new Bullet(random, x, y, 5, damage, enemies);
		bullets.emplace_back(bullet);
	}
}



Weapons::Radiate::Radiate(sf::Texture&, int damage, float& playerOriginX, float& playerOriginY)
	: Weapon::Weapon(texture, damage, enemies),
	playerOriginX(playerOriginX), playerOriginY(playerOriginY) {
	bulletsPerShot = 36;
}
