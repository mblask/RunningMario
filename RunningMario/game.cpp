#include "game.h"

void runGame() {
	sf::RenderWindow window(sf::VideoMode(800, 600), "Running Mario");
	window.setFramerateLimit(60);

	GameManager* gameManager = GameManager::GetInstance();

	sf::Color backgroundColor = sf::Color(150.0f, 100.0f, 50.0f);
	sf::Vector3f colorChangeSigns = { 1.0f, 1.0f, 1.0f };

	while (window.isOpen()) {

		window.clear(backgroundColor);
		backgroundColor = colorFlow(backgroundColor, colorChangeSigns);

		sf::Event event;
		while (window.pollEvent(event)) {

			if (event.type == sf::Event::KeyPressed) {
				if (event.key.code == sf::Keyboard::Escape)
					window.close();
			}

			if (event.type == sf::Event::Closed)
				window.close();
		}

		window.setActive();

		window.display();
	}
}

sf::Color colorFlow(const sf::Color color, sf::Vector3f& colorChangeSigns) {
	sf::Vector3f colorChange = { 100.0f, 80.0f, 60.0f };
	sf::Color newColor = color;

	newColor.r += (uint8_t)(colorChangeSigns.x * colorChange.x * 0.01f);
	if (newColor.r <= 0.0f || newColor.r >= 255.0f)
		colorChangeSigns.x *= -1;
	newColor.g += (uint8_t)(colorChangeSigns.y * colorChange.y * 0.01f);
	if (newColor.g <= 0.0f || newColor.g >= 255.0f)
		colorChangeSigns.y *= -1;
	newColor.b += (uint8_t)(colorChangeSigns.z * colorChange.z * 0.01f);
	if (newColor.b <= 0.0f || newColor.b >= 255.0f)
		colorChangeSigns.z *= -1;

	return newColor;
}