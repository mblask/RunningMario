#pragma once

#include <iostream>

#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>

#include "textObject.h"

class GameManager
{
private:
	static GameManager* _instance;
	GameManager();
	GameManager(const GameManager& obj) = delete;

public:
	static GameManager* GetInstance();

private:
	sf::Clock _clock;
	float _fpsTimer;
	float _timePassed;
	float _timeDelta;

public:
	void Update();
	float GetPassedTime();
	float GetTimeDelta();
	void ResetTimePassed();

private:
	int _score;
	int _numberOfHighscores;
	std::vector<float> _highscores;
	TextObject* _highscoresTextObject;

public:
	void UpdateScore(int increment = 1);
	int GetScore();
	void ResetScore();
	void AddHighscore();
	void SetHighscoresTextObject(TextObject* textObject);
	void ShowHighscores();
};