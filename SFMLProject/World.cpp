#include<SFML\Graphics.hpp>
#include"World.h"
#include"Common.h"

World::World(sf::RenderWindow* window) {
	this->window = window;
	backgroundTexture.loadFromFile(spritesPath + "grass.png");
	
}

void World::setBackground() {
	background.setTexture(backgroundTexture);
}

void World::drawBackground() {
	window->draw(background);
}