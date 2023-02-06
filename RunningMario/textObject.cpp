#include "textObject.h"

TextObject::TextObject(sf::RenderWindow* window, std::string text) {
	_window = window;
	_font.loadFromFile("D:\\C++\\Materials\\DrawingKids.ttf");
	_text.setFont(_font);
	_text.setString(text);
	_text.setOutlineThickness(1.0f);
	_text.setCharacterSize((unsigned int)20.0f);
	_textOrigin = { 0.5f, 0.5f };
}

void TextObject::SetText(std::string text) {
	_text.setString(text);
}

void TextObject::SetPosition(sf::Vector2f position) {
	_text.setPosition({
		_window->getSize().x* position.x - _text.getLocalBounds().width * _textOrigin.x,
		_window->getSize().y * position.y - _text.getLocalBounds().height * _textOrigin.y
		});
}

void TextObject::SetOrigin(sf::Vector2f origin) {
	_textOrigin = origin;
}

void TextObject::SetCharacterSize(unsigned int size) {
	_text.setCharacterSize(size);
}

sf::Text TextObject::GetText() {
	return _text;
}

void TextObject::ClearText() {
	_text.setString("");
}

void TextObject::Draw() {
	_window->draw(_text);
}