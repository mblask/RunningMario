#pragma once
#include <iostream>

#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>

#include "gameManager.h"

void runGame();
sf::Color colorFlow(const sf::Color color, sf::Vector3f& colorChangeSigns);