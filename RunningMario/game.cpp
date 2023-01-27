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
	
		if (i < 1)
			projectiles[i].ActivateProjectile(true);
	}
	gameManager->SetProjectiles(projectiles, numberOfProjectiles);

	sf::Color backgroundColor = sf::Color((sf::Uint8)150.0f, (sf::Uint8)100.0f, (sf::Uint8)50.0f);
	sf::Vector3f colorChangeSigns = { 1.0f, 1.0f, 1.0f };

	TextObject timeText(&window, "Time: 0s");
	timeText.SetPosition({ 0.5f, 0.05f });

	TextObject scoreText(&window, "Score: 0");
	scoreText.SetPosition({ 0.85f, 0.05f });

	TextObject exitText(&window, "To exit,\nhit 'Esc'!");
	exitText.SetPosition({ 0.92f, 0.92f });
	exitText.SetCharacterSize(14);

	TextObject highscoresTextTitle(&window, "Highscores:");
	highscoresTextTitle.SetPosition({ 0.94f, 0.3f });
	highscoresTextTitle.SetCharacterSize(16);
	TextObject highscoresText(&window, "");
	highscoresText.SetPosition({ 0.95f, 0.33f });
	highscoresText.SetCharacterSize(14);

	gameManager->SetHighscoresTextObject(&highscoresText);

	bool testBool = false;
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
		timeText.SetText("Time: " + std::to_string((int)(gameManager->GetPassedTime())) + "s");
		scoreText.SetText("Score: " + std::to_string(gameManager->GetScore()));

		//OBJECT DRAWING
		window.draw(targetPoint.GetSprite());
		window.draw(marioObject->GetSprite());
		for (int i = 0; i < numberOfProjectiles; i++)
			window.draw(projectiles[i].GetSprite());

		//TEXT DRAWING
		window.draw(timeText.GetText());
		window.draw(scoreText.GetText());
		window.draw(exitText.GetText());
		window.draw(highscoresTextTitle.GetText());
		window.draw(highscoresText.GetText());

		window.display();
	}
}

void activateProjectiles(ProjectileObject projectiles[], int totalNumberOfProjectiles) {
	int numberOfProjectilesToActivate = 2;
	int count = 0;
	for (int i = 0; i < totalNumberOfProjectiles; i++)
	{
		if (projectiles[i].IsActive())
			continue;

		count++;
		if (count > numberOfProjectilesToActivate)
			break;

		projectiles[i].ActivateProjectile(true);
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