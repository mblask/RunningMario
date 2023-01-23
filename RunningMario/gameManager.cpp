#include "gameManager.h"

GameManager* GameManager::_instance = NULL;

GameManager* GameManager::GetInstance() {
	if (_instance == NULL) {
		_instance = new GameManager();
	}

	return _instance;
}

GameManager::GameManager() {
	_fpsTimer = 0.0f;
	_timePassed = 0.0f;
	_timeDelta = 0.0f;
	_score = 0;
	_numberOfHighscores = 10;
	_highscoresTextObject = NULL;

	std::cout << "GameManager initialized!" << std::endl;
}

void GameManager::Update() {
	_timeDelta = _clock.getElapsedTime().asSeconds();
	_timePassed += _timeDelta;
	_fpsTimer += _timeDelta;

	_clock.restart();

	float printFPSAfter = 5.0f;
	if (_fpsTimer > printFPSAfter) {
		std::cout << 1 / _timeDelta << std::endl;
		_fpsTimer = 0.0f;
	}
}

float GameManager::GetTimeDelta() {
	return _timeDelta;
}

float GameManager::GetPassedTime() {
	return _timePassed;
}

void GameManager::ResetTimePassed() {
	_timePassed = 0.0f;
}

void GameManager::UpdateScore(int increment) {
	_score += increment;
}

int GameManager::GetScore() {
	return _score;
}

void GameManager::ResetScore() {
	_score = 0;
}

void GameManager::AddHighscore() {
	float newHighscore = _timePassed * _score;

	if (newHighscore == 0.0f)
		return;

	_highscores.push_back(newHighscore);

	if (_highscores.size() > 1)
		std::sort(_highscores.begin(), _highscores.end(), std::greater<float>());

	if (_highscores.size() > _numberOfHighscores)
		_highscores.resize(_numberOfHighscores);

	ShowHighscores();
}

void GameManager::SetHighscoresTextObject(TextObject* textObject) {
	_highscoresTextObject = textObject;
}

void GameManager::ShowHighscores() {
	_highscoresTextObject->ClearText();

	std::string newTextString;
	for (int i = 0; i < _highscores.size(); i++)
	{
		newTextString.append(std::to_string((int)_highscores[i]));
		if (i != _highscores.size() - 1)
			newTextString.append("\n");
	}

	_highscoresTextObject->SetText(newTextString);
}