#include "helperFunctions.h"

float FindMaxFromVectorFloat(std::vector<float> vector) {

	if (vector.size() == 1)
		return vector.at(0);

	float max = vector[0];
	for (int i = 0; i < vector.size(); i++)
	{
		if (max < vector[i])
			max = vector[i];
	}

	return max;
}

sf::Vector2f GetRandomDirection() {

	return GetRandomDirectionBetweenAngles({ 0, 0 });
}

sf::Vector2f GetRandomDirectionBetweenAngles(sf::Vector2i angles) {

	if (angles.x > angles.y) {
		std::cout << "Incorrect angle range" << std::endl;
		return sf::Vector2f(0, 0);
	}

	if (angles == sf::Vector2i(0, 0)) {
		float randomAngle = (float)(rand() % 360);
		return sf::Vector2f(std::cosf(randomAngle), std::sinf(randomAngle));
	}

	int range = angles.y - angles.x;
	float randomAngle = (float)(angles.x + rand() % range);

	return sf::Vector2f(std::cosf(randomAngle), std::sinf(randomAngle));
}

sf::Vector2f GetRandomPosition(sf::Vector2i windowSize) {
	return sf::Vector2f((float)(rand() % windowSize.x), (float)(rand() % windowSize.y));
}

sf::Vector2f GetRandomBoundaryPosition(sf::Vector2i windowSize, sf::Vector2f margin) {
	sf::Vector2f randomPosition;

	//fix one border
	if (chanceFunction(50))
	{
		//fix x boundary to either side of the window
		randomPosition.x = chanceFunction(50) ? 0.0f : (float)windowSize.x;
		if (randomPosition.x == 0.0f)
			randomPosition.x += margin.x;
		else
			randomPosition.x -= margin.x;

		randomPosition.y = (float)(rand() % windowSize.y);
	}
	else {
		//fix y boundary to either side of the window
		randomPosition.y = chanceFunction(50) ? 0.0f : (float)windowSize.y;
		if (randomPosition.y == 0.0f)
			randomPosition.y += margin.y;
		else
			randomPosition.y -= margin.y;
		randomPosition.x = (float)(rand() % windowSize.x);
	}

	return randomPosition;
}

bool chanceFunction(int chance) {
	int randomNumber = rand() % 100;

	if (randomNumber <= chance)
		return true;

	return false;
}

float getVector2Length(sf::Vector2f v) {
	return std::sqrtf(std::powf(v.x, 2) + std::powf(v.y, 2));
}

sf::Vector2f normalizeVector2(sf::Vector2f v)
{
	double length = std::sqrt(std::pow(v.x, 2) + std::pow(v.y, 2));

	if (length == 0.0f)
		return sf::Vector2f(0.0f, 0.0f);

	return sf::Vector2f(v.x / (float)length, v.y / (float)length);
}