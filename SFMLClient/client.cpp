#include<iostream>
#include<SFML/Network.hpp>

sf::UdpSocket socket;
unsigned short port = 3000;

char data[6] = "hello";
sf::IpAddress recipient = "192.168.0.10";

int main() {
	std::cout << "Client started." << std::endl;


	while (true) {
		
		if (socket.send(data, sizeof(data), recipient, port) != sf::Socket::Done)
		{
			std::cout << "Something went wrong while trying to send data to " << recipient << " at " << port << std::endl;
		}
		//std::cout << "Sent " << data << std::endl;
	}

		
	int x;
	std::cin >> x;
	return 0;
}