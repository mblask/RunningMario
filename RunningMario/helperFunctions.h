#pragma once

#include <iostream>

#include "SFML/Window.hpp"
#include "SFML/Graphics.hpp"

float FindMaxFromVectorFloat(std::vector<float> vector);

sf::Vector2f GetRandomDirection();

sf::Vector2f GetRandomDirectionBetweenAngles(sf::Vector2i angles);

sf::Vector2f GetRandomPosition(sf::Vector2i windowSize);

sf::Vector2f GetRandomBoundaryPosition(sf::Vector2i windowSize, sf::Vector2f margin = sf::Vector2f(0.0f, 0.0f));

bool chanceFunction(int chance);

float getVector2Length(sf::Vector2f v);

sf::Vector2f normalizeVector2(sf::Vector2f v);