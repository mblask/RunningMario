#include "marioObject.h"

MarioObject* MarioObject::_instance = NULL;

MarioObject* MarioObject::GetInstance() {
	if (_instance == NULL)
	{
		_instance = new MarioObject();
	}

	return _instance;
}

MarioObject::MarioObject() {

	_spriteRowColumnDifference = 0;
	_directionVector = { 0.0f, 0.0f };
	_movementSpeed = 300.0f;
	_speedMultiplier = 1.0f;
	_objectIsRotating = false;
	_objectRotationSpeed = 500.0f;
	_objectTotalRotation = 0.0f;
	_rotationSign = 1.0f;
	_window = NULL;

	_objectTexture.loadFromFile("..\\media\\mario.png");
	_objectSprite.setTexture(_objectTexture);

	_spriteSheetOrigin = { 5, 76 };
	_spriteRowColumnDifference = 40;
	_spriteDimensions = { 22, 28 };
	_spriteAnchor = { 0.5f, 0.5f };

	_previousObjectSprite = { 0, 0 };
	_currentObjectSprite = { 0, 0 };

	_objectSprite.setOrigin(_spriteDimensions.x * _spriteAnchor.x, _spriteDimensions.y * _spriteAnchor.y);
	_objectSprite.setPosition(100, 100);
	_objectSprite.setScale(2, 2);

	updateSpriteRenderer();

	std::cout << "MarioObject initialized!" << std::endl;
}

void MarioObject::Update() {
	playerInput();
	move(_directionVector);
	rotateObjectNTimes(1);
	animator();
	updateSpriteRenderer();
	checkTargetPoint();
}

sf::Sprite MarioObject::GetSprite() {
	return _objectSprite;
}

void MarioObject::SetWindow(sf::RenderWindow* window) {
	_window = window;
}

void MarioObject::GrabTargetPoint(TargetCoin* targetPoint) {
	_targetPoint = targetPoint;
}

void MarioObject::ResetPosition() {
	_objectSprite.setPosition(_window->getSize().x / 2.0f, _window->getSize().y / 2.0f);
}

void MarioObject::checkTargetPoint() {
	float reachPosition = 30.0f;
	float distance = getVector2Length(_objectSprite.getPosition() - _targetPoint->GetSprite().getPosition());

	if (distance < 30.0f)
	{
		_targetPoint->SetRandomPosition();
		GameManager::GetInstance()->UpdateScore();
	}
}

void MarioObject::playerInput() {

	_directionVector = { 0.0f, 0.0f };

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
		_directionVector += { 0.0f, -1.0f };
	}
	else
		_directionVector -= { 0.0f, -1.0f };

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
		_directionVector += { 0.0f, +1.0f };
	}
	else
		_directionVector -= { 0.0f, +1.0f };

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
		_directionVector += { +1.0f, 0.0f };
	}
	else
		_directionVector -= { +1.0f, 0.0f };

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
		_directionVector += { -1.0f, 0.0f };
	}
	else
		_directionVector -= { -1.0f, 0.0f };

	_directionVector = normalizeVector2(_directionVector);

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::LShift))
		_speedMultiplier = 1.4f;
	else
		_speedMultiplier = 1.0f;

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::R)) {
		if (_objectIsRotating)
			return;

		_objectIsRotating = true;
	}
}

void MarioObject::animator() {

}

void MarioObject::animateRunning() {

}

void MarioObject::animateRotation() {

}

void MarioObject::move(sf::Vector2f direction) {

	if (_directionVector == sf::Vector2f(0.0f, 0.0f))
		return;

	sf::Vector2f position = _objectSprite.getPosition();
	position += _directionVector * _movementSpeed * _speedMultiplier * GameManager::GetInstance()->GetTimeDelta();

	if (positionValid(position))
		_objectSprite.setPosition(position);
}

bool MarioObject::positionValid(sf::Vector2f position, sf::Vector2f margins) {

	if (_window == NULL) {
		std::cout << "Window not set!" << std::endl;
		return false;
	}

	if (_window->getSize().x == 0 && _window->getSize().y == 0)
		return true;

	if (position.x > 0.0f + margins.x &&
		position.x < _window->getSize().x - margins.x &&
		position.y > 0.0f + margins.y &&
		position.y < _window->getSize().y - margins.y)
		return true;

	return false;
}

void MarioObject::updateSpriteRenderer() {
	_objectSprite.setTextureRect({
		_spriteSheetOrigin.x + _spriteRowColumnDifference * _currentObjectSprite.x,
		_spriteSheetOrigin.y + _spriteRowColumnDifference * _currentObjectSprite.y,
		_spriteDimensions.x,
		_spriteDimensions.y
		});
}

void MarioObject::rotateObjectNTimes(int times) {
	if (!_objectIsRotating)
		return;

	float rotationAngle = _objectSprite.getRotation();
	rotationAngle += _objectRotationSpeed * GameManager::GetInstance()->GetTimeDelta();
	_objectTotalRotation += _objectRotationSpeed * GameManager::GetInstance()->GetTimeDelta();

	float fullRotation = times * 360.0f;
	if (_objectTotalRotation < fullRotation)
		_objectSprite.setRotation(rotationAngle);
	else {
		_objectSprite.setRotation(0.0f);
		_objectTotalRotation = 0.0f;
		_objectIsRotating = false;
		_currentObjectSprite = _previousObjectSprite;
	}
}