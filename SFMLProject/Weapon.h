#include<vector>
#include"Bullet.cpp"

class Weapon {
protected:
	sf::Texture texture;
	sf::Sprite sprite;
	int damage;
	int bulletsPerShot;
	int totalAmmo;
	int ammo;
	int range;
	std::vector<Enemy*>* enemies;
public:
	Weapon(sf::Texture&, sf::Sprite&, int, std::vector<Enemy*>*);
	virtual bool checkFiringConditions(const int bullets);
	virtual void addDamage(int newValue);
};


class Shotgun : public Weapon {

public:
	Shotgun(sf::Texture& texture, sf::Sprite& sprite, int damage);
	void fire(const float angle, std::vector<Bullet*>& bullets, const float x, const float y);
};

class Radiate : public Weapon {
	float& playerOriginX;
	float& playerOriginY;

public:
	Radiate(sf::Texture&, sf::Sprite&, int damage, float& playerOriginX, float& playerOriginY);
	void fire(const float& angle, std::vector<Bullet*>& bullets, const float x, const float y);
};	

enum EWeapons {
	Pistol,
	Shotgun,
	Radiate
};