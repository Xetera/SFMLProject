#include <SFML/Graphics.hpp>
#include<SFML/Network.hpp>
#include<iostream>
#include"Bullet.h"
#include"Player.cpp"
#include"Enemy.h"
#include"Common.h"
#include"World.h"

using std::cout;
using std::endl;

sf::Vector2f position;
std::vector<Enemy*> *enemies = new std::vector<Enemy*>;

struct keyPress {
	bool up;
	bool down;
	bool left;
	bool right;
};

sf::Packet& operator >>(sf::Packet& packet, keyPress& character) {
	return packet >> character.up >> character.down >> character.left >> character.right;
}

sf::Packet& operator <<(sf::Packet& packet, const keyPress& character)
{
	return packet << character.up << character.down << character.left << character.right;
}


void horde(unsigned const int amount) {
	while (enemies->size() < amount) {
		cout << enemies->size() << "in main" << endl;
		int random = util::randomRange(0, (int)windowY);
		Enemy* enemy = new Enemy(random, 0, 10, enemies);

	}
}

sf::UdpSocket socket;

unsigned short port = 8080;


void listen() {
	sf::IpAddress sender;

	sf::Packet packet;
	std::size_t received;
	bool up;
	bool down;
	bool left;
	bool right;
	if (socket.receive(packet, sender, port) != sf::Socket::Done) return;
	
	else {
		std::cout << "Received packet from " << sender << " on port " << port << std::endl;
		up = packet;
		packet >> up >> down >> left >> right;
		cout << up << down << left << right << endl;
	}

}

int main() {

	srand(time(0));
	

	// UDP socket:
	socket.bind(port);
	/*
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

	float x = 4.f; 
	float y = 4.f;

	window.setFramerateLimit(60);
	World world(window_ptr);
	
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
		while (window.pollEvent(event)){
			switch (event.type) {
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

		horde(200);
		window.draw(cursor);


		player.updateMousePosition(position);
		

		player.update();
		world.drawBackground();
		window.display();
		
	
	}
	*/
	while (true) {
		listen();

	}
	return 0;
}