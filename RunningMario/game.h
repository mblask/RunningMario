#pragma once
#include <iostream>

#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>

#include "gameManager.h"
#include "marioObject.h"
#include "targetCoin.h"
#include "projectileObject.h"

void runGame();
sf::Color colorFlow(const sf::Color color, sf::Vector3f& colorChangeSigns);
void activateProjectiles(ProjectileObject projectiles[], int totalNumberOfProjectiles);