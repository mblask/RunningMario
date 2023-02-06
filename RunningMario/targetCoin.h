#pragma once

#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>

#include <iostream>
#include "helperFunctions.h"

class TargetCoin {
public:
    void Setup();
    void SetWindow(sf::RenderWindow* window);
    void SetPosition(sf::Vector2f newPosition);
    void SetRandomPosition();

    sf::Sprite GetSprite();
    void Draw();

private:
    sf::Texture _targetCoinTexture;
    sf::Sprite _targetPointSprite;

    sf::Vector2i _spriteSheetOrigin;
    sf::Vector2i _spriteDimensions;
    sf::Vector2i _spriteOrigin;
    sf::Vector2f _spriteAnchor;
    sf::Vector2f _spriteScale;

    sf::Vector2i _previousObjectSprite;
    sf::Vector2i _currentObjectSprite;

    sf::RenderWindow* _window;
};