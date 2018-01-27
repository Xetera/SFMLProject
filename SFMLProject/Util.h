#pragma once

namespace util {
	float radiansToDegrees(float radians);
	float DegreesToRadians(float degrees);
	float getDistance(float x1, float y1, float x2, float y2);
	float getDistance(sf::Vector2f& vector1, sf::Vector2f& vector2);

	extern float randomRange(float rangeStart, float rangeEnd);
	extern int   randomRange(int min, int max);
	extern float getVectorAngle(sf::Vector2f&);
	extern sf::Vector2f getUnitVector(sf::Vector2f& vector);
	extern bool vectorEmpty(sf::Vector2f& vector);

	template<typename T>
	extern void printVector(std::vector<T> vector);

	extern int generateID();
}
