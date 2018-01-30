#pragma once

class World {
	sf::RenderWindow* window;
	sf::Texture backgroundTexture;
	sf::Sprite background;
	void setBackground();
public:
	World(sf::RenderWindow* window);
	void drawBackground();
};