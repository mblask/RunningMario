#include "game.h"

void runGame() {
	sf::RenderWindow window(sf::VideoMode(800, 600), "Running Mario");
	window.setFramerateLimit(120);

	GameManager* gameManager = GameManager::GetInstance();

	TargetCoin targetPoint;
	targetPoint.SetWindow(&window);
	targetPoint.Setup();

	MarioObject* marioObject = MarioObject::GetInstance();
	marioObject->SetWindow(&window);
	marioObject->GrabTargetPoint(&targetPoint);
	
	const int numberOfProjectiles = 10;
	ProjectileObject projectiles[numberOfProjectiles];
	for (int i = 0; i < numberOfProjectiles; i++)
	{
		projectiles[i].SetWindow(&window);
		projectiles[i].Setup();

		if (i < 2)
			projectiles[i].ActivateProjectile(true);

		//gameManager->AddProjectile(&projectiles[i]);
	}

	sf::Color backgroundColor = sf::Color((sf::Uint8)150.0f, (sf::Uint8)100.0f, (sf::Uint8)50.0f);
	sf::Vector3f colorChangeSigns = { 1.0f, 1.0f, 1.0f };

	TextObject scoreText1(&window, "Score: 0");
	scoreText1.SetPosition({ 0.85f, 0.05f });

	while (window.isOpen()) {

		window.clear(backgroundColor);

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

		//OBJECT UPDATES
		backgroundColor = colorFlow(backgroundColor, colorChangeSigns);
		
		gameManager->Update();
		marioObject->Update();
		for (int i = 0; i < numberOfProjectiles; i++)
			projectiles[i].Update();

		//TEXT UPDATES
		scoreText1.SetText("Score: " + std::to_string(gameManager->GetScore()));

		//OBJECT DRAWING
		window.draw(targetPoint.GetSprite());
		window.draw(marioObject->GetSprite());
		for (int i = 0; i < numberOfProjectiles; i++)
			window.draw(projectiles[i].GetSprite());

		//TEXT DRAWING
		window.draw(scoreText1.GetText());

		window.display();
	}
}

sf::Color colorFlow(const sf::Color color, sf::Vector3f& colorChangeSigns) {
	sf::Vector3f colorChange = { 1.0f, 0.8f, 1.2f };
	sf::Color newColor = color;

	newColor.r += (uint8_t)(colorChangeSigns.x * colorChange.x);
	if (newColor.r <= 0.0f || newColor.r >= 255.0f)
		colorChangeSigns.x *= -1;
	newColor.g += (uint8_t)(colorChangeSigns.y * colorChange.y);
	if (newColor.g <= 0.0f || newColor.g >= 255.0f)
		colorChangeSigns.y *= -1;
	newColor.b += (uint8_t)(colorChangeSigns.z * colorChange.z);
	if (newColor.b <= 0.0f || newColor.b >= 255.0f)
		colorChangeSigns.z *= -1;

	return newColor;
}