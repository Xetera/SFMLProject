#include <SFML/Graphics.hpp>
#define _USE_MATH_DEFINES
#include<math.h>
#include"Util.h"
#include<ctime>


#include<iostream>
#include <random>


float util::radiansToDegrees(float radians) {
	return radians * (180.f / M_PI);
}

float util::DegreesToRadians(float degrees) {
	return degrees * (M_PI / 180.f );
}

float util::getDistance(float x1, float y1, float x2, float y2) {
	return sqrt(pow(x2 - x1, 2) + pow(y2 - y1, 2));
}

float util::getDistance(sf::Vector2f& vector1, sf::Vector2f& vector2) {
	return sqrt(pow(vector2.x - vector1.x, 2) + pow(vector2.y - vector1.y, 2));
}
	
float util::randomRange(float min, float max) {

	float amount = (max - min) * ((((float)rand()) / (float)RAND_MAX)) + min;
	//std::cout << "Random Number: " << amount << std::endl;
	return amount;

}

int util::randomRange(int min, int max) {
	std::random_device rd; // obtain a random number from hardware
	std::mt19937 eng(rd()); // seed the generator
	std::uniform_int_distribution<> distr(min, max); // define the range

	return distr(eng);
}

float util::getVectorAngle(sf::Vector2f& vector) {
	return atan2(vector.y, vector.x);
}

sf::Vector2f util::getUnitVector(sf::Vector2f& vector) {
	sf::Vector2f out;
	double pow1 = pow((double)vector.x, 2);
	double pow2 = pow((double)vector.y, 2);

	float distance = sqrt(pow1 + pow2);
	out.x = (float)(vector.x / distance);
	out.y = (float)(vector.y / distance);
	return out;
}

bool util::vectorEmpty(sf::Vector2f& vector) {
	return vector.x == 0 && vector.y == 0;
}

template<typename T>
void util::printVector(std::vector<T> vector) {
	size_t size = vector.size();
	for (std::vector<T>::size_type i = 0; i < size; ++i) {
		std::cout << vector[i] << std::endl;
	}
}

int util::generateID() {
	return util::randomRange(100000, 999999);
}