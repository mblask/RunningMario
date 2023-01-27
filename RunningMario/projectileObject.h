#pragma once

#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>

#include <iostream>
#include "helperFunctions.h"
#include "gameManager.h"
#include "marioObject.h"

class GameManager;
class MarioObject;

class ProjectileObject {
public:
    void Setup();
    void Update();

    void SetCurrentSprite(sf::Vector2i currentSpritePosition);
    void SetWindow(sf::RenderWindow* window);
    void SetPosition(sf::Vector2f position);
    sf::Sprite GetSprite();

    void ActivateProjectile(bool value);
    bool IsActive();
    void ResetPosition();
    void IncreaseSpeedByPercentage(float percentage);
    void ResetSpeed();

private:
    sf::Texture _objectTexture;
    sf::Sprite _objectSprite;

    sf::Vector2i _spriteSheetOrigin;
    sf::Vector2i _spriteDimensions;
    sf::Vector2i _spriteOrigin;
    sf::Vector2f _spriteAnchor;

    sf::Vector2i _previousObjectSprite;
    sf::Vector2i _currentObjectSprite;

    sf::RenderWindow* _window;

    bool _isActive;

    sf::Vector2f _initialPosition;
    float _baseSpeed = 0.0f;
    float _speedBonus = 1.0f;
    sf::Vector2f _projectileDirection;

    GameManager* _gameManager = NULL;
    MarioObject* _marioObject = NULL;

    void move();
    void checkMario();
};