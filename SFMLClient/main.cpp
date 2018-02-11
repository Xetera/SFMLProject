#include<iostream>
#define SFML_STATIC
#include<SFML/Network.hpp>

sf::UdpSocket socket;
unsigned short port = 3000;

char data[6] = "hello";
sf::IpAddress recipient = "68.4.235.189";

int main() {
	if (socket.bind(port) != sf::Socket::Done)
	{
		std::cout << "Something went wrong trying to connect to " << port << std::endl;
	}

	if (socket.send(data, 100, recipient, port) != sf::Socket::Done)
	{
		std::cout << "Something went wrong while trying to send data to " << recipient << " at " << port << std::endl;
	}

	int x;
	std::cin >> x;
	return 0;
}