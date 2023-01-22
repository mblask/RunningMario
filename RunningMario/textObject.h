#pragma once

#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>

#include <iostream>

class TextObject {
public:
	TextObject(sf::RenderWindow* window, std::string text);
	void SetText(std::string text);
	void SetPosition(sf::Vector2f position);
	void SetOrigin(sf::Vector2f origin);
	void SetCharacterSize(unsigned int size);
	sf::Text GetText();
	void ClearText();

private:
	sf::Font _font;
	sf::Text _text;
	sf::RenderWindow* _window;
	sf::Vector2f _textOrigin;
};