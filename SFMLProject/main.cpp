#include <SFML/Graphics.hpp>
#include<iostream>


#include"Player.cpp"
#include"Enemy.h"
#include"Common.h"
#include"World.h"

using std::cout;
using std::endl;



// mouseMap mousePositions;
sf::Vector2f position;
/*
void updateEntities() {
	size_t entitySize = entities.size();
	for (std::vector<Entity>::size_type i = 0; i < entitySize; ++i) {
		entities[i].update();
	}
}*/

Quad world(Point(0, 0), Point(windowX, windowY));


void horde(unsigned const int amount) {

	while (enemies->size() < amount) {
		int random = util::randomRange(0, (int)windowY);
		Enemy* enemy = new Enemy(enemies, random, 0 , 10);

		//Node enemyNode(enemy);
		//world.insert(&enemyNode);

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


	Player player(window_ptr, enemies);

	//entities.emplace_back(player);

	float x = 4.f; 
	float y = 4.f;

	window.setFramerateLimit(60);
	World world(window_ptr);
	//Enemy* enemy = new Enemy(enemies, 10);
	//Enemy* enemy2 = new Enemy(enemies, 10);
	
	//cout << "Enemies size: " << enemies->size() << endl;

	

	while (window.isOpen()) {
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
		size_t enemySize = enemies->size();
		
		for (std::vector<Enemy*>::size_type i = 0; i < enemySize; ++i) {
			Enemy* loopEnemy = enemies->at(i);
			loopEnemy->update();
			loopEnemy->move(sf::Vector2f(0, 1));
			window.draw(loopEnemy->sprite);
			

		}
		horde(500);
		window.draw(cursor);


		player.updateMousePosition(position);
		

		player.update();
		world.drawBackground();
		window.display();


	}

	return 0;
}