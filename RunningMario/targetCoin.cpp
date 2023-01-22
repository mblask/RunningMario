#include "targetCoin.h"

void TargetCoin::Setup() {
	_targetCoinTexture.loadFromFile("..\\media\\coinGold.png");
	_targetPointSprite.setTexture(_targetCoinTexture);

	_spriteSheetOrigin = { 0, 0 };
	_spriteDimensions = { 80, 80 };
	_spriteOrigin = { 24, 24 };
	_spriteAnchor = { 0.5f, 0.5f };
	_spriteScale = { 0.7f, 0.7f };

	_previousObjectSprite = { 0, 0 };
	_currentObjectSprite = { 0, 0 };

	_targetPointSprite.setOrigin(_spriteDimensions.x * _spriteAnchor.x, _spriteDimensions.y * _spriteAnchor.y);
	_targetPointSprite.setTextureRect({ _spriteOrigin.x, _spriteOrigin.y, _spriteDimensions.x, _spriteDimensions.y });

	_targetPointSprite.setPosition(GetRandomPosition((sf::Vector2i)_window->getSize()));
	_targetPointSprite.setScale({ _spriteScale.x, _spriteScale.y });
}

void TargetCoin::SetWindow(sf::RenderWindow* window) {
	_window = window;
}

void TargetCoin::SetPosition(sf::Vector2f newPosition) {
	_targetPointSprite.setPosition(newPosition);
}

void TargetCoin::SetRandomPosition() {
	_targetPointSprite.setPosition(GetRandomPosition((sf::Vector2i)_window->getSize()));
}

sf::Sprite TargetCoin::GetSprite() {
	return _targetPointSprite;
}