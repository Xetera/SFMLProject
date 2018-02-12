#include<iostream>
#include<SFML/Network.hpp>
#include<SFML/Graphics.hpp>
#include<string>

using std::cout;
using std::endl;

sf::UdpSocket socket;
unsigned short port = 8080;

sf::IpAddress recipient = "68.4.235.189";
std::string spritesPath = "../Media/topdown_shooter/";
sf::Packet pack; 

struct keyPress : public sf::Packet{
	bool packet[4];
	bool up;
	bool down;
	bool left;
	bool right;


	void clearKeys() {
		up = NULL;
		down = NULL;
		left = NULL;
		right = NULL;

	}

	bool isEmpty() {
		return !(up && down && right && left);
	}

};


sf::Packet& operator >> (sf::Packet& packet, keyPress& character) {
	return packet >> character.up >> character.down >> character.left >> character.right;
}

sf::Packet& operator <<(sf::Packet& packet, const keyPress& character)
{
	return packet << character.up << character.down << character.left << character.right;
}

bool sendPacket(sf::Packet data) {
	return socket.send(data, recipient, port) != sf::Socket::Done;
}

int main() {

	std::cout << "Client started." << std::endl;
	sf::Sprite cursor;
	sf::Texture cursorTexture;
	sf::RenderWindow window(sf::VideoMode(800, 600), "SFML Game");

	cursorTexture.loadFromFile(spritesPath + "cursors/mouse_pointer.png");
	cursor.setTexture(cursorTexture);
	window.setMouseCursorVisible(false);
	cursor.setPosition(0, 0);

	sf::RenderWindow* window_ptr = &window;

	float x = 4.f;
	float y = 4.f;

	window.setFramerateLimit(60);

	while (window.isOpen()) {
		keyPress keys;
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
			keys.up = true;
		}

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
			keys.down = true;
		}

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
			keys.right = true;
		}

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
			keys.left = true;
		}

		sf::Event event;
		while (window.pollEvent(event)) {
			switch (event.type) {
			case sf::Event::Closed:
				window.close();
				break;
			case sf::Event::MouseMoved:
				//std::cout << event.mouseMove.x << std::endl;
				//std::cout << event.mouseMove.y << std::endl;
				cursor.setPosition(event.mouseMove.x, event.mouseMove.y);
				break;
			}
		}


		window.clear();
		window.draw(cursor);

		window.display();

		pack >> keys;
		cout << pack << endl;
		if (!keys.isEmpty()) {
			sendPacket(pack);
			keys.clear();
		}
		pack.clear();
	}

		
	return 0;
}