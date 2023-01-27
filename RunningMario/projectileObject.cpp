#include "projectileObject.h"

void ProjectileObject::Setup() {
	_objectTexture.loadFromFile("D:\\C++\\Materials\\projectiles_0.png");
	_objectSprite.setTexture(_objectTexture);

	_spriteSheetOrigin = { 0, 0 };
	_spriteDimensions = { 80, 80 };
	_spriteAnchor = { 0.5f, 0.5f };

	_previousObjectSprite = { 0, 0 };
	_currentObjectSprite = { 0, 0 };

	_objectSprite.setOrigin(_spriteDimensions.x * _spriteAnchor.x, _spriteDimensions.y * _spriteAnchor.y);
	_objectSprite.setTextureRect({
		_spriteOrigin.x + _spriteDimensions.x * _currentObjectSprite.x,
		_spriteOrigin.y + _spriteDimensions.y * _currentObjectSprite.y,
		_spriteDimensions.x,
		_spriteDimensions.y
		});

	_objectSprite.setPosition(GetRandomBoundaryPosition((sf::Vector2i)_window->getSize(), {-1.0f * _spriteDimensions.x, -1.0f * _spriteDimensions.y}));

	_isActive = false;
	_initialPosition = _objectSprite.getPosition();

	_baseSpeed = 200.0f;
	_projectileDirection = GetRandomDirection();

	_gameManager = GameManager::GetInstance();
	_marioObject = MarioObject::GetInstance();
}

void ProjectileObject::Update() {
	if (!_isActive)
		return;

	move();
	checkMario();
}

void ProjectileObject::SetCurrentSprite(sf::Vector2i currentSprite) {
	_currentObjectSprite = currentSprite;
}

void ProjectileObject::SetWindow(sf::RenderWindow* window) {
	_window = window;
}

void ProjectileObject::SetPosition(sf::Vector2f position) {
	_objectSprite.setPosition(position);
}

void ProjectileObject::ResetPosition() {
	_objectSprite.setPosition(_initialPosition);
}

sf::Sprite ProjectileObject::GetSprite() {
	return _objectSprite;
}

void ProjectileObject::ActivateProjectile(bool value) {
	_isActive = value;
}

bool ProjectileObject::IsActive() {
	return _isActive;
}

void ProjectileObject::IncreaseSpeedByPercentage(float percentage) {
	_speedBonus *= (1.0f + percentage / 100.0f);
}

void ProjectileObject::ResetSpeed() {
	_speedBonus = 1.0f;
}

void ProjectileObject::move() {
	if (_projectileDirection == sf::Vector2f(0, 0))
	{
		sf::Vector2f direction = sf::Vector2f(0.0f, 0.0f) - _objectSprite.getPosition();
		_projectileDirection = normalizeVector2(direction);
	}

	if (_baseSpeed == 0) {
		std::cout << "No projectile speed set!" << std::endl;
		return;
	}

	float speed = _baseSpeed * _speedBonus;
	sf::Vector2f objectPosition = _objectSprite.getPosition();
	objectPosition += speed * _projectileDirection * _gameManager->GetTimeDelta();

	if (objectPosition.x < -(float)_window->getSize().x * 0.1f || objectPosition.y < -(float)_window->getSize().y * 0.1f ||
		objectPosition.x > +(float)_window->getSize().x * 1.1f || objectPosition.y > +(float)_window->getSize().y * 1.1f) {
		_objectSprite.setPosition(GetRandomBoundaryPosition((sf::Vector2i)_window->getSize(), { 0.0f, 0.0f }));

		sf::Vector2f direction = _marioObject->GetSprite().getPosition() - _objectSprite.getPosition();
		_projectileDirection = normalizeVector2(direction);

		return;
	}

	_objectSprite.setPosition(objectPosition);
}

void ProjectileObject::checkMario() {
	float reachDistance = 30.0f;
	float distance = getVector2Length(_objectSprite.getPosition() - _marioObject->GetSprite().getPosition());
	if (distance > reachDistance)
		return;

	_gameManager->AddHighscore();
	_gameManager->ResetScore();
	_gameManager->ResetTimePassed();
	_marioObject->ResetPosition();

	SetPosition(GetRandomBoundaryPosition((sf::Vector2i)_window->getSize(), {0.0f, 0.0f}));
	sf::Vector2f direction = _marioObject->GetSprite().getPosition() - _objectSprite.getPosition();
	_projectileDirection = normalizeVector2(direction);
}