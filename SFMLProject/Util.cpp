#include <SFML/Graphics.hpp>
#define _USE_MATH_DEFINES
#include<math.h>
#include"Util.h"
#include<ctime>


#include<iostream>
#include <random>


namespace util {
	float radiansToDegrees(float radians) {
		return radians * (180.f / M_PI);
	}

	float DegreesToRadians(float degrees) {
		return degrees * (M_PI / 180.f );
	}

	float getDistance(float x1, float y1, float x2, float y2) {
		return sqrt(pow(x2 - x1, 2) + pow(y2 - y1, 2));
	}

	float getDistance(sf::Vector2f& vector1, sf::Vector2f& vector2) {
		return sqrt(pow(vector2.x - vector1.x, 2) + pow(vector2.y - vector1.y, 2));
	}
	
	float randomRange(float min, float max) {

		float amount = (max - min) * ((((float)rand()) / (float)RAND_MAX)) + min;
		std::cout << "Random Number: " << amount << std::endl;
		return amount;

	}
	float getVectorAngle(sf::Vector2f& vector) {
		return atan2(vector.y, vector.x);
	}
	sf::Vector2f getUnitVector(sf::Vector2f& vector) {
		sf::Vector2f out;
		float distance = sqrt(pow(vector.x, 2) + pow(vector.y, 2));
		out.x = vector.x / distance;
		out.y = vector.y / distance;
		return out;
	}
}
