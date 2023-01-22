#pragma once

#include <iostream>

#include "SFML/Window.hpp"
#include "SFML/Graphics.hpp"

#include "helperFunctions.h"
#include "gameManager.h"
#include "targetCoin.h"

class MarioObject
{
private:
	static MarioObject* _instance;
	MarioObject();
	MarioObject(const MarioObject& object) = delete;

public:
	static MarioObject* GetInstance();
    void Update();

private:
    sf::Texture _objectTexture;
    sf::Sprite _objectSprite;

    sf::Vector2i _spriteSheetOrigin;
    int _spriteRowColumnDifference;
    sf::Vector2i _spriteDimensions;
    sf::Vector2f _spriteAnchor;

    sf::Vector2i _previousObjectSprite;
    sf::Vector2i _currentObjectSprite;

public:
    sf::Sprite GetSprite();

private:
    sf::RenderWindow* _window;

public:
    void SetWindow(sf::RenderWindow* window);


private:
    TargetCoin* _targetPoint = NULL;
    void checkTargetPoint();

public:
    void GrabTargetPoint(TargetCoin* targetPoint);


private:
    sf::Vector2f _directionVector;
    float _movementSpeed;
    float _speedMultiplier;
    bool _objectIsRotating;
    float _rotationSign;
    float _objectRotationSpeed;
    float _objectTotalRotation;

    void playerInput();

    void animator();

    void animateRunning();

    void animateRotation();

    void move(sf::Vector2f direction);

    bool positionValid(sf::Vector2f position, sf::Vector2f margins = sf::Vector2f(0.0f, 0.0f));

    void updateSpriteRenderer();

    void rotateObjectNTimes(int times);

public:
    void ResetPosition();
};