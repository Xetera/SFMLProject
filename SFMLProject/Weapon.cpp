#include<SFML\Graphics.hpp>
#include"Common.h"
#include"Weapon.h"
#include"Util.h"
#include"Bullet.cpp"

Weapon::Weapon(sf::Texture& texture, sf::Sprite& sprite, int damage) 
	: texture(texture), sprite(sprite), damage(damage) {
}

bool Weapon::fire(const int bulletsToFire) {
	if (bulletsToFire < ammo) {
		return false;
	}
	return true;
}

void Weapon::addDamage(int damage) {
	this->damage += damage;
}

Shotgun::Shotgun(sf::Texture& texture, sf::Sprite& sprite, int damage) 
	: Weapon::Weapon(texture, sprite, damage) {
	bulletsPerShot = 4;
}

void Shotgun::fire(const float& angle, std::vector<Bullet*>& bullets, const float x, const float y) {
	if (!Weapon::fire(bulletsPerShot)) {
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



Radiate::Radiate(sf::Texture&, sf::Sprite&, int damage, float playerOriginX, float playerOriginY)
	: Weapon::Weapon(texture, sprite, damage), {

}