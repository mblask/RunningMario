#pragma once

#include <iostream>

#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>

class GameManager
{
private:
	static GameManager* _instance;
	GameManager();
	GameManager(const GameManager& obj) = delete;

public:
	static GameManager* GetInstance();

	float GetTimeDelta();
};