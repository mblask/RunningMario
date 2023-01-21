#include "gameManager.h"

GameManager* GameManager::_instance = NULL;

GameManager* GameManager::GetInstance() {
	if (_instance == NULL) {
		_instance = new GameManager();
	}

	return _instance;
}

GameManager::GameManager() {
	std::cout << "GameManager initialized!" << std::endl;
}

float GameManager::GetTimeDelta() {
	return 0.1f;
}