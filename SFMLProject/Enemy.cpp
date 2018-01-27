#include"Entity.h"
#include <SFML/Graphics.hpp>
#include"Common.h"

Enemy::Enemy() {
	enemies->emplace_back(this);
}