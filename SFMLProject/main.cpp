#include <SFML/Graphics.hpp>
#include"typedefs.h"
#include<iostream>
#include"Player.cpp"
#include"Enemy.h"
#include"Common.h"

using std::cout;
using std::endl;

std::vector<Entity> entities;

// mouseMap mousePositions;
sf::Vector2f position;

void updateEntities() {
	size_t entitySize = entities.size();
	for (std::vector<Entity>::size_type i = 0; i < entitySize; ++i) {
		entities[i].update();
	}
}

int main() {
	srand(time(0));
	
	sf::Sprite cursor;
	sf::Texture cursorTexture;
	sf::RenderWindow window(sf::VideoMode(800, 600), "SFML Game");

	// we really have to clean up our main method
	cursorTexture.loadFromFile(spritesPath + "cursors/mouse_pointer.png");
	cursor.setTexture(cursorTexture);
	window.setMouseCursorVisible(false);
	cursor.setPosition(0, 0);

	sf::RenderWindow* window_ptr = &window;

	Player player(window_ptr);

	entities.emplace_back(player);

	float x = 4.f; 
	float y = 4.f;
	window.setFramerateLimit(120);

	Enemy enemy;
	Enemy enemy2;

	cout << enemies->size() << endl;

	while (window.isOpen())
	{

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
			player.moveUp();
		}

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
			player.moveDown();
		}

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
			player.moveRight();
		}

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
			player.moveLeft();
		}

		sf::Event event;
		while (window.pollEvent(event))
		{
			switch (event.type) 
			{
			case sf::Event::Closed:
				window.close();
				break;
			case sf::Event::MouseMoved:
				//std::cout << event.mouseMove.x << std::endl;
				//std::cout << event.mouseMove.y << std::endl;
				cursor.setPosition(event.mouseMove.x, event.mouseMove.y);
				break;
			case sf::Event::MouseButtonPressed:
				player.fireShotgun();
				break;
			}
	





			
				
		}

		position = static_cast<sf::Vector2f>(sf::Mouse::getPosition(window));


		window.clear();

		window.draw(player.sprite);
		window.draw(cursor);

		player.updateMousePosition(position);
		

		player.update();

		window.display();


	}

	return 0;
}